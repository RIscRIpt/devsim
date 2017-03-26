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

    const resource_type type;
    const unsigned capacity;
};
