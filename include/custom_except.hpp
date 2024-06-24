#ifndef CUSTOM_EXCEPT_HPP
#define CUSTOM_EXCEPT_HPP

#include <exception>
#include <string>

class CustomException : public std::exception {
public:
	CustomException(const std::string &message);
	const char *what() const noexcept override;

private:
	const std::string message_;
};

class FileNotFound : public CustomException {
public:
	FileNotFound(const std::string &filename);
};

class InvalidLanguage : public CustomException {
public:
	InvalidLanguage();
};

class DisallowedPlayerName : public CustomException {
public:
	DisallowedPlayerName();
};

#endif // "CUSTOM_EXCEPT_HPP"