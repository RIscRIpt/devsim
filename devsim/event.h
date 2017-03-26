#pragma once

#include <memory>

#include "source.h"
#include "server.h"

enum class event_type {
    begin,
    spawn_entity,
    server_free,
    server_busy,
};

class event
{
public:
    event(event_type type);

    const event_type type;

};

class event_begin : public event {
public:
    event_begin() :
        event(event_type::begin)
    {}
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

class event_server_free : public event {
public:
    event_server_free(std::shared_ptr<server> srv) :
        event(event_type::server_free)
    {}
};

class event_server_busy : public event {
public:
    event_server_busy(std::shared_ptr<server> srv) :
        event(event_type::server_busy)
    {}
};
