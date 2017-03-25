#include "rdtsc.h"

__declspec(naked) static unsigned rdtsc() {
    __asm rdtsc
}

unsigned rng::rdtsc::next() {
    return ::rdtsc();
}

unsigned rng::rdtsc::minimal() const {
    return 0;
}

unsigned rng::rdtsc::maximal() const {
    return 0xFFFFFFFF;
}
