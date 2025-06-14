#include "shader.hh"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

GLShader GLShader::Empty()
{
    static GLShader shader { 0 };
    return shader;
}

GLShader GLShader::CreateFromSources( const std::string &vertexSource, const std::string &fragmentSource )
{
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *vertexShaderSource = vertexSource.c_str();
    glShaderSource( vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader( vertexShader );

    int success;
    char infoLog[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if( !success )
    {
        glGetShaderInfoLog( vertexShader, 512, nullptr, infoLog );
        std::cout << infoLog << std::endl;
        glDeleteShader( vertexShader );
        return Empty();
    }

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *fragmentShaderSource = fragmentSource.c_str();
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader( fragmentShader );

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if( !success )
    {
        glGetShaderInfoLog( fragmentShader, 512, nullptr, infoLog );
        std::cout << infoLog << std::endl;
        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );
        return Empty();
    }

    const GLuint shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    if( !success )
    {
        glGetProgramInfoLog( shaderProgram, 512, nullptr, infoLog );
        std::cout << infoLog << std::endl;
        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );
        glDeleteProgram( shaderProgram );
        return Empty();
    }

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    GLShader shader { shaderProgram };
    return shader;
}

GLShader GLShader::LoadFromFiles( const std::string &vertexShaderPath, const std::string &fragmentShaderPath )
{
    std::ifstream vertexShaderFile;
    vertexShaderFile.open( vertexShaderPath );

    if ( vertexShaderFile.fail() )
    {
        std::cout << "Failed to open file: " << vertexShaderPath << std::endl;
        return Empty();
    }

    std::stringstream vertexShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();

    std::ifstream fragmentShaderFile;
    fragmentShaderFile.open( fragmentShaderPath );

    if ( fragmentShaderFile.fail() )
    {
        std::cout << "Failed to open file: " << fragmentShaderPath << std::endl;
        return Empty();
    }

    std::stringstream fragmentShaderStream;
    fragmentShaderStream << fragmentShaderFile.rdbuf();

    return CreateFromSources( vertexShaderStream.str(), fragmentShaderStream.str() );
}

void GLShader::Use() const
{
    glUseProgram( GetHandle() );
}

unsigned int GLShader::GetHandle() const
{
    if (!mHandle)
        return 0;

    return mHandle->Handle;
}

unsigned int GLShader::GetUseCount() const
{
    return mHandle.use_count();
}

bool GLShader::IsValid() const
{
    return mHandle && GetHandle() != 0;
}

void GLShader::SetFloat( const std::string &name, float value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform1f( location, value );
}

void GLShader::SetFloatVec2( const std::string &name, float x, float y ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform2f( location, x, y );
}

void GLShader::SetFloatVec3( const std::string &name, float x, float y, float z ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform3f( location, x, y, z );
}

void GLShader::SetFloatVec4( const std::string &name, float x, float y, float z, float w ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform4f( location, x, y, z, w );
}

void GLShader::SetFloatVec2( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform2fv( location, 1, value );
}

void GLShader::SetFloatVec3( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform3fv( location, 1, value );
}

void GLShader::SetFloatVec4( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform4fv( location, 1, value );
}

void GLShader::SetInt( const std::string &name, int value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform1i( location, value );
}

void GLShader::SetIntVec2( const std::string &name, int x, int y ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform2i( location, x, y );
}

void GLShader::SetIntVec3( const std::string &name, int x, int y, int z ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform3i( location, x, y, z );
}

void GLShader::SetIntVec4( const std::string &name, int x, int y, int z, int w ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform4i( location, x, y, z, w );
}

void GLShader::SetIntVec2( const std::string &name, const int *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform2iv( location, 1, value );
}

void GLShader::SetIntVec3( const std::string &name, const int *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform3iv( location, 1, value );
}

void GLShader::SetIntVec4( const std::string &name, const int *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform4iv( location, 1, value );
}

void GLShader::SetUInt( const std::string &name, unsigned int value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform1ui( location, value );
}

void GLShader::SetUIntVec2( const std::string &name, unsigned int x, unsigned int y ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform2ui( location, x, y );
}

void GLShader::SetUIntVec3( const std::string &name, unsigned int x, unsigned int y, unsigned int z ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform3ui( location, x, y, z );
}

void GLShader::SetUIntVec4( const std::string &name, unsigned int x, unsigned int y, unsigned int z, unsigned int w ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform4ui( location, x, y, z, w );
}

void GLShader::SetUIntVec2( const std::string &name, const unsigned int *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform2uiv( location, 1, value );
}

void GLShader::SetUIntVec3( const std::string &name, const unsigned int *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform3uiv( location, 1, value );
}

void GLShader::SetUIntVec4( const std::string &name, const unsigned int *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniform4uiv( location, 1, value );
}

void GLShader::SetMat4( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix4fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat4x3( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix4x3fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat4x2( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix4x2fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat3( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix3fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat3x4( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix3x4fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat3x2( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix3x2fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat2( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix2fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat2x4( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix2x4fv( location, 1, GL_FALSE, value );
}

void GLShader::SetMat2x3( const std::string &name, const float *value ) const
{
    const GLint location = glGetUniformLocation( GetHandle(), name.c_str() );
    glUniformMatrix2x3fv( location, 1, GL_FALSE, value );
}