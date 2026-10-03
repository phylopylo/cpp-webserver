{
  inputs = {
    nixpkgs.url = "github:cachix/devenv-nixpkgs/rolling";
    devenv.url = "github:cachix/devenv";
  };

  nixConfig = {
    extra-trusted-public-keys = "devenv.cachix.org-1:w1cLUi8dv3hnoSPGAuibQv+f9TZLr6cv/Hm9XgU50cw=";
    extra-substituters = "https://devenv.cachix.org";
  };

  outputs = { nixpkgs, devenv, ... } @ inputs:
    let
      systems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAll = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
      pythonEnv = pkgs: pkgs.python3.withPackages (ps: [ ps.fastapi ps.uvicorn ]);
    in {
      # nix run  ->  serves the app on http://127.0.0.1:8000
      # extra args are passed to uvicorn, e.g. nix run . -- --workers 4
      apps = forAll (pkgs: {
        default = {
          type = "app";
          program = "${pkgs.writeShellScript "api" ''
            exec ${pythonEnv pkgs}/bin/uvicorn main:app --app-dir ${./.} --port 8000 "$@"
          ''}";
        };
      });

      devShells = forAll (pkgs: {
        default = devenv.lib.mkShell {
          inherit inputs pkgs;
          modules = [
            ({ pkgs, ... }: {
              packages = [ (pythonEnv pkgs) pkgs.wrk ];
            })
          ];
        };
      });
    };
}
