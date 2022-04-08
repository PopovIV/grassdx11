#include "Log.h"
#include <comdef.h>

void Log::print(std::string message) {
	std::cout << "-- " << message << std::endl;
}

void Log::warning(std::string warningMessage) {
	std::cout << "## WARNING [ " << warningMessage << " ]" << std::endl;
}

void Log::error(std::string errorMessage) {
	//MessageBox(	NULL, errorMessage.c_str(), "ERROR", MB_OK);
}

void Log::resultFailed(std::string errorMessage, HRESULT& result) {
	_com_error err(result);
	LPCTSTR errMsg = err.ErrorMessage();
	//Log::error(errorMessage + "\nHRESULT: " + std::string(errMsg));
}
