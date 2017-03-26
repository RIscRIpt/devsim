#include <deque>

using namespace std;

#include "queue.h"

queue::queue(::engine &engine, wstring name, unsigned capacity, queue_kind kind) :
    resource(engine, resource_type::queue, capacity, name),
    kind(kind)
{
}

queue_kind queue::get_kind() const {
    return kind;
}

void queue::set_kind(queue_kind value) {
    kind = value;
}

engine_time queue::next_available_time() const {
    return can_get() ? ALWAYS : NEVER;
}

bool queue::can_put() const {
    return capacity == INFINITE || engaged() < capacity;
}

bool queue::can_get() const {
    return engaged() > 0;
}

bool queue::put(shared_ptr<entity> e) {
    if(!can_put())
        return false;
    container.push_back(e);
    return true;
}

shared_ptr<entity> queue::get() {
    if(!can_get())
        return nullptr;

    shared_ptr<entity> e = nullptr;
    
    switch(kind) {
    case queue_kind::FIFO:
        e = container.front();
        container.pop_front();
        break;
    case queue_kind::LIFO:
        e = container.back();
        container.pop_back();
        break;
    }

    return e;
}

unsigned queue::engaged() const {
    return container.size();
}

unsigned queue::engaged(std::function<bool(entity&)> pred) const {
    unsigned count = 0;
    for(auto &&e : container) {
        count += pred(*e);
    }
    return count;
}

shared_ptr<entity> queue::peek() const {
    if(engaged() <= 0)
        return nullptr;
    return container.front();
}
