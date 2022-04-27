// Include header <C++>
#include <iostream>
#include <fstream>
#include <filesystem>

// Include header <Self>
#include "../include/File.h"

/**
 * This function used for check
 * The file is exist or not
 */
[[maybe_unused]] bool File::IsExist(std::string path) {
	// Check if file is exist
	// Setup
	std::ifstream temp;

	// Open
	temp.open(path);

	// Get
	bool exist = temp.is_open();

	// Close
	temp.close();

	// return
	return exist;
}

/**
 * This function used for get path
 */
[[maybe_unused]] std::string File::GetPath(std::string path) {
	// Return Path
	return std::filesystem::absolute(
		std::filesystem::current_path().string() + "\\" + path)
		.string();
}