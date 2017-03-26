#pragma once

enum class object_type {
    block,
    entity,
};

class object
{
public:
    typedef unsigned long long int id_t;

    static const id_t INVALID_ID;
    static const id_t ALL_ID;

    object(object_type type);

    const id_t id;

private:
    object_type type;

    id_t get_next_id();

    static id_t ID_NEXT;
};
