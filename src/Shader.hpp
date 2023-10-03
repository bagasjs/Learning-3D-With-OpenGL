#pragma once

#include <string>
#include <stdint.h>
#include <vector>

std::string LoadFileData(const std::string& filepath);

class Shader {
public:
    enum class Type {
        FLOAT = 0, VEC2, VEC3, VEC4,
        INT, IVEC2, IVEC3, IVEC4,
        MAT3, MAT4
    };

public:
    Shader(const std::string& vertSrc, const std::string& fragSrc);
    ~Shader();

    static Shader CreateFromFile(const std::string& vertSrcPath, const std::string& fragSrcPath);

    inline uint32_t GetID() const { return m_ID; }
    inline bool IsError() const { return m_Error; }
    inline std::string Why() const  { return m_Reason; }
    int GetUniformLocation(const std::string& name) const;
    void SetUniform(const std::string& name, Type type, int count, const void* data, bool transponse);
    void Enable(void);

private:
    uint32_t LoadModule(int type, const std::string& source);
private:
    uint32_t m_ID;

    bool m_Error;
    std::string m_Reason;
};
