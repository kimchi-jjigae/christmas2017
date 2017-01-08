#pragma once
#include <cstdint>
#include <functional>
#include <ostream>

namespace spr
{
struct StringHash
{
    size_t hash;
    const char* string;
};

bool operator==(const StringHash& a, const StringHash& b);
bool operator<(const StringHash& a, const StringHash& b);
std::ostream& operator<<(std::ostream& out, const StringHash& hash);
}

constexpr spr::StringHash operator "" _hash( const char* data, size_t len)
{
    const char* original = data;
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

    return {h, original};
} 

static_assert("run_left"_hash.hash == size_t{1811686161}, "nice");

namespace std
{
    template <> struct hash<spr::StringHash>
    {
        size_t operator()(const spr::StringHash& h) const
        {
            return h.hash;
        }
    };
}
