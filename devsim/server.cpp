#include <string>

using namespace std;

#include "source.h"
#include "server.h"

server::server(wstring name, unsigned capacity, rng::distribution_random *default_time_source) :
    resource(resource_type::server, name),
    capacity(capacity),
    default_time_source(default_time_source)
{
}

void server::set_serve_distribution(source::id_t id, rng::distribution_random *time_source) {
    source_time_source[id] = time_source;
}
