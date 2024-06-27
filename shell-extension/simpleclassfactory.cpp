#include <new>
#include "simpleshellextension.hpp"
#include "simpleclassfactory.hpp"
#include <Shlwapi.h>

extern long globalLibraryReference;

SimpleClassFactory::SimpleClassFactory() {
	this->classReferenceCount = 1;
	InterlockedIncrement(&globalLibraryReference);
}

SimpleClassFactory::~SimpleClassFactory() {
	InterlockedDecrement(&globalLibraryReference);
}

HRESULT STDMETHODCALLTYPE SimpleClassFactory::QueryInterface(REFIID identifier, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* output) {
static const QITAB supportedInterfaces[] = {
		QITABENT(SimpleClassFactory, IClassFactory),
		{0}
	};

	return QISearch(this, supportedInterfaces, identifier, output);
}

ULONG STDMETHODCALLTYPE SimpleClassFactory::AddRef(void) {
	return InterlockedIncrement(&classReferenceCount);
}

ULONG STDMETHODCALLTYPE SimpleClassFactory::Release(void) {
	ULONG referenceCount = InterlockedDecrement(&classReferenceCount);

	if(!referenceCount) {
		delete this;
	}

	return referenceCount;
}

HRESULT STDMETHODCALLTYPE SimpleClassFactory::CreateInstance(_In_opt_ IUnknown* unknown, _In_ REFIID identifier, _COM_Outptr_ void** output) {
	if(!unknown) {
		return CLASS_E_NOAGGREGATION;
	}

	SimpleShellExtension* extension = new SimpleShellExtension();

	if(!extension) {
		return E_OUTOFMEMORY;
	}

	HRESULT result = extension->QueryInterface(identifier, output);
	extension->Release();
	return result;
}

HRESULT STDMETHODCALLTYPE SimpleClassFactory::LockServer(BOOL lock) {
	if(lock) {
		InterlockedIncrement(&globalLibraryReference);
		return S_OK;
	}

	InterlockedDecrement(&globalLibraryReference);
	return S_OK;
}
