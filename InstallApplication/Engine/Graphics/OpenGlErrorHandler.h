#pragma once

#include <map>
#include <string>
#include <GL/glew.h>


class OpenGlErrorHandler {
public:
	OpenGlErrorHandler();
	
	~OpenGlErrorHandler();

	bool LogError(const char* function, const char* file, int line);

	void ClearError();

	std::string GetError(GLenum errorFlag);
private:
	typedef std::map<GLenum, std::string> GlErrorMap;

	GlErrorMap glErrorMapping;
};

