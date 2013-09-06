#include "utils.hpp"

BEGIN_NAMESPACE_UTILS

std::string val2bin(uint16_t i)
{
    std::string res = "0x";
    for(std::size_t n = 15; n < 16; n--)
    {
        uint16_t mask = (uint16_t)(1 << n);
        res += (mask&i?"1":"0");
    }
    return res;
}

END_NAMESPACE_UTILS
