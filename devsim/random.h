#pragma once

namespace rng {

    template<typename T>
    class random
    {
    public:
        virtual T next() = 0;

        virtual T minimal() const = 0;
        virtual T maximal() const = 0;
    };

}
