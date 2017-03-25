#pragma once

#include "block.h"
#include "distribution_random.h"

class source :
    public block
{
public:
    source(std::wstring name, rng::distribution_random &rng_source);

private:
    rng::distribution_random &rng_source;
};
