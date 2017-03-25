#pragma once

#include "distribution_random.h"

namespace rng {

    class uniform :
        public distribution_random
    {
    public:
        uniform(double minimum, double maximum);

        uniform(source_t *source, double minimum, double maximum);

        virtual double next() override;

        virtual double minimal() const override;
        virtual double maximal() const override;

    private:
        double minimum;
        double maximum;
    };

}
