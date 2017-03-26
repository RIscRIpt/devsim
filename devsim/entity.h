#pragma once

#include "object.h"

class entity :
    public object
{
public:
    entity(object::id_t source_id);

    const object::id_t source_id;

};
