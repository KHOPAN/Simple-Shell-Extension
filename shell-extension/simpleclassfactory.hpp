#include <Unknwn.h>

class SimpleClassFactory : public IClassFactory {
private:
	long classReferenceCount;
public:
	SimpleClassFactory();
protected:
	~SimpleClassFactory();
public:
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID identifier, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* output);
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE CreateInstance(_In_opt_ IUnknown* unknown, _In_ REFIID identifier, _COM_Outptr_ void** output);
	HRESULT STDMETHODCALLTYPE LockServer(BOOL lock);
};
