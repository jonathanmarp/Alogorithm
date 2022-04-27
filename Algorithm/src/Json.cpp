// Include header <C++>
#include <iostream>
#include <fstream>

// Include header <Self>
#include "../include/Json.h"

// Include header <File>
#include "../include/File.h"

// Include header <Log>
#include "../include/Log.h"

// Constructor
Json::Json(std::string path) {
	// Setup file path
	std::string pathFile = File::GetPath(path);
	
	// Check file is exist
	if (!File::IsExist(pathFile)) {
		// Show error
		Log::Error("File is not defined: " + pathFile);
	
		// Return
		return;
	}

	// Get data
	std::fstream file;

	// Open file
	file.open(pathFile, std::ios::in);

	// Write data to json
	file >> this->data;

	// Close file
	file.close();
}