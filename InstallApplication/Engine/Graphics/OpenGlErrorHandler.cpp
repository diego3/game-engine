#include "OpenGlErrorHandler.h"
#include <string>
#include <iostream>

OpenGlErrorHandler::OpenGlErrorHandler() {
	glErrorMapping = {};
	glErrorMapping.emplace(GL_INVALID_ENUM, "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.");
	glErrorMapping.emplace(GL_INVALID_VALUE, "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.");
	glErrorMapping.emplace(GL_INVALID_OPERATION, "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.");
	glErrorMapping.emplace(GL_INVALID_FRAMEBUFFER_OPERATION, "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.");
	glErrorMapping.emplace(GL_OUT_OF_MEMORY, "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
	glErrorMapping.emplace(GL_STACK_UNDERFLOW, "An attempt has been made to perform an operation that would cause an internal stack to underflow");
	glErrorMapping.emplace(GL_STACK_OVERFLOW, "An attempt has been made to perform an operation that would cause an internal stack to overflow.");
}

OpenGlErrorHandler::~OpenGlErrorHandler() {
	glErrorMapping = {};
}

bool OpenGlErrorHandler::LogError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {

		// criar um func para mapear os enums de erros
		std::cout << "OpenGl Error[" << error << "] " << std::endl;
		std::cout << "Doc:" << this->GetError(error) << std::endl;
		std::cout << "function: " << function << std::endl;
		std::cout << "file: " << file << std::endl;
		std::cout << "line: " << line << std::endl;
		return false;
	}
	return true;
}

void OpenGlErrorHandler::ClearError() {
	// std::cout << "gl-clear-error start" << std::endl;
	while (glGetError() != GL_NO_ERROR);
	// std::cout << "gl-clear-error end" << std::endl;
}

std::string OpenGlErrorHandler::GetError(GLenum errorFlag) {
	GlErrorMap::iterator iterator = glErrorMapping.find(errorFlag);

	if (!iterator->second.empty()) {
		return iterator->first + " : " + iterator->second;
	}
	return "invalid errorFlag";
}
