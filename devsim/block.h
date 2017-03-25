#pragma once

#include <string>

#include "object.h"

enum class block_type {
    source,
    sink,
    resource,
};

class block :
    public object
{
public:
    block(block_type type);
    block(block_type type, std::wstring name);

    block_type get_block_type() const;

    const std::wstring name;

private:
    block_type type;
};
