#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <memory>
#include <vector>
#include "BlockingQueue.h"
#include "Graphics/OpenGLContext/GLFunctions.h"
#include "Graphics/OpenGLContext/opengl_Attributes.h"
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "opengl_Command.h"
#include "splice-pool.hpp"


#ifdef MUPENPLUSAPI
#include <mupenplus/GLideN64_mupenplus.h>
#else
#include <Graphics/OpenGLContext/windows/WindowsWGL.h>
#endif

namespace opengl {

	class GlBlendFuncCommand : public OpenGlCommand
	{
	public:
		GlBlendFuncCommand() :
			OpenGlCommand(false, false, "glBlendFunc")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum sfactor, GLenum dfactor)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBlendFuncCommand>(poolId);
			ptr->set(sfactor, dfactor);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBlendFunc(m_sfactor, m_dfactor);
		}
	private:
		void set(GLenum sfactor, GLenum dfactor)
		{
			m_sfactor = sfactor;
			m_dfactor = dfactor;
		}

		GLenum m_sfactor;
		GLenum m_dfactor;
	};

	class GlPixelStoreiCommand : public OpenGlCommand
	{
	public:
		GlPixelStoreiCommand() :
			OpenGlCommand(false, false, "glPixelStorei")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum pname, GLint param)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlPixelStoreiCommand>(poolId);
			ptr->set(pname, param);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glPixelStorei(m_pname, m_param);
		}

	private:
		void set(GLenum pname, GLint param)
		{
			m_pname = pname;
			m_param = param;
		}

		GLenum m_pname;
		GLint m_param;
	};

	class GlClearColorCommand : public OpenGlCommand
	{
	public:
		GlClearColorCommand() :
			OpenGlCommand(false, false, "glClearColor")
		{

		}

		static std::shared_ptr<OpenGlCommand> get(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlClearColorCommand>(poolId);
			ptr->set(red, green, blue, alpha);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glClearColor(m_red, m_green, m_blue, m_alpha);
		}
	private:
		void set(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
		{
			m_red = red;
			m_green = green;
			m_blue = blue;
			m_alpha = alpha;
		}

		GLfloat m_red;
		GLfloat m_green;
		GLfloat m_blue;
		GLfloat m_alpha;
	};

	class GlCullFaceCommand : public OpenGlCommand
	{
	public:
		GlCullFaceCommand() :
			OpenGlCommand(false, false, "glCullFace")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum mode)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCullFaceCommand>(poolId);
			ptr->set(mode);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glCullFace(m_mode);
		}

	private:
		void set(GLenum mode)
		{
			m_mode = mode;
		}

		GLenum m_mode;
	};

	class GlDepthFuncCommand : public OpenGlCommand
	{
	public:
		GlDepthFuncCommand() :
			OpenGlCommand(false, false, "glDepthFunc")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum func)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDepthFuncCommand>(poolId);
			ptr->set(func);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDepthFunc(m_func);
		}
	private:
		void set(GLenum func)
		{
			m_func = func;
		}

		GLenum m_func;
	};

	class GlDepthMaskCommand : public OpenGlCommand
	{
	public:
		GlDepthMaskCommand() :
			OpenGlCommand(false, false, "glDepthMask")
		{

		}

		static std::shared_ptr<OpenGlCommand> get(GLboolean flag)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDepthMaskCommand>(poolId);
			ptr->set(flag);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDepthMask(m_flag);
		}
	private:
		void set(GLboolean flag)
		{
			m_flag = flag;
		}

		GLboolean m_flag;
	};

	class GlDisableCommand : public OpenGlCommand
	{
	public:
		GlDisableCommand() :
			OpenGlCommand(false, false, "glDisable")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum cap)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDisableCommand>(poolId);
			ptr->set(cap);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDisable(m_cap);
		}
	private:
		void set(GLenum cap)
		{
			m_cap = cap;
		}

		GLenum m_cap;
	};

	class GlEnableCommand : public OpenGlCommand
	{
	public:
		GlEnableCommand() :
			OpenGlCommand(false, false, "glEnable")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum cap)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlEnableCommand>(poolId);
			ptr->set(cap);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glEnable(m_cap);
		}
	private:
		void set(GLenum cap)
		{
			m_cap = cap;
		}

		GLenum m_cap;
	};

	class GlDisableiCommand : public OpenGlCommand
	{
	public:
		GlDisableiCommand() :
			OpenGlCommand(false, false, "glDisablei")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint index)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDisableiCommand>(poolId);
			ptr->set(target, index);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDisablei(m_target, m_index);
		}
	private:
		void set(GLenum target, GLuint index)
		{
			m_target = target;
			m_index = index;
		}

		GLenum m_target;
		GLuint m_index;
	};

	class GlEnableiCommand : public OpenGlCommand
	{
	public:
		GlEnableiCommand() :
			OpenGlCommand(false, false, "glEnablei")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint index)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlEnableiCommand>(poolId);
			ptr->set(target, index);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glEnablei(m_target, m_index);
		}
	private:
		void set(GLenum target, GLuint index)
		{
			m_target = target;
			m_index = index;
		}

		GLenum m_target;
		GLuint m_index;
	};

	class GlPolygonOffsetCommand : public OpenGlCommand
	{
	public:
		GlPolygonOffsetCommand() :
			OpenGlCommand(false, false, "glPolygonOffset")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLfloat factor, GLfloat units)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlPolygonOffsetCommand>(poolId);
			ptr->set(factor, units);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glPolygonOffset(m_factor, m_units);
		}
	private:
		void set(GLfloat factor, GLfloat units)
		{
			m_factor = factor;
			m_units = units;
		}

		GLfloat m_factor;
		GLfloat m_units;
	};

	class GlScissorCommand : public OpenGlCommand
	{
	public:
		GlScissorCommand() :
			OpenGlCommand(false, false, "glScissor")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlScissorCommand>(poolId);
			ptr->set(x, y, width, height);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glScissor(m_x, m_y, m_width, m_height);
		}
	private:
		void set(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			m_x = x;
			m_y = y;
			m_width = width;
			m_height = height;
		}

		GLint m_x;
		GLint m_y;
		GLsizei m_width;
		GLsizei m_height;
	};

	class GlViewportCommand : public OpenGlCommand
	{
	public:
		GlViewportCommand() :
			OpenGlCommand(false, false, "glViewport")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlViewportCommand>(poolId);
			ptr->set(x, y, width, height);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glViewport(m_x, m_y, m_width, m_height);
		}
	private:
		void set(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			m_x = x;
			m_y = y;
			m_width = width;
			m_height = height;
		}

		GLint m_x;
		GLint m_y;
		GLsizei m_width;
		GLsizei m_height;
	};

	class GlBindTextureCommand : public OpenGlCommand
	{
	public:
		GlBindTextureCommand() :
			OpenGlCommand(false, false, "glBindTexture")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint texture)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindTextureCommand>(poolId);
			ptr->set(target, texture);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindTexture(m_target, m_texture);
		}
	private:
		void set(GLenum target, GLuint texture)
		{
			m_target = target;
			m_texture = texture;
		}

		GLenum m_target;
		GLuint m_texture;
	};

	class GlTexImage2DCommand : public OpenGlCommand
	{
	public:
		GlTexImage2DCommand() :
			OpenGlCommand(false, false, "glTexImage2D")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
			GLint border, GLenum format, GLenum type, std::unique_ptr<u8[]> pixels)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexImage2DCommand>(poolId);
			ptr->set(target, level, internalformat, width, height, border, format, type, std::move(pixels));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexImage2D(m_target, m_level, m_internalformat, m_width, m_height, m_border, m_format, m_type,
				m_pixels.get());
		}
	private:
		void set(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
			GLint border, GLenum format, GLenum type, std::unique_ptr<u8[]> pixels)
		{
			m_target = target;
			m_level = level;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
			m_border = border;
			m_format = format;
			m_type = type;
			m_pixels = std::move(pixels);
		}

		GLenum m_target;
		GLint m_level;
		GLint m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
		GLint m_border;
		GLenum m_format;
		GLenum m_type;
		std::unique_ptr<u8[]> m_pixels;
	};

	class GlTexParameteriCommand : public OpenGlCommand
	{
	public:
		GlTexParameteriCommand() :
			OpenGlCommand(false, false, "glTexParameteri")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum pname, GLint param)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexParameteriCommand>(poolId);
			ptr->set(target, pname, param);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexParameteri(m_target, m_pname, m_param);
		}
	private:
		void set(GLenum target, GLenum pname, GLint param)
		{
			m_target = target;
			m_pname = pname;
			m_param = param;
		}

		GLenum m_target;
		GLenum m_pname;
		GLint m_param;
	};

	class GlGetIntegervCommand : public OpenGlCommand
	{
	public:
		GlGetIntegervCommand() :
			OpenGlCommand(true, false, "glGetIntegerv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum pname, GLint* data)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetIntegervCommand>(poolId);
			ptr->set(pname, data);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetIntegerv(m_pname, m_data);
		}
	private:
		void set(GLenum pname, GLint* data)
		{
			m_pname = pname;
			m_data = data;
		}

		GLenum m_pname;
		GLint* m_data;
	};

	class GlGetStringCommand : public OpenGlCommand
	{
	public:
		GlGetStringCommand() :
			OpenGlCommand(true, false, "glGetString")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum name, const GLubyte*& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetStringCommand>(poolId);
			ptr->set(name, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glGetString(m_name);
		}
	private:
		void set(GLenum name, const GLubyte*& returnValue)
		{
			m_name = name;
			m_returnValue = &returnValue;
		}

		GLenum m_name;
		const GLubyte** m_returnValue;
	};

	class GlReadPixelsCommand : public OpenGlCommand
	{
	public:
		GlReadPixelsCommand() :
			OpenGlCommand(true, true, "glReadPixels")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlReadPixelsCommand>(poolId);
			ptr->set(x, y, width, height, format, type, pixels);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glReadPixels(m_x, m_y, m_width, m_height, m_format, m_type, m_pixels);
		}
	private:
		void set(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
		{
			m_x = x;
			m_y = y;
			m_width = width;
			m_height = height;
			m_format = format;
			m_type = type;
			m_pixels = pixels;
		}

		GLint m_x;
		GLint m_y;
		GLsizei m_width;
		GLsizei m_height;
		GLenum m_format;
		GLenum m_type;
		void* m_pixels;
	};

	class GlReadPixelsAsyncCommand : public OpenGlCommand
	{
	public:
		GlReadPixelsAsyncCommand() :
			OpenGlCommand(false, false, "GlReadPixelsAync")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlReadPixelsAsyncCommand>(poolId);
			ptr->set(x, y, width, height, format, type);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glReadPixels(m_x, m_y, m_width, m_height, m_format, m_type, nullptr);
		}

        static GLuint getBoundBuffer()
        {
            return m_readPixelsBoundBuffer;
        }

        static void setBoundBuffer(GLuint buffer)
        {
            m_readPixelsBoundBuffer = buffer;
        }

	private:
		void set(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type)
		{
			m_x = x;
			m_y = y;
			m_width = width;
			m_height = height;
			m_format = format;
			m_type = type;
		}

		GLint m_x;
		GLint m_y;
		GLsizei m_width;
		GLsizei m_height;
		GLenum m_format;
		GLenum m_type;
		static GLuint m_readPixelsBoundBuffer;
	};

	class GlTexSubImage2DUnbufferedCommand : public OpenGlCommand
	{
	public:
		GlTexSubImage2DUnbufferedCommand() :
			OpenGlCommand(false, false, "glTexSubImage2D")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
			GLenum format, GLenum type, std::unique_ptr<u8[]> pixels)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexSubImage2DUnbufferedCommand>(poolId);
			ptr->set(target, level, xoffset, yoffset, width, height, format, type, std::move(pixels));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexSubImage2D(m_target, m_level, m_xoffset, m_yoffset, m_width, m_height, m_format, m_type, m_pixels.get());
		}
	private:
		void set(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
			GLenum format, GLenum type, std::unique_ptr<u8[]> pixels)
		{
			m_target = target;
			m_level = level;
			m_xoffset = xoffset;
			m_yoffset = yoffset;
			m_width = width;
			m_height = height;
			m_format = format;
			m_type = type;
			m_pixels = std::move(pixels);
		}

		GLenum m_target;
		GLint m_level;
		GLint m_xoffset;
		GLint m_yoffset;
		GLsizei m_width;
		GLsizei m_height;
		GLenum m_format;
		GLenum m_type;
		std::unique_ptr<u8[]> m_pixels;
	};

	class GlDrawArraysCommand : public OpenGlCommand
	{
	public:
		GlDrawArraysCommand() :
			OpenGlCommand(false, false, "glDrawArrays")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum mode, GLint first, GLsizei count)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDrawArraysCommand>(poolId);
			ptr->set(mode, first, count);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDrawArrays(m_mode, m_first, m_count);
		}
	private:
		void set(GLenum mode, GLint first, GLsizei count)
		{
			m_mode = mode;
			m_first = first;
			m_count = count;
		}

		GLenum m_mode;
		GLint m_first;
		GLsizei m_count;
	};

	class GlVertexAttribPointerManager
    {
    public:
        struct VertexAttributeData
        {
            GLuint m_index;
            GLint m_size;
            GLenum m_type;
            GLboolean m_normalized;
            GLsizei m_stride;
            const void* m_pointer;
            bool m_enabled;
            bool m_updated = false;
        };

        static void enableVertexAttributeIndexRender(unsigned int index)
        {
            VertexAttributeData& attributeData = m_vertexAttributePointersRender[index];
            attributeData.m_enabled = true;

            updatedSmallestPtrRender();
        }

        static void disableVertexAttributeIndexRender(unsigned int index)
        {
            VertexAttributeData& attributeData = m_vertexAttributePointersRender[index];
            attributeData.m_enabled = false;

            updatedSmallestPtrRender();
        }

        static std::unordered_map<int, VertexAttributeData>& getVertexAttributesRender()
        {
            return m_vertexAttributePointersRender;
        }

        static void updateRender(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
        {
            VertexAttributeData &vertexAttributeData = m_vertexAttributePointersRender[index];
            vertexAttributeData.m_index = index;
            vertexAttributeData.m_size = size;
            vertexAttributeData.m_type = type;
            vertexAttributeData.m_normalized = normalized;
            vertexAttributeData.m_stride = stride;
            vertexAttributeData.m_pointer = pointer;
            vertexAttributeData.m_updated = true;

            updatedSmallestPtrRender();
        }

        static const char* getSmallestPtrRender() {
            return reinterpret_cast<const char*>(smallestDataPtrRender);
        }

        static void enableVertexAttributeIndex(unsigned int index)
        {
            VertexAttributeData& attributeData = m_vertexAttributePointers[index];
            attributeData.m_enabled = true;

            updatedSmallestPtr();
        }

        static void disableVertexAttributeIndex(int index)
        {
            VertexAttributeData& attributeData = m_vertexAttributePointers[index];
            attributeData.m_enabled = false;

            updatedSmallestPtr();
        }

        static int getStride()
        {
            int stride = 0;
            for (auto& data : m_vertexAttributePointers) {
                if (data.second.m_pointer && data.second.m_enabled) {
                    stride = data.second.m_stride;
                    break;
                }
            }

            return stride;
        }

        static void update(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
        {
            VertexAttributeData &vertexAttributeData = m_vertexAttributePointers[index];
            vertexAttributeData.m_index = index;
            vertexAttributeData.m_size = size;
            vertexAttributeData.m_type = type;
            vertexAttributeData.m_normalized = normalized;
            vertexAttributeData.m_stride = stride;
            vertexAttributeData.m_pointer = pointer;

            updatedSmallestPtr();
        }

        static const char* getSmallestPtr() {
            return reinterpret_cast<const char*>(smallestDataPtr);
        }

        static splicer::Node<std::vector<char>>* getVectorFromPool() {
            return m_vectorPool.acquireOne().release();
        }

        static void releaseVectorFromPool(splicer::Node<std::vector<char>>* node) {
            m_vectorPool.release(node);
        }

    private:
        static void updatedSmallestPtrRender()
        {
            smallestDataPtrRender = nullptr;

            for (auto& data : m_vertexAttributePointersRender) {
                if (data.second.m_pointer && data.second.m_enabled && (smallestDataPtrRender == nullptr || data.second.m_pointer < smallestDataPtrRender)) {
                    smallestDataPtrRender = data.second.m_pointer;
				}
            }
        }

        static void updatedSmallestPtr()
        {
            smallestDataPtr = nullptr;

            for (auto& data : m_vertexAttributePointers) {
                if (data.second.m_pointer && data.second.m_enabled && (smallestDataPtr == nullptr || data.second.m_pointer < smallestDataPtr)) {
                    smallestDataPtr = data.second.m_pointer;
                }
            }
        }

	    static std::unordered_map<int, VertexAttributeData> m_vertexAttributePointersRender;
        static const void* smallestDataPtrRender;

        static std::unordered_map<int, VertexAttributeData> m_vertexAttributePointers;
        static const void* smallestDataPtr;

        static splicer::ObjectPool<std::vector<char>> m_vectorPool;
    };

    class GlVertexAttribPointerUnbufferedCommand : public OpenGlCommand
    {
    public:
        GlVertexAttribPointerUnbufferedCommand() :
                OpenGlCommand(false, false, "glVertexAttribPointer")
        {
        }

        static std::shared_ptr<OpenGlCommand> get(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
        {
            static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
            auto ptr = getFromPool<GlVertexAttribPointerUnbufferedCommand>(poolId);
            ptr->set(index, size, type, normalized, stride, pointer);
            return ptr;
        }

        void commandToExecute() override
        {
            GlVertexAttribPointerManager::updateRender(m_index, m_size, m_type, m_normalized, m_stride, m_pointer);
        }

    private:
        void set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
        {
            m_index = index;
            m_size = size;
            m_type = type;
            m_normalized = normalized;
            m_stride = stride;
            m_pointer = pointer;
        }

        GLuint m_index;
        GLint m_size;
        GLenum m_type;
        GLboolean m_normalized;
        GLsizei m_stride;
        const void* m_pointer;
    };

	class GlDrawArraysUnbufferedCommand : public OpenGlCommand
	{
	public:
		GlDrawArraysUnbufferedCommand() :
			OpenGlCommand(false, false, "glDrawArraysUnbuffered")
		{
            static bool attribsDataInitialized = false;

            if (!attribsDataInitialized) {
                m_attribsData.resize(2*1024*1024, 0);
                attribsDataInitialized = true;
            }
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum mode, GLint first, GLsizei count, splicer::Node<std::vector<char>>* data)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDrawArraysUnbufferedCommand>(poolId);
			ptr->set(mode, first, count, data);
			return ptr;
		}

		void commandToExecute() override
		{
            auto& vertexAttributes = GlVertexAttribPointerManager::getVertexAttributesRender();

            for (auto& data : vertexAttributes) {
                if (data.second.m_updated && data.second.m_enabled) {

                    unsigned long ptrOffset = reinterpret_cast<const char*>(data.second.m_pointer) -
                                              GlVertexAttribPointerManager::getSmallestPtrRender();
                    g_glVertexAttribPointer(data.second.m_index, data.second.m_size, data.second.m_type, data.second.m_normalized,
                                            data.second.m_stride, reinterpret_cast<const GLvoid*>(m_attribsData.data() + ptrOffset));
                    data.second.m_updated = false;
                }
            }
			std::copy_n(m_data->val().begin(), m_data->val().size(), m_attribsData.begin());
			g_glDrawArrays(m_mode, m_first, m_count);
            GlVertexAttribPointerManager::releaseVectorFromPool(m_data);
		}
	private:
		void set(GLenum mode, GLint first, GLsizei count, splicer::Node<std::vector<char>>* data)
		{
			m_mode = mode;
			m_first = first;
			m_count = count;
			m_data = data;
		}

		GLenum m_mode;
		GLint m_first;
		GLsizei m_count;
        splicer::Node<std::vector<char>>* m_data;
        static std::vector<char> m_attribsData;
	};

	class GlGetErrorCommand : public OpenGlCommand
	{
	public:
		GlGetErrorCommand() :
			OpenGlCommand(true, true, "glGetError")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetErrorCommand>(poolId);
			ptr->set(returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glGetError();
		}
	private:
		void set(GLenum& returnValue)
		{
			m_returnValue = &returnValue;
		}

		GLenum* m_returnValue;
	};

	class GlDrawElementsUnbufferedCommand : public OpenGlCommand
	{
	public:
		GlDrawElementsUnbufferedCommand() :
			OpenGlCommand(false, false, "glDrawElementsUnbuffered")
		{
            static bool attribsDataInitialized = false;

            if (!attribsDataInitialized) {
                m_attribsData.resize(2*1024*1024, 0);
                attribsDataInitialized = true;
            }
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum mode, GLsizei count, GLenum type, std::unique_ptr<u8[]> indices,
        	splicer::Node<std::vector<char>>* data)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDrawElementsUnbufferedCommand>(poolId);
			ptr->set(mode, count, type, std::move(indices), std::move(data));
			return ptr;
		}

		void commandToExecute() override
		{
            auto& vertexAttributes = GlVertexAttribPointerManager::getVertexAttributesRender();
            int count = 0;

            for (auto& data : vertexAttributes) {
                if (data.second.m_updated && data.second.m_enabled) {
                    unsigned long ptrOffset = reinterpret_cast<const char*>(data.second.m_pointer) -
                                              GlVertexAttribPointerManager::getSmallestPtrRender();
                    g_glVertexAttribPointer(data.second.m_index, data.second.m_size, data.second.m_type, data.second.m_normalized,
                                            data.second.m_stride, reinterpret_cast<const GLvoid*>(m_attribsData.data() + ptrOffset));
                    data.second.m_updated = false;
                }
            }

            std::copy_n(m_data->val().begin(), m_data->val().size(), m_attribsData.begin());
            g_glDrawElements(m_mode, m_count, m_type, m_indices.get());
            GlVertexAttribPointerManager::releaseVectorFromPool(m_data);
		}
	private:
		void set(GLenum mode, GLsizei count, GLenum type, std::unique_ptr<u8[]> indices,
			splicer::Node<std::vector<char>>* data)
		{
			m_mode = mode;
			m_count = count;
			m_type = type;
			m_indices = std::move(indices);
			m_data = data;
		}

		GLenum m_mode;
		GLsizei m_count;
		GLenum m_type;
		std::unique_ptr<u8[]> m_indices;
        splicer::Node<std::vector<char>>* m_data;
        static std::vector<char> m_attribsData;
	};

	class GlLineWidthCommand : public OpenGlCommand
	{
	public:
		GlLineWidthCommand() :
			OpenGlCommand(false, false, "glLineWidth")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLfloat width)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlLineWidthCommand>(poolId);
			ptr->set(width);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glLineWidth(m_width);
		}
	private:
		void set(GLfloat width)
		{
			m_width = width;
		}

		GLfloat m_width;
	};

	class GlClearCommand : public OpenGlCommand
	{
	public:
		GlClearCommand() :
			OpenGlCommand(false, false, "glClear")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLbitfield mask)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlClearCommand>(poolId);
			ptr->set(mask);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glClear(m_mask);
		}
	private:
		void set(GLbitfield mask)
		{
			m_mask = mask;
		}

		GLbitfield m_mask;
	};

	class GlClearBufferfvCommand : public OpenGlCommand
	{
	public:
		GlClearBufferfvCommand() :
			OpenGlCommand(false, false, "glClearBufferfv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum buffer, GLint drawbuffer, std::unique_ptr<GLfloat[]> value)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlClearBufferfvCommand>(poolId);
			ptr->set(buffer, drawbuffer, std::move(value));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glClearBufferfv(m_buffer, m_drawbuffer, m_value.get());
		}
	private:
		void set(GLenum buffer, GLint drawbuffer, std::unique_ptr<GLfloat[]> value)
		{
			m_buffer = buffer;
			m_drawbuffer = drawbuffer;
			m_value = std::move(value);
		}

		GLenum m_buffer;
		GLint m_drawbuffer;
		std::unique_ptr<GLfloat[]> m_value;
	};

	class GlGetFloatvCommand : public OpenGlCommand
	{
	public:
		GlGetFloatvCommand() :
			OpenGlCommand(true, false, "glGetFloatv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum pname, GLfloat* data)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetFloatvCommand>(poolId);
			ptr->set(pname, data);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetFloatv(m_pname, m_data);
		}
	private:
		void set(GLenum pname, GLfloat* data)
		{
			m_pname = pname;
			m_data = data;
		}

		GLenum m_pname;
		GLfloat* m_data;
	};

	class GlDeleteTexturesCommand : public OpenGlCommand
	{
	public:
		GlDeleteTexturesCommand() :
			OpenGlCommand(false, false, "glDeleteTextures")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, std::unique_ptr<GLuint[]> textures)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteTexturesCommand>(poolId);
			ptr->set(n, std::move(textures));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteTextures(m_n, m_textures.get());
		}
	private:
		void set(GLsizei n, std::unique_ptr<GLuint[]> textures)
		{
			m_n = n;
			m_textures = std::move(textures);
		}

		GLsizei m_n;
		std::unique_ptr<GLuint[]> m_textures;
	};

	class GlGenTexturesCommand : public OpenGlCommand
	{
	public:
		GlGenTexturesCommand() :
			OpenGlCommand(true, false, "glGenTextures")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* textures)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGenTexturesCommand>(poolId);
			ptr->set(n, textures);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGenTextures(m_n, m_textures);
		}
	private:
		void set(GLsizei n, GLuint* textures)
		{
			m_n = n;
			m_textures = textures;
		}

		GLsizei m_n;
		GLuint* m_textures;
	};

	class GlTexParameterfCommand : public OpenGlCommand
	{
	public:
		GlTexParameterfCommand() :
			OpenGlCommand(false, false, "glTexParameterf")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum pname, GLfloat param)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexParameterfCommand>(poolId);
			ptr->set(target, pname, param);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexParameterf(m_target, m_pname, m_param);
		}
	private:
		void set(GLenum target, GLenum pname, GLfloat param)
		{
			m_target = target;
			m_pname = pname;
			m_param = param;
		}

		GLenum m_target;
		GLenum m_pname;
		GLfloat m_param;
	};

	class GlActiveTextureCommand : public OpenGlCommand
	{
	public:
		GlActiveTextureCommand() :
			OpenGlCommand(false, false, "glActiveTexture")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum texture)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlActiveTextureCommand>(poolId);
			ptr->set(texture);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glActiveTexture(m_texture);
		}
	private:
		void set(GLenum texture)
		{
			m_texture = texture;
		}

		GLenum m_texture;
	};

	class GlBlendColorCommand : public OpenGlCommand
	{
	public:
		GlBlendColorCommand() :
			OpenGlCommand(false, false, "glBlendColor")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBlendColorCommand>(poolId);
			ptr->set(red, green, blue, alpha);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBlendColor(m_red, m_green, m_blue, m_alpha);
		}
	private:
		void set(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
		{
			m_red = red;
			m_green = green;
			m_blue = blue;
			m_alpha = alpha;
		}

		GLfloat m_red;
		GLfloat m_green;
		GLfloat m_blue;
		GLfloat m_alpha;
	};

	class GlReadBufferCommand : public OpenGlCommand
	{
	public:
		GlReadBufferCommand() :
			OpenGlCommand(false, false, "glReadBuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum src)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlReadBufferCommand>(poolId);
			ptr->set(src);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glReadBuffer(m_src);
		}
	private:
		void set(GLenum src)
		{
			m_src = src;
		}

		GLenum m_src;
	};

	class GlCreateShaderCommand : public OpenGlCommand
	{
	public:
		GlCreateShaderCommand() :
			OpenGlCommand(true, true, "glCreateShader")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum type, GLuint& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCreateShaderCommand>(poolId);
			ptr->set(type, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glCreateShader(m_type);
		}
	private:
		void set(GLenum type, GLuint& returnValue)
		{
			m_type = type;
			m_returnValue = &returnValue;
		}

		GLenum m_type;
		GLuint* m_returnValue;
	};

	class GlCompileShaderCommand : public OpenGlCommand
	{
	public:
		GlCompileShaderCommand() :
			OpenGlCommand(false, false, "glCompileShader")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint shader)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCompileShaderCommand>(poolId);
			ptr->set(shader);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glCompileShader(m_shader);
		}
	private:
		void set(GLuint shader)
		{
			m_shader = shader;
		}

		GLuint m_shader;
	};

	class GlShaderSourceCommand : public OpenGlCommand
	{
	public:
		GlShaderSourceCommand() :
			OpenGlCommand(false, false, "glShaderSource")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint shader, const std::string& string)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlShaderSourceCommand>(poolId);
			ptr->set(shader, string);
			return ptr;
		}

		void commandToExecute() override
		{
			const GLchar* strShaderData = m_string.data();
			g_glShaderSource(m_shader, 1, &strShaderData, nullptr);
		}
	private:
		void set(GLuint shader, const std::string& string)
		{
			m_shader = shader;
			m_string = std::move(string);
		}

		GLuint m_shader;
		std::string m_string;
	};

	class GlCreateProgramCommand : public OpenGlCommand
	{
	public:
		GlCreateProgramCommand() :
			OpenGlCommand(true, true, "glCreateProgram")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCreateProgramCommand>(poolId);
			ptr->set(returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glCreateProgram();
		}
	private:
		void set(GLuint& returnValue)
		{
			m_returnValue = &returnValue;
		}

		GLuint* m_returnValue;
	};

	class GlAttachShaderCommand : public OpenGlCommand
	{
	public:
		GlAttachShaderCommand() :
			OpenGlCommand(false, false, "glAttachShader")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLuint shader)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlAttachShaderCommand>(poolId);
			ptr->set(program, shader);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glAttachShader(m_program, m_shader);
		}
	private:
		void set(GLuint program, GLuint shader)
		{
			m_program = program;
			m_shader = shader;
		}

		GLuint m_program;
		GLuint m_shader;
	};

	class GlLinkProgramCommand : public OpenGlCommand
	{
	public:
		GlLinkProgramCommand() :
			OpenGlCommand(false, false, "glLinkProgram")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlLinkProgramCommand>(poolId);
			ptr->set(program);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glLinkProgram(m_program);
		}
	private:
		void set(GLuint program)
		{
			m_program = program;
		}

		GLuint m_program;
	};

	class GlUseProgramCommand : public OpenGlCommand
	{
	public:
		GlUseProgramCommand() :
			OpenGlCommand(false, false, "glUseProgram")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUseProgramCommand>(poolId);
			ptr->set(program);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUseProgram(m_program);
		}
	private:
		void set(GLuint program)
		{
			m_program = program;
		}

		GLuint m_program;
	};

	class GlGetUniformLocationCommand : public OpenGlCommand
	{
	public:
		GlGetUniformLocationCommand() :
			OpenGlCommand(true, true, "glGetUniformLocation")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, const GLchar* name, GLint& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetUniformLocationCommand>(poolId);
			ptr->set(program, name, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glGetUniformLocation(m_program, m_name);
		}
	private:
		void set(GLuint program, const GLchar* name, GLint& returnValue)
		{
			m_program = program;
			m_name = name;
			m_returnValue = &returnValue;
		}

		GLint* m_returnValue;
		GLuint m_program;
		const GLchar* m_name;
	};

	class GlUniform1iCommand : public OpenGlCommand
	{
	public:
		GlUniform1iCommand() :
			OpenGlCommand(false, false, "glUniform1i")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLint v0)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform1iCommand>(poolId);
			ptr->set(location, v0);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform1i(m_location, m_v0);
		}
	private:
		void set(GLint location, GLint v0)
		{
			m_location = location;
			m_v0 = v0;
		}

		GLint m_location;
		GLint m_v0;
	};

	class GlUniform1fCommand : public OpenGlCommand
	{
	public:
		GlUniform1fCommand() :
			OpenGlCommand(false, false, "glUniform1f")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLfloat v0)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform1fCommand>(poolId);
			ptr->set(location, v0);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform1f(m_location, m_v0);
		}
	private:
		void set(GLint location, GLfloat v0)
		{
			m_location = location;
			m_v0 = v0;
		}

		GLint m_location;
		GLfloat m_v0;
	};

	class GlUniform2fCommand : public OpenGlCommand
	{
	public:
		GlUniform2fCommand() :
			OpenGlCommand(false, false, "glUniform2f")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLfloat v0, GLfloat v1)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform2fCommand>(poolId);
			ptr->set(location, v0, v1);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform2f(m_location, m_v0, m_v1);
		}
	private:
		void set(GLint location, GLfloat v0, GLfloat v1)
		{
			m_location = location;
			m_v0 = v0;
			m_v1 = v1;
		}

		GLint m_location;
		GLfloat m_v0;
		GLfloat m_v1;
	};

	class GlUniform2iCommand : public OpenGlCommand
	{
	public:
		GlUniform2iCommand() :
			OpenGlCommand(false, false, "glUniform2i")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLint v0, GLint v1)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform2iCommand>(poolId);
			ptr->set(location, v0, v1);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform2i(m_location, m_v0, m_v1);
		}
	private:
		void set(GLint location, GLint v0, GLint v1)
		{
			m_location = location;
			m_v0 = v0;
			m_v1 = v1;
		}

		GLint m_location;
		GLint m_v0;
		GLint m_v1;
	};

	class GlUniform4iCommand : public OpenGlCommand
	{
	public:
		GlUniform4iCommand() :
			OpenGlCommand(false, false, "glUniform4i")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform4iCommand>(poolId);
			ptr->set(location, v0, v1, v2, v3);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform4i(m_location, m_v0, m_v1, m_v2, m_v3);
		}
	private:
		void set(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
		{
			m_location = location;
			m_v0 = v0;
			m_v1 = v1;
			m_v2 = v2;
			m_v3 = v3;
		}

		GLint m_location;
		GLint m_v0;
		GLint m_v1;
		GLint m_v2;
		GLint m_v3;
	};

	class GlUniform4fCommand : public OpenGlCommand
	{
	public:
		GlUniform4fCommand() :
			OpenGlCommand(false, false, "glUniform4f")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform4fCommand>(poolId);
			ptr->set(location, v0, v1, v2, v3);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform4f(m_location, m_v0, m_v1, m_v2, m_v3);
		}
	private:
		void set(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
		{
			m_location = location;
			m_v0 = v0;
			m_v1 = v1;
			m_v2 = v2;
			m_v3 = v3;
		}

		GLint m_location;
		GLfloat m_v0;
		GLfloat m_v1;
		GLfloat m_v2;
		GLfloat m_v3;
	};

	class GlUniform3fvCommand : public OpenGlCommand
	{
	public:
		GlUniform3fvCommand() :
			OpenGlCommand(false, false, "glUniform3fv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLsizei count, std::unique_ptr<GLfloat[]> value)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform3fvCommand>(poolId);
			ptr->set(location, count, std::move(value));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform3fv(m_location, m_count, m_value.get());
		}
	private:
		void set(GLint location, GLsizei count, std::unique_ptr<GLfloat[]> value)
		{
			m_location = location;
			m_count = count;
			m_value = std::move(value);
		}

		GLint m_location;
		GLsizei m_count;
		std::unique_ptr<GLfloat[]> m_value;
	};

	class GlUniform4fvCommand : public OpenGlCommand
	{
	public:
		GlUniform4fvCommand() :
			OpenGlCommand(false, false, "glUniform4fv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint location, GLsizei count, std::unique_ptr<GLfloat[]> value)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniform4fvCommand>(poolId);
			ptr->set(location, count, std::move(value));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniform4fv(m_location, m_count, m_value.get());
		}
	private:
		void set(GLint location, GLsizei count, std::unique_ptr<GLfloat[]> value)
		{
			m_location = location;
			m_count = count;
			m_value = std::move(value);
		}

		GLint m_location;
		GLsizei m_count;
		std::unique_ptr<GLfloat[]> m_value;
	};

	class GlDetachShaderCommand : public OpenGlCommand
	{
	public:
		GlDetachShaderCommand() :
			OpenGlCommand(false, false, "glDetachShader")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLuint shader)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDetachShaderCommand>(poolId);
			ptr->set(program, shader);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDetachShader(m_program, m_shader);
		}
	private:
		void set(GLuint program, GLuint shader)
		{
			m_program = program;
			m_shader = shader;
		}

		GLuint m_program;
		GLuint m_shader;
	};

	class GlDeleteShaderCommand : public OpenGlCommand
	{
	public:
		GlDeleteShaderCommand() :
			OpenGlCommand(false, false, "glDeleteShader")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint shader)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteShaderCommand>(poolId);
			ptr->set(shader);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteShader(m_shader);
		}
	private:
		void set(GLuint shader)
		{
			m_shader = shader;
		}

		GLuint m_shader;
	};

	class GlDeleteProgramCommand : public OpenGlCommand
	{
	public:
		GlDeleteProgramCommand() :
			OpenGlCommand(false, false, "glDeleteProgram")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteProgramCommand>(poolId);
			ptr->set(program);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteProgram(m_program);
		}
	private:
		void set(GLuint program)
		{
			m_program = program;
		}

		GLuint m_program;
	};

	class GlGetProgramInfoLogCommand : public OpenGlCommand
	{
	public:
		GlGetProgramInfoLogCommand() :
			OpenGlCommand(true, true, "glGetProgramInfoLog")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetProgramInfoLogCommand>(poolId);
			ptr->set(program, bufSize, length, infoLog);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetProgramInfoLog(m_program, m_bufSize, m_length, m_infoLog);
		}
	private:
		void set(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
		{
			m_program = program;
			m_bufSize = bufSize;
			m_length = length;
			m_infoLog = infoLog;
		}

		GLuint m_program;
		GLsizei m_bufSize;
		GLsizei* m_length;
		GLchar* m_infoLog;
	};

	class GlGetShaderInfoLogCommand : public OpenGlCommand
	{
	public:
		GlGetShaderInfoLogCommand() :
			OpenGlCommand(true, true, "glGetShaderInfoLog")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetShaderInfoLogCommand>(poolId);
			ptr->set(shader, bufSize, length, infoLog);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetShaderInfoLog(m_shader, m_bufSize, m_length, m_infoLog);
		}
	private:
		void set(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
		{
			m_shader = shader;
			m_bufSize = bufSize;
			m_length = length;
			m_infoLog = infoLog;
		}

		GLuint m_shader;
		GLsizei m_bufSize;
		GLsizei* m_length;
		GLchar* m_infoLog;
	};

	class GlGetShaderivCommand : public OpenGlCommand
	{
	public:
		GlGetShaderivCommand() :
			OpenGlCommand(true, true, "glGetShaderiv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint shader, GLenum pname, GLint* params)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetShaderivCommand>(poolId);
			ptr->set(shader, pname, params);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetShaderiv(m_shader, m_pname, m_params);
		}
	private:
		void set(GLuint shader, GLenum pname, GLint* params)
		{
			m_shader = shader;
			m_pname = pname;
			m_params = params;
		}

		GLuint m_shader;
		GLenum m_pname;
		GLint* m_params;
	};

	class GlGetProgramivCommand : public OpenGlCommand
	{
	public:
		GlGetProgramivCommand() :
			OpenGlCommand(true, true, "glGetProgramiv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLenum pname, GLint* params)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetProgramivCommand>(poolId);
			ptr->set(program, pname, params);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetProgramiv(m_program, m_pname, m_params);
		}
	private:
		void set(GLuint program, GLenum pname, GLint* params)
		{
			m_program = program;
			m_pname = pname;
			m_params = params;
		}

		GLuint m_program;
		GLenum m_pname;
		GLint* m_params;
	};

	class GlEnableVertexAttribArrayCommand : public OpenGlCommand
	{
	public:
		GlEnableVertexAttribArrayCommand() :
			OpenGlCommand(false, false, "glEnableVertexAttribArray")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint index)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlEnableVertexAttribArrayCommand>(poolId);
			ptr->set(index);
			return ptr;
		}

		void commandToExecute() override
		{
            GlVertexAttribPointerManager::enableVertexAttributeIndexRender(m_index);
            g_glEnableVertexAttribArray(m_index);
		}
	private:
		void set(GLuint index)
		{
			m_index = index;
		}

		GLuint m_index;
	};

	class GlDisableVertexAttribArrayCommand : public OpenGlCommand
	{
	public:
		GlDisableVertexAttribArrayCommand() :
			OpenGlCommand(false, false, "glDisableVertexAttribArray")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint index)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDisableVertexAttribArrayCommand>(poolId);
			ptr->set(index);
			return ptr;
		}

		void commandToExecute() override
		{
            GlVertexAttribPointerManager::disableVertexAttributeIndexRender(m_index);
			g_glDisableVertexAttribArray(m_index);
		}
	private:
		void set(GLuint index)
		{
			m_index = index;
		}

		GLuint m_index;
	};

	class GlVertexAttribPointerBufferedCommand : public OpenGlCommand
	{
	public:
		GlVertexAttribPointerBufferedCommand() :
			OpenGlCommand(false, false, "glVertexAttribPointer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
        	const GLvoid* offset)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlVertexAttribPointerBufferedCommand>(poolId);
			ptr->set(index, size, type, normalized, stride, offset);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glVertexAttribPointer(m_index, m_size, m_type, m_normalized, m_stride, m_offset);
		}
	private:
		void set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
        	const GLvoid* offset)
		{
			m_index = index;
			m_size = size;
			m_type = type;
			m_normalized = normalized;
			m_stride = stride;
			m_offset = offset;
		}

		GLuint m_index;
		GLint m_size;
		GLenum m_type;
		GLboolean m_normalized;
		GLsizei m_stride;
        const GLvoid* m_offset;
	};

	class GlBindAttribLocationCommand : public OpenGlCommand
	{
	public:
		GlBindAttribLocationCommand() :
			OpenGlCommand(false, false, "glBindAttribLocation")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLuint index, const std::string& name)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindAttribLocationCommand>(poolId);
			ptr->set(program, index, name);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindAttribLocation(m_program, m_index, m_name.data());
		}
	private:
		void set(GLuint program, GLuint index, const std::string& name)
		{
			m_program = program;
			m_index = index;
			m_name = std::move(name);
		}

		GLuint m_program;
		GLuint m_index;
		std::string m_name;
	};

	class GlVertexAttrib1fCommand : public OpenGlCommand
	{
	public:
		GlVertexAttrib1fCommand() :
			OpenGlCommand(false, false, "glVertexAttrib1f")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint index, GLfloat x)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlVertexAttrib1fCommand>(poolId);
			ptr->set(index, x);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glVertexAttrib1f(m_index, m_x);
		}
	private:
		void set(GLuint index, GLfloat x)
		{
			m_index = index;
			m_x = x;
		}

		GLuint m_index;
		GLfloat m_x;
	};

	class GlVertexAttrib4fCommand : public OpenGlCommand
	{
	public:
		GlVertexAttrib4fCommand() :
			OpenGlCommand(false, false, "glVertexAttrib4f")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlVertexAttrib4fCommand>(poolId);
			ptr->set(index, x, y, z, w);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glVertexAttrib4f(m_index, m_x, m_y, m_z, m_w);
		}
	private:
		void set(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
			m_index = index;
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		GLuint m_index;
		GLfloat m_x;
		GLfloat m_y;
		GLfloat m_z;
		GLfloat m_w;
	};

	class GlVertexAttrib4fvCommand : public OpenGlCommand
	{
	public:
		GlVertexAttrib4fvCommand() :
			OpenGlCommand(false, false, "glVertexAttrib4fv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint index, std::unique_ptr<GLfloat[]> v)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlVertexAttrib4fvCommand>(poolId);
			ptr->set(index, std::move(v));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glVertexAttrib4fv(m_index, m_v.get());
		}
	private:
		void set(GLuint index, std::unique_ptr<GLfloat[]> v)
		{
			m_index = index;
			m_v = std::move(v);
		}

		GLuint m_index;
		std::unique_ptr<GLfloat[]> m_v;
	};

	class GlDepthRangefCommand : public OpenGlCommand
	{
	public:
		GlDepthRangefCommand() :
			OpenGlCommand(false, false, "glDepthRangef")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLfloat n, GLfloat f)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDepthRangefCommand>(poolId);
			ptr->set(n, f);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDepthRangef(m_n,m_f);
		}
	private:
		void set(GLfloat n, GLfloat f)
		{
			m_n = n;
			m_f = f;
		}

		GLfloat m_n;
		GLfloat m_f;
	};

	class GlClearDepthfCommand : public OpenGlCommand
	{
	public:
		GlClearDepthfCommand() :
			OpenGlCommand(false, false, "glClearDepthf")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLfloat d)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlClearDepthfCommand>(poolId);
			ptr->set(d);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glClearDepthf(m_d);
		}
	private:
		void set(GLfloat d)
		{
			m_d = d;
		}

		GLfloat m_d;
	};

	class GlDrawBuffersCommand : public OpenGlCommand
	{
	public:
		GlDrawBuffersCommand() :
			OpenGlCommand(false, false, "glDrawBuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, std::unique_ptr<GLenum[]> bufs)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDrawBuffersCommand>(poolId);
			ptr->set(n, std::move(bufs));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDrawBuffers(m_n, m_bufs.get());
		}
	private:
		void set(GLsizei n, std::unique_ptr<GLenum[]> bufs)
		{
			m_n = n;
			m_bufs = std::move(bufs);
		}

		GLsizei m_n;
		std::unique_ptr<GLenum[]> m_bufs;
	};

	class GlGenFramebuffersCommand : public OpenGlCommand
	{
	public:
		GlGenFramebuffersCommand() :
			OpenGlCommand(true, false, "glGenFramebuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* framebuffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGenFramebuffersCommand>(poolId);
			ptr->set(n, framebuffers);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGenFramebuffers(m_n, m_framebuffers);
		}
	private:
		void set(GLsizei n, GLuint* framebuffers)
		{
			m_n = n;
			m_framebuffers = framebuffers;
		}

		GLsizei m_n;
		GLuint* m_framebuffers;
	};

	class GlBindFramebufferCommand : public OpenGlCommand
	{
	public:
		GlBindFramebufferCommand() :
			OpenGlCommand(false, false, "glBindFramebuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint framebuffer)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindFramebufferCommand>(poolId);
			ptr->set(target, framebuffer);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindFramebuffer(m_target, m_framebuffer);
		}
	private:
		void set(GLenum target, GLuint framebuffer)
		{
			m_target = target;
			m_framebuffer = framebuffer;
		}

		GLenum m_target;
		GLuint m_framebuffer;
	};

	class GlDeleteFramebuffersCommand : public OpenGlCommand
	{
	public:
		GlDeleteFramebuffersCommand() :
			OpenGlCommand(false, false, "glDeleteFramebuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, std::unique_ptr<GLuint[]> framebuffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteFramebuffersCommand>(poolId);
			ptr->set(n, std::move(framebuffers));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteFramebuffers(m_n, m_framebuffers.get());
		}
	private:
		void set(GLsizei n, std::unique_ptr<GLuint[]> framebuffers)
		{
			m_n = n;
			m_framebuffers = std::move(framebuffers);
		}

		GLsizei m_n;
		std::unique_ptr<GLuint[]> m_framebuffers;
	};

	class GlFramebufferTexture2DCommand : public OpenGlCommand
	{
	public:
		GlFramebufferTexture2DCommand() :
			OpenGlCommand(false, false, "glFramebufferTexture2D")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlFramebufferTexture2DCommand>(poolId);
			ptr->set(target, attachment, textarget, texture, level);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glFramebufferTexture2D(m_target, m_attachment, m_textarget, m_texture, m_level);
		}
	private:
		void set(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
		{
			m_target = target;
			m_attachment = attachment;
			m_textarget = textarget;
			m_texture = texture;
			m_level = level;
		}

		GLenum m_target;
		GLenum m_attachment;
		GLenum m_textarget;
		GLuint m_texture;
		GLint m_level;
	};

	class GlTexImage2DMultisampleCommand : public OpenGlCommand
	{
	public:
		GlTexImage2DMultisampleCommand() :
			OpenGlCommand(false, false, "glTexImage2DMultisample")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width,
			GLsizei height, GLboolean fixedsamplelocations)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexImage2DMultisampleCommand>(poolId);
			ptr->set(target, samples, internalformat, width, height, fixedsamplelocations);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexImage2DMultisample(m_target, m_samples, m_internalformat, m_width, m_height, m_fixedsamplelocations);
		}
	private:
		void set(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width,
			GLsizei height, GLboolean fixedsamplelocations)
		{
			m_target = target;
			m_samples = samples;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
			m_fixedsamplelocations = fixedsamplelocations;
		}

		GLenum m_target;
		GLsizei m_samples;
		GLenum m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
		GLboolean m_fixedsamplelocations;
	};

	class GlTexStorage2DMultisampleCommand : public OpenGlCommand
	{
	public:
		GlTexStorage2DMultisampleCommand() :
			OpenGlCommand(false, false, "glTexStorage2DMultisample")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width,
			GLsizei height, GLboolean fixedsamplelocations)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexStorage2DMultisampleCommand>(poolId);
			ptr->set(target, samples, internalformat, width, height, fixedsamplelocations);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexStorage2DMultisample(m_target, m_samples, m_internalformat, m_width, m_height, m_fixedsamplelocations);
		}
	private:
		void set(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width,
			GLsizei height, GLboolean fixedsamplelocations)
		{
			m_target = target;
			m_samples = samples;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
			m_fixedsamplelocations = fixedsamplelocations;
		}

		GLenum m_target;
		GLsizei m_samples;
		GLenum m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
		GLboolean m_fixedsamplelocations;
	};

	class GlGenRenderbuffersCommand : public OpenGlCommand
	{
	public:
		GlGenRenderbuffersCommand() :
			OpenGlCommand(true, false, "glGenRenderbuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* renderbuffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGenRenderbuffersCommand>(poolId);
			ptr->set(n, renderbuffers);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGenRenderbuffers(m_n, m_renderbuffers);
		}
	private:
		void set(GLsizei n, GLuint* renderbuffers)
		{
			m_n = n;
			m_renderbuffers = renderbuffers;
		}

		GLsizei m_n;
		GLuint* m_renderbuffers;
	};

	class GlBindRenderbufferCommand : public OpenGlCommand
	{
	public:
		GlBindRenderbufferCommand() :
			OpenGlCommand(false, false, "glBindRenderbuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint renderbuffer)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindRenderbufferCommand>(poolId);
			ptr->set(target, renderbuffer);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindRenderbuffer(m_target, m_renderbuffer);
		}
	private:
		void set(GLenum target, GLuint renderbuffer)
		{
			m_target = target;
			m_renderbuffer = renderbuffer;
		}

		GLenum m_target;
		GLuint m_renderbuffer;
	};

	class GlRenderbufferStorageCommand : public OpenGlCommand
	{
	public:
		GlRenderbufferStorageCommand() :
			OpenGlCommand(false, false, "glRenderbufferStorage")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlRenderbufferStorageCommand>(poolId);
			ptr->set(target, internalformat, width, height);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glRenderbufferStorage(m_target, m_internalformat, m_width, m_height);
		}
	private:
		void set(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
		{
			m_target = target;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
		}

		GLenum m_target;
		GLenum m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
	};

	class GlDeleteRenderbuffersCommand : public OpenGlCommand
	{
	public:
		GlDeleteRenderbuffersCommand() :
			OpenGlCommand(false, false, "glDeleteRenderbuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, std::unique_ptr<GLuint[]> renderbuffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteRenderbuffersCommand>(poolId);
			ptr->set(n, std::move(renderbuffers));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteRenderbuffers(m_n, m_renderbuffers.get());
		}
	private:
		void set(GLsizei n, std::unique_ptr<GLuint[]> renderbuffers)
		{
			m_n = n;
			m_renderbuffers = std::move(renderbuffers);
		}

		GLsizei m_n;
		std::unique_ptr<GLuint[]> m_renderbuffers;
	};

	class GlFramebufferRenderbufferCommand : public OpenGlCommand
	{
	public:
		GlFramebufferRenderbufferCommand() :
			OpenGlCommand(false, false, "glFramebufferRenderbuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlFramebufferRenderbufferCommand>(poolId);
			ptr->set(target, attachment, renderbuffertarget, renderbuffer);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glFramebufferRenderbuffer(m_target, m_attachment, m_renderbuffertarget, m_renderbuffer);
		}
	private:
		void set(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
		{
			m_target = target;
			m_attachment = attachment;
			m_renderbuffertarget = renderbuffertarget;
			m_renderbuffer = renderbuffer;
		}

		GLenum m_target;
		GLenum m_attachment;
		GLenum m_renderbuffertarget;
		GLuint m_renderbuffer;
	};

	class GlCheckFramebufferStatusCommand : public OpenGlCommand
	{
	public:
		GlCheckFramebufferStatusCommand() :
			OpenGlCommand(true, true, "glCheckFramebufferStatus")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCheckFramebufferStatusCommand>(poolId);
			ptr->set(target, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glCheckFramebufferStatus(m_target);
		}
	private:
		void set(GLenum target, GLenum& returnValue)
		{
			m_target = target;
			m_returnValue = &returnValue;
		}

		GLenum m_target;
		GLenum* m_returnValue;
	};

	class GlBlitFramebufferCommand : public OpenGlCommand
	{
	public:
		GlBlitFramebufferCommand() :
			OpenGlCommand(false, false, "glBlitFramebuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,
			GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBlitFramebufferCommand>(poolId);
			ptr->set(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBlitFramebuffer(m_srcX0, m_srcY0, m_srcX1, m_srcY1, m_dstX0, m_dstY0, m_dstX1, m_dstY1, m_mask,
				m_filter);
		}
	private:
		void set(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,
			GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
		{
			m_srcX0 = srcX0;
			m_srcY0 = srcY0;
			m_srcX1 = srcX1;
			m_srcY1 = srcY1;
			m_dstX0 = dstX0;
			m_dstY0 = dstY0;
			m_dstX1 = dstX1;
			m_dstY1 = dstY1;
			m_mask = mask;
			m_filter = filter;
		}

		GLint m_srcX0;
		GLint m_srcY0;
		GLint m_srcX1;
		GLint m_srcY1;
		GLint m_dstX0;
		GLint m_dstY0;
		GLint m_dstX1;
		GLint m_dstY1;
		GLbitfield m_mask;
		GLenum m_filter;
	};

	class GlGenVertexArraysCommand : public OpenGlCommand
	{
	public:
		GlGenVertexArraysCommand() :
			OpenGlCommand(true, false, "glGenVertexArrays")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* arrays)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGenVertexArraysCommand>(poolId);
			ptr->set(n, arrays);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGenVertexArrays(m_n, m_arrays);
		}
	private:
		void set(GLsizei n, GLuint* arrays)
		{
			m_n = n;
			m_arrays = arrays;
		}

		GLsizei m_n;
		GLuint* m_arrays;
	};

	class GlBindVertexArrayCommand : public OpenGlCommand
	{
	public:
		GlBindVertexArrayCommand() :
			OpenGlCommand(false, false, "glBindVertexArray")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint array)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindVertexArrayCommand>(poolId);
			ptr->set(array);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindVertexArray(m_array);
		}
	private:
		void set(GLuint array)
		{
			m_array = array;
		}

		GLuint m_array;
	};

	class GlDeleteVertexArraysCommand : public OpenGlCommand
	{
	public:
		GlDeleteVertexArraysCommand() :
			OpenGlCommand(false, false, "glDeleteVertexArrays")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, std::unique_ptr<GLuint[]> arrays)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteVertexArraysCommand>(poolId);
			ptr->set(n, std::move(arrays));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteVertexArrays(m_n, m_arrays.get());
		}
	private:
		void set(GLsizei n, std::unique_ptr<GLuint[]> arrays)
		{
			m_n = n;
			m_arrays = std::move(arrays);
		}

		GLsizei m_n;
		std::unique_ptr<GLuint[]> m_arrays;
	};

	class GlGenBuffersCommand : public OpenGlCommand
	{
	public:
		GlGenBuffersCommand() :
			OpenGlCommand(true, false, "glGenBuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* buffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGenBuffersCommand>(poolId);
			ptr->set(n, buffers);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGenBuffers(m_n, m_buffers);
		}
	private:
		void set(GLsizei n, GLuint* buffers)
		{
			m_n = n;
			m_buffers = buffers;
		}

		GLsizei m_n;
		GLuint* m_buffers;
	};

	class GlBindBufferCommand : public OpenGlCommand
	{
	public:
		GlBindBufferCommand() :
			OpenGlCommand(false, false, "glBindBuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint buffer)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindBufferCommand>(poolId);
			ptr->set(target, buffer);
			return ptr;
		}

		static GLuint getBoundBufferRender(GLenum target)
		{
			return m_boundBuffersRender[target];
		}

        static void setBoundBuffer(GLenum target, GLuint buffer)
        {
            m_boundBuffers[target] = buffer;
        }

        static GLuint getBoundBuffer(GLenum target)
        {
            return m_boundBuffers[target];
        }

		void commandToExecute() override
		{
			g_glBindBuffer(m_target, m_buffer);
            m_boundBuffersRender[m_target] = m_buffer;
		}
	private:
		void set(GLenum target, GLuint buffer)
		{
			m_target = target;
			m_buffer = buffer;
		}

		GLenum m_target;
		GLuint m_buffer;

		static std::unordered_map<GLenum, GLuint> m_boundBuffersRender;
        static std::unordered_map<GLenum, GLuint> m_boundBuffers;
	};

	template <class dataType>
	class GlBufferDataCommand : public OpenGlCommand
	{
	public:
		GlBufferDataCommand() :
			OpenGlCommand(false, false, "glBufferData")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizeiptr size, std::unique_ptr<dataType[]> data, GLenum usage)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBufferDataCommand>(poolId);
			ptr->set(target, size, std::move(data), usage);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBufferData(m_target, m_size, m_data.get(), m_usage);
		}
	private:
		void set(GLenum target, GLsizeiptr size, std::unique_ptr<dataType[]> data, GLenum usage)
		{
			m_target = target;
			m_size = size;
			m_data = std::move(data);
			m_usage = usage;
		}

		GLenum m_target;
		GLsizeiptr m_size;
		std::unique_ptr<dataType[]> m_data;
		GLenum m_usage;
	};

	class GlMapBufferCommand : public OpenGlCommand
	{
	public:
		GlMapBufferCommand() :
			OpenGlCommand(false, false, "glMapBuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLenum access)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlMapBufferCommand>(poolId);
			ptr->set(target, access);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glMapBuffer(m_target, m_access);
		}
	private:
		void set(GLenum target, GLenum access)
		{
			m_target = target;
			m_access = access;
		}

		GLenum m_target;
		GLenum m_access;
	};

	class GlMapBufferRangeCommand : public OpenGlCommand
	{
	public:
		GlMapBufferRangeCommand() :
			OpenGlCommand(true, true, "glMapBufferRange")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access,
			void*& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlMapBufferRangeCommand>(poolId);
			ptr->set(target, offset, length, access, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glMapBufferRange(m_target, m_offset, m_length, m_access);
		}
	private:
		void set(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access,
			void*& returnValue)
		{
			m_target = target;
			m_offset = offset;
			m_length = length;
			m_access = access;
			m_returnValue = &returnValue;
		}

		GLenum m_target;
		GLintptr m_offset;
		GLsizeiptr m_length;
		GLbitfield m_access;
		void** m_returnValue;
	};

	class GlMapBufferRangeWriteAsyncCommand : public OpenGlCommand
	{
	public:
		GlMapBufferRangeWriteAsyncCommand() :
			OpenGlCommand(false, false, "GlMapBufferRangeWriteAsyncCommand")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLintptr offset, u32 length,
			GLbitfield access, splicer::Node<std::vector<char>>* data)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlMapBufferRangeWriteAsyncCommand>(poolId);
			ptr->set(target, offset, length, access, data);
			return ptr;
		}

		void commandToExecute() override
		{
			void* buffer_pointer = g_glMapBufferRange(m_target, m_offset, m_length, m_access);
			memcpy(buffer_pointer, m_data->val().data(), m_length);
			m_vectorPool.release(m_data);
		}

        static std::shared_ptr<std::vector<u8>> getData(GLuint buffer, u32 length)
        {
            verifyBuffer(buffer, length);
            return m_TempData[buffer];
        }

		static void setTemp(GLenum target, GLintptr offset, u32 length, GLbitfield access)
		{
			m_targetTemp = target;
			m_offsetTemp = offset;
			m_lengthTemp = length;
			m_accessTemp = access;
		}

		static GLenum getTempTarget(void)
		{
			return m_targetTemp;
		}

		static GLintptr getTempOffset(void)
		{
			return m_offsetTemp;
		}

		static u32 getTempLength(void)
		{
			return m_lengthTemp;
		}

		static GLbitfield getTempAccess(void)
		{
			return m_accessTemp;
		}

		static splicer::Node<std::vector<char>>* getVectorFromPool() {
			return m_vectorPool.acquireOne().release();
		}

	private:
		void set(GLenum target, GLintptr offset, u32 length, GLbitfield access, splicer::Node<std::vector<char>>* data)
		{
			m_target = target;
			m_offset = offset;
			m_length = length;
			m_access = access;
			m_data = data;
		}

        static void verifyBuffer(GLuint buffer, u32 length)
        {
            if (m_TempData[buffer] == nullptr || m_TempData[buffer]->size() < length) {
                m_TempData[buffer] = std::make_shared<std::vector<u8>>(length);
            }
        }

		GLenum m_target;
		GLintptr m_offset;
		u32 m_length;
		GLbitfield m_access;
		splicer::Node<std::vector<char>>* m_data;

		static GLenum m_targetTemp;
		static GLintptr m_offsetTemp;
		static u32 m_lengthTemp;
		static GLbitfield m_accessTemp;
        static std::unordered_map<int, std::shared_ptr<std::vector<u8>>> m_TempData;
		static splicer::ObjectPool<std::vector<char>> m_vectorPool;
	public:
		static constexpr GLbitfield WRITE_ACCESS_ASYNC = GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
	};

	class GlMapBufferRangeReadAsyncCommand : public OpenGlCommand
	{
	public:
		GlMapBufferRangeReadAsyncCommand() :
			OpenGlCommand(false, false, "GlMapBufferRangeReadAsyncCommand")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLintptr offset, u32 length,
			GLbitfield access)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlMapBufferRangeReadAsyncCommand>(poolId);
			ptr->set(target, offset, length, access);
			return ptr;
		}

		void commandToExecute() override
		{
			void* buffer_pointer = g_glMapBufferRange(m_target, m_offset, m_length, m_access);

			if (buffer_pointer != nullptr) {
				std::unique_lock<std::mutex> lock(m_mapMutex);
				GLuint buffer = GlBindBufferCommand::getBoundBufferRender(m_target);
				verifyBuffer(buffer, m_length);
				auto data = m_data[buffer];
				memcpy(data->data(), buffer_pointer, m_length);
			}
		}

		static std::shared_ptr<std::vector<u8>> getData(GLuint buffer, u32 length)
		{
			std::unique_lock<std::mutex> lock(m_mapMutex);
			verifyBuffer(buffer, length);
			return m_data[buffer];
		}
		
	private:
		void set(GLenum target, GLintptr offset, u32 length, GLbitfield access)
		{
			m_target = target;
			m_offset = offset;
			m_length = length;
			m_access = access;
		}
	
		static void verifyBuffer(GLuint buffer, u32 length)
		{
			if (m_data[buffer] == nullptr || m_data[buffer]->size() < length) {
				m_data[buffer] = std::make_shared<std::vector<u8>>(length);
			}
		}
		
		GLenum m_target;
		GLintptr m_offset;
		u32 m_length;
		GLbitfield m_access;
		static std::unordered_map<int, std::shared_ptr<std::vector<u8>>> m_data;
		static std::mutex m_mapMutex;
	};

	class GlUnmapBufferCommand : public OpenGlCommand
	{
	public:
		GlUnmapBufferCommand() :
			OpenGlCommand(true, true, "glUnmapBuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLboolean& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUnmapBufferCommand>(poolId);
			ptr->set(target, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glUnmapBuffer(m_target);
		}
	private:
		void set(GLenum target, GLboolean& returnValue)
		{
			m_target = target;
			m_returnValue = &returnValue;
		}

		GLenum m_target;
		GLboolean* m_returnValue;
	};

	class GlUnmapBufferAsyncCommand : public OpenGlCommand
	{
	public:
		GlUnmapBufferAsyncCommand() :
			OpenGlCommand(false, false, "glUnmapBuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUnmapBufferAsyncCommand>(poolId);
			ptr->set(target);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUnmapBuffer(m_target);
		}
	private:
		void set(GLenum target)
		{
			m_target = target;
		}

		GLenum m_target;
	};

	class GlDeleteBuffersCommand : public OpenGlCommand
	{
	public:
		GlDeleteBuffersCommand() :
			OpenGlCommand(false, false, "glDeleteBuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, std::unique_ptr<GLuint[]> buffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteBuffersCommand>(poolId);
			ptr->set(n, std::move(buffers));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteBuffers(m_n, m_buffers.get());
		}
	private:
		void set(GLsizei n, std::unique_ptr<GLuint[]> buffers)
		{
			m_n = n;
			m_buffers = std::move(buffers);
		}

		GLsizei m_n;
		std::unique_ptr<GLuint[]> m_buffers;
	};

	class GlBindImageTextureCommand : public OpenGlCommand
	{
	public:
		GlBindImageTextureCommand() :
			OpenGlCommand(false, false, "glBindImageTexture")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer,
			GLenum access, GLenum format)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindImageTextureCommand>(poolId);
			ptr->set(unit, texture, level, layered, layer, access, format);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindImageTexture(m_unit, m_texture, m_level, m_layered, m_layer, m_access, m_format);
		}
	private:
		void set(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer,
			GLenum access, GLenum format)
		{
			m_unit = unit;
			m_texture = texture;
			m_level = level;
			m_layered = layered;
			m_layer = layer;
			m_access = access;
			m_format = format;
		}

		GLuint m_unit;
		GLuint m_texture;
		GLint m_level;
		GLboolean m_layered;
		GLint m_layer;
		GLenum m_access;
		GLenum m_format;
	};

	class GlMemoryBarrierCommand : public OpenGlCommand
	{
	public:
		GlMemoryBarrierCommand() :
			OpenGlCommand(false, false, "glMemoryBarrier")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLbitfield barriers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlMemoryBarrierCommand>(poolId);
			ptr->set(barriers);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glMemoryBarrier(m_barriers);
		}
	private:
		void set(GLbitfield barriers)
		{
			m_barriers = barriers;
		}

		GLbitfield m_barriers;
	};

	class GlTextureBarrierCommand : public OpenGlCommand
	{
	public:
		GlTextureBarrierCommand() :
			OpenGlCommand(false, false, "glTextureBarrier")
		{
		}

		static std::shared_ptr<OpenGlCommand> get()
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureBarrierCommand>(poolId);
			ptr->set();
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureBarrier();
		}
	private:
		void set()
		{
		}
	};

	class GlTextureBarrierNVCommand : public OpenGlCommand
	{
	public:
		GlTextureBarrierNVCommand() :
			OpenGlCommand(false, false, "glTextureBarrierNV")
		{
		}

		static std::shared_ptr<OpenGlCommand> get()
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureBarrierNVCommand>(poolId);
			ptr->set();
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureBarrierNV();
		}
	private:
		void set()
		{
		}
	};

	class GlGetStringiCommand : public OpenGlCommand
	{
	public:
		GlGetStringiCommand() :
			OpenGlCommand(true, false, "glGetStringi")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum name, GLuint index, const GLubyte*& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetStringiCommand>(poolId);
			ptr->set(name, index, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glGetStringi(m_name, m_index);
		}
	private:
		void set(GLenum name, GLuint index, const GLubyte*& returnValue)
		{
			m_name = name;
			m_index = index;
			m_returnValue = &returnValue;
		}

		GLenum m_name;
		GLuint m_index;
		const GLubyte** m_returnValue;
	};

	class GlInvalidateFramebufferCommand : public OpenGlCommand
	{
	public:
		GlInvalidateFramebufferCommand() :
			OpenGlCommand(false, false, "glInvalidateFramebuffer")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizei numAttachments, std::unique_ptr<GLenum[]> attachments)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlInvalidateFramebufferCommand>(poolId);
			ptr->set(target, numAttachments, std::move(attachments));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glInvalidateFramebuffer(m_target, m_numAttachments, m_attachments.get());
		}
	private:
		void set(GLenum target, GLsizei numAttachments, std::unique_ptr<GLenum[]> attachments)
		{
			m_target = target;
			m_numAttachments = numAttachments;
			m_attachments = std::move(attachments);
		}

		GLenum m_target;
		GLsizei m_numAttachments;
		std::unique_ptr<GLenum[]> m_attachments;
	};

	template <class dataType>
	class GlBufferStorageCommand : public OpenGlCommand
	{
	public:
		GlBufferStorageCommand() :
			OpenGlCommand(false, false, "glBufferStorage")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizeiptr size, std::unique_ptr<dataType[]> data, GLbitfield flags)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBufferStorageCommand>(poolId);
			ptr->set(target, size, std::move(data), flags);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBufferStorage(m_target, m_size, m_data.get(), m_flags);
		}
	private:
		void set(GLenum target, GLsizeiptr size, std::unique_ptr<dataType[]> data, GLbitfield flags)
		{
			m_target = target;
			m_size = size;
			m_data = std::move(data);
			m_flags = flags;
		}

		GLenum m_target;
		GLsizeiptr m_size;
		std::unique_ptr<dataType[]> m_data;
		GLbitfield m_flags;
	};

	class GlFenceSyncCommand : public OpenGlCommand
	{
	public:
		GlFenceSyncCommand() :
			OpenGlCommand(true, false, "glFenceSync")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum condition, GLbitfield flags, GLsync& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlFenceSyncCommand>(poolId);
			ptr->set(condition, flags, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glFenceSync(m_condition, m_flags);
		}
	private:
		void set(GLenum condition, GLbitfield flags, GLsync& returnValue)
		{
			m_condition = condition;
			m_flags = flags;
			m_returnValue = &returnValue;
		}

		GLenum m_condition;
		GLbitfield m_flags;
		GLsync* m_returnValue;
	};

	class GlClientWaitSyncCommand : public OpenGlCommand
	{
	public:
		GlClientWaitSyncCommand() :
			OpenGlCommand(true, false, "glClientWaitSync")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsync sync, GLbitfield flags, GLuint64 timeout)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlClientWaitSyncCommand>(poolId);
			ptr->set(sync, flags, timeout);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glClientWaitSync(m_sync, m_flags, m_timeout);
		}
	private:
		void set(GLsync sync, GLbitfield flags, GLuint64 timeout)
		{
			m_sync = sync;
			m_flags = flags;
			m_timeout = timeout;
		}

		GLsync m_sync;
		GLbitfield m_flags;
		GLuint64 m_timeout;
	};

	class GlDeleteSyncCommand : public OpenGlCommand
	{
	public:
		GlDeleteSyncCommand() :
			OpenGlCommand(true, false, "glDeleteSync")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsync sync)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDeleteSyncCommand>(poolId);
			ptr->set(sync);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDeleteSync(m_sync);
		}
	private:
		void set(GLsync sync)
		{
			m_sync = sync;
		}

		GLsync m_sync;
	};

	class GlGetUniformBlockIndexCommand : public OpenGlCommand
	{
	public:
		GlGetUniformBlockIndexCommand() :
			OpenGlCommand(true, true, "glGetUniformBlockIndex")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, const GLchar* uniformBlockName, GLuint& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetUniformBlockIndexCommand>(poolId);
			ptr->set(program, uniformBlockName, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = g_glGetUniformBlockIndex(m_program, m_uniformBlockName);
		}
	private:
		void set(GLuint program, const GLchar* uniformBlockName, GLuint& returnValue)
		{
			m_program = program;
			m_uniformBlockName = uniformBlockName;
			m_returnValue = &returnValue;
		}

		GLuint m_program;
		const GLchar* m_uniformBlockName;
		GLuint* m_returnValue;
	};

	class GlUniformBlockBindingCommand : public OpenGlCommand
	{
	public:
		GlUniformBlockBindingCommand() :
			OpenGlCommand(false, false, "glUniformBlockBinding")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlUniformBlockBindingCommand>(poolId);
			ptr->set(program, uniformBlockIndex, uniformBlockBinding);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glUniformBlockBinding(m_program, m_uniformBlockIndex, m_uniformBlockBinding);
		}
	private:
		void set(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
		{
			m_program = program;
			m_uniformBlockIndex = uniformBlockIndex;
			m_uniformBlockBinding = uniformBlockBinding;
		}

		GLuint m_program;
		GLuint m_uniformBlockIndex;
		GLuint m_uniformBlockBinding;
	};

	class GlGetActiveUniformBlockivCommand : public OpenGlCommand
	{
	public:
		GlGetActiveUniformBlockivCommand() :
			OpenGlCommand(true, true, "glGetActiveUniformBlockiv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetActiveUniformBlockivCommand>(poolId);
			ptr->set(program, uniformBlockIndex, pname, params);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetActiveUniformBlockiv(m_program, m_uniformBlockIndex, m_pname, m_params);
		}
	private:
		void set(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
		{
			m_program = program;
			m_uniformBlockIndex = uniformBlockIndex;
			m_pname = pname;
			m_params = params;
		}

		GLuint m_program;
		GLuint m_uniformBlockIndex;
		GLenum m_pname;
		GLint* m_params;
	};

	class GlGetUniformIndicesCommand : public OpenGlCommand
	{
	public:
		GlGetUniformIndicesCommand() :
			OpenGlCommand(true, true, "glGetUniformIndices")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames,
			GLuint* uniformIndices)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetUniformIndicesCommand>(poolId);
			ptr->set(program, uniformCount, uniformNames, uniformIndices);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetUniformIndices(m_program, m_uniformCount, m_uniformNames, m_uniformIndices);
		}
	private:
		void set(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames,
			GLuint* uniformIndices)
		{
			m_program = program;
			m_uniformCount = uniformCount;
			m_uniformNames = uniformNames;
			m_uniformIndices = uniformIndices;
		}

		GLuint m_program;
		GLsizei m_uniformCount;
		const GLchar* const* m_uniformNames;
		GLuint* m_uniformIndices;
	};

	class GlGetActiveUniformsivCommand : public OpenGlCommand
	{
	public:
		GlGetActiveUniformsivCommand() :
			OpenGlCommand(true, true, "glGetActiveUniformsiv")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname,
			GLint* params)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetActiveUniformsivCommand>(poolId);
			ptr->set(program, uniformCount, uniformIndices, pname, params);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetActiveUniformsiv(m_program, m_uniformCount, m_uniformIndices, m_pname, m_params);
		}
	private:
		void set(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname,
			GLint* params)
		{
			m_program = program;
			m_uniformCount = uniformCount;
			m_uniformIndices = uniformIndices;
			m_pname = pname;
			m_params = params;
		}

		GLuint m_program;
		GLsizei m_uniformCount;
		const GLuint* m_uniformIndices;
		GLenum m_pname;
		GLint* m_params;
	};

	class GlBindBufferBaseCommand : public OpenGlCommand
	{
	public:
		GlBindBufferBaseCommand() :
			OpenGlCommand(false, false, "glBindBufferBase")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLuint index, GLuint buffer)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBindBufferBaseCommand>(poolId);
			ptr->set(target, index, buffer);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBindBufferBase(m_target, m_index, m_buffer);
		}
	private:
		void set(GLenum target, GLuint index, GLuint buffer)
		{
			m_target = target;
			m_index = index;
			m_buffer = buffer;
		}

		GLenum m_target;
		GLuint m_index;
		GLuint m_buffer;
	};

	template <class dataType>
	class GlBufferSubDataCommand : public OpenGlCommand
	{
	public:
		GlBufferSubDataCommand() :
			OpenGlCommand(false, false, "glBufferSubData")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLintptr offset, GLsizeiptr size, std::unique_ptr<dataType[]> data)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlBufferSubDataCommand>(poolId);
			ptr->set(target, offset, size, std::move(data));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glBufferSubData(m_target, m_offset, m_size, m_data.get());
		}
	private:
		void set(GLenum target, GLintptr offset, GLsizeiptr size, std::unique_ptr<dataType[]> data)
		{
			m_target = target;
			m_offset = offset;
			m_size = size;
			m_data = std::move(data);
		}

		GLenum m_target;
		GLintptr m_offset;
		GLsizeiptr m_size;
		std::unique_ptr<dataType[]> m_data;
	};

	class GlGetProgramBinaryCommand : public OpenGlCommand
	{
	public:
		GlGetProgramBinaryCommand() :
			OpenGlCommand(true, true, "glGetProgramBinary")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlGetProgramBinaryCommand>(poolId);
			ptr->set(program, bufSize, length, binaryFormat, binary);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glGetProgramBinary(m_program, m_bufSize, m_length, m_binaryFormat, m_binary);
		}
	private:
		void set(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary)
		{
			m_program = program;
			m_bufSize = bufSize;
			m_length = length;
			m_binaryFormat = binaryFormat;
			m_binary = binary;
		}

		GLuint m_program;
		GLsizei m_bufSize;
		GLsizei* m_length;
		GLenum* m_binaryFormat;
		void* m_binary;
	};

	template <class dataType>
	class GlProgramBinaryCommand : public OpenGlCommand
	{
	public:
		GlProgramBinaryCommand() :
			OpenGlCommand(false, false, "glProgramBinary")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLenum binaryFormat, std::unique_ptr<dataType[]> binary, GLsizei length)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlProgramBinaryCommand>(poolId);
			ptr->set(program, binaryFormat, std::move(binary), length);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glProgramBinary(m_program, m_binaryFormat, m_binary.get(), m_length);
		}
	private:
		void set(GLuint program, GLenum binaryFormat, std::unique_ptr<dataType[]> binary, GLsizei length)
		{
			m_program = program;
			m_binaryFormat = binaryFormat;
			m_binary = std::move(binary);
			m_length = length;
		}

		GLuint m_program;
		GLenum m_binaryFormat;
		std::unique_ptr<dataType[]> m_binary;
		GLsizei m_length;
	};

	class GlProgramParameteriCommand : public OpenGlCommand
	{
	public:
		GlProgramParameteriCommand() :
			OpenGlCommand(false, false, "glProgramParameteri")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint program, GLenum pname, GLint value)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlProgramParameteriCommand>(poolId);
			ptr->set(program, pname, value);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glProgramParameteri(m_program, m_pname, m_value);
		}
	private:
		void set(GLuint program, GLenum pname, GLint value)
		{
			m_program = program;
			m_pname = pname;
			m_value = value;
		}

		GLuint m_program;
		GLenum m_pname;
		GLint m_value;
	};

	class GlTexStorage2DCommand : public OpenGlCommand
	{
	public:
		GlTexStorage2DCommand() :
			OpenGlCommand(false, false, "glTexStorage2D")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTexStorage2DCommand>(poolId);
			ptr->set(target, levels, internalformat, width, height);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTexStorage2D(m_target, m_levels, m_internalformat, m_width, m_height);
		}
	private:
		void set(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
		{
			m_target = target;
			m_levels = levels;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
		}

		GLenum m_target;
		GLsizei m_levels;
		GLenum m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
	};

	class GlTextureStorage2DCommand : public OpenGlCommand
	{
	public:
		GlTextureStorage2DCommand() :
			OpenGlCommand(false, false, "glTextureStorage2D")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureStorage2DCommand>(poolId);
			ptr->set(texture, levels, internalformat, width, height);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureStorage2D(m_texture, m_levels, m_internalformat, m_width, m_height);
		}
	private:
		void set(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
		{
			m_texture = texture;
			m_levels = levels;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
		}

		GLuint m_texture;
		GLsizei m_levels;
		GLenum m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
	};

	class GlTextureSubImage2DUnbufferedCommand : public OpenGlCommand
	{
	public:
		GlTextureSubImage2DUnbufferedCommand() :
			OpenGlCommand(false, false, "glTextureSubImage2D")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
			GLsizei height, GLenum format, GLenum type, std::unique_ptr<u8[]> pixels)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureSubImage2DUnbufferedCommand>(poolId);
			ptr->set(texture, level, xoffset, yoffset, width, height, format, type, std::move(pixels));
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureSubImage2D(m_texture, m_level, m_xoffset, m_yoffset, m_width, m_height, m_format, m_type,
								  m_pixels.get());
		}
	private:
		void set(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
			GLsizei height, GLenum format, GLenum type, std::unique_ptr<u8[]> pixels)
		{
			m_texture = texture;
			m_level = level;
			m_xoffset = xoffset;
			m_yoffset = yoffset;
			m_width = width;
			m_height = height;
			m_format = format;
			m_type = type;
			m_pixels = std::move(pixels);
		}

		GLuint m_texture;
		GLint m_level;
		GLint m_xoffset;
		GLint m_yoffset;
		GLsizei m_width;
		GLsizei m_height;
		GLenum m_format;
		GLenum m_type;
		std::unique_ptr<u8[]> m_pixels;
	};

	class GlTextureStorage2DMultisampleCommand : public OpenGlCommand
	{
	public:
		GlTextureStorage2DMultisampleCommand() :
			OpenGlCommand(false, false, "glTextureStorage2DMultisample")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat,
			GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureStorage2DMultisampleCommand>(poolId);
			ptr->set(texture, target, samples, internalformat, width, height, fixedsamplelocations);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureStorage2DMultisample(m_texture, m_target, m_samples, m_internalformat,m_width, m_height,
				m_fixedsamplelocations);
		}
	private:
		void set(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat,
			GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
		{
			m_texture = texture;
			m_target = target;
			m_samples = samples;
			m_internalformat = internalformat;
			m_width = width;
			m_height = height;
			m_fixedsamplelocations = fixedsamplelocations;
		}

		GLuint m_texture;
		GLenum m_target;
		GLsizei m_samples;
		GLenum m_internalformat;
		GLsizei m_width;
		GLsizei m_height;
		GLboolean m_fixedsamplelocations;
	};

	class GlTextureParameteriCommand : public OpenGlCommand
	{
	public:
		GlTextureParameteriCommand() :
			OpenGlCommand(false, false, "glTextureParameteri")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint texture, GLenum pname, GLint param)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureParameteriCommand>(poolId);
			ptr->set(texture, pname, param);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureParameteri(m_texture, m_pname, m_param);
		}
	private:
		void set(GLuint texture, GLenum pname, GLint param)
		{
			m_texture = texture;
			m_pname = pname;
			m_param = param;
		}

		GLuint m_texture;
		GLenum m_pname;
		GLint m_param;
	};

	class GlTextureParameterfCommand : public OpenGlCommand
	{
	public:
		GlTextureParameterfCommand() :
			OpenGlCommand(false, false, "glTextureParameterf")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint texture, GLenum pname, GLfloat param)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlTextureParameterfCommand>(poolId);
			ptr->set(texture, pname, param);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glTextureParameterf(m_texture, m_pname, m_param);
		}
	private:
		void set(GLuint texture, GLenum pname, GLfloat param)
		{
			m_texture = texture;
			m_pname = pname;
			m_param = param;
		}

		GLuint m_texture;
		GLenum m_pname;
		GLfloat m_param;
	};

	class GlCreateTexturesCommand : public OpenGlCommand
	{
	public:
		GlCreateTexturesCommand() :
			OpenGlCommand(true, false, "glCreateTextures")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLsizei n, GLuint* textures)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCreateTexturesCommand>(poolId);
			ptr->set(target, n, textures);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glCreateTextures(m_target, m_n, m_textures);
		}
	private:
		void set(GLenum target, GLsizei n, GLuint* textures)
		{
			m_target = target;
			m_n = n;
			m_textures = textures;
		}

		GLenum m_target;
		GLsizei m_n;
		GLuint* m_textures;
	};

	class GlCreateBuffersCommand : public OpenGlCommand
	{
	public:
		GlCreateBuffersCommand() :
			OpenGlCommand(true, false, "glCreateBuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* buffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCreateBuffersCommand>(poolId);
			ptr->set(n, buffers);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glCreateBuffers(m_n, m_buffers);
		}
	private:
		void set(GLsizei n, GLuint* buffers)
		{
			m_n = n;
			m_buffers = buffers;
		}

		GLsizei m_n;
		GLuint* m_buffers;
	};

	class GlCreateFramebuffersCommand : public OpenGlCommand
	{
	public:
		GlCreateFramebuffersCommand() :
			OpenGlCommand(true, false, "glCreateFramebuffers")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLsizei n, GLuint* framebuffers)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlCreateFramebuffersCommand>(poolId);
			ptr->set(n, framebuffers);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glCreateFramebuffers(m_n, m_framebuffers);
		}
	private:
		void set(GLsizei n, GLuint* framebuffers)
		{
			m_n = n;
			m_framebuffers = framebuffers;
		}

		GLsizei m_n;
		GLuint* m_framebuffers;
	};

	class GlNamedFramebufferTextureCommand : public OpenGlCommand
	{
	public:
		GlNamedFramebufferTextureCommand() :
			OpenGlCommand(false, false, "glNamedFramebufferTexture")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlNamedFramebufferTextureCommand>(poolId);
			ptr->set(framebuffer, attachment, texture, level);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glNamedFramebufferTexture(m_framebuffer, m_attachment, m_texture, m_level);
		}
	private:
		void set(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
		{
			m_framebuffer = framebuffer;
			m_attachment = attachment;
			m_texture = texture;
			m_level = level;
		}

		GLuint m_framebuffer;
		GLenum m_attachment;
		GLuint m_texture;
		GLint m_level;
	};

	class GlDrawRangeElementsBaseVertexCommand : public OpenGlCommand
	{
	public:
		GlDrawRangeElementsBaseVertexCommand() :
			OpenGlCommand(false, false, "glDrawRangeElementsBaseVertex")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
			const u16* indices, GLint basevertex)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlDrawRangeElementsBaseVertexCommand>(poolId);
			ptr->set(mode, start, end, count, type, indices, basevertex);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glDrawRangeElementsBaseVertex(m_mode, m_start, m_end, m_count, m_type, m_indices, m_basevertex);
		}
	private:
		void set(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
			const u16* indices, GLint basevertex)
		{
		    m_mode = mode;
			m_start = start;
			m_end = end;
			m_count = count;
			m_type = type;
			m_indices = indices;
			m_basevertex = basevertex;
		}

		GLenum m_mode;
		GLuint m_start;
		GLuint m_end;
		GLsizei m_count;
		GLenum m_type;
		const u16* m_indices;
		GLint m_basevertex;
	};

	class GlFlushMappedBufferRangeCommand : public OpenGlCommand
	{
	public:
		GlFlushMappedBufferRangeCommand() :
			OpenGlCommand(false, false, "glFlushMappedBufferRange")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, GLintptr offset, GLsizeiptr length)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlFlushMappedBufferRangeCommand>(poolId);
			ptr->set(target, offset, length);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glFlushMappedBufferRange(m_target, m_offset, m_length);
		}
	private:
		void set(GLenum target, GLintptr offset, GLsizeiptr length)
		{
			m_target = target;
			m_offset = offset;
			m_length = length;
		}

		GLenum m_target;
		GLintptr m_offset;
		GLsizeiptr m_length;
	};

	class GlFinishCommand : public OpenGlCommand
	{
	public:
		GlFinishCommand() :
			OpenGlCommand(true, true, "glFinish")
		{
		}

		static std::shared_ptr<OpenGlCommand> get()
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlFinishCommand>(poolId);
			ptr->set();
			return ptr;
		}

		void commandToExecute() override
		{
			g_glFinish();
		}
	private:
		void set()
		{

		}
	};

	class GlEGLImageTargetTexture2DOESCommand : public OpenGlCommand
	{
	public:
		GlEGLImageTargetTexture2DOESCommand() :
				OpenGlCommand(false, false, "glEGLImageTargetTexture2DOES")
		{
		}

		static std::shared_ptr<OpenGlCommand> get(GLenum target, void* image)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<GlEGLImageTargetTexture2DOESCommand>(poolId);
			ptr->set(target, image);
			return ptr;
		}

		void commandToExecute() override
		{
			g_glEGLImageTargetTexture2DOES(m_target, m_image);
		}
	private:
		void set(GLenum target, void* image)
		{
			m_target = target;
			m_image = image;
		}

		GLenum m_target;
		void* m_image;
	};

#if defined(OS_ANDROID)
    class EglGetNativeClientBufferANDROIDCommand : public OpenGlCommand
    {
    public:
        EglGetNativeClientBufferANDROIDCommand() :
                OpenGlCommand(true, true, "eglGetNativeClientBufferANDROID")
        {
        }

        static std::shared_ptr<OpenGlCommand> get(const AHardwareBuffer *buffer, EGLClientBuffer& returnValue)
        {
            static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
            auto ptr = getFromPool<EglGetNativeClientBufferANDROIDCommand>(poolId);
            ptr->set(buffer, returnValue);
            return ptr;
        }

        void commandToExecute() override
        {
            *m_returnValue = g_eglGetNativeClientBufferANDROID(m_buffer);
        }
    private:
        void set(const AHardwareBuffer *buffer, EGLClientBuffer& returnValue)
        {
            m_buffer = buffer;
            m_returnValue = &returnValue;
        }

        const struct AHardwareBuffer *m_buffer;
        EGLClientBuffer* m_returnValue;
    };
#endif
#ifdef MUPENPLUSAPI
	//Vid ext functions
	class CoreVideoInitCommand : public OpenGlCommand
	{
	public:
		CoreVideoInitCommand() :
			OpenGlCommand(true, false, "CoreVideo_Init", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get()
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<CoreVideoInitCommand>(poolId);
			ptr->set();
			return ptr;
		}

		void commandToExecute() override
		{
			::CoreVideo_Init();
		}
	private:
		void set()
		{
		}
	};

	class CoreVideoQuitCommand : public OpenGlCommand
	{
	public:
		CoreVideoQuitCommand() :
			OpenGlCommand(true, false, "CoreVideo_Quit", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get()
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<CoreVideoQuitCommand>(poolId);
			ptr->set();
			return ptr;
		}

		void commandToExecute() override
		{
			::CoreVideo_Quit();
		}
	private:
		void set()
		{
		}
	};

	class CoreVideoSetVideoModeCommand : public OpenGlCommand
	{
	public:
		CoreVideoSetVideoModeCommand() :
			OpenGlCommand(true, false, "CoreVideo_SetVideoMode", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get(int screenWidth, int screenHeight, int bitsPerPixel, m64p_video_mode mode,
			m64p_video_flags flags, m64p_error& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<CoreVideoSetVideoModeCommand>(poolId);
			ptr->set(screenWidth, screenHeight, bitsPerPixel, mode, flags, returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = ::CoreVideo_SetVideoMode(m_screenWidth, m_screenHeight, m_bitsPerPixel, m_mode, m_flags);

			initGLFunctions();
		}
	private:
		void set(int screenWidth, int screenHeight, int bitsPerPixel, m64p_video_mode mode,
			m64p_video_flags flags, m64p_error& returnValue)
		{
			m_screenWidth = screenWidth;
			m_screenHeight = screenHeight;
			m_bitsPerPixel = bitsPerPixel;
			m_mode = mode;
			m_flags = flags;
			m_returnValue = &returnValue;
		}

		int m_screenWidth;
		int m_screenHeight;
		int m_bitsPerPixel;
		m64p_video_mode m_mode;
		m64p_video_flags m_flags;
		m64p_error* m_returnValue;
	};

	class CoreVideoGLSetAttributeCommand : public OpenGlCommand
	{
	public:
		CoreVideoGLSetAttributeCommand() :
			OpenGlCommand(true, false, "CoreVideo_GL_SetAttribute", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get(m64p_GLattr attribute, int value)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<CoreVideoGLSetAttributeCommand>(poolId);
			ptr->set(attribute, value);
			return ptr;
		}

		void commandToExecute() override
		{
			::CoreVideo_GL_SetAttribute(m_attribute, m_value);
		}
	private:
		void set(m64p_GLattr attribute, int value)
		{
			m_attribute = attribute;
			m_value = value;
		}

		m64p_GLattr m_attribute;
		int m_value;
	};

	class CoreVideoGLGetAttributeCommand : public OpenGlCommand
	{
	public:
		CoreVideoGLGetAttributeCommand() :
			OpenGlCommand(true, false, "CoreVideo_GL_GetAttribute", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get(m64p_GLattr attribute, int* value)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<CoreVideoGLGetAttributeCommand>(poolId);
			ptr->set(attribute, value);
			return ptr;
		}

		void commandToExecute() override
		{
			::CoreVideo_GL_GetAttribute(m_attribute, m_value);
		}
	private:
		void set(m64p_GLattr attribute, int* value)
		{
			m_attribute = attribute;
			m_value = value;
		}

		m64p_GLattr m_attribute;
		int* m_value;
	};

	class CoreVideoGLSwapBuffersCommand : public OpenGlCommand
	{
	public:
		CoreVideoGLSwapBuffersCommand() :
			OpenGlCommand(false, false, "CoreVideo_GL_SwapBuffers", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get(std::function<void()> swapBuffersCallback)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<CoreVideoGLSwapBuffersCommand>(poolId);
			ptr->set(swapBuffersCallback);
			return ptr;
		}

		void commandToExecute() override
		{
			::CoreVideo_GL_SwapBuffers();
			m_swapBuffersCallback();
		}
	private:
		void set(std::function<void()> swapBuffersCallback)
		{
			m_swapBuffersCallback = swapBuffersCallback;
		}

		std::function<void()> m_swapBuffersCallback;
	};
#else
	//Zilmar API functions
	class WindowsStartCommand : public OpenGlCommand
	{
	public:
		WindowsStartCommand() :
			OpenGlCommand(true, false, "WindowsStartCommand", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get(bool& returnValue)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<WindowsStartCommand>(poolId);
			ptr->set(returnValue);
			return ptr;
		}

		void commandToExecute() override
		{
			*m_returnValue = WindowsWGL::start();
		}

	private:
		void set(bool& returnValue)
		{
			m_returnValue = &returnValue;
		}

		bool* m_returnValue;
	};

	class WindowsStopCommand : public OpenGlCommand
	{
	public:
		WindowsStopCommand() :
			OpenGlCommand(true, false, "WindowsStopCommand", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get()
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<WindowsStopCommand>(poolId);
			ptr->set();
			return ptr;
		}

		void commandToExecute() override
		{
			WindowsWGL::stop();
		}

	private:
		void set()
		{
		}
	};

	class WindowsSwapBuffersCommand : public OpenGlCommand
	{
	public:
		WindowsSwapBuffersCommand() :
			OpenGlCommand(false, false, "WindowsSwapBuffersCommand", false)
		{
		}

		static std::shared_ptr<OpenGlCommand> get(std::function<void()> swapBuffersCallback)
		{
			static int poolId = OpenGlCommandPool::get().getNextAvailablePool();
			auto ptr = getFromPool<WindowsSwapBuffersCommand>(poolId);
			ptr->set(swapBuffersCallback);
			return ptr;
		}

		void commandToExecute() override
		{
			WindowsWGL::swapBuffers();
			m_swapBuffersCallback();
		}
	private:
		void set(std::function<void()> swapBuffersCallback)
		{
			m_swapBuffersCallback = swapBuffersCallback;
		}

		std::function<void()> m_swapBuffersCallback;
	};

#endif
}
