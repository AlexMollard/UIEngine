#include "pch.h"

#include "Texture.h"

#include "SOIL2/SOIL2.h"
#include "gl/glew.h"
#include <GLFW/glfw3.h>

Texture::Texture(std::string dir)
{
	/* load an image file directly as a new OpenGL texture */
	GLuint tex_2d = SOIL_load_OGL_texture(dir.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	/* check for an error during the load process */
	if (0 == tex_2d) { printf("SOIL loading error: '%s'\n", SOIL_last_result()); }

	m_TextureID = tex_2d;
}

Texture::Texture(unsigned int* id) : m_TextureID(*id)
{}

Texture::~Texture() = default;

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

unsigned int Texture::GetID()
{
	return m_TextureID;
}

void Texture::SetID(unsigned int newID)
{
	m_TextureID = newID;
}

unsigned int Texture::GetWidth()
{
	return m_Width;
}

unsigned int Texture::GetHeight()
{
	return m_Height;
}

void Texture::SetWidth(unsigned int newWidth)
{
	m_Width = newWidth;
}

void Texture::SetHeight(unsigned int newHeight)
{
	m_Height = newHeight;
}