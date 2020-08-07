#pragma once
#include "OpenGLTexture.h"
#include <glad/glad.h>

#ifndef BB_STBI_IMAGE
#define BB_STBI_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

namespace BlackboardRuntime {
    OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_Path(path){
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        BB_CORE_ASSERT(data, "Failed to load image!");
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;

        if(channels == 3){
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }

        BB_CORE_ASSERT(internalFormat & dataFormat, "Texture format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);
        glTextureStorage2D(m_Handle, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_Handle, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_Handle);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, m_Handle);
    }
}