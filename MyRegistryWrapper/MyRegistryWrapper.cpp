#include <windows.h>
#include "RegistryWrapper.h"

#include <string>
#include <iostream>

int main()
{
    std::wstring testSubkey = L"Name\\Your\\Subkey";
    std::wstring testValue = L"NameYourValue";

    try
    {
        DWORD data = RegGetDword(HKEY_CURRENT_USER, testSubkey, testValue);
        std::wcout << testSubkey << L"\\" << testValue << L" DWORD data: " << data << std::endl;
    }
    catch (const RegistryError& e) {
        std::cerr << "error: " << e.ErrorCode() << std::endl;
    }
}
