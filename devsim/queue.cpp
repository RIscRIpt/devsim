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
    return NEVER;
}

bool queue::can_put() const {
    return capacity == INFINITE || container.size() < capacity;
}

bool queue::can_get() const {
    return container.size() > 0;
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
