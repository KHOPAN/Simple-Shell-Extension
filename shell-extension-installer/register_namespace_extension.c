#include <khopanwin32.h>
#include <khopanstring.h>
#include "installer.h"

BOOL RegisterNamespaceExtension() {
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

	BOOL result = KHWin32RegistrySetStringValueW(keyNamespaceExtension, NULL, L"Simple Shell Extension");
	RegCloseKey(keyNamespaceExtension);

	if(!result) {
		KHWin32ConsoleErrorW(GetLastError(), L"KHWin32RegistrySetStringValueW");
		return FALSE;
	}

	HKEY keyApproved;
	error = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &keyApproved, NULL);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		return FALSE;
	}

	LPWSTR approvedKeyName = KHFormatMessageW(L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", CLSID_SimpleShellExtension.Data1, CLSID_SimpleShellExtension.Data2, CLSID_SimpleShellExtension.Data3, CLSID_SimpleShellExtension.Data4[0], CLSID_SimpleShellExtension.Data4[1], CLSID_SimpleShellExtension.Data4[2], CLSID_SimpleShellExtension.Data4[3], CLSID_SimpleShellExtension.Data4[4], CLSID_SimpleShellExtension.Data4[5], CLSID_SimpleShellExtension.Data4[6], CLSID_SimpleShellExtension.Data4[7]);

	if(!approvedKeyName) {
		KHWin32ConsoleErrorW(ERROR_FUNCTION_FAILED, L"KHFormatMessageW");
		RegCloseKey(keyApproved);
		return FALSE;
	}

	result = KHWin32RegistrySetStringValueW(keyNamespaceExtension, approvedKeyName, L"Simple Shell Extension");
	LocalFree(approvedKeyName);
	RegCloseKey(keyApproved);

	if(!result) {
		KHWin32ConsoleErrorW(GetLastError(), L"KHWin32RegistrySetStringValueW");
		return FALSE;
	}

	return TRUE;
}
