#include "extension.h"
#include <Shlwapi.h>
#include "factory.hpp"

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
	return S_OK;
}
