#pragma once

#include "pseudo_random.h"

namespace rng {

    class rdtsc :
        public random<unsigned>
    {
    public:
        virtual unsigned next() override;

        virtual unsigned minimal() const override;
        virtual unsigned maximal() const override;

    private:
        unsigned seed;
    };

}
