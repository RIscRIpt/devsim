#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "resource.h"
#include "distribution_random.h"
#include "entity.h"

class server :
    public resource
{
public:
    server(::engine &engine, std::wstring name = nullptr, unsigned capacity = INFINITE, std::shared_ptr<rng::distribution_random> default_time_source = nullptr);

    void set_serve_distribution(source::id_t id, std::shared_ptr<rng::distribution_random> time_source);

    virtual engine_time next_available_time() const override;
    virtual bool can_put() const override;
    virtual bool can_get() const override;
    virtual bool put(std::shared_ptr<entity> e) override;
    virtual std::shared_ptr<entity> get() override;
    virtual unsigned engaged() const override;
    virtual unsigned engaged(std::function<bool(entity&)> pred) const override;
    virtual std::shared_ptr<entity> peek() const override;

private:
    bool is_served_before(std::shared_ptr<entity> e1, std::shared_ptr<entity> e2);
    std::shared_ptr<rng::distribution_random> get_time_source(source::id_t source_id);

    std::shared_ptr<rng::distribution_random> default_time_source;

    std::map<source::id_t, std::shared_ptr<rng::distribution_random>> source_time_source;
    std::map<entity::id_t, engine_time> serving_end_time;
    std::vector<std::shared_ptr<entity>> serving;
};
