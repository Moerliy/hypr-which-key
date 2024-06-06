#define WLR_USE_UNSTABLE

#include <string>
#include <sstream>
#include <optional>

#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/managers/KeybindManager.hpp>

#include "globals.hpp"

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    const std::string HASH = __hyprland_api_get_hash();

    // ALWAYS add this to your plugins. It will prevent random crashes coming from
    // mismatched header versions.
    if (HASH != GIT_COMMIT_HASH) {
        HyprlandAPI::addNotification(PHANDLE, "[hypr-which-key] Mismatched headers! Can't proceed.", CColor{1.0, 0.2, 0.2, 1.0}, 5000);
        throw std::runtime_error("[hypr-which-key] Version mismatch");
    }

    std::ostringstream printStr;
    for (const auto& bind : g_pKeybindManager->m_lKeybinds) {
        printStr << "submap: '" << bind.submap << "' on key: '" << bind.key << "'\n";
    }

    // throw std::runtime_error(printStr.str());

    HyprlandAPI::addNotification(PHANDLE, "[hypr-which-key] Initialized successfully!", CColor{0.2, 1.0, 0.2, 1.0}, 5000);

    return {"hypr-which-key", "An amazing plugin that is going to change the world!", "Moritz Gleissner, Yusuf Duran", "0.1"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    // ...
}
