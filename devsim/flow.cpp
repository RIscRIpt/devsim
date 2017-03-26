#include <algorithm>
#include <memory>

using namespace std;

#include "flow.h"

flow::flow()
{
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
            auto &&e = curr_block->get();
            if(e == nullptr)
                break;
            if(!next_block->put(e))
                throw 1;
        }
        if(next_possible_shed > curr_block->next_available_time())
            next_possible_shed = curr_block->next_available_time();
    }
    return next_possible_shed;
}

flow& flow::add(shared_ptr<block> b) {
    if(chain.size() > 0) {
        next_block_map[chain.back()->id] = b->id;
    }
    chain.push_back(b);
    blocks[b->id] = b;
    return *this;
}
