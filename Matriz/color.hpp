#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

namespace color
{
    inline std::ostream &red(std::ostream &os) { return os << "\033[31m"; }
    inline std::ostream &green(std::ostream &os) { return os << "\033[32m"; }
    inline std::ostream &yellow(std::ostream &os) { return os << "\033[33m"; }
    inline std::ostream &blue(std::ostream &os) { return os << "\033[34m"; }
    inline std::ostream &reset(std::ostream &os) { return os << "\033[0m"; }
}

#endif
