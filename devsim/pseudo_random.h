#pragma once

#include "random.h"

namespace rng {

    template<typename T, typename U>
    class pseudo_random : random<T> {
    public:
        virtual void set_seed(U seed) = 0;
        virtual U get_seed() const = 0;
    };
}
