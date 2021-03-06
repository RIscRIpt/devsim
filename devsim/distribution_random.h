#pragma once

#include "random.h"

namespace rng {

    class distribution_random :
        public random<double>
    {
    public:
        typedef random<double> source_t;

        distribution_random(source_t &source);

        source_t &source;
    };

}
