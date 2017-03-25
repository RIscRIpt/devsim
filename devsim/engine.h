#pragma once

#include "flow.h"
#include "event.h"

#include <functional>

class engine
{
public:
    typedef std::function<bool(const engine&)> fn_stop_condition_t;
    typedef std::function<void(const engine&, const event&)> fn_event_callback_t;

    engine();
    ~engine();

    double get_time() const { return time; }

    void run();

    engine& add(flow &f);

    void set_stop_condition(fn_stop_condition_t fn);
    void set_event_listener(fn_event_callback_t fn);

private:
    double time;

    fn_stop_condition_t fn_stop_condition;
    fn_event_callback_t fn_event_callback;
};
