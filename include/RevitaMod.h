
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    struct ModVersion {
        int major;
        int minor;
        int patch;
    };

    __declspec(dllexport) const char* RevitaMod_GetName();
    __declspec(dllexport) ModVersion* RevitaMod_GetVersion();
    __declspec(dllexport) const char* RevitaMod_GetAuthors();

    __declspec(dllexport) void RevitaMod_Entry();

    typedef const char*(*RevitaMod_GetName_t)();
    typedef ModVersion*(*RevitaMod_GetVersion_t)();
    typedef const char*(*RevitaMod_GetAuthors_t)();
    typedef void(*RevitaMod_Entry_t)();

#ifdef __cplusplus
}
#endif