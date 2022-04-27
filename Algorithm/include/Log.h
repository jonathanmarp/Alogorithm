#ifndef LOG_H
#define LOG_H

// Include header <C++>
#include <string>

// Class <Log>
class Log {
private:
	// This variable used for get time
	inline static std::time_t now;
	inline static char str[26];

public:
	/**
	 * This function used for show message
	 * <Erorr> into console
	 */
	static void Error(std::string message);

	/**
	 * This function used for show message
	 * <Init> into console
	 */
	static void Init(std::string message);
};

#endif // LOG_H