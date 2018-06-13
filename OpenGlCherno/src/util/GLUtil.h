#ifndef _GLUTIL
#define _GLUTIL

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak()

#define GLCALL(x) gl_clean_errors();\
x;\
ASSERT(gl_check_error(#x, __FILE__, __LINE__))

inline void gl_clean_errors() { while(glGetError() != GL_NO_ERROR); }

inline bool gl_check_error(const char* func, const char* file, const unsigned int line) {
	bool no_errors = true;
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << std::endl;
		no_errors = false;
	}
	return no_errors;
}

#endif // !_GLUTIL
