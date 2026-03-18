
#pragma once

#include <string>
#include <RevitaMod.h>

class RevitaMod {
public:
    static std::string name;
    static ModVersion version;
    static std::string authors;

    static void Entry();
};

extern "C" {
    inline const char* RevitaMod_GetName() {
        return RevitaMod::name.c_str();
    }

    inline ModVersion* RevitaMod_GetVersion() {
        return &RevitaMod::version;
    }

    inline const char* RevitaMod_GetAuthors() {
        return RevitaMod::authors.c_str();
    }

    inline void RevitaMod_Entry() {
        RevitaMod::Entry();
    }
}
