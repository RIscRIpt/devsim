#include <deque>

using namespace std;

#include "queue.h"

queue::queue(wstring name, unsigned capacity, queue_kind kind) :
    resource(resource_type::queue, name),
    capacity(capacity),
    kind(kind)
{
}

queue_kind queue::get_kind() const {
    return kind;
}

void queue::set_kind(queue_kind value) {
    kind = value;
}
