// Include header <C++>
#include <iostream>
#include <ctime>

// Include header <Self>
#include "../include/Log.h"


/**
 * This function used for show message
 * <Erorr> into console
 */
void Log::Error(std::string message) {
	// Get time
	std::time(&Log::now);
	ctime_s(Log::str, 26, &Log::now);
	str[24] = '\0';

	// Show message <Error>
	std::cout << "Error: " << "[";
	std::cout << str << "] ";
	std::cout << message << std::endl;
}

/**
 * This function used for show message
 * <Init> into console
 */
void Log::Init(std::string message) {
	// Get time
	std::time(&Log::now);
	ctime_s(Log::str, 26, &Log::now);
	str[24] = '\0';

	// Show message <Error>
	std::cout << "Successfull Init: " << "[";
	std::cout << str << "] ";
	std::cout << message << std::endl;
}