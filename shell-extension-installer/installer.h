#pragma once

#include <Windows.h>

// {E761549A-5209-4183-88CA-D587FCD89393}
DEFINE_GUID(CLSID_SIMPLE_SHELL_EXTENSION, 0xE761549A, 0x5209, 0x4183, 0x88, 0xCA, 0xD5, 0x87, 0xFC, 0xD8, 0x93, 0x93);

BOOL RegisterInProcessServer();
BOOL RegisterContextMenuHandler();
