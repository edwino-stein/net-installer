#include "../../header/util/Conversions.h"

TCHAR * Conversions::stringToTCHAR(std::string input) {

	TCHAR *output;

	if (input.empty()) {
		TCHAR *output = new TCHAR[1];
		*output = '\0';
		return output;
	}

	TCHAR *i;
	output = new TCHAR[input.size() + 1];
	output[input.size()] = 0;

	char *c = &input[0];
	i = output;

	while (*c != '\0') {
		*i = *c;
		i++;
		c++;
	}

	return output;
}

TCHAR * Conversions::charToTCHAR(char *input) {

	int length = strlen(input);
	TCHAR *output;

	if (length <= 0) {
		TCHAR *output = new TCHAR[1];
		*output = '\0';
		return output;
	}

	TCHAR *i;
	output = new TCHAR[length + 1];
	output[length] = 0;

	char *c = &input[0];
	i = output;

	while (*c != '\0') {
		*i = *c;
		i++;
		c++;
	}

	return output;
}

std::string Conversions::TCHARToString(TCHAR *input) {
	std::wstring wString(input);
	std::string output(wString.begin(), wString.end());
	return output;
}