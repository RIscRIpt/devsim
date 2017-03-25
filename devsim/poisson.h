#pragma once

#include "distribution_random.h"
#include "exponential.h"

namespace rng {

    class poisson :
        public distribution_random
    {
    public:
        poisson(double lambda);
        poisson(source_t *source);
        poisson(source_t *source, double lambda);

        virtual double next() override;
        virtual double minimal() const override;
        virtual double maximal() const override;

        double get_lambda() const;
        void set_lambda(double value);

    private:
        exponential exp_d;
    };
}
