#include "factory.hpp"
#include <Shlwapi.h>

static const QITAB tabList[] = {
	QITABENT(SimpleClassFactory, IClassFactory),
	{0}
};

SimpleClassFactory::SimpleClassFactory() {
	this->referenceCount = 1;
}

IFACEMETHODIMP SimpleClassFactory::QueryInterface(REFIID identifier, void** output) {
	return QISearch(this, tabList, identifier, output);
}

IFACEMETHODIMP_(ULONG) SimpleClassFactory::AddRef() {
	return InterlockedIncrement(&referenceCount);
}

IFACEMETHODIMP_(ULONG) SimpleClassFactory::Release() {
	ULONG reference = InterlockedDecrement(&referenceCount);

	if(!reference) {
		delete this;
	}

	return reference;
}

IFACEMETHODIMP SimpleClassFactory::CreateInstance(IUnknown* unknown, REFIID identifier, void** output) {
	return S_OK;
}

IFACEMETHODIMP SimpleClassFactory::LockServer(BOOL lock) {
	return S_OK;
}
