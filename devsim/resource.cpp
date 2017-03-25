#include <string>

using namespace std;

#include "resource.h"

resource::resource(resource_type type, wstring name) :
    block(block_type::resource, name),
    type(type)
{}

resource_type resource::get_resource_type() const {
    return type;
}
