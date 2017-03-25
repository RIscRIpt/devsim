#pragma once

#include <string>

#include "block.h"

class sink :
    public block
{
public:
    sink(std::wstring name = nullptr);

};
