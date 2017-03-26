#include <string>

using namespace std;

#include "resource.h"

resource::resource(::engine &engine, resource_type type, unsigned capacity, wstring name) :
    block(engine, block_type::resource, name),
    type(type),
    capacity(capacity)
{}
