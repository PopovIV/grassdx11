#include "Log.h"
#include <comdef.h>

void Log::print(std::string message) {
	std::cout << "-- " << message << std::endl;
}

void Log::warning(std::string warningMessage) {
	std::cout << "## WARNING [ " << warningMessage << " ]" << std::endl;
}

void Log::error(std::string errorMessage) {
	LPWSTR tmp = new wchar_t[errorMessage.size() + 1];
	copy(errorMessage.begin(), errorMessage.end(), tmp);
	tmp[errorMessage.size()] = 0;

	MessageBox(	NULL, tmp, L"ERROR", MB_OK);

	delete[] tmp;
}

void Log::resultFailed(std::string errorMessage, HRESULT& result) {
	_com_error err(result);
	LPCTSTR errMsg = err.ErrorMessage();

	std::wstring w;
	w = errMsg;

	Log::error(errorMessage + "\nHRESULT: " + std::string(w.begin(), w.end()));
}
