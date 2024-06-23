#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE instance, DWORD flags, LPVOID reserved) {
	MessageBoxW(NULL, L"DllMain()", L"Simple Shell Extension", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_SYSTEMMODAL);
	return TRUE;
}

_Check_return_ STDAPI DllGetClassObject(_In_ REFCLSID classIdentifier, _In_ REFIID identifier, _Outptr_ LPVOID FAR* output) {
	MessageBoxW(NULL, L"DllGetClassObject()", L"Simple Shell Extension", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_SYSTEMMODAL);

	if(!output) {
		return E_INVALIDARG;
	}

	(*output) = NULL;
	return S_OK;
}

__control_entrypoint(DllExport) STDAPI DllCanUnloadNow(void) {
	MessageBoxW(NULL, L"DllCanUnloadNow()", L"Simple Shell Extension", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_SYSTEMMODAL);
	return S_OK;
}
