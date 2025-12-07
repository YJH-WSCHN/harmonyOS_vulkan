#include <napi/native_api.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <hilog/log.h>

#undef LOG_DOMAIN
#define LOG_DOMAIN 0x1234
#undef LOG_TAG
#define LOG_TAG "VULKAN_DEMO"

extern bool CreateVulkanInstance();
extern void OnSurfaceCreatedCB(OH_NativeXComponent* component, void* window);
extern void Run();
int cont = 0;
static napi_value InitVulkan(napi_env env, napi_callback_info info) {
    bool success = CreateVulkanInstance();
    napi_value result;
    napi_get_boolean(env, success, &result);
    return result;
}
static napi_value RunP(napi_env env, napi_callback_info info)
{
    Run();
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    return undefined;            
}
OH_NativeXComponent_Callback callback{};
static napi_value Init(napi_env env, napi_value exports) {
    cont++;
    static int times = 0;
    times++;
    OH_LOG_INFO(LOG_APP, "Init() 第 %d 次", times);
    napi_property_descriptor desc[] = {
        {"initVulkan", nullptr, InitVulkan, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"run", nullptr, RunP, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    napi_value exportInstance = nullptr;
    OH_NativeXComponent* nativeXComponent = nullptr;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok ||
        exportInstance == nullptr) {
        OH_LOG_ERROR(LOG_APP, "Init: 找不到 OH_NATIVE_XCOMPONENT_OBJ，检查 ETS 侧 id 与 libraryname！");
        return exports;
    }
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent)) != napi_ok ||
        nativeXComponent == nullptr) {
        OH_LOG_WARN(LOG_APP, "第 %{public}d 次调用拿不到 nativeXComponent，跳过", times);
        return exports;
    }
    OH_LOG_INFO(LOG_APP, "===== 第 %{public}d 次调用成功拿到 nativeXComponent =====", times);
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] =  {};
    uint64_t idSize = sizeof(idStr);
    OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize);
    OH_LOG_INFO(LOG_APP, "Init: XComponent id=%{public}s", idStr);
    callback.OnSurfaceCreated = OnSurfaceCreatedCB;
    int32_t ret = OH_NativeXComponent_RegisterCallback(nativeXComponent, &callback);
    OH_LOG_INFO(LOG_APP, "RegisterCallback ret=%{public}d", ret);
    return exports;
    }


NAPI_MODULE(entry, Init)