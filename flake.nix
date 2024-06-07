{
  description = "hypr-which-key";

  inputs = {
    hyprland.url = "git+https://github.com/Moerliy/Hyprland?submodules=1";
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
        hypr-which-key = callPackage ./hypr-which-key {};
      };
    };

    checks = eachSystem (system: self.packages.${system});

    devShells = eachSystem (system:
      with pkgsFor.${system}; {
        default = mkShell.override {stdenv = gcc13Stdenv;} {
          name = "hypr-which-key";
          buildInputs = [hyprland.packages.${system}.hyprland];
          inputsFrom = [
            hyprland.packages.${system}.hyprland
            # self.packages.${system}.hypr-which-key
          ];
        };
        programs.hyprland = {
          enable = true; 
          package = (hyprland.packages.${system}.hyprland.override { debug = true; });
        };
      });
  };
}
