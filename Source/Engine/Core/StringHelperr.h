#pragma once
#include <string>

namespace nebula {
	inline std::string toLower(const std::string& str) {
		std::string result = str;
		for (char& c : result) {
			c = std::tolower(c);
		}
		return result;
	}

	inline bool equalsIgnoreCase(const std::string& a, const std::string& b) {
		if (a.length() != b.length()) {
			return false;
		}

		return std::equal(a.begin(), a.end(), b.begin(), [](char a, char b) {
			return std::tolower(a) == std::tolower(b);
			});
	}
}