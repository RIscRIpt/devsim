#include <string>

using namespace std;

#include "block.h"

block::block(::engine &engine, block_type type, wstring name) :
    object(object_type::block),
    engine(engine),
    type(type),
    name(name)
{
}
