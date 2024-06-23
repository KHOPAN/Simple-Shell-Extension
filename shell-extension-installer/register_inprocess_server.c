#include <khopanwin32.h>
#include <khopanstring.h>
#include "installer.h"

BOOL RegisterInProcessServer() {
	const LPWSTR pathFileShellExtension = L"D:\\GitHub Repository\\Simple-Shell-Extension\\x64\\Debug\\shell-extension.dll";
	const LPWSTR valueThreadingModel = L"Apartment";
	LPWSTR pathRegistryRoot = KHFormatMessageW(L"CLSID\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", CLSID_SIMPLE_SHELL_EXTENSION.Data1, CLSID_SIMPLE_SHELL_EXTENSION.Data2, CLSID_SIMPLE_SHELL_EXTENSION.Data3, CLSID_SIMPLE_SHELL_EXTENSION.Data4[0], CLSID_SIMPLE_SHELL_EXTENSION.Data4[1], CLSID_SIMPLE_SHELL_EXTENSION.Data4[2], CLSID_SIMPLE_SHELL_EXTENSION.Data4[3], CLSID_SIMPLE_SHELL_EXTENSION.Data4[4], CLSID_SIMPLE_SHELL_EXTENSION.Data4[5], CLSID_SIMPLE_SHELL_EXTENSION.Data4[6], CLSID_SIMPLE_SHELL_EXTENSION.Data4[7]);

	if(!pathRegistryRoot) {
		KHWin32ConsoleErrorW(ERROR_FUNCTION_FAILED, L"KHFormatMessageW");
		return FALSE;
	}

	HKEY keyRoot;
	LSTATUS error = RegCreateKeyExW(HKEY_CLASSES_ROOT, pathRegistryRoot, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY, NULL, &keyRoot, NULL);
	LocalFree(pathRegistryRoot);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		return FALSE;
	}

	HKEY keyServer;
	error = RegCreateKeyExW(keyRoot, L"InprocServer32", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &keyServer, NULL);
	RegCloseKey(keyRoot);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		return FALSE;
	}

	error = RegSetValueExW(keyServer, NULL, 0, REG_SZ, (const BYTE*) pathFileShellExtension, (DWORD) ((wcslen(pathFileShellExtension) + 1) * sizeof(WCHAR)));

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegSetValueExW");
		RegCloseKey(keyServer);
		return FALSE;
	}

	error = RegSetValueExW(keyServer, L"ThreadingModel", 0, REG_SZ, (const BYTE*) valueThreadingModel, (DWORD) ((wcslen(valueThreadingModel) + 1) * sizeof(WCHAR)));
	RegCloseKey(keyServer);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegSetValueExW");
		return FALSE;
	}

	return TRUE;
}
