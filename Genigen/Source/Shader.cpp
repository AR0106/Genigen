/* Project Includes */
#include "Shader.h"
#include "Renderer.h"

/* System Includes */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	ShaderSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.vertexSrc, source.fragmentSrc);
}

Shader::~Shader()
{
	glCall(glDeleteProgram(m_RendererID));
}

ShaderSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class shaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	shaderType type = shaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = shaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = shaderType::FRAGMENT;
		}

		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	// Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Init Shader Variables
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Attach Shaders
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	// Remove Shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	glCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	glCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 v)
{
	glCall(glUniform4f(GetUniformLocation(name), v.r, v.g, v.b, v.a));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	glCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning : Uniform '" << name << "' Doesn't Exist!" << std::endl;

	m_UniformLocationCache[name] = location;

	return location;
}