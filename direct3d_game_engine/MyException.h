#pragma once
#include <exception>
#include <sstream>

class MyException : public std::exception
{
public:
	MyException(int line, const char* file);
	const char* what() const override;
	const char* GetType() const;
	int GetLine() const;
	const std::string& GetFile() const;
	std::string GetOriginString() const;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};

