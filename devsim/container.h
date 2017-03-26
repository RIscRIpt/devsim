#pragma once

#include <string>
#include <vector>
#include <memory>

#include "block.h"

class container :
    public block
{
public:
    container(::engine &engine, std::wstring name = nullptr);

    container& add(std::shared_ptr<block> b);

    virtual engine_time next_available_time() const override;
    virtual bool can_put() const override;
    virtual bool can_get() const override;
    virtual bool put(std::shared_ptr<entity> e) override;
    virtual std::shared_ptr<entity> get() override;

private:
    std::vector<std::shared_ptr<block>> blocks;

};
