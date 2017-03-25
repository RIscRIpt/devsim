#include "poisson.h"

#include <cmath>

using namespace rng;
using namespace std;

poisson::poisson(double lambda) :
    poisson(nullptr, lambda)
{}

poisson::poisson(source_t *source) :
    poisson(source, 1.0)
{}

poisson::poisson(source_t *source, double lambda) :
    distribution_random(source),
    exp_d(lambda)
{
}

double poisson::next() {
    return exp_d.next();
}

double poisson::minimal() const {
    return 0.0;
}

double poisson::maximal() const {
    return INFINITY;
}

double poisson::get_lambda() const {
    return exp_d.get_lambda();
}

void poisson::set_lambda(double value) {
    exp_d.set_lambda(value);
}
