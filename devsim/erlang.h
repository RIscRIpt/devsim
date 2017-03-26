#pragma once

#include "distribution_random.h"
#include "exponential.h"

namespace rng {

    class erlang :
        public distribution_random
    {
    public:
        erlang(source_t &source, unsigned k, double lambda);

        virtual double next() override;
        virtual double minimal() const override;
        virtual double maximal() const override;

        unsigned get_k() const;
        void set_k(unsigned value);

        double get_lambda() const;
        void set_lambda(double value);

    private:
        unsigned k;
        double lambda;
    };
}
