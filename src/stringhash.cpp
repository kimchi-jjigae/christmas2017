#include "stringhash.hpp"

bool operator==(const StringHash& a, const StringHash& b)
{
    return a.hash == b.hash;
}

bool operator<(const StringHash& a, const StringHash& b)
{
    return a.hash < b.hash;
}

std::ostream& operator<<(std::ostream& out, const StringHash& hash)
{
    out << std::string(hash.string);
    return out;
}
