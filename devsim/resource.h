#pragma once

#include <string>
#include <memory>

#include "block.h"
#include "entity.h"

enum class resource_type {
    queue,
    server,
};

class resource :
    public block
{
public:
    static const unsigned INFINITE = -1;

    resource(::engine &engine, resource_type type, unsigned capacity = INFINITE, std::wstring name = nullptr);

    virtual unsigned engaged() const = 0;
    virtual std::shared_ptr<entity> peek() const = 0;

    const resource_type type;
    const unsigned capacity;
};
