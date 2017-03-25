#include "normal.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace rng;
using namespace std;

normal::normal(double mean, double sd) :
    normal(nullptr, mean, sd)
{}

normal::normal(source_t *source) :
    normal(source, 0.0, 1.0)
{}

normal::normal(source_t *source, double mean, double sd) :
    distribution_random(source)
{
    set_mean(mean);
    set_sd(sd);
}

double normal::next() {
    source_t *source = get_source();
    double x, result;
    do {
        result = mean + sd * source->next();
        x = source->next();
    } while(!in_standard_bell(x, result));
    return result;
}

bool normal::in_standard_bell(double x, double value) {
    return x <= exp(
        -(x*x / 2.0)
    ) / sqrt(2.0 * M_PI);
}

double normal::minimal() const {
    return -INFINITY;
}

double normal::maximal() const {
    return INFINITY;
}

double normal::get_mean() const {
    return mean;
}

void normal::set_mean(double value) {
    mean = value;
}

double normal::get_sd() const {
    return sd;
}

void normal::set_sd(double value) {
    sd = value;
}
