#define VOLK_IMPLEMENTATION
#include "external/volk.h"

#include <iostream>

int main() {
    std::cout << "Hello, vulkan!" << std::endl;

    if (volkInitialize() == VK_SUCCESS) {
        std::cout << "Volk initialized!" << std::endl;
    }
}