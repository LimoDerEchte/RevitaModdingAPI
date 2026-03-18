
#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>

#include "RevitaMod.h"

namespace fs = std::filesystem;

struct LoadedMod {
    HMODULE module;
    std::string name;
    ModVersion* version;
    std::string authors;

    RevitaMod_Entry_t entry;
};

class Loader {
    static void LoadMod(HMODULE module, const wchar_t* file);
    static void Traverse(const fs::directory_iterator& dir);

public:
    static std::vector<std::unique_ptr<LoadedMod>> loadedMods;

    static void LoadMods(const std::string& folder);
};
