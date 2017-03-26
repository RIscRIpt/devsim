#include <algorithm>
#include <memory>

using namespace std;

#include "flow.h"

flow::flow()
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
    engine_time next_possible_shed = NEVER;
    for(auto i = chain.rbegin(); i != chain.rend(); ++i) {
        auto &&curr_block = *i;
        if(curr_block->type == block_type::sink)
            continue;
        auto next_block_id = next_block_map[curr_block->id];
        auto &&next_block = blocks[next_block_id];
        while(true) {
            if(!next_block->can_put())
                break;
            auto &&ent = curr_block->get();
            if(ent == nullptr)
                break;
            if(!next_block->put(ent))
                throw 1;
            on_entity_moved(next_block, curr_block, ent);
        }
        if(next_possible_shed > curr_block->next_available_time())
            next_possible_shed = curr_block->next_available_time();
    }
    return next_possible_shed;
}

void flow::set_event_listener(fn_event_callback_t fn) {
    fn_event_callback = fn;
}

void flow::on_entity_moved(shared_ptr<block> dest, shared_ptr<block> src, shared_ptr<entity> ent) {
    if(fn_event_callback == nullptr)
        return;

    //XXX: ugly hack for reporting event for current example
    if(src->type == block_type::container) {
        auto source_block = static_pointer_cast<source>(src);
        fn_event_callback(
            *make_shared<event_spawn_entity>(source_block, ent)
        );
    }
}
