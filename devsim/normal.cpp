#include "normal.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace rng;
using namespace std;

normal::normal(source_t &source, double mean, double sd) :
    distribution_random(source),
    mean(mean),
    sd(sd)
{
}

double normal::next() {
    double x, standard;
    do {
        standard = -5.0 + 10.0 * source.next();
        x = 0.4 * source.next();
    } while(!in_standard_bell(x, standard));
    return mean + sd * standard;
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
