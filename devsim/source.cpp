#include <string>

using namespace std;

#include "source.h"

source::source(wstring name, rng::distribution_random &rng_source) :
    block(block_type::source, name),
    rng_source(rng_source)
{
}
