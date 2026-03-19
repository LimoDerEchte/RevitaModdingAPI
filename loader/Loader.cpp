
#include "Loader.hpp"

#include "Console/Console.hpp"

bool Loader::wasInitialized = false;
std::vector<std::unique_ptr<LoadedMod>> Loader::loadedMods{};

void Loader::LoadMods(const std::string &folder) {
    if (!fs::exists(folder)) {
        printf_s("Could not find mods folder!\n");
        return;
    }

    printf_s("Loading Mods...\n\n");
    Traverse(fs::directory_iterator(folder));

    printf_s("Running Mod Entries...\n\n");
    for (const auto &entry : loadedMods) {
        entry->entry();
    }

    printf_s("\nMods Loaded.\n\n");
}

// Little trampoline so the proxy can properly call this
extern "C" __declspec(dllexport) void revita_loader_entry() {
    Loader::Entry();
}

void Loader::Entry() {
    if (wasInitialized)
        return;
    wasInitialized = true;

    Console::Alloc();
    printf_s("Revita Mod Loader Version 0.1.0\n\n");

    const HMODULE minHook = LoadLibraryA("loader/MinHook.x86.dll");
    if (minHook == nullptr) {
        printf_s("Failed to load MinHook.x86.dll!");
        return;
    }

    const auto mh_initialize = GetProcAddress(minHook, "MH_Initialize");
    if (mh_initialize == nullptr) {
        printf_s("Failed to get MH_Initialize!");
        return;
    }

    if (mh_initialize() != 0) {
        printf_s("Failed to initialize MinHook!");
        return;
    }
    printf_s("MinHook successfully initialized.\n");
    LoadMods("mods");
}

void Loader::LoadMod(const HMODULE module, const wchar_t* file) {
    const auto getName = reinterpret_cast<RevitaMod_GetName_t>(GetProcAddress(module, "RevitaMod_GetName"));
    if (!getName) {
        printf_s("| Could not load mod! (RevitaMod_GetName not found; %ls)\n\n", file);
        return;
    }

    const char* name = getName();
    if (!name) {
        printf_s("| Could not load mod! (Name is nullptr; %ls)\n\n", file);
        return;
    }

    const auto getVersion = reinterpret_cast<RevitaMod_GetVersion_t>(GetProcAddress(module, "RevitaMod_GetVersion"));
    if (!getVersion) {
        printf_s("| Could not load %s! (RevitaMod_GetVersion not found)\n\n", name);
        return;
    }

    ModVersion* version = getVersion();
    if (!version) {
        printf_s("| Could not load %s! (Version is nullptr)\n\n", name);
        return;
    }

    const auto getAuthors = reinterpret_cast<RevitaMod_GetAuthors_t>(GetProcAddress(module, "RevitaMod_GetAuthors"));
    if (!getAuthors) {
        printf_s("| Could not load %s! (RevitaMod_GetAuthors not found)\n\n", name);
        return;
    }

    const char* authors = getAuthors();
    if (!authors) {
        printf_s("| Could not load %s! (Authors is nullptr)\n\n", name);
        return;
    }

    const auto modEntry = reinterpret_cast<RevitaMod_Entry_t>(GetProcAddress(module, "RevitaMod_Entry"));
    if (!modEntry) {
        printf_s("| Could not load %s! (Entry is nullptr)\n\n", name);
        return;
    }

    printf_s("| Loaded: %s\n", name);
    printf_s("| Version: %d.%d.%d\n", version->major, version->minor, version->patch);
    printf_s("| Authors: %s\n\n", authors);

    auto entry = std::make_unique<LoadedMod>();
    entry->module = module;
    entry->name = name;
    entry->version = version;
    entry->entry = modEntry;
    loadedMods.push_back(std::move(entry));
}

void Loader::Traverse(const fs::directory_iterator &dir) { // NOLINT(*-no-recursion)
    for (const auto &entry : fs::directory_iterator(dir)) {
        if (entry.is_directory()) {
            Traverse(fs::directory_iterator(entry));
            continue;
        }
        if (!entry.is_regular_file())
            continue;

        if (std::wstring ext = entry.path().extension().wstring(); ext != L".dll" && ext != L".DLL")
            continue;

        const HMODULE mod = LoadLibraryW(entry.path().c_str());
        if (!mod) {
            printf_s("| Could not load module %ls (%lu)\n\n", entry.path().c_str(), GetLastError());
            continue;
        }
        LoadMod(mod, entry.path().c_str());
    }
}
