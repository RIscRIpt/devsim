#pragma once

#include <string>
#include <deque>

#include "resource.h"
#include "entity.h"

enum class queue_kind {
    FIFO,
    LIFO,
};

class queue :
    public resource
{
public:
    static const unsigned INFINITE = -1;

    queue(std::wstring name, unsigned capacity, queue_kind kind);

    queue_kind get_kind() const;
    void set_kind(queue_kind value);

private:
    unsigned capacity;

    queue_kind kind;

    std::deque<entity*> container;

};
