#include "uniform.h"

using namespace rng;

uniform::uniform(source_t *source, double minimum, double maximum) :
    distribution_random(source),
    minimum(minimum),
    maximum(maximum)
{
}

double uniform::next() {
    source_t *source = get_source();

    double source_range = source->maximal() - source->minimal();
    double required_range = maximum - minimum;

    double min_correction = minimum - source->minimal();
    double range_correction = required_range / source_range;

    return (source->next() + min_correction) * range_correction;
}

double uniform::minimal() const {
    return minimum;
}

double uniform::maximal() const {
    return maximum;
}
