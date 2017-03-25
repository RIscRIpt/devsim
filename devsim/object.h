#pragma once

class object
{
public:
    typedef unsigned long long int id_t;

    static const id_t INVALID_ID;
    static const id_t ALL_ID;

    object();

    const id_t id;

private:

    id_t get_next_id();

    static id_t ID_NEXT;
};
