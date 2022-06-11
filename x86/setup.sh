# adapted from: https://wiki.osdev.org/UEFI_Bare_Bones

sudo apt-get install qemu ovmf gnu-efi binutils-mingw-w64 gcc-mingw-w64 xorriso mtools
mkdir $HOME/uefi_out
# get ovmf firmware
cp /usr/share/ovmf/OVMF.fd OVMF.fd

wget -qO- https://jaist.dl.sourceforge.net/project/gnu-efi/gnu-efi-3.0.8.tar.bz2 | tar -xjvf -
sed -i 's/LibStubStriCmp/NULL/g' gnu-efi-3.0.8/lib/data.c
sed -i 's/LibStubMetaiMatch/NULL/g' gnu-efi-3.0.8/lib/data.c
sed -i 's/LibStubStrLwrUpr/NULL/g' gnu-efi-3.0.8/lib/data.c
cp gnu-efi-3.0.8/lib/lib.h lib.h