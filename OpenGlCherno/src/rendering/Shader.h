#ifndef _SHADER
#define _SHADER

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource {
	std::string vertex, fragment;
};

class Shader {
private:
	unsigned m_shaderID;
	std::unordered_map<std::string, int> uniformCache;

	ShaderProgramSource* parse_shader(const std::string& file_path);
	unsigned compile_shader(unsigned type, const std::string& source);
	unsigned create_shader(const ShaderProgramSource* source);
	int uniform_location(const std::string& name);

public:
	Shader(const std::string& filename);
	~Shader();

	void use_program() const;
	
	void setUniform1f(const std::string& name, float val = 0);
	void setUniform1i(const std::string& name, int val = 0);
	void setUniform4f(const std::string& name, float a,  float b, float c, float d);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
		
	inline unsigned renderer_id() const { return m_shaderID; }
};

#endif