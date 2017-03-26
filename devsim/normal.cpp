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
    const double magic_const = (8.0 * (M_PI - 3.0)) /
        (3.0 * M_PI * (4.0 - M_PI));
    const double two_over_pi_a = 2.0 / (M_PI * magic_const);
    double x = 2.0 * source.next() - 1.0;
    double log_1_m_x = log1p(-x*x);
    double b_plus_half_log = two_over_pi_a + log_1_m_x / 2.0;
    double sign = -signbit(x) * 2.0 + 1.0;
    double errF_inv = sign * sqrt(
        sqrt( pow(b_plus_half_log, 2.0) - log_1_m_x/magic_const ) - b_plus_half_log
    );
    return mean + sd * (sqrt(2.0) * errF_inv);
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
