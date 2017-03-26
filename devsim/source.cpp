#include <string>
#include <memory>

using namespace std;

#include "source.h"

source::source(::engine &engine, rng::distribution_random &rng_source, wstring name) :
    block(engine, block_type::source, name),
    rng_source(rng_source)
{
    next_spawn_time = rng_source.next();
}

engine_time source::next_available_time() const {
    return next_spawn_time;
}

bool source::can_put() const {
    return false;
}

bool source::can_get() const {
    return this->engine.get_time() >= next_available_time();
}

bool source::put(shared_ptr<entity> e) {
    return false;
}

shared_ptr<entity> source::get() {
    if(!can_get())
        return nullptr;
    next_spawn_time += rng_source.next();
    return make_shared<entity>(id);
}
