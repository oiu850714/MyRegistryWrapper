#include "RegistryWrapper.h"
#include <cwchar>

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

ULONGLONG RegGetQword(
    HKEY hKey,
    const std::wstring& subKey,
    const std::wstring& value
)
{
    ULONGLONG data{};
    DWORD dataSize = sizeof(data);
    LONG retCode = ::RegGetValue(
        hKey,
        subKey.c_str(),
        value.c_str(),
        RRF_RT_REG_QWORD,
        nullptr,
        &data,
        &dataSize
    );
    if (retCode != ERROR_SUCCESS)
    {
        throw RegistryError{ "Cannot read QWORD from registry.", retCode };
    }
    return data;
}

std::wstring RegGetString(
    HKEY hKey,
    const std::wstring& subKey,
    const std::wstring& value
)
{
    DWORD dataSize{};
    LONG retCode = ::RegGetValue(
        hKey,
        subKey.c_str(),
        value.c_str(),
        RRF_RT_REG_SZ,
        nullptr,
        nullptr,
        &dataSize
    );

    if (retCode != ERROR_SUCCESS)
    {
        throw  RegistryError{ "Cannot read string from registry.", retCode };
    }

    std::wstring data;
    data.resize(dataSize / sizeof(wchar_t));

    retCode = ::RegGetValue(
        hKey,
        subKey.c_str(),
        value.c_str(),
        RRF_RT_REG_SZ,
        nullptr,
        &data[0],
        &dataSize
    );

    if (retCode != ERROR_SUCCESS)
    {
        throw  RegistryError{ "Cannot read string from registry.", retCode };
    }

    DWORD wstringDataSize = dataSize / sizeof(wchar_t);
    wstringDataSize--;
    data.resize(wstringDataSize);

    return data;
}

std::vector<std::wstring> RegGetMultiString(
    HKEY hKey,
    const std::wstring& subKey,
    const std::wstring& value
)
{
    DWORD dataSize{};
    LONG retCode = ::RegGetValue(
        hKey,
        subKey.c_str(),
        value.c_str(),
        RRF_RT_REG_MULTI_SZ,
        nullptr,
        nullptr,
        &dataSize
    );

    if (retCode != ERROR_SUCCESS)
    {
        throw  RegistryError{ "Cannot read string from registry.", retCode };
    }

    std::vector<wchar_t> data;
    data.resize(dataSize / sizeof(wchar_t));

    retCode = ::RegGetValue(
        hKey,
        subKey.c_str(),
        value.c_str(),
        RRF_RT_REG_MULTI_SZ,
        nullptr,
        &data[0],
        &dataSize
    );

    if (retCode != ERROR_SUCCESS)
    {
        throw  RegistryError{ "Cannot read string from registry.", retCode };
    }

    DWORD wstringDataSize = dataSize / sizeof(wchar_t);
    data.resize(wstringDataSize);

    std::vector<std::wstring> result;
    wchar_t *currStringPtr = data.data();
    while (*currStringPtr != L'\0') {
        const size_t currStringLength = ::wcslen(currStringPtr);
        result.push_back(std::wstring{ currStringPtr, currStringPtr + currStringLength });
        currStringPtr += currStringLength + 1;
    }
    return result;
}