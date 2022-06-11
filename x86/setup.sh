# adapted from: https://wiki.osdev.org/UEFI_Bare_Bones

sudo apt-get install qemu ovmf binutils-mingw-w64 gcc-mingw-w64 xorriso mtools
# get ovmf firmware
cp /usr/share/ovmf/OVMF.fd OVMF.fd

# wget -qO- https://jaist.dl.sourceforge.net/project/gnu-efi/gnu-efi-3.0.8.tar.bz2 | tar -xjvf -
git clone https://git.code.sf.net/p/gnu-efi/code gnu-efi
cd gnu-efi
make
cd ..
sed -i 's/LibStubStriCmp/NULL/g' gnu-efi/lib/data.c
sed -i 's/LibStubMetaiMatch/NULL/g' gnu-efi/lib/data.c
sed -i 's/LibStubStrLwrUpr/NULL/g' gnu-efi/lib/data.c
# outdated
# cp gnu-efi/lib/lib.h lib.h