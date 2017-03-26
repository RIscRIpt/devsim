#pragma once

#include <string>
#include <memory>

#include "object.h"
#include "entity.h"
#include "engine.h"

enum class block_type {
    source,
    sink,
    resource,
    container,
};

class block :
    public object
{
public:
    block(engine &engine, block_type type, std::wstring name = nullptr);

    virtual engine_time next_available_time() const = 0;
    virtual bool can_put() const = 0;
    virtual bool can_get() const = 0;
    virtual bool put(std::shared_ptr<entity> e) = 0;
    virtual std::shared_ptr<entity> get() = 0;

    const block_type type;
    const std::wstring name;

    engine &engine;
};
