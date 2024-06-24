#include "custom_except.hpp"

CustomException::CustomException(const std::string &message)
	: message_(message) {}

const char *CustomException::what() const noexcept
{
	return message_.c_str();
}

FileNotFound::FileNotFound(const std::string &filename)
	: CustomException("Error: file not found: " + filename) {}

InvalidLanguage::InvalidLanguage()
	: CustomException("Error: language not supported yet.") {}

DisallowedPlayerName::DisallowedPlayerName()
	: CustomException("Error: disallowed player name.") {}