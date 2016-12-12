#pragma once
#include <cstdint>

constexpr size_t operator "" _hash( const char* data, size_t len)
{
    unsigned int seed = 1337;
    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    unsigned int h = seed ^ len;

    while(len >= 4)
    {
        unsigned int k = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m; 
        k ^= k >> r; 
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch(len)
    {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
                h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
} 

static_assert("run_left"_hash == 1811686161, "nice");
