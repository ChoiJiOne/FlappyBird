#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>

#include <glad/glad.h>

#include "FileModule.h"

#include "Assertion.h"
#include "Shader.h"

Shader::Shader(const std::string& vsPath, const std::string& fsPath)
{
	uniformLocationCache_ = std::map<std::string, uint32_t>();

	std::string vsSource = ReadShaderFile(vsPath);
	std::string fsSource = ReadShaderFile(fsPath);

	uint32_t vsID = CreateAndCompileShader(EType::Vertex, vsSource);
	ASSERT(vsID != 0, L"failed to create and compile %s", vsPath.c_str());

	uint32_t fsID = CreateAndCompileShader(EType::Fragment, fsSource);
	ASSERT(fsID != 0, L"failed to create and compile %s", fsPath.c_str());

	programID_ = glCreateProgram();
	CHECK(programID_ != 0);

	GL_FAILED(glAttachShader(programID_, vsID));
	GL_FAILED(glAttachShader(programID_, fsID));
	GL_FAILED(glLinkProgram(programID_));

	int32_t success;
	GL_FAILED(glGetProgramiv(programID_, GL_LINK_STATUS, &success));
	if (!success)
	{
		char buffer[1024];

		glGetProgramInfoLog(programID_, 1024, nullptr, buffer);
		ASSERT(false, "failed to link shader program\n%s", buffer);
	}

	GL_FAILED(glDeleteShader(vsID));
	GL_FAILED(glDeleteShader(fsID));

	bIsInitialized_ = true;
}

Shader::Shader(const std::string& vsPath, const std::string& gsPath, const std::string& fsPath)
{
	std::string vsSource = ReadShaderFile(vsPath);
	std::string gsSource = ReadShaderFile(gsPath);
	std::string fsSource = ReadShaderFile(fsPath);

	uint32_t vsID = CreateAndCompileShader(EType::Vertex, vsSource);
	ASSERT(vsID != 0, L"failed to create and compile %s", vsPath.c_str());

	uint32_t gsID = CreateAndCompileShader(EType::Geometry, gsSource);
	ASSERT(gsID != 0, L"failed to create and compile %s", gsPath.c_str());

	uint32_t fsID = CreateAndCompileShader(EType::Fragment, fsSource);
	ASSERT(fsID != 0, L"failed to create and compile %s", fsPath.c_str());

	programID_ = glCreateProgram();
	CHECK(programID_ != 0);

	GL_FAILED(glAttachShader(programID_, vsID));
	GL_FAILED(glAttachShader(programID_, gsID));
	GL_FAILED(glAttachShader(programID_, fsID));
	GL_FAILED(glLinkProgram(programID_));

	int32_t success;
	GL_FAILED(glGetProgramiv(programID_, GL_LINK_STATUS, &success));
	if (!success)
	{
		char buffer[1024];

		glGetProgramInfoLog(programID_, 1024, nullptr, buffer);
		ASSERT(false, "failed to link shader program\n%s", buffer);
	}

	GL_FAILED(glDeleteShader(vsID));
	GL_FAILED(glDeleteShader(gsID));
	GL_FAILED(glDeleteShader(fsID));

	bIsInitialized_ = true;
}

Shader::~Shader()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Shader::Release()
{
	CHECK(bIsInitialized_);

	if (programID_)
	{
		GL_FAILED(glDeleteProgram(programID_));
	}

	bIsInitialized_ = false;
}

void Shader::Bind()
{
	GL_FAILED(glUseProgram(programID_));
}

void Shader::Unbind()
{
	GL_FAILED(glUseProgram(0));
}
void Shader::SetUniform(const std::string& name, bool value)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform1i(location, static_cast<int32_t>(value)));
}

void Shader::SetUniform(const std::string& name, int32_t value)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform1i(location, value));
}

void Shader::SetUniform(const std::string& name, float value)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform1f(location, value));
}

void Shader::SetUniform(const std::string& name, const Vec2f& value)
{
	int32_t location = GetUniformLocation(name);

	const float* valuePtr = value.GetPtr();
	GL_FAILED(glUniform2fv(location, 1, valuePtr));
}

void Shader::SetUniform(const std::string& name, float x, float y)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform2f(location, x, y));
}

void Shader::SetUniform(const std::string& name, const Vec2i& value)
{
	int32_t location = GetUniformLocation(name);

	const int32_t* valuePtr = value.GetPtr();
	GL_FAILED(glUniform2iv(location, 1, valuePtr));
}

void Shader::SetUniform(const std::string& name, int32_t x, int32_t y)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform2i(location, x, y));
}

void Shader::SetUniform(const std::string& name, const Vec3f& value)
{
	int32_t location = GetUniformLocation(name);

	const float* valuePtr = value.GetPtr();
	GL_FAILED(glUniform3fv(location, 1, valuePtr));
}

void Shader::SetUniform(const std::string& name, float x, float y, float z)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform3f(location, x, y, z));
}

void Shader::SetUniform(const std::string& name, const Vec3i& value)
{
	int32_t location = GetUniformLocation(name);

	const int32_t* valuePtr = value.GetPtr();
	GL_FAILED(glUniform3iv(location, 1, valuePtr));
}

void Shader::SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform3i(location, x, y, z));
}

void Shader::SetUniform(const std::string& name, const Vec4f& value)
{
	int32_t location = GetUniformLocation(name);

	const float* valuePtr = value.GetPtr();
	GL_FAILED(glUniform4fv(location, 1, valuePtr));
}

void Shader::SetUniform(const std::string& name, float x, float y, float z, float w)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform4f(location, x, y, z, w));
}

void Shader::SetUniform(const std::string& name, const Vec4i& value)
{
	int32_t location = GetUniformLocation(name);

	const int32_t* valuePtr = value.GetPtr();
	GL_FAILED(glUniform4iv(location, 1, valuePtr));
}

void Shader::SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniform4i(location, x, y, z, w));
}

void Shader::SetUniform(const std::string& name, const Mat2x2f& value)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniformMatrix2fv(location, 1, GL_FALSE, value.GetPtr()));
}

void Shader::SetUniform(const std::string& name, const Mat3x3f& value)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniformMatrix3fv(location, 1, GL_FALSE, value.GetPtr()));
}

void Shader::SetUniform(const std::string& name, const Mat4x4f& value)
{
	int32_t location = GetUniformLocation(name);
	GL_FAILED(glUniformMatrix4fv(location, 1, GL_FALSE, value.GetPtr()));
}

int32_t Shader::GetUniformLocation(const std::string& name)
{
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);

	if (uniformLocation == uniformLocationCache_.end())
	{
		int32_t location = glGetUniformLocation(programID_, name.c_str());
		CHECK(location != -1);

		uniformLocationCache_.insert({ name, location });
		return location;
	}
	else
	{
		return uniformLocation->second;
	}
}

std::string Shader::ReadShaderFile(const std::string& path)
{
	std::vector<uint8_t> shaderSourceBuffer;
	ASSERT(FileModule::ReadBufferFromFile(path, shaderSourceBuffer), "failed to read %s shader file buffer", path.c_str());

	return std::string(shaderSourceBuffer.begin(), shaderSourceBuffer.end());
}

uint32_t Shader::CreateAndCompileShader(const EType& type, const std::string& source)
{
	const char* sourcePtr = source.c_str();
	uint32_t shaderID = 0;

	switch (type)
	{
	case EType::Vertex:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		ASSERT(shaderID != 0, "failed to create vertex shader");
		break;

	case EType::Geometry:
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		ASSERT(shaderID != 0, "failed to create geometry shader");
		break;

	case EType::Fragment:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		ASSERT(shaderID != 0, "failed to create fragment shader");
		break;

	default:
		ASSERT(false, "undefined shader type");
		break;
	}
	
	GL_FAILED(glShaderSource(shaderID, 1, &sourcePtr, nullptr));
	GL_FAILED(glCompileShader(shaderID));

	int32_t success;
	GL_FAILED(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		char buffer[1024];

		glGetShaderInfoLog(shaderID, 1024, nullptr, buffer);
		ASSERT(false, "failed to compile shader\n%s", buffer);
	}

	return shaderID;
}

void Shader::WriteDynamicVertexBuffer(uint32_t vertexBufferID, const void* vertexPtr, uint32_t bufferByteSize)
{
	CHECK(vertexPtr != nullptr);

	GL_FAILED(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID));
	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	CHECK(bufferPtr != nullptr);

	std::memcpy(bufferPtr, vertexPtr, bufferByteSize);
	GLboolean bSuccssed = glUnmapBuffer(GL_ARRAY_BUFFER);
	ASSERT(bSuccssed, "failed to unmap the entire data store of a specified buffer object into the client's address space...");

	GL_FAILED(glBindBuffer(GL_ARRAY_BUFFER, 0));
}