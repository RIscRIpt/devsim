#pragma once

#include <string>

#include "block.h"

enum class resource_type {
    queue,
    server,
};

class resource :
    public block
{
public:
    resource(resource_type type, std::wstring name);

    resource_type get_resource_type() const;

private:
    resource_type type;
};
