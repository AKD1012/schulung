#include "generate_randomstring.h"

std::string randomStrGen(int length) {
	static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	static bool bRandCalled = false;
	std::string result;
	result.resize(length);
	if (!bRandCalled) {
		srand(time(NULL));
		bRandCalled = true;
	}
	for (int i = 0; i < length; i++) {
		result[i] = charset[rand() % charset.length()];
	}
	return result;
}
