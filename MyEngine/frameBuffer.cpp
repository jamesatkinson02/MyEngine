#include "frameBuffer.h"
#include "logger.h"

namespace corona
{
	frameBuffer::frameBuffer() : m_fboID{ 0 }
	{
		load();
	}

	bool frameBuffer::load()
	{
		glGenFramebuffers(1, &m_fboID);
		bindFBO();
		return true;
	}

	void frameBuffer::attachTexture(texture& t)
	{

	}

	void frameBuffer::bindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, m_texID);
	}

	void frameBuffer::unbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void frameBuffer::attachRBO()
	{
		glGenRenderbuffers(1, &m_rboID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rboID);
		int m_width = 0; int m_height = 0;
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void frameBuffer::bindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
	}

	void frameBuffer::unbindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void frameBuffer::clean()
	{
		glDeleteRenderbuffers(1, &m_rboID);
		glDeleteTextures(1, &m_texID);
		glDeleteFramebuffers(1, &m_fboID);
	}

	bool frameBuffer::checkStatus()
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			logger::error("Missing attachments to framebuffer!");
			return false;
		}

		logger::trace("Successfully initialised new framebuffer!");
		return true;
	}


}

