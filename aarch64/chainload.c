#include <efi.h>
#include <efilib.h>

#define  BASE_64KB   0x00010000
#define  BASE_32KB   0x00008000

EFI_SYSTEM_TABLE *ST;
EFI_BOOT_SERVICES *BS;

EFI_STATUS Puts(CHAR16 *String)
{
    ST->ConOut->OutputString(ST->ConOut, String);
    return EFI_SUCCESS;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;

    EFI_STATUS Status;
    
    EFI_HANDLE PciControllerHandle; // set to pci controller handle of network card pci option rom
    EFI_PCI_IO_PROTOCOL *PciIo;

    Puts(L"                    #\n");
    Puts(L"                  %%&\n");
    Puts(L"              ,%%%%%%    #,\n");
    Puts(L"            %%%%%%%%%       (\n");
    Puts(L"         *%%%%%%%%%%%\n");
    Puts(L"      #%%%%%%%%%%%@. &%@.        /                           _     __\n");
    Puts(L"    %%%%%%& %%%%%%%% %%%%%%%%%@     (        _______ ___ _  (_)__ / /\n");
    Puts(L" @*%%%%%%%%%%%%%%%%% %&%%%%%%%%%%%%%%@ /    / __/ _ `/  ' \/ / -_) /\n");
    Puts(L"   &@@@&%%%%%%%%%%%% %%%%%%%%%%%%%%%% /    /_/  \_,_/_/_/_/_/\__/_/\n");
    Puts(L"      @@@@@@@@%%%%%% %%%%%%%%%%%%%         ------- seer / 0xwillow\n");
    Puts(L"        %@@@@&@@@@@@ %%%%%%%%%%&/\n");
    Puts(L"           #@@@@@@@@ %%%%%%%%*\n");
    Puts(L"              #@@@&@ %%%%%(\n");
    Puts(L"                 @@@.%%%\n");
    Puts(L"                   #%#\n\n");
    

    Status = BS->OpenProtocol(PciControllerHandle, 
                    &gEfiPciIoProtocolGuid,
                    (void **) &PciIo,
                    ImageHandle,
                    NULL, 
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    Puts(L"<ramiel> [OK] resolved PCI io protocol associated with PciControllerHandle\n");

    EFI_DEVICE_PATH_PROTOCOL *PciDevicePath;
    EFI_DEVICE_PATH_PROTOCOL *PciOptionRomDevicePath;

    Status = BS->OpenProtocol(
                PciControllerHandle,
                &gEfiDevicePathProtocolGuid,
                (void **) &PciDevicePath,
                ImageHandle,
                NULL,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    Puts(L"<ramiel> [OK] resolved device path protocol associated with PciControllerHandle\n");

    // https://edk2-docs.gitbook.io/edk-ii-uefi-driver-writer-s-guide/5_uefi_services/readme.2/524_loadimage_and_startimage
    MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH OptionRomNode;
    OptionRomNode.Header.Type = MEDIA_DEVICE_PATH;
    OptionRomNode.Header.SubType = MEDIA_RELATIVE_OFFSET_RANGE_DP;
    SetDevicePathNodeLength(&OptionRomNode.Header, sizeof(OptionRomNode));

    /* 
        Note: The use of a 32 KB offset and 32 KB length simplifies this example. 
        An addin adapter that stores UEFI Applications in a PCI Option ROM container 
        would likely define vendor specific descriptors to determine the offset and 
        size of one or more UEFI Applications. 
    */
    OptionRomNode.StartingOffset = BASE_32KB;
    OptionRomNode.EndingOffset = BASE_64KB - 1;
    PciOptionRomDevicePath = AppendDevicePathNode (
                            PciDevicePath,
                            &OptionRomNode.Header);

    Puts(L"<ramiel> loading .efi from PCI option ROM ...\n");
    EFI_HANDLE *NewImageHandle;
    Status = BS->LoadImage(FALSE,
                    ImageHandle, 
                    PciOptionRomDevicePath,
                    NULL,
                    0, 
                    &NewImageHandle);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    Puts(L"<ramiel> [OK] loaded\n");

    Status = BS->StartImage(NewImageHandle, NULL, NULL);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    Puts(L"<ramiel> transferring control to loaded .efi...\n");

	return EFI_SUCCESS;
}
