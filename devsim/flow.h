#pragma once

#include <vector>
#include <map>
#include <memory>

#include "event.h"
#include "block.h"
#include "resource.h"
#include "source.h"
#include "sink.h"

class flow
{
public:
    typedef std::function<void(const event&)> fn_event_callback_t;

    flow();

    flow& add(std::shared_ptr<block> b);

private:
    friend class engine;

    engine_time shed();

    void set_event_listener(fn_event_callback_t fn);

    void on_entity_moved(std::shared_ptr<block> dest, std::shared_ptr<block> src, std::shared_ptr<entity> ent);

    fn_event_callback_t fn_event_callback;

    std::vector<std::shared_ptr<block>> chain;
    std::map<block::id_t, block::id_t> next_block_map;
    std::map<block::id_t, std::shared_ptr<block>> blocks;
};
