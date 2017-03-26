#pragma once

#include <vector>
#include <map>
#include <memory>

#include "block.h"
#include "resource.h"
#include "source.h"
#include "sink.h"

class flow
{
public:
    flow();

    flow& add(std::shared_ptr<block> b);

private:
    friend class engine;

    engine_time shed();

    std::vector<std::shared_ptr<block>> chain;
    std::map<block::id_t, block::id_t> next_block_map;
    std::map<block::id_t, std::shared_ptr<block>> blocks;
};
