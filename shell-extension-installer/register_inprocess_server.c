#include <khopanwin32.h>
#include <khopanstring.h>
#include "installer.h"

BOOL RegisterInProcessServer() {
	LPWSTR pathExtensionRoot = KHFormatMessageW(L"CLSID\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", CLSID_SimpleShellExtension.Data1, CLSID_SimpleShellExtension.Data2, CLSID_SimpleShellExtension.Data3, CLSID_SimpleShellExtension.Data4[0], CLSID_SimpleShellExtension.Data4[1], CLSID_SimpleShellExtension.Data4[2], CLSID_SimpleShellExtension.Data4[3], CLSID_SimpleShellExtension.Data4[4], CLSID_SimpleShellExtension.Data4[5], CLSID_SimpleShellExtension.Data4[6], CLSID_SimpleShellExtension.Data4[7]);

	if(!pathExtensionRoot) {
		KHWin32ConsoleErrorW(ERROR_FUNCTION_FAILED, L"KHFormatMessageW");
		return FALSE;
	}

	HKEY keyExtensionRoot;
	LSTATUS error = RegCreateKeyExW(HKEY_CLASSES_ROOT, pathExtensionRoot, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY, NULL, &keyExtensionRoot, NULL);
	LocalFree(pathExtensionRoot);
	BOOL returnValue = FALSE;

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		goto closeKeyExtensionRoot;
	}

	HKEY keyInProcServer32;
	error = RegCreateKeyExW(keyExtensionRoot, L"InProcServer32", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &keyInProcServer32, NULL);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		goto closeKeyExtensionRoot;
	}

	if(!KHWin32RegistrySetStringValueW(keyInProcServer32, NULL, L"D:\\GitHub Repository\\Simple-Shell-Extension\\x64\\Debug\\shell-extension.dll")) {
		KHWin32ConsoleErrorW(GetLastError(), L"KHWin32RegistrySetStringValueW");
		RegCloseKey(keyInProcServer32);
		goto closeKeyExtensionRoot;
	}

	if(!KHWin32RegistrySetStringValueW(keyInProcServer32, L"ThreadingModel", L"Apartment")) {
		KHWin32ConsoleErrorW(GetLastError(), L"KHWin32RegistrySetStringValueW");
		RegCloseKey(keyInProcServer32);
		goto closeKeyExtensionRoot;
	}

	returnValue = TRUE;
closeKeyExtensionRoot:
	RegCloseKey(keyExtensionRoot);
	return returnValue;
}
