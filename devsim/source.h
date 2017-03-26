#pragma once

#include <memory>

#include "block.h"
#include "distribution_random.h"
#include "entity.h"

class source :
    public block
{
public:
    source(::engine &engine, rng::distribution_random &rng_source, std::wstring name = nullptr);

    virtual engine_time next_available_time() const override;
    virtual bool can_put() const override;
    virtual bool can_get() const override;
    virtual bool put(std::shared_ptr<entity> e) override;
    virtual std::shared_ptr<entity> get() override;

private:
    rng::distribution_random &rng_source;
    engine_time next_spawn_time;
};
