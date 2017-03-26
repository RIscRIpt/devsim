#include "entity.h"

entity::entity(object::id_t source_id) :
    object(object_type::entity),
    source_id(source_id)
{
}
