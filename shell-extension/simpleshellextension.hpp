#include <ShlObj.h>

class SimpleShellExtension : public IShellFolder {
private:
	long classReferenceCount;
public:
	SimpleShellExtension();
protected:
	~SimpleShellExtension();
public:
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID identifier, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* output);
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE ParseDisplayName(__RPC__in_opt HWND window, __RPC__in_opt IBindCtx* context, __RPC__in_string LPWSTR displayName, _Reserved_ ULONG* pchEaten, __RPC__deref_out_opt PIDLIST_RELATIVE* ppidl, __RPC__inout_opt ULONG* pdwAttributes);
	HRESULT STDMETHODCALLTYPE EnumObjects(__RPC__in_opt HWND window, SHCONTF grfFlags, __RPC__deref_out_opt IEnumIDList** ppenumIDList);
	HRESULT STDMETHODCALLTYPE BindToObject(__RPC__in PCUIDLIST_RELATIVE pidl, __RPC__in_opt IBindCtx* pbc, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppv);
	HRESULT STDMETHODCALLTYPE BindToStorage(__RPC__in PCUIDLIST_RELATIVE pidl, __RPC__in_opt IBindCtx* pbc, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppv);
	HRESULT STDMETHODCALLTYPE CompareIDs(LPARAM lParam, __RPC__in PCUIDLIST_RELATIVE pidl1, __RPC__in PCUIDLIST_RELATIVE pidl2);
	HRESULT STDMETHODCALLTYPE CreateViewObject(__RPC__in_opt HWND window, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppv);
	HRESULT STDMETHODCALLTYPE GetAttributesOf(UINT cidl, __RPC__in_ecount_full_opt(cidl) PCUITEMID_CHILD_ARRAY apidl, __RPC__inout SFGAOF* rgfInOut);
	HRESULT STDMETHODCALLTYPE GetUIObjectOf(__RPC__in_opt HWND window, UINT cidl, __RPC__in_ecount_full_opt(cidl) PCUITEMID_CHILD_ARRAY apidl, __RPC__in REFIID riid, _Reserved_ UINT* rgfReserved, __RPC__deref_out_opt void** ppv);
	HRESULT STDMETHODCALLTYPE GetDisplayNameOf(__RPC__in_opt PCUITEMID_CHILD identifier, SHGDNF flags, __RPC__out STRRET* outputName);
	HRESULT STDMETHODCALLTYPE SetNameOf(_In_opt_ HWND window, _In_ PCUITEMID_CHILD pidl, _In_ LPCWSTR pszName, _In_ SHGDNF uFlags, _Outptr_opt_ PITEMID_CHILD* ppidlOut);
};
