#include "simpleshellextension.hpp"
#include <Shlwapi.h>

extern long globalLibraryReference;

SimpleShellExtension::SimpleShellExtension() {
	this->classReferenceCount = 1;
	InterlockedIncrement(&globalLibraryReference);
}

SimpleShellExtension::~SimpleShellExtension() {
	InterlockedDecrement(&globalLibraryReference);
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::QueryInterface(REFIID identifier, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* output) {
	static const QITAB supportedInterfaces[] = {
		QITABENT(SimpleShellExtension, IShellExtInit),
		QITABENT(SimpleShellExtension, IShellFolder),
		{0}
	};

	return QISearch(this, supportedInterfaces, identifier, output);
}

ULONG STDMETHODCALLTYPE SimpleShellExtension::AddRef(void) {
	return InterlockedIncrement(&classReferenceCount);
}

ULONG STDMETHODCALLTYPE SimpleShellExtension::Release(void) {
	ULONG referenceCount = InterlockedDecrement(&classReferenceCount);

	if(!referenceCount) {
		delete this;
	}

	return referenceCount;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::Initialize(_In_opt_ PCIDLIST_ABSOLUTE itemList, _In_opt_ IDataObject* object, _In_opt_ HKEY key) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::ParseDisplayName(__RPC__in_opt HWND window, __RPC__in_opt IBindCtx* context, __RPC__in_string LPWSTR displayName, _Reserved_ ULONG* pchEaten, __RPC__deref_out_opt PIDLIST_RELATIVE* ppidl, __RPC__inout_opt ULONG* pdwAttributes) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::EnumObjects(__RPC__in_opt HWND window, SHCONTF grfFlags, __RPC__deref_out_opt IEnumIDList** ppenumIDList) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::BindToObject(__RPC__in PCUIDLIST_RELATIVE pidl, __RPC__in_opt IBindCtx* pbc, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppv) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::BindToStorage(__RPC__in PCUIDLIST_RELATIVE pidl, __RPC__in_opt IBindCtx* pbc, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppv) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::CompareIDs(LPARAM lParam, __RPC__in PCUIDLIST_RELATIVE pidl1, __RPC__in PCUIDLIST_RELATIVE pidl2) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::CreateViewObject(__RPC__in_opt HWND window, __RPC__in REFIID riid, __RPC__deref_out_opt void** ppv) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::GetAttributesOf(UINT cidl, __RPC__in_ecount_full_opt(cidl) PCUITEMID_CHILD_ARRAY apidl, __RPC__inout SFGAOF* rgfInOut) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::GetUIObjectOf(__RPC__in_opt HWND window, UINT cidl, __RPC__in_ecount_full_opt(cidl) PCUITEMID_CHILD_ARRAY apidl, __RPC__in REFIID riid, _Reserved_ UINT* rgfReserved, __RPC__deref_out_opt void** ppv) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::GetDisplayNameOf(__RPC__in_opt PCUITEMID_CHILD identifier, SHGDNF flags, __RPC__out STRRET* outputName) {
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE SimpleShellExtension::SetNameOf(_In_opt_ HWND window, _In_ PCUITEMID_CHILD pidl, _In_ LPCWSTR pszName, _In_ SHGDNF uFlags, _Outptr_opt_ PITEMID_CHILD* ppidlOut) {
	return E_NOTIMPL;
}
