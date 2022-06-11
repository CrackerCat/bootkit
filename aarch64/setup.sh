#!/bin/sh

# adapted from https://github.com/tnishinaga/aarch64-uefi-llvm_helloworld
# https://krinkinmu.github.io/2020/11/21/EFI-aarch64.html
# https://wiki.osdev.org/UEFI

sudo apt-get install qemu-efi-aarch64
cp /usr/share/qemu-efi-aarch64/QEMU_EFI.fd OVMF_aarch64.fd
mkdir -p $HOME/opt/llvm/aarch64-none-eabi
wget -qO- https://jaist.dl.sourceforge.net/project/gnu-efi/gnu-efi-3.0.8.tar.bz2 | tar -xjvf -
# git clone https://git.code.sf.net/p/gnu-efi/code gnu-efi
# cd gnu-efi
# make
# cd ..
sed -i 's/LibStubStriCmp/NULL/g' gnu-efi-3.0.8/lib/data.c
sed -i 's/LibStubMetaiMatch/NULL/g' gnu-efi-3.0.8/lib/data.c
sed -i 's/LibStubStrLwrUpr/NULL/g' gnu-efi-3.0.8/lib/data.c
cp gnu-efi-3.0.8/lib/lib.h lib.h
cd gnu-efi-3.0.8/inc
make PREFIX=$HOME/opt/llvm/aarch64-none-eabi ARCH=aarch64 install