#include "distribution_random.h"

using namespace rng;

distribution_random::distribution_random(source_t &source) :
    source(source)
{
    if(source.minimal() < 0.0 || source.maximal() > 1.0)
        throw 1;
}
