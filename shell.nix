{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-25.05") {} }:

pkgs.mkShell {
  packages = with pkgs; [
    qmk
  ];
}
