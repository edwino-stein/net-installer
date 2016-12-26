#include "../../header/util/NetworkChecker.h"

BOOL NetworkChecker::check() {

	HRESULT hr = 0;
	VARIANT_BOOL vb = 0;
	INetworkListManager* pNlm = NULL;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return false;
	}

	hr = CoCreateInstance(
		CLSID_NetworkListManager,
		NULL,
		CLSCTX_ALL,
		IID_INetworkListManager,
		(void**)&pNlm);

	if (FAILED(hr)) {
		CoUninitialize();
		return false;
	}

	hr = pNlm->get_IsConnected(&vb);
	BOOL r;

	if (SUCCEEDED(hr)) {
		if (vb) {
			r = true;
		}
		else {
			r = false;
		}
	}
	else {
		r = false;
	}

	pNlm->Release();
	CoUninitialize();
	return r;
}