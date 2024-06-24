#include <Unknwn.h>

class SimpleClassFactory : public IClassFactory {
private:
	long referenceCount;
public:
	SimpleClassFactory();
	IFACEMETHODIMP QueryInterface(REFIID identifier, void** output);
	IFACEMETHODIMP_(ULONG) AddRef();
	IFACEMETHODIMP_(ULONG) Release();
	IFACEMETHODIMP CreateInstance(IUnknown* unknown, REFIID identifier, void** output);
	IFACEMETHODIMP LockServer(BOOL lock);
};
