#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE instance, DWORD flags, LPVOID reserved) {
	return TRUE;
}

_Check_return_ STDAPI DllGetClassObject(_In_ REFCLSID classIdentifier, _In_ REFIID identifier, _Outptr_ LPVOID FAR* output) {
	if(!output) {
		return E_INVALIDARG;
	}

	(*output) = NULL;
	return S_OK;
}

__control_entrypoint(DllExport) STDAPI DllCanUnloadNow(void) {
	return S_OK;
}
