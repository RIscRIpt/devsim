#include <functional>

using namespace std;

#include "engine.h"

engine::engine() :
    time(0)
{
}

engine::~engine() {
}

void engine::run() {
}

engine& engine::add(flow &f) {
    return *this;
}

void engine::set_stop_condition(fn_stop_condition_t fn) {
    fn_stop_condition = fn;
}

void engine::set_event_listener(fn_event_callback_t fn) {
    fn_event_callback = fn;
}
