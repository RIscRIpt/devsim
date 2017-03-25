#include <functional>

#include <cmath>

#include "engine.h"

#include "uniform.h"
#include "exponential.h"
#include "erlang.h"
#include "normal.h"
#include "poisson.h"

#include "source.h"
#include "sink.h"
#include "queue.h"
#include "server.h"

#include "flow.h"

using namespace std;

__declspec(naked) int fast_rand() {
    __asm rdtsc
}

int main() {
    engine e;

    rng::uniform random_source(nullptr, 0.0, 1.0);
    rng::poisson rng_pois(&random_source, 0.2);
    rng::erlang rng_erlang(&random_source, 2, 0.1);
    rng::normal rng_normal(&random_source, 20, 3);
    rng::exponential rng_exp(&random_source, 0.2);

    source s_pois(L"source::poisson", rng_pois);
    source s_erlang(L"source::erlang", rng_erlang);

    queue q(L"queue", queue::INFINITE, queue_kind::LIFO);

    server server(L"server", 1);

    server.set_serve_distribution(s_pois.id, &rng_normal);
    server.set_serve_distribution(s_erlang.id, &rng_exp);

    sink end(L"end");

    flow f_pois;
    f_pois
        .add(s_pois)
        .add(q)
        .add(server)
        .add(end);

    flow f_erlang;
    f_erlang
        .add(s_erlang)
        .add(q)
        .add(server)
        .add(end);

    e
        .add(f_pois)
        .add(f_erlang);

    e.set_stop_condition([](const engine &e) -> bool {
        return e.get_time() >= 500.0;
    });

    e.set_event_listener([](const engine &eng, const event &ev) -> void {

    });

    e.run();

    return 0;
}
