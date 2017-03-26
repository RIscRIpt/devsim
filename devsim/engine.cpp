#include <memory>
#include <functional>

using namespace std;

#include "engine.h"
#include "flow.h"

engine::engine() :
    time(0)
{
}

engine::~engine() {
}

void engine::run() {
    time = 0;
    if(fn_event_callback != nullptr)
        fn_event_callback(*this, *make_shared<event_begin>());
    while(true) {
        if(fn_stop_condition != nullptr) {
            if(fn_stop_condition(*this))
                break;
        }
        engine_time next_possible_shed = NEVER;
        for(auto &&f : flows) {
            engine_time next_shed = f->shed();
            if(next_possible_shed > next_shed)
                next_possible_shed = next_shed;
            if(next_possible_shed == ALWAYS)
                next_possible_shed = get_time();
            time = next_possible_shed;
        }
    }
}

engine& engine::add(shared_ptr<flow> f) {
    flows.push_back(f);
    f->set_event_listener(bind(&engine::flow_event, this, placeholders::_1));
    return *this;
}

void engine::set_stop_condition(fn_stop_condition_t fn) {
    fn_stop_condition = fn;
}

void engine::set_event_listener(fn_event_callback_t fn) {
    fn_event_callback = fn;
}

void engine::flow_event(const event &ev) {
    if(fn_event_callback == nullptr)
        return;
    fn_event_callback(*this, ev);
}
