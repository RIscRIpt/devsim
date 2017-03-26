#include <algorithm>
#include <memory>

using namespace std;

#include "flow.h"
#include "engine.h"

flow::flow(::engine &engine) :
    engine(engine)
{
}

flow& flow::add(shared_ptr<block> b) {
    if(chain.size() > 0) {
        next_block_map[chain.back()->id] = b->id;
    }
    chain.push_back(b);
    blocks[b->id] = b;
    return *this;
}

engine_time flow::shed() {
    engine_time next_possible_shed;
    vector<shared_ptr<event>> events;
    bool repeat;
    do {
        repeat = false;
        next_possible_shed = NEVER;
        for(auto i = chain.begin(); i != chain.end(); ++i) {
            auto &&curr_block = *i;
            if(curr_block->type == block_type::sink)
                continue;
            auto next_block_id = next_block_map[curr_block->id];
            auto &&next_block = blocks[next_block_id];
            bool could_put = curr_block->can_put();
            while(true) {
                if(!next_block->can_put())
                    break;
                auto &&ent = curr_block->get();
                if(ent == nullptr)
                    break;
                if(!next_block->put(ent))
                    throw 1;

                if(curr_block->type == block_type::container) {
                    auto source_block = static_pointer_cast<source>(curr_block);
                    events.push_back(make_shared<event_spawn_entity>(source_block, ent));
                }
            }
            if(!could_put && curr_block->can_put()) {
                repeat = true;
            }
            if(repeat)
                continue;
            engine_time next_available_time = curr_block->next_available_time();
            if(next_possible_shed > next_available_time) {
                if(next_available_time > engine.get_time() || (curr_block->can_get() && next_block->can_put()))
                    next_possible_shed = next_available_time;
            }
        }
        if(next_possible_shed == ALWAYS)
            next_possible_shed = engine.get_time();
    } while(repeat);
    if(fn_event_callback != nullptr) {
        for(auto &&ev : events)
            fn_event_callback(*ev);
    }
    return next_possible_shed;
}

void flow::set_event_listener(fn_event_callback_t fn) {
    fn_event_callback = fn;
}
