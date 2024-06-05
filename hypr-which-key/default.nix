{
  lib,
  hyprland,
  hyprlandPlugins,
}:
hyprlandPlugins.mkHyprlandPlugin hyprland {
  pluginName = "hypr-which-key";
  version = "0.1";
  src = ./.;

  inherit (hyprland) nativeBuildInputs;

  meta = with lib; {
    homepage = "https://github.com/Moerliy/hypr-which-key";
    description = "Which Key for Hyprland";
    license = licenses.mit;
    platforms = platforms.linux;
  };
}
