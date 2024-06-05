#include <hyprland/src/plugins/PluginAPI.hpp>

inline HANDLE                          PHANDLE = nullptr;

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    const std::string HASH = __hyprland_api_get_hash();

    // ALWAYS add this to your plugins. It will prevent random crashes coming from
    // mismatched header versions.
    if (HASH != GIT_COMMIT_HASH) {
        HyprlandAPI::addNotification(PHANDLE, "[Hypr-Which-Key] Mismatched headers! Can't proceed.", CColor{1.0, 0.2, 0.2, 1.0}, 5000);
        throw std::runtime_error("[Hypr-Which-key] Version mismatch");
    }

    // ...

    return {"Hypr-Which-Key", "An amazing plugin that is going to change the world!", "Moritz Gleissner, Yusuf Duran", "0.1"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    // ...
}
