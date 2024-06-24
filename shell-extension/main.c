#include "extension.h"

static HINSTANCE globalInstance;

// {E761549A-5209-4183-88CA-D587FCD89393}
EXTERN_GUID(CLSID_SimpleShellExtension, 0xE761549A, 0x5209, 0x4183, 0x88, 0xCA, 0xD5, 0x87, 0xFC, 0xD8, 0x93, 0x93);

BOOL WINAPI DllMain(HINSTANCE instance, DWORD flags, LPVOID reserved) {
	switch(flags) {
	case DLL_PROCESS_ATTACH:
		globalInstance = instance;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

HINSTANCE GetProgramInstance() {
	return globalInstance;
}
