#include <stdio.h>
#include <khopanwin32.h>
#include <khopanstring.h>

// {E761549A-5209-4183-88CA-D587FCD89393}
EXTERN_GUID(CLSID_SIMPLE_SHELL_EXTENSION, 0xE761549A, 0x5209, 0x4183, 0x88, 0xCA, 0xD5, 0x87, 0xFC, 0xD8, 0x93, 0x93);

int main(int argc, char** argv) {
	const LPWSTR pathFileShellExtension = L"D:\\GitHub Repository\\Simple-Shell-Extension\\x64\\Debug\\shell-extension.dll";
	const LPWSTR valueThreadingModel = L"Apartment";
	LPWSTR pathRegistryRoot = KHFormatMessageW(L"CLSID\\{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", CLSID_SIMPLE_SHELL_EXTENSION.Data1, CLSID_SIMPLE_SHELL_EXTENSION.Data2, CLSID_SIMPLE_SHELL_EXTENSION.Data3, CLSID_SIMPLE_SHELL_EXTENSION.Data4[0], CLSID_SIMPLE_SHELL_EXTENSION.Data4[1], CLSID_SIMPLE_SHELL_EXTENSION.Data4[2], CLSID_SIMPLE_SHELL_EXTENSION.Data4[3], CLSID_SIMPLE_SHELL_EXTENSION.Data4[4], CLSID_SIMPLE_SHELL_EXTENSION.Data4[5], CLSID_SIMPLE_SHELL_EXTENSION.Data4[6], CLSID_SIMPLE_SHELL_EXTENSION.Data4[7]);

	if(!pathRegistryRoot) {
		KHWin32ConsoleErrorW(ERROR_FUNCTION_FAILED, L"KHFormatMessageW");
		return 1;
	}

	HKEY keyRoot;
	LSTATUS error = RegCreateKeyExW(HKEY_CLASSES_ROOT, pathRegistryRoot, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY, NULL, &keyRoot, NULL);
	LocalFree(pathRegistryRoot);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		return 1;
	}

	HKEY keyServer;
	error = RegCreateKeyExW(keyRoot, L"InprocServer32", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &keyServer, NULL);
	RegCloseKey(keyRoot);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegCreateKeyExW");
		return 1;
	}

	error = RegSetValueExW(keyServer, NULL, 0, REG_SZ, (const BYTE*) pathFileShellExtension, (DWORD) ((wcslen(pathFileShellExtension) + 1) * sizeof(WCHAR)));

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegSetValueExW");
		RegCloseKey(keyServer);
		return 1;
	}

	error = RegSetValueExW(keyServer, L"ThreadingModel", 0, REG_SZ, (const BYTE*) valueThreadingModel, (DWORD) ((wcslen(valueThreadingModel) + 1) * sizeof(WCHAR)));
	RegCloseKey(keyServer);

	if(error) {
		KHWin32ConsoleErrorW(error, L"RegSetValueExW");
		return 1;
	}

	printf("Installation finished\n");
	return 0;
}
