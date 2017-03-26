#pragma once

#include "distribution_random.h"

namespace rng {

    class exponential :
        public distribution_random
    {
    public:
        exponential(source_t &source, double lambda);

        virtual double next() override;
        virtual double minimal() const override;
        virtual double maximal() const override;

        double get_lambda() const;
        void set_lambda(double value);

    private:
        double lambda;
    };
}
