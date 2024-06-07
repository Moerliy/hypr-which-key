#define WLR_USE_UNSTABLE

#include <string>
#include <sstream>
#include <optional>

#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/managers/KeybindManager.hpp>
#include <hyprland/src/config/ConfigManager.hpp>

#include "globals.hpp"

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

static void onSubmap(void* self, std::any data) {
    // data is guaranteed
    const auto submap = std::any_cast<std::string>(data);

    HyprlandAPI::addNotification(PHANDLE, "[hypr-which-key] changed submap to " + submap + " !", CColor{0.2, 1.0, 0.2, 1.0}, 5000);
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

    const auto&        COMMAND    = "bind";
    const auto&        VALUE      = "SUPER, V, \"Test\", exec, kitty";
    const auto&        keybindRet = g_pConfigManager->handleBind(COMMAND, VALUE);

    std::ostringstream printStr;
    for (const auto& bind : g_pKeybindManager->m_lKeybinds) {
        if (bind.submap != "") {
            continue;
        }
        printStr << "submap: '" << bind.submap << "' on key: '" << bind.key << "', arg: '" << bind.arg << "', handler: '" << bind.handler << "', desc: '" << bind.description
                 << "'\n";
    }
    static auto P = HyprlandAPI::registerCallbackDynamic(PHANDLE, "submap", [&](void* self, SCallbackInfo& info, std::any data) { onSubmap(self, data); });
    // throw std::runtime_error(printStr.str());

    HyprlandAPI::addNotification(PHANDLE, "[hypr-which-key] Initialized successfully!", CColor{0.2, 1.0, 0.2, 1.0}, 5000);

    return {"hypr-which-key", "An amazing plugin that is going to change the world!", "Moritz Gleissner, Yusuf Duran", "0.1"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    // ...
}
