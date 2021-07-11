#include "mppch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Maple {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) 
		: m_Width(width), m_Height(height) {
		m_InternalFormat = GL_RGBA8;
		m_Format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path) {

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		MP_CORE_ASSERT(data, "Texture failed to load!");
		m_Width = width; m_Height = height;

		GLenum format = 0, internalFormat = 0;
		if (channels == STBI_grey) {
			format = GL_RED;
			internalFormat = GL_RED;
		}
		else if (channels == STBI_grey_alpha) {
			format = GL_RG;
			internalFormat = GL_RG8;
		}
		else if (channels == STBI_rgb) {
			format = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else if (channels == STBI_rgb_alpha) {
			format = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		MP_CORE_ASSERT(internalFormat & format, "Image format not supported!");
		m_Format = format;
		m_InternalFormat = internalFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);
		
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		uint32_t bytesPerPixel = m_Format == GL_RGBA ? 4 : m_Format == GL_RG ? 2 : m_Format == GL_RED ? 1 : 3;
		MP_CORE_ASSERT(size == m_Width * m_Height * bytesPerPixel, "Parameter 'size' does not match data's actual size!");
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_TextureID);
	}

}