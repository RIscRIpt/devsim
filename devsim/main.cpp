#include <iostream>
#include <iomanip>
#include <functional>
#include <memory>

#include <cmath>

#include "engine.h"

#include "random.h"
#include "pseudo_random.h"
#include "distribution_random.h"
#include "exponential.h"
#include "erlang.h"
#include "normal.h"

#include "container.h"
#include "source.h"
#include "sink.h"
#include "queue.h"
#include "server.h"

#include "flow.h"

using namespace std;

__declspec(naked) unsigned _fast_rand() {
    __asm rdtsc
}

class cpp_rand :
    public rng::pseudo_random<double, unsigned int>
{
public:
    virtual double next() override { return (double)rand() / RAND_MAX; }
    virtual double minimal() const override { return 0.0; }
    virtual double maximal() const override { return 1.0; }
    virtual void set_seed(unsigned int seed) override { _seed = seed;  srand(seed); }
    virtual unsigned int get_seed() const override { return _seed; }
private:
    int _seed;
};

class rdtsc_rand :
    public rng::random<double>
{
public:
    virtual double next() override { return (double)_fast_rand() / (double)0xFFFFFFFF; }
    virtual double minimal() const override { return 0.0; }
    virtual double maximal() const override { return 1.0; }
};

int main() {
    engine e;

    auto random_source = make_shared<cpp_rand>();
    random_source->set_seed(time(NULL));

    rng::exponential rng_pois(*random_source, 0.2);
    rng::erlang rng_erlang(*random_source, 2, 0.1);
    rng::normal rng_normal(*random_source, 20, 3);
    rng::exponential rng_exp(*random_source, 0.2);

    source s_pois(e, rng_pois, L"l1");
    source s_erlang(e, rng_erlang, L"l2");

    queue q(e, L"queue", queue::INFINITE, queue_kind::LIFO);

    server server(e, L"server", 1);

    server.set_serve_distribution(s_pois.id, shared_ptr<rng::distribution_random>(&rng_normal));
    server.set_serve_distribution(s_erlang.id, shared_ptr<rng::distribution_random>(&rng_exp));

    sink end(e, L"end");

    container sources(e, L"sources");
    sources
        .add(shared_ptr<block>(&s_pois))
        .add(shared_ptr<block>(&s_erlang));

    flow f(e);
    f
        .add(shared_ptr<block>(&sources))
        .add(shared_ptr<block>(&q))
        .add(shared_ptr<block>(&server))
        .add(shared_ptr<block>(&end));

    e.add(shared_ptr<flow>(&f));

    e.set_stop_condition([](const engine &e) -> bool {
        return e.get_time() >= 500.0;
    });
    e.set_event_listener([&](const engine &eng, const event &ev) -> void {
        wstring spawn_name = L"";
        if(ev.type == event_type::spawn_entity) {
            auto &spawn_ent_ev = static_cast<const event_spawn_entity&>(ev);
            if(spawn_ent_ev.ent->source_id == s_pois.id)
                spawn_name = s_pois.name;
            else
                spawn_name = s_erlang.name;
        }

        wstring server_busy_with = L"none";
        auto serving = server.peek();
        if(serving != nullptr) {
            if(serving->source_id == s_pois.id)
                server_busy_with = s_pois.name;
            else if(serving->source_id == s_erlang.id)
                server_busy_with = s_erlang.name;
        }

        wcout << setprecision(3)
            << setw(4) << spawn_name << ','
            << setw(8) << eng.get_time() << ','
            << setw(8) << s_pois.next_available_time() << ','
            << setw(8) << s_erlang.next_available_time() << ','
            << setw(8) << server.next_available_time() << ','
            << setw(2) << (server.engaged() > 0) << ','
            << setw(8) << q.engaged() << ','
            << setw(8) << server_busy_with << '\n';
    });
    e.run();

    //TODO: fix destructors
    exit(1);

    return 0;
}
