#include <khopanwin32.h>
#include <khopanstring.h>
#include "installer.h"

BOOL RegisterContextMenuHandler() {
	LPWSTR valueContextMenuHandler = KHFormatMessageW(L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", CLSID_SimpleShellExtension.Data1, CLSID_SimpleShellExtension.Data2, CLSID_SimpleShellExtension.Data3, CLSID_SimpleShellExtension.Data4[0], CLSID_SimpleShellExtension.Data4[1], CLSID_SimpleShellExtension.Data4[2], CLSID_SimpleShellExtension.Data4[3], CLSID_SimpleShellExtension.Data4[4], CLSID_SimpleShellExtension.Data4[5], CLSID_SimpleShellExtension.Data4[6], CLSID_SimpleShellExtension.Data4[7]);

	if(!valueContextMenuHandler) {
		KHWin32ConsoleErrorW(ERROR_FUNCTION_FAILED, L"KHFormatMessageW");
		return FALSE;
	}

	HKEY keyContextMenuHandler;
	LSTATUS error = RegCreateKeyExW(HKEY_CLASSES_ROOT, L"*\\ShellEx\\ContextMenuHandlers\\SimpleShellExtension", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &keyContextMenuHandler, NULL);
	
	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		LocalFree(valueContextMenuHandler);
		return FALSE;
	}

	error = RegSetValueExW(keyContextMenuHandler, NULL, 0, REG_SZ, (const BYTE*) valueContextMenuHandler, (DWORD) ((wcslen(valueContextMenuHandler) + 1) * sizeof(WCHAR)));
	LocalFree(valueContextMenuHandler);
	RegCloseKey(keyContextMenuHandler);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegSetValueExW");
		return FALSE;
	}

	return TRUE;
}
