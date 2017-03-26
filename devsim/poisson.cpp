#include "poisson.h"

#include <cmath>

using namespace rng;
using namespace std;

poisson::poisson(source_t &source, double lambda) :
    distribution_random(source),
    lambda(lambda)
{
}

double poisson::next() {
    double L = exp(-lambda);
    unsigned k = -1;
    double p = 1.0;
    do {
        k++;
        p *= source.next();
    } while(p > L);
    return k;
}

double poisson::minimal() const {
    return 0.0;
}

double poisson::maximal() const {
    return INFINITY;
}

double poisson::get_lambda() const {
    return lambda;
}

void poisson::set_lambda(double value) {
    lambda = value;
}
