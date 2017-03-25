#include <string>

using namespace std;

#include "block.h"

block::block(block_type type) :
    block(type, nullptr)
{}

block::block(block_type type, wstring name) :
    object(),
    type(type),
    name(name)
{
}

block_type block::get_block_type() const {
    return type;
}
