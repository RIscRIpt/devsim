#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "devsim.h"

class engine
{
public:
    typedef std::function<bool(const engine&)> fn_stop_condition_t;
    typedef std::function<void(const engine&, const event&)> fn_event_callback_t;

    engine();
    ~engine();

    engine_time get_time() const { return time; }

    void run();

    engine& add(std::shared_ptr<flow> f);

    void set_stop_condition(fn_stop_condition_t fn);
    void set_event_listener(fn_event_callback_t fn);

private:
    void flow_event(const event &ev);

    engine_time time;

    fn_stop_condition_t fn_stop_condition;
    fn_event_callback_t fn_event_callback;

    std::vector<std::shared_ptr<flow>> flows;
};
