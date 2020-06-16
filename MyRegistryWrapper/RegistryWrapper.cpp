#include "RegistryWrapper.h"


DWORD RegGetDword(
    HKEY hKey,
    const std::wstring& subKey,
    const std::wstring& value
)
{
    DWORD data{};
    DWORD dataSize = sizeof(data);
    LONG retCode = ::RegGetValue(
        hKey,
        subKey.c_str(),
        value.c_str(),
        RRF_RT_REG_DWORD,
        nullptr,
        &data,
        &dataSize
    );
    if (retCode != ERROR_SUCCESS)
    {
        throw RegistryError{ "Cannot read DWORD from registry.", retCode };
    }
    return data;
}