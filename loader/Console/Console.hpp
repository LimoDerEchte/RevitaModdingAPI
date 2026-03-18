
#pragma once

#define LOG(...) printf(__VA_ARGS__)

namespace  Console {
    void Alloc();
    void Free();
};
