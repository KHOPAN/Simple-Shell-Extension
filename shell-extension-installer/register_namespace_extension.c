#include <khopanwin32.h>
#include <khopanstring.h>
#include "installer.h"

BOOL RegisterNamespaceExtension() {
	const LPWSTR namespaceExtensionName = L"Simple Shell Extension";
	LPWSTR pathNamespaceExtension = KHFormatMessageW(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", CLSID_SimpleShellExtension.Data1, CLSID_SimpleShellExtension.Data2, CLSID_SimpleShellExtension.Data3, CLSID_SimpleShellExtension.Data4[0], CLSID_SimpleShellExtension.Data4[1], CLSID_SimpleShellExtension.Data4[2], CLSID_SimpleShellExtension.Data4[3], CLSID_SimpleShellExtension.Data4[4], CLSID_SimpleShellExtension.Data4[5], CLSID_SimpleShellExtension.Data4[6], CLSID_SimpleShellExtension.Data4[7]);

	if(!pathNamespaceExtension) {
		KHWin32ConsoleErrorW(ERROR_FUNCTION_FAILED, L"KHFormatMessageW");
		return FALSE;
	}

	HKEY keyNamespaceExtension;
	LSTATUS error = RegCreateKeyExW(HKEY_LOCAL_MACHINE, pathNamespaceExtension, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &keyNamespaceExtension, NULL);
	LocalFree(pathNamespaceExtension);
	
	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		return FALSE;
	}

	error = RegSetValueExW(keyNamespaceExtension, NULL, 0, REG_SZ, (const BYTE*) namespaceExtensionName, (DWORD) ((wcslen(namespaceExtensionName) + 1) * sizeof(WCHAR)));
	RegCloseKey(keyNamespaceExtension);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegSetValueExW");
		return FALSE;
	}

	return TRUE;
}
