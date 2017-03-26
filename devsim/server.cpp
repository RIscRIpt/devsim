#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "source.h"
#include "server.h"

server::server(::engine &engine, wstring name, unsigned capacity, shared_ptr<rng::distribution_random> default_time_source) :
    resource(engine, resource_type::server, capacity, name),
    default_time_source(default_time_source)
{
}

void server::set_serve_distribution(source::id_t id, shared_ptr<rng::distribution_random> time_source) {
    source_time_source[id] = time_source;
}

engine_time server::next_available_time() const {
    if(engaged() <= 0)
        return NEVER;
    return serving_end_time.find(serving.front()->id)->second;
}

bool server::can_put() const {
    return engaged() < capacity;
}

bool server::can_get() const {
    return next_available_time() <= this->engine.get_time();
}

bool server::put(shared_ptr<entity> e) {
    if(!can_put())
        return false;
    auto time_source = get_time_source(e->source_id);
    serving_end_time[e->id] = this->engine.get_time() + time_source->next();
    serving.push_back(e);
    push_heap(serving.begin(), serving.end(), bind(&server::is_served_before, this, placeholders::_1, placeholders::_2));
    return true;
}

shared_ptr<entity> server::get() {
    if(!can_get())
        return nullptr;
    shared_ptr<entity> served = serving.front();
    serving_end_time.erase(served->id);
    pop_heap(serving.begin(), serving.end(), bind(&server::is_served_before, this, placeholders::_1, placeholders::_2));
    serving.pop_back();
    return served;
}

unsigned server::engaged() const {
    return serving.size();
}

shared_ptr<entity> server::peek() const {
    if(engaged() <= 0)
        return nullptr;
    return serving.front();
}

bool server::is_served_before(shared_ptr<entity> e1, shared_ptr<entity> e2) {
    return serving_end_time[e1->id] < serving_end_time[e2->id];
}

shared_ptr<rng::distribution_random> server::get_time_source(source::id_t source_id) {
    auto time_source = source_time_source.find(source_id);
    if(time_source != source_time_source.end())
        return time_source->second;
    return default_time_source;
}
