#include "ErrorLogger.h" 
#include <comdef.h>

void ErrorLogger::Log(std::string message) {
    std::string error_message = "Error" + message;
    MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}
//
//void ErrorLogger::Log(HRESULT hr, std::string message) {
//	_com_error error(hr);
//	/*std::string error_message = "Error: " + message + "\n" + error.ErrorMessage();
//	MessageBox(NULL, error_message.c_str(), "Error", MB_ICONERROR);*/
//}