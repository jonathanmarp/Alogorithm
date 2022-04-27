#ifndef JSON_H
#define JSON_H

// Include header <C++>
#include <string>

// Include header <3party>
// <Json(nlohmann)>
#include <nlohmann/json.hpp>

class Json {
public:
	/**
	 * This variable used for get information
	 * Or getting data important
	 */
	nlohmann::json data;

public:
	// Constructor
	Json(std::string path);
};

#endif // JSON_H