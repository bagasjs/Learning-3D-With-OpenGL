#pragma once

#include <stdint.h>

class Texture2D {
public:
    Texture2D(const int8_t* data, int width, int height, int channels);
    ~Texture2D();

    void Enable(int slot);
    void Update(const int8_t* data, int width, int height);
private:
    uint32_t m_ID;
    int m_DataFormat;
};
