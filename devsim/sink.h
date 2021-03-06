#pragma once

#include <string>
#include <memory>

#include "block.h"
#include "entity.h"

class sink :
    public block
{
public:
    sink(::engine &engine, std::wstring name = nullptr);

    virtual engine_time next_available_time() const override;
    virtual bool can_put() const override;
    virtual bool can_get() const override;
    virtual bool put(std::shared_ptr<entity> e) override;
    virtual std::shared_ptr<entity> get() override;

};
