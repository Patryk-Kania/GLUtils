#ifndef SHADER_HH
#define SHADER_HH

#include <memory>
#include <string>

#include <GL/glew.h>

class GLShader
{
public:
    static GLShader Empty();
    static GLShader CreateFromSources( const std::string &vertexSource, const std::string &fragmentSource );
    static GLShader LoadFromFiles( const std::string &vertexShaderPath, const std::string &fragmentShaderPath );

    void Use() const;
    [[nodiscard]] unsigned int GetHandle() const;
    [[nodiscard]] unsigned int GetUseCount() const;
    [[nodiscard]] bool IsValid() const;

    void SetFloat( const std::string &name, float value ) const;
    void SetFloatVec2( const std::string &name, float x, float y ) const;
    void SetFloatVec3( const std::string &name, float x, float y, float z ) const;
    void SetFloatVec4( const std::string &name, float x, float y, float z, float w ) const;
    void SetFloatVec2( const std::string &name, const float *value ) const;
    void SetFloatVec3( const std::string &name, const float *value ) const;
    void SetFloatVec4( const std::string &name, const float *value ) const;

    void SetInt( const std::string &name, int value ) const;
    void SetIntVec2( const std::string &name, int x, int y ) const;
    void SetIntVec3( const std::string &name, int x, int y, int z ) const;
    void SetIntVec4( const std::string &name, int x, int y, int z, int w ) const;
    void SetIntVec2( const std::string &name, const int *value ) const;
    void SetIntVec3( const std::string &name, const int *value ) const;
    void SetIntVec4( const std::string &name, const int *value ) const;

    void SetUInt( const std::string &name, unsigned int value ) const;
    void SetUIntVec2( const std::string &name, unsigned int x, unsigned int y ) const;
    void SetUIntVec3( const std::string &name, unsigned int x, unsigned int y, unsigned int z ) const;
    void SetUIntVec4( const std::string &name, unsigned int x, unsigned int y, unsigned int z, unsigned int w ) const;
    void SetUIntVec2( const std::string &name, const unsigned int *value ) const;
    void SetUIntVec3( const std::string &name, const unsigned int *value ) const;
    void SetUIntVec4( const std::string &name, const unsigned int *value ) const;

    void SetMat4( const std::string &name, const float *value ) const;
    void SetMat4x3( const std::string &name, const float *value ) const;
    void SetMat4x2( const std::string &name, const float *value ) const;

    void SetMat3( const std::string &name, const float *value ) const;
    void SetMat3x4( const std::string &name, const float *value ) const;
    void SetMat3x2( const std::string &name, const float *value ) const;

    void SetMat2( const std::string &name, const float *value ) const;
    void SetMat2x4( const std::string &name, const float *value ) const;
    void SetMat2x3( const std::string &name, const float *value ) const;

private:
    struct ShaderHandle
    {
        unsigned int Handle;

        explicit ShaderHandle( unsigned int handle ) : Handle( handle ) {}

        ~ShaderHandle()
        {
            if ( Handle != 0 )
                glDeleteProgram(Handle);
        }
    };

    explicit GLShader( unsigned int handle = 0 ) : mHandle{ std::make_shared<ShaderHandle>( handle )} {}

    std::shared_ptr<ShaderHandle> mHandle;
};

#endif //SHADER_HH
