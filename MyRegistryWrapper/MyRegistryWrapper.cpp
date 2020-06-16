#include <windows.h>
#include "RegistryWrapper.h"

#include <string>
#include <iostream>

int main()
{
    std::wstring testSubkey = L"Name\\Your\\Subkey";
    std::wstring testDwordValue = L"NameYourValue";
    std::wstring testQwordValue = L"NameYourValue";
    std::wstring testStringValue = L"NameYourValue";

    try
    {
        DWORD dwordData = RegGetDword(HKEY_CURRENT_USER, testSubkey, testDwordValue);
        std::wcout << testSubkey << L"\\" << testDwordValue << L" DWORD data: " << dwordData << std::endl;

        ULONGLONG qwordData = RegGetQword(HKEY_CURRENT_USER, testSubkey, testQwordValue);
        std::wcout << testSubkey << L"\\" << testQwordValue << L" QWORD data: " << qwordData << std::endl;

        std::wstring stringData = RegGetString(HKEY_CURRENT_USER, testSubkey, testStringValue);
        std::wcout << testSubkey << L"\\" << testStringValue << L" string data: " << stringData << std::endl;
    }
    catch (const RegistryError& e) {
        std::cerr << "error: " << e.ErrorCode() << std::endl;
    }
}
