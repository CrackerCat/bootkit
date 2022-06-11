#!/bin/bash

# adapted from https://wiki.osdev.org/UEFI

make \
&& dd if=/dev/zero of=main.img bs=512 count=93750 \
&& parted main.img -s -a minimal mklabel gpt \
&& parted main.img -s -a minimal mkpart EFI FAT16 2048s 93716s \
&& parted main.img -s -a minimal toggle 1 boot \
&& dd if=/dev/zero of=/tmp/part.img bs=512 count=91669 \
&& mformat -i /tmp/part.img -h 32 -t 32 -n 64 -c 1 \
&& mcopy -i /tmp/part.img main.efi :: \
&& dd if=/tmp/part.img of=main.img bs=512 count=91669 seek=2048 conv=notrunc \
&& qemu-system-aarch64 -machine virt -cpu max \
    -bios OVMF_aarch64.fd \
    -drive format=raw,file=main.img \
    -net none \
    -nographic
