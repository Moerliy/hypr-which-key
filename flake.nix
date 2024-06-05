{
  description = "hypr-which-key";

  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    systems.follows = "hyprland/systems";
  };

  outputs = {
    self,
    hyprland,
    systems,
    ...
  }: let
    inherit (hyprland.inputs) nixpkgs;
    inherit (nixpkgs) lib;
    eachSystem = lib.genAttrs (import systems);

    pkgsFor = eachSystem (system:
      import nixpkgs {
        localSystem.system = system;
        overlays = [
          self.overlays.hyprland-plugins
          hyprland.overlays.hyprland-packages
        ];
      });
  in {
    packages = eachSystem (system: {
      inherit
        (pkgsFor.${system})
        hypr-which-key
        ;
    });

    overlays = {
      default = self.overlays.hyprland-plugins;

      hyprland-plugins = final: prev: let
        inherit (final) callPackage;
      in {
        hypr-whcih-key = callPackage ./hypr-which-key.nix {};
      };
    };

    checks = eachSystem (system: self.packages.${system});

    devShells = eachSystem (system:
      with pkgsFor.${system}; {
        default = mkShell.override {stdenv = gcc13Stdenv;} {
          shellHook = ''
            meson setup build --reconfigure
            sed -e 's/c++23/c++2b/g' ./build/compile_commands.json > ./compile_commands.json
          '';
          name = "hypr-which-key";
          buildInputs = [hyprland.packages.${system}.hyprland];
          inputsFrom = [
            hyprland.packages.${system}.hyprland
            self.packages.${system}.hypr-which-key
          ];
        };
      });
  };
}
