#pragma once

#include <memory>

#include "source.h"

enum class event_type {
    spawn_entity,
};

class event
{
public:
    event(event_type type);

    const event_type type;

};

class event_spawn_entity : public event {
public:
    event_spawn_entity(std::shared_ptr<source> src, std::shared_ptr<entity> ent) :
        event(event_type::spawn_entity),
        src(src),
        ent(ent)
    {}

    const std::shared_ptr<source> src;
    const std::shared_ptr<entity> ent;
};
