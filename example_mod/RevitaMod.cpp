
#include <RevitaMod.hpp>

std::string RevitaMod::name = "Example Mod";
std::string RevitaMod::authors = "Limo";
ModVersion RevitaMod::version = { 0, 1, 0 };

void RevitaMod::Entry() {
    printf("Hello from the example mod!\n");
}
