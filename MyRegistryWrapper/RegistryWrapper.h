#pragma once
#include <windows.h>
#include <winreg.h>
#include <string>
#include <stdexcept>

class RegistryError : public std::runtime_error
{
public:
    RegistryError(const char* message, LONG errorCode)
        : std::runtime_error{message},
        m_errorCode(errorCode)
    {

    }

    LONG ErrorCode() const noexcept
    {
        return m_errorCode;
    }
private:
    LONG m_errorCode;
};
