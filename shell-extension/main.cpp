#include <Shlwapi.h>
#include "simpleclassfactory.hpp"

// {E761549A-5209-4183-88CA-D587FCD89393}
EXTERN_GUID(CLSID_SimpleShellExtension, 0xE761549A, 0x5209, 0x4183, 0x88, 0xCA, 0xD5, 0x87, 0xFC, 0xD8, 0x93, 0x93);

HINSTANCE globalInstance = NULL;
long globalLibraryReference = 0;

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

_Check_return_ STDAPI DllGetClassObject(_In_ REFCLSID classIdentifier, _In_ REFIID identifier, _Outptr_ LPVOID FAR* output) {
	if(!IsEqualCLSID(CLSID_SimpleShellExtension, classIdentifier)) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	SimpleClassFactory* factory = new SimpleClassFactory();

	if(!factory) {
		return E_OUTOFMEMORY;
	}

	HRESULT result = factory->QueryInterface(identifier, output);
	factory->Release();
	return result;
}

__control_entrypoint(DllExport) STDAPI DllCanUnloadNow(void) {
	return globalLibraryReference > 0 ? S_FALSE : S_OK;
}
