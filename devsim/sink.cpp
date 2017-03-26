#include <string>
#include <memory>

using namespace std;

#include "sink.h"

sink::sink(::engine &engine, wstring name) :
    block(engine, block_type::sink, name)
{
}

engine_time sink::next_available_time() const {
    return NEVER;
}

bool sink::can_put() const {
    return true;
}

bool sink::can_get() const {
    return false;
}

bool sink::put(shared_ptr<entity> e) {
    return true;
}

shared_ptr<entity> sink::get() {
    return nullptr;
}
