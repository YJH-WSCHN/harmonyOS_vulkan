#include <vulkan/vulkan.h>
#include <native_window/external_window.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include "../cpp/types/vulkan_library/include/application.h"
#include "../cpp/types/vulkan_library/include/config.h"
#include "../cpp/types/vulkan_library/include/utils/utils.h"
#include <vector>
#include <hilog/log.h>
#undef LOG_DOMAIN
#define LOG_DOMAIN 0x1234
#undef LOG_TAG
#define LOG_TAG "VULKAN_DEMO"

static VkInstance              g_vkInstance   = VK_NULL_HANDLE;
static VkSurfaceKHR            g_vkSurface    = VK_NULL_HANDLE;
static OHNativeWindow*         g_nativeWindow = nullptr;   // ① 用 nullptr
bool d = true;
static vulkan::Window window{g_nativeWindow,static_cast<unsigned int>(360), static_cast<unsigned int>(360)};
static vulkan::Application* app = nullptr;
bool CreateVulkanInstance() {
    OH_LOG_INFO(LOG_APP, "CreateVulkanInstance");
    VkApplicationInfo appInfo{};
    appInfo.sType         = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanDemo";
    appInfo.apiVersion    = VK_API_VERSION_1_1;

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;

    const char* extensions[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_OHOS_SURFACE_EXTENSION_NAME
    };
    instanceInfo.enabledExtensionCount = 2;
    instanceInfo.ppEnabledExtensionNames = extensions;

    VkResult err = vkCreateInstance(&instanceInfo, nullptr, &g_vkInstance);
    if (err != VK_SUCCESS) {
        OH_LOG_ERROR(LOG_APP, "vkCreateInstance fail, err=%d", err);
        return false;
    }
    OH_LOG_INFO(LOG_APP, "Vulkan Instance 创建成功");
    return true;
}

void OnSurfaceCreatedCB(OH_NativeXComponent*, void* window) {
    OH_LOG_INFO(LOG_APP, "========== OnSurfaceCreatedCB 被系统回调了 ==========");
    OH_LOG_INFO(LOG_APP, "window=%p", window);
    if (!window) {
        OH_LOG_ERROR(LOG_APP, "window is null");
        return;
    }
    g_nativeWindow = static_cast<OHNativeWindow*>(window);

    /*if (g_vkInstance == VK_NULL_HANDLE) {
        OH_LOG_ERROR(LOG_APP, "Instance not ready");
        CreateVulkanInstance();
    }
    if (g_vkSurface != VK_NULL_HANDLE) {          // ② 防止重复创建
        OH_LOG_WARN(LOG_APP, "Surface already exists");
    }

    VkSurfaceCreateInfoOHOS info{};               // ③ 完全清零
    info.sType  = VK_STRUCTURE_TYPE_SURFACE_CREATE_INFO_OHOS;
    info.pNext  = nullptr;
    info.flags  = 0;
    info.window = g_nativeWindow;

    VkResult err = vkCreateSurfaceOHOS(g_vkInstance, &info, nullptr, &g_vkSurface);
    if (err != VK_SUCCESS) {
        OH_LOG_ERROR(LOG_APP, "vkCreateSurfaceOHOS fail, err=%d", err);
        // 可选：把 Instance 也销毁，让上层重新来过
        vkDestroyInstance(g_vkInstance, nullptr);
        g_vkInstance = VK_NULL_HANDLE;
    } else {
        OH_LOG_INFO(LOG_APP, "Vulkan Surface 创建成功");
    }*/
}



void Run(){
    if(g_nativeWindow!=nullptr){
        OH_LOG_INFO(LOG_APP, "Vulkan Surface 创建成功");
    }
    OH_LOG_INFO(LOG_APP, "g_nativeWindow=%{public}p", g_nativeWindow);
    window = vulkan::Window{g_nativeWindow,static_cast<unsigned int>(360), static_cast<unsigned int>(360)};
    auto vulkanApp = vulkan::Application(&window);
    
    app = &vulkanApp;
    
    if (app == nullptr){
        OH_LOG_INFO(LOG_APP, "app初始化失败");
        return;
    }
    else{
        OH_LOG_INFO(LOG_APP, "===app初始化成功===");
        OH_LOG_INFO(LOG_APP, "g_nativeWindow=%{public}p",app->getWindow());
    }
    if (!app->validate()) {
        OH_LOG_INFO(LOG_APP, "validate");
        return;
    }
   if(g_nativeWindow!=nullptr){
        OH_LOG_INFO(LOG_APP, "111");
        auto result = app->draw_frame();
        if (result.has_value()) {
            OH_LOG_INFO(LOG_APP, "has_value");
            if (result.value()) {
                if (!app->refresh()) {
                    OH_LOG_INFO(LOG_APP, "refresh");
                }
            }
        }
    }
    
}
