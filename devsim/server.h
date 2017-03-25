#pragma once

#include <string>
#include <map>

#include "resource.h"
#include "distribution_random.h"

class server :
    public resource
{
public:
    server(std::wstring name = nullptr, unsigned capacity = -1, rng::distribution_random *default_time_source = nullptr);

    void set_serve_distribution(source::id_t id, rng::distribution_random *time_source);

private:
    unsigned capacity;

    rng::distribution_random *default_time_source;

    std::map<source::id_t, rng::distribution_random*> source_time_source;
};
