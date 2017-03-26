#pragma once

#include <string>
#include <deque>
#include <memory>

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
    queue(::engine &engine, std::wstring name, unsigned capacity, queue_kind kind);

    queue_kind get_kind() const;
    void set_kind(queue_kind value);

    virtual engine_time next_available_time() const override;
    virtual bool can_put() const override;
    virtual bool can_get() const override;
    virtual bool put(std::shared_ptr<entity> e) override;
    virtual std::shared_ptr<entity> get() override;
    virtual unsigned engaged() const override;
    virtual std::shared_ptr<entity> peek() const override;

private:
    queue_kind kind;

    std::deque<std::shared_ptr<entity>> container;

};
