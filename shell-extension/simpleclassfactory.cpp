#include "simpleclassfactory.hpp"
#include <Shlwapi.h>

static const QITAB tabList[] = {
	QITABENT(SimpleClassFactory, IClassFactory),
	{0}
};

extern long globalLibraryReference;

SimpleClassFactory::SimpleClassFactory() {
	this->classReferenceCount = 1;
	InterlockedIncrement(&globalLibraryReference);
}

SimpleClassFactory::~SimpleClassFactory() {
	InterlockedDecrement(&globalLibraryReference);
}

IFACEMETHODIMP SimpleClassFactory::QueryInterface(REFIID identifier, void** output) {
	return QISearch(this, tabList, identifier, output);
}

IFACEMETHODIMP_(ULONG) SimpleClassFactory::AddRef() {
	return InterlockedIncrement(&classReferenceCount);
}

IFACEMETHODIMP_(ULONG) SimpleClassFactory::Release() {
	ULONG reference = InterlockedDecrement(&classReferenceCount);

	if(!reference) {
		delete this;
	}

	return reference;
}

IFACEMETHODIMP SimpleClassFactory::CreateInstance(IUnknown* unknown, REFIID identifier, void** output) {
	if(!unknown) {
		return CLASS_E_NOAGGREGATION;
	}

	return S_OK;
}

IFACEMETHODIMP SimpleClassFactory::LockServer(BOOL lock) {
	if(lock) {
		InterlockedIncrement(&globalLibraryReference);
		return S_OK;
	}

	InterlockedDecrement(&globalLibraryReference);
	return S_OK;
}
