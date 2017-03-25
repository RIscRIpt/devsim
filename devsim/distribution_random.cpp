#include "distribution_random.h"

using namespace rng;

distribution_random::distribution_random(source_t *source) :
    source(source)
{
}

distribution_random::source_t* distribution_random::get_source() {
    return source;
}

void distribution_random::set_source(source_t *rnd) {
    if(rnd->minimal() < 0.0 || rnd->maximal() > 1.0)
        throw 1;
    source = rnd;
}
