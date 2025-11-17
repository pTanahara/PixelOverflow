#pragma once

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG

#include <iostream>
#include <sstream>

template <typename... Args>
void dprint(Args&&... args) {
    std::ostringstream oss;
    (oss << ... << args);
    std::cout << oss.str() << std::endl;
}

#else 

template <typename... Args>
void dprint(Args&&... args) {}

#endif

