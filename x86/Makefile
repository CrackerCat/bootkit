CFLAGS='-target x86_64-unknown-windows 
        -ffreestanding 
        -fshort-wchar 
        -mno-red-zone 
        -Ignu-efi-3.0.8/inc -Ignu-efi-3.0.8/inc/x86_64 -Ignu-efi-3.0.8/inc/protocol'
LDFLAGS='-target x86_64-unknown-windows 
        -nostdlib 
        -Wl,-entry:efi_main 
        -Wl,-subsystem:efi_application 
        -fuse-ld=lld-link'
clang $CFLAGS -c -o hello.o hello.c
clang $CFLAGS -c -o data.o gnu-efi-3.0.8/lib/data.c
clang $LDFLAGS -o main.efi hello.o data.o