#include "exponential.h"

#include <cmath>

using namespace rng;
using namespace std;

exponential::exponential(source_t &source, double lambda) :
    distribution_random(source)
{
    set_lambda(lambda);
}

double exponential::next() {
    return -log(source.next()) / lambda;
}

double exponential::minimal() const {
    return 0.0;
}

double exponential::maximal() const {
    return INFINITY;
}

double exponential::get_lambda() const {
    return lambda;
}

void exponential::set_lambda(double value) {
    lambda = value;
}
