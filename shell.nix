{
  pkgs ? import <nixpkgs> { },
  py ? "313",
}:

let
  name = "imgui-demo";
  xlibs = with pkgs; [
    xorg.libX11
    xorg.libXcursor
    xorg.libXrandr
    xorg.libXi
    xorg.libXinerama
    libGL
    glfw
  ];
in
pkgs.mkShell {

  name = "${name}-env";
  nativeBuildInputs =
    with pkgs;
    [
      zlib
      cmake
      pkgs."python${py}"
      pkgs."python${py}Packages".pip

      libgcc
      clang-tools

      cmake-format
      cmake-lint
      neocmakelsp
      taplo
      vscode-langservers-extracted
      black
      pyright

      nodePackages.nodejs
      emmet-ls
      typescript-language-server
      taplo
      yaml-language-server
      prettierd
      eslint
      mdformat
    ]
    ++ xlibs;

  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath (
    [
      pkgs.stdenv.cc.cc
      pkgs.zlib
    ]
    ++ xlibs
  );

  shellHook = ''
    echo -e "${name} nix-shell activated"
  '';

}
