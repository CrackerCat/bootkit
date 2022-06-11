#include <efi.h>

EFI_SYSTEM_TABLE *ST;
EFI_BOOT_SERVICES *BS;

EFI_STATUS Puts(CHAR16 *String)
{
    ST->ConOut->OutputString(ST->ConOut, String);
    return EFI_SUCCESS;
}


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;

    ST = SystemTable;
    BS = SystemTable->BootServices;

    Puts(L"<ramiel> loading kernel EFI STUB...\n");
    EFI_HANDLE *LoadedImageHandle;
    BS->LoadImage(FALSE, ImageHandle, , NULL, 0, &LoadedImageHandle);
    Puts(L"<ramiel> transferring control to kernel EFI STUB...\n");


	return EFI_SUCCESS;
}
