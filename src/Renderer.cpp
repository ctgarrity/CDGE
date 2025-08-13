#include "Renderer.h"

#define VOLK_IMPLEMENTATION
#include "external/volk.h"

#define VK_NO_PROTOTYPES
#include "vulkan/vk_enum_string_helper.h" // Needed for string_VkResult helper

#include <cassert>
#include <iostream>
#include <algorithm>

#define VK_CHECK(func) { \
    const VkResult result = func; \
    if (result != VK_SUCCESS) { \
        std::cerr << "Error calling function " << #func \
                  << "at " << __FILE__ << ":" \
                  << __LINE__ << ". Result is " \
                  << string_VkResult(result) \
                  << std::endl; \
        assert(false); \
    } \
}

Renderer::Renderer() {
    init_vulkan();
}

Renderer::~Renderer() {
    destroy_vulkan();
}

void Renderer::init_volk() {
    VK_CHECK(volkInitialize());
    std::cout << "Volk initialized" << std::endl;
}

void Renderer::init_sdl() {
    // Todo: Write initialization code
}

void Renderer::init_vulkan() {
    init_volk();
    init_sdl();
    bool layers_found = get_instance_layers(m_requested_instance_layers);
    create_instance(layers_found);
}

void Renderer::destroy_vulkan() {
    vkDestroyInstance(m_instance, nullptr);
}

bool Renderer::get_instance_layers(const std::vector<const char*>& requested) {
    uint32_t property_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&property_count, nullptr));
    std::vector<VkLayerProperties> properties(property_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&property_count, properties.data()));

    std::vector<std::string> layers;
    std::transform(properties.begin(), properties.end(), std::back_inserter(layers), [](const VkLayerProperties& props) {return props.layerName;});
    // std::cout << "Available Instance Layers:\n";
    // for (const std::string& layer : layers) {
    //     std::cout << '\t' << layer << '\n';
    // }

    for (int i = 0; i < requested.size(); i++) {
        bool found = false;
        for (int j = 0; j < layers.size(); j++) {
            if (layers[j] == requested[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << requested[i] << " which was requested was not found\n";
            return false;
        }
    }

    std::cout << "Requested layers found" << std::endl;
    return true;
}

void Renderer::create_instance(bool layers_found) {
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Casual Distraction Games Engine";
    app_info.pEngineName = "Casual Distraction Games Engine";
    app_info.apiVersion = VK_MAKE_API_VERSION(0, 1, 4, 0);

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledLayerCount = static_cast<uint32_t>(m_requested_instance_layers.size());
    create_info.ppEnabledLayerNames = m_requested_instance_layers.data();
    // Todo: Enable SDL extensions
    VK_CHECK(vkCreateInstance(&create_info, nullptr, &m_instance));

    volkLoadInstance(m_instance);
    std::cout << "Instance created and loaded for volk" << std::endl;
}

void Renderer::create_device() {
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
}