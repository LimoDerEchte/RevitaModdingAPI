
#include "include/RevitaMod.hpp"

class RevitaModImpl final : public IRevitaMod {
    ~RevitaModImpl() override = default;
};

extern "C" __declspec(dllexport) IRevitaMod* core_mod_get_interface() {
    static RevitaModImpl impl;
    return &impl;
}
