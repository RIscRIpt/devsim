#include <string>

using namespace std;

#include "sink.h"

sink::sink(wstring name) :
    block(block_type::sink, name)
{
}
