#include "object.h"

const object::id_t object::INVALID_ID = -1;
const object::id_t object::ALL_ID = 0;
object::id_t object::ID_NEXT = 1;

object::object() :
    id(get_next_id())
{
}

object::id_t object::get_next_id() {
    //TODO: make thread-safe
    return ID_NEXT++;
}
