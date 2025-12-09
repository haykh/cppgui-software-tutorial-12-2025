{
  pkgs ? import <nixpkgs> { },
  py ? "313",
}:

let
  name = "imgui-demo";
in
pkgs.mkShell {

  name = "${name}-env";
  nativeBuildInputs = with pkgs; [
    zlib
    cmake
    pkgs."python${py}"
    pkgs."python${py}Packages".pip

    libgcc
    clang-tools
    glfw

    cmake-format
    cmake-lint
    neocmakelsp
    taplo
    vscode-langservers-extracted
    black
    pyright
  ];

  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath ([
    pkgs.stdenv.cc.cc
    pkgs.zlib
  ]);

  shellHook = ''
    BLUE='\033[0;34m'
    NC='\033[0m'

    echo -e "${name} nix-shell activated"
  '';

}
