#include "mppch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Maple {
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path) {

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		MP_CORE_ASSERT(data, "Texture failed to load!");
		m_Width = width; m_Height = height;

		// Now setup the OpenGL texture implementation
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, GL_RGB8, m_Width, m_Height);
		// Texture parameters
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// Upload the data
		GLenum mode;
		if (channels == STBI_grey)
			mode = GL_RED;
		else if (channels == STBI_grey_alpha)
			mode = GL_RG;
		else if (channels == STBI_rgb)
			mode = GL_RGB;
		else if (channels == STBI_rgb_alpha)
			mode = GL_RGBA;
		else
			MP_CORE_ASSERT(false, "Image mode not supported!");
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, mode, GL_UNSIGNED_BYTE, data);
		// Free the data
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_TextureID);
	}

}