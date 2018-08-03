#pragma once

// C/C++ standard headers
#include <string>

// Other external headers
// Windows headers
#include <tchar.h>

// Original headers


////////////////////////////////////////////////////////////////////////////////
//
// macro utilities
//


////////////////////////////////////////////////////////////////////////////////
//
// constants and macros
//


////////////////////////////////////////////////////////////////////////////////
//
// types
//


////////////////////////////////////////////////////////////////////////////////
//
// prototypes
//

bool IsServiceInstalled(
    __in const std::basic_string<TCHAR>& ServiceName);

bool LoadDriver(
    __in const std::basic_string<TCHAR>& ServiceName,
    __in const std::basic_string<TCHAR>& DriverFile);

bool UnloadDriver(
    __in const std::basic_string<TCHAR>& ServiceName);


////////////////////////////////////////////////////////////////////////////////
//
// variables
//


////////////////////////////////////////////////////////////////////////////////
//
// implementations
//

