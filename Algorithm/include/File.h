#ifndef FILE_H
#define FILE_H

// Include header <C++>
#include <string>

class File {
public:
	/**
	 * This function used for check
	 * The file is exist or not
	 */
	[[maybe_unused]] static bool IsExist(std::string path);

	/**
	 * This function used for get path
	 */
	[[maybe_unused]] static std::string GetPath(std::string path);
};

#endif // FILE_H