#include "erlang.h"

#include <cmath>

using namespace rng;
using namespace std;

erlang::erlang(source_t &source, unsigned k, double lambda) :
    distribution_random(source),
    k(k),
    lambda(lambda)
{
}

double erlang::next() {
    double product = 1.0;
    for(unsigned i = 0; i < k; i++)
        product *= source.next();
    return -(1.0 / lambda) * log(product);
}

double erlang::minimal() const {
    return 0.0;
}

double erlang::maximal() const {
    return INFINITY;
}

unsigned erlang::get_k() const {
    return k;
}

void erlang::set_k(unsigned value) {
    k = value;
}

double erlang::get_lambda() const {
    return lambda;
}

void erlang::set_lambda(double value) {
    lambda = value;
}
