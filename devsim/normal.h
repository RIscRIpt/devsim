#pragma once

#include "distribution_random.h"

namespace rng {

    class normal :
        public distribution_random
    {
    public:
        normal(double mean, double sd);
        normal(source_t *source);
        normal(source_t *source, double mean, double sd);

        virtual double next() override;
        virtual double minimal() const override;
        virtual double maximal() const override;

        double get_mean() const;
        void set_mean(double value);

        double get_sd() const;
        void set_sd(double value);

    private:
        double mean;
        double sd;

        bool in_standard_bell(double x, double value);
    };
}
