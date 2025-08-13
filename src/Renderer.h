#ifndef RENDERER_H
#define RENDERER_H

#include "external/volk.h"
#include <vector>
#include <string>

class Renderer {
    std::vector<const char*> m_requested_instance_layers = {"VK_LAYER_KHRONOS_validation"};
    VkInstance m_instance = VK_NULL_HANDLE;

    void init_volk();
    void init_sdl();
    void init_vulkan();
    void destroy_vulkan();

    bool get_instance_layers(const std::vector<const char*>& requested);
    void create_instance(bool layers_found);
    void create_device();

public:
    Renderer();
    ~Renderer();
};

#endif
