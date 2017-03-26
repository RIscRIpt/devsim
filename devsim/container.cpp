#include <memory>

using namespace std;

#include "container.h"

container::container(::engine &engine, wstring name) :
    block(engine, block_type::container, name)
{
}

container& container::add(shared_ptr<block> b) {
    blocks.push_back(b);
    return *this;
}

engine_time container::next_available_time() const {
    engine_time min_time = NEVER;
    for(auto &&b : blocks) {
        if(min_time > b->next_available_time())
            min_time = b->next_available_time();
    }
    return min_time;
}

bool container::can_put() const {
    for(auto &&b : blocks) {
        if(b->can_put())
            return true;
    }
    return false;
}

bool container::can_get() const {
    for(auto &&b : blocks) {
        if(b->can_get())
            return true;
    }
    return false;
}

bool container::put(shared_ptr<entity> e) {
    for(auto &&b : blocks) {
        if(b->put(e))
            return true;
    }
    return false;
}

shared_ptr<entity> container::get() {
    for(auto &&b : blocks) {
        auto &&e = b->get();
        if(e != nullptr)
            return e;
    }
    return nullptr;
}
