#ifndef GLFUNCTIONS_H
#define GLFUNCTIONS_H

#ifdef OS_WINDOWS
#include <windows.h>
#elif defined(OS_LINUX)
#include <winlnxdefs.h>
#endif

#ifdef EGL
#include <GL/glcorearb.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#elif defined(OS_MAC_OS_X)
#include <OpenGL/OpenGL.h>
#include <stddef.h>
#include <OpenGL/gl3.h>

#elif defined(OS_IOS)
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
// Add missing type defintions for iOS
typedef double GLclampd;
typedef double GLdouble;
// These will get redefined by other GL headers.
#undef GL_DRAW_FRAMEBUFFER_BINDING
#undef GL_COPY_READ_BUFFER_BINDING
#undef GL_COPY_WRITE_BUFFER_BINDING
#include <GL/glcorearb.h>
#else
#include <GL/gl.h>
#endif

#include <GL/glext.h>
#include <stdexcept>
#include <sstream>
#include "Log.h"

#define IS_GL_FUNCTION_VALID(proc_name) g_##proc_name != nullptr

#if defined(EGL) || defined(OS_IOS)

extern PFNGLBLENDFUNCPROC g_glBlendFunc;
extern PFNGLPIXELSTOREIPROC g_glPixelStorei;
extern PFNGLCLEARCOLORPROC g_glClearColor;
extern PFNGLCULLFACEPROC g_glCullFace;
extern PFNGLDEPTHFUNCPROC g_glDepthFunc;
extern PFNGLDEPTHMASKPROC g_glDepthMask;
extern PFNGLDISABLEPROC g_glDisable;
extern PFNGLENABLEPROC g_glEnable;
extern PFNGLPOLYGONOFFSETPROC g_glPolygonOffset;
extern PFNGLSCISSORPROC g_glScissor;
extern PFNGLVIEWPORTPROC g_glViewport;
extern PFNGLBINDTEXTUREPROC g_glBindTexture;
extern PFNGLTEXIMAGE2DPROC g_glTexImage2D;
extern PFNGLTEXPARAMETERIPROC g_glTexParameteri;
extern PFNGLGETINTEGERVPROC g_glGetIntegerv;
extern PFNGLGETSTRINGPROC g_glGetString;
extern PFNGLREADPIXELSPROC g_glReadPixels;
extern PFNGLTEXSUBIMAGE2DPROC g_glTexSubImage2D;
extern PFNGLDRAWARRAYSPROC g_glDrawArrays;
extern PFNGLGETERRORPROC g_glGetError;
extern PFNGLDRAWELEMENTSPROC g_glDrawElements;
extern PFNGLLINEWIDTHPROC g_glLineWidth;
extern PFNGLCLEARPROC g_glClear;
extern PFNGLGETFLOATVPROC g_glGetFloatv;
extern PFNGLDELETETEXTURESPROC g_glDeleteTextures;
extern PFNGLGENTEXTURESPROC g_glGenTextures;
extern PFNGLTEXPARAMETERFPROC g_glTexParameterf;
extern PFNGLACTIVETEXTUREPROC g_glActiveTexture;
extern PFNGLBLENDCOLORPROC g_glBlendColor;
extern PFNGLREADBUFFERPROC g_glReadBuffer;
extern PFNGLFINISHPROC g_glFinish;
#if defined(OS_ANDROID)
extern PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC g_glGetNativeClientBufferANDROID;
#endif
#endif

#ifdef OS_WINDOWS
extern PFNGLACTIVETEXTUREPROC g_glActiveTexture;
extern PFNGLBLENDCOLORPROC g_glBlendColor;
#endif

#define glGetError g_glGetError
#define glBlendFunc(...) opengl::FunctionWrapper::wrBlendFunc(__VA_ARGS__)
#define glPixelStorei(...) opengl::FunctionWrapper::wrPixelStorei(__VA_ARGS__)
#define glClearColor(...) opengl::FunctionWrapper::wrClearColor(__VA_ARGS__)
#define glCullFace(...) opengl::FunctionWrapper::wrCullFace(__VA_ARGS__)
#define glDepthFunc(...) opengl::FunctionWrapper::wrDepthFunc(__VA_ARGS__)
#define glDepthMask(...) opengl::FunctionWrapper::wrDepthMask(__VA_ARGS__)
#define glDisable(...) opengl::FunctionWrapper::wrDisable(__VA_ARGS__)
#define glEnable(...) opengl::FunctionWrapper::wrEnable(__VA_ARGS__)
#define glPolygonOffset(...) opengl::FunctionWrapper::wrPolygonOffset(__VA_ARGS__)
#define glScissor(...) opengl::FunctionWrapper::wrScissor(__VA_ARGS__)
#define glViewport(...) opengl::FunctionWrapper::wrViewport(__VA_ARGS__)
#define glBindTexture(...) opengl::FunctionWrapper::wrBindTexture(__VA_ARGS__)
#define glTexImage2D(...) opengl::FunctionWrapper::wrTexImage2D(__VA_ARGS__)
#define glTexParameteri(...) opengl::FunctionWrapper::wrTexParameteri(__VA_ARGS__)
#define glGetIntegerv(...) opengl::FunctionWrapper::wrGetIntegerv(__VA_ARGS__)
#define glGetString(...) opengl::FunctionWrapper::wrGetString(__VA_ARGS__)
#define glReadPixels(...) opengl::FunctionWrapper::wrReadPixels(__VA_ARGS__)
#define glTexSubImage2D(...) opengl::FunctionWrapper::wrTexSubImage2D(__VA_ARGS__)
#define glDrawArrays(...) opengl::FunctionWrapper::wrDrawArrays(__VA_ARGS__)
#define glDrawElements(...) opengl::FunctionWrapper::wrDrawElements(__VA_ARGS__)
#define glLineWidth(...) opengl::FunctionWrapper::wrLineWidth(__VA_ARGS__)
#define glClear(...) opengl::FunctionWrapper::wrClear(__VA_ARGS__)
#define glGetFloatv(...) opengl::FunctionWrapper::wrGetFloatv(__VA_ARGS__)
#define glDeleteTextures(...) opengl::FunctionWrapper::wrDeleteTextures(__VA_ARGS__)
#define glGenTextures(...) opengl::FunctionWrapper::wrGenTextures(__VA_ARGS__)
#define glTexParameterf(...) opengl::FunctionWrapper::wrTexParameterf(__VA_ARGS__)
#define glActiveTexture(...) opengl::FunctionWrapper::wrActiveTexture(__VA_ARGS__)
#define glBlendColor(...) opengl::FunctionWrapper::wrBlendColor(__VA_ARGS__)
#define glReadBuffer(...) opengl::FunctionWrapper::wrReadBuffer(__VA_ARGS__)
#define glFinish(...) opengl::FunctionWrapper::wrFinish(__VA_ARGS__)
#if defined(OS_ANDROID)
#define eglGetNativeClientBufferANDROID(...) opengl::FunctionWrapper::ewrGetNativeClientBufferANDROID(__VA_ARGS__)
#endif
#define glCreateShader(...) opengl::FunctionWrapper::wrCreateShader(__VA_ARGS__)
#define glCompileShader(...) opengl::FunctionWrapper::wrCompileShader(__VA_ARGS__)
#define glShaderSource(...) opengl::FunctionWrapper::wrShaderSource(__VA_ARGS__)
#define glCreateProgram(...) opengl::FunctionWrapper::wrCreateProgram(__VA_ARGS__)
#define glAttachShader(...) opengl::FunctionWrapper::wrAttachShader(__VA_ARGS__)
#define glLinkProgram(...) opengl::FunctionWrapper::wrLinkProgram(__VA_ARGS__)
#define glUseProgram(...) opengl::FunctionWrapper::wrUseProgram(__VA_ARGS__)
#define glGetUniformLocation(...) opengl::FunctionWrapper::wrGetUniformLocation(__VA_ARGS__)
#define glUniform1i(...) opengl::FunctionWrapper::wrUniform1i(__VA_ARGS__)
#define glUniform1f(...) opengl::FunctionWrapper::wrUniform1f(__VA_ARGS__)
#define glUniform2f(...) opengl::FunctionWrapper::wrUniform2f(__VA_ARGS__)
#define glUniform2i(...) opengl::FunctionWrapper::wrUniform2i(__VA_ARGS__)
#define glUniform4i(...) opengl::FunctionWrapper::wrUniform4i(__VA_ARGS__)

#define glUniform4f(...) opengl::FunctionWrapper::wrUniform4f(__VA_ARGS__)
#define glUniform3fv(...) opengl::FunctionWrapper::wrUniform3fv(__VA_ARGS__)
#define glUniform4fv(...) opengl::FunctionWrapper::wrUniform4fv(__VA_ARGS__)
#define glDetachShader(...) opengl::FunctionWrapper::wrDetachShader(__VA_ARGS__)
#define glDeleteShader(...) opengl::FunctionWrapper::wrDeleteShader(__VA_ARGS__)
#define glDeleteProgram(...) opengl::FunctionWrapper::wrDeleteProgram(__VA_ARGS__)
#define glGetProgramInfoLog(...) opengl::FunctionWrapper::wrGetProgramInfoLog(__VA_ARGS__)
#define glGetShaderInfoLog(...) opengl::FunctionWrapper::wrGetShaderInfoLog(__VA_ARGS__)
#define glGetShaderiv(...) opengl::FunctionWrapper::wrGetShaderiv(__VA_ARGS__)
#define glGetProgramiv(...) opengl::FunctionWrapper::wrGetProgramiv(__VA_ARGS__)

#define glEnableVertexAttribArray(...) opengl::FunctionWrapper::wrEnableVertexAttribArray(__VA_ARGS__)
#define glDisableVertexAttribArray(...) opengl::FunctionWrapper::wrDisableVertexAttribArray(__VA_ARGS__)
#define glVertexAttribPointer(...) opengl::FunctionWrapper::wrVertexAttribPointer(__VA_ARGS__)
#define glBindAttribLocation(...) opengl::FunctionWrapper::wrBindAttribLocation(__VA_ARGS__)
#define glVertexAttrib1f(...) opengl::FunctionWrapper::wrVertexAttrib1f(__VA_ARGS__)
#define glVertexAttrib4f(...) opengl::FunctionWrapper::wrVertexAttrib4f(__VA_ARGS__)
#define glVertexAttrib4fv(...) opengl::FunctionWrapper::wrVertexAttrib4fv(__VA_ARGS__)

#define glDepthRangef(...) opengl::FunctionWrapper::wrDepthRangef(__VA_ARGS__)
#define glClearDepthf(...) opengl::FunctionWrapper::wrClearDepthf(__VA_ARGS__)

#define glBindBuffer(...) opengl::FunctionWrapper::wrBindBuffer(__VA_ARGS__)
#define glBindFramebuffer(...) opengl::FunctionWrapper::wrBindFramebuffer(__VA_ARGS__)
#define glBindRenderbuffer(...) opengl::FunctionWrapper::wrBindRenderbuffer(__VA_ARGS__)
#define glDrawBuffers(...) opengl::FunctionWrapper::wrDrawBuffers(__VA_ARGS__)
#define glGenFramebuffers(...) opengl::FunctionWrapper::wrGenFramebuffers(__VA_ARGS__)
#define glDeleteFramebuffers(...) opengl::FunctionWrapper::wrDeleteFramebuffers(__VA_ARGS__)
#define glFramebufferTexture2D(...) opengl::FunctionWrapper::wrFramebufferTexture2D(__VA_ARGS__)
#define glTexImage2DMultisample(...) opengl::FunctionWrapper::wrTexImage2DMultisample(__VA_ARGS__)
#define glTexStorage2DMultisample(...) opengl::FunctionWrapper::wrTexStorage2DMultisample(__VA_ARGS__)
#define glGenRenderbuffers(...) opengl::FunctionWrapper::wrGenRenderbuffers(__VA_ARGS__)
#define glRenderbufferStorage(...) opengl::FunctionWrapper::wrRenderbufferStorage(__VA_ARGS__)
#define glDeleteRenderbuffers(...) opengl::FunctionWrapper::wrDeleteRenderbuffers(__VA_ARGS__)
#define glFramebufferRenderbuffer(...) opengl::FunctionWrapper::wrFramebufferRenderbuffer(__VA_ARGS__)
#define glCheckFramebufferStatus(...) opengl::FunctionWrapper::wrCheckFramebufferStatus(__VA_ARGS__)
#define glBlitFramebuffer(...) opengl::FunctionWrapper::wrBlitFramebuffer(__VA_ARGS__)
#define glGenVertexArrays(...) opengl::FunctionWrapper::wrGenVertexArrays(__VA_ARGS__)
#define glBindVertexArray(...) opengl::FunctionWrapper::wrBindVertexArray(__VA_ARGS__)
#define glDeleteVertexArrays(...) opengl::FunctionWrapper::wrDeleteVertexArrays(__VA_ARGS__);
#define glGenBuffers(...) opengl::FunctionWrapper::wrGenBuffers(__VA_ARGS__)
#define glBufferData(...) opengl::FunctionWrapper::wrBufferData(__VA_ARGS__)
#define glMapBuffer(...) opengl::FunctionWrapper::wrMapBuffer(__VA_ARGS__)
#define glMapBufferRange(...) opengl::FunctionWrapper::wrMapBufferRange(__VA_ARGS__)
#define glUnmapBuffer(...) opengl::FunctionWrapper::wrUnmapBuffer(__VA_ARGS__)
#define glDeleteBuffers(...) opengl::FunctionWrapper::wrDeleteBuffers(__VA_ARGS__)
#define glBindImageTexture(...) opengl::FunctionWrapper::wrBindImageTexture(__VA_ARGS__)
#define glMemoryBarrier(...) opengl::FunctionWrapper::wrMemoryBarrier(__VA_ARGS__)
#define glGetStringi(...) opengl::FunctionWrapper::wrGetStringi(__VA_ARGS__)
#define glInvalidateFramebuffer(...) opengl::FunctionWrapper::wrInvalidateFramebuffer(__VA_ARGS__)
#define glBufferStorage(...) opengl::FunctionWrapper::wrBufferStorage(__VA_ARGS__)
#define glFenceSync(...) opengl::FunctionWrapper::wrFenceSync(__VA_ARGS__)
#define glClientWaitSync(...) opengl::FunctionWrapper::wrClientWaitSync(__VA_ARGS__)
#define glDeleteSync(...) opengl::FunctionWrapper::wrDeleteSync(__VA_ARGS__)

#define glGetUniformBlockIndex(...) opengl::FunctionWrapper::wrGetUniformBlockIndex(__VA_ARGS__)
#define glUniformBlockBinding(...) opengl::FunctionWrapper::wrUniformBlockBinding(__VA_ARGS__)
#define glGetActiveUniformBlockiv(...) opengl::FunctionWrapper::wrGetActiveUniformBlockiv(__VA_ARGS__)
#define glGetUniformIndices(...) opengl::FunctionWrapper::wrGetUniformIndices(__VA_ARGS__)
#define glGetActiveUniformsiv(...) opengl::FunctionWrapper::wrGetActiveUniformsiv(__VA_ARGS__)
#define glBindBufferBase(...) opengl::FunctionWrapper::wrBindBufferBase(__VA_ARGS__)
#define glBufferSubData(...) opengl::FunctionWrapper::wrBufferSubData(__VA_ARGS__)

#define glGetProgramBinary(...) opengl::FunctionWrapper::wrGetProgramBinary(__VA_ARGS__)
#define glProgramBinary(...) opengl::FunctionWrapper::wrProgramBinary(__VA_ARGS__)
#define glProgramParameteri(...) opengl::FunctionWrapper::wrProgramParameteri(__VA_ARGS__)

#define glTexStorage2D(...) opengl::FunctionWrapper::wrTexStorage2D(__VA_ARGS__)
#define glTextureStorage2D(...) opengl::FunctionWrapper::wrTextureStorage2D(__VA_ARGS__)
#define glTextureSubImage2D(...) opengl::FunctionWrapper::wrTextureSubImage2D(__VA_ARGS__)
#define glTextureStorage2DMultisample(...) opengl::FunctionWrapper::wrTextureStorage2DMultisample(__VA_ARGS__)
#define glTextureParameteri(...) opengl::FunctionWrapper::wrTextureParameteri(__VA_ARGS__)
#define glTextureParameterf(...) opengl::FunctionWrapper::wrTextureParameterf(__VA_ARGS__)
#define glCreateTextures(...) opengl::FunctionWrapper::wrCreateTextures(__VA_ARGS__)
#define glCreateBuffers(...) opengl::FunctionWrapper::wrCreateBuffers(__VA_ARGS__)
#define glCreateFramebuffers(...) opengl::FunctionWrapper::wrCreateFramebuffers(__VA_ARGS__)
#define glNamedFramebufferTexture(...) opengl::FunctionWrapper::wrNamedFramebufferTexture(__VA_ARGS__)
#define glDrawRangeElementsBaseVertex(...) opengl::FunctionWrapper::wrDrawRangeElementsBaseVertex(__VA_ARGS__)
#define glFlushMappedBufferRange(...) opengl::FunctionWrapper::wrFlushMappedBufferRange(__VA_ARGS__)
#define glTextureBarrier(...) opengl::FunctionWrapper::wrTextureBarrier(__VA_ARGS__)
#define glTextureBarrierNV(...) opengl::FunctionWrapper::wrTextureBarrierNV(__VA_ARGS__)
#define glClearBufferfv(...) opengl::FunctionWrapper::wrClearBufferfv(__VA_ARGS__)
#define glEnablei(...) opengl::FunctionWrapper::wrEnablei(__VA_ARGS__)
#define glDisablei(...) opengl::FunctionWrapper::wrDisablei(__VA_ARGS__)
#define glEGLImageTargetTexture2DOES(...) opengl::FunctionWrapper::wrEGLImageTargetTexture2DOES(__VA_ARGS__)

extern PFNGLCREATESHADERPROC g_glCreateShader;
extern PFNGLCOMPILESHADERPROC g_glCompileShader;
extern PFNGLSHADERSOURCEPROC g_glShaderSource;
extern PFNGLCREATEPROGRAMPROC g_glCreateProgram;
extern PFNGLATTACHSHADERPROC g_glAttachShader;
extern PFNGLLINKPROGRAMPROC g_glLinkProgram;
extern PFNGLUSEPROGRAMPROC g_glUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC g_glGetUniformLocation;
extern PFNGLUNIFORM1IPROC g_glUniform1i;
extern PFNGLUNIFORM1FPROC g_glUniform1f;
extern PFNGLUNIFORM2FPROC g_glUniform2f;
extern PFNGLUNIFORM2IPROC g_glUniform2i;
extern PFNGLUNIFORM4IPROC g_glUniform4i;

extern PFNGLUNIFORM4FPROC g_glUniform4f;
extern PFNGLUNIFORM3FVPROC g_glUniform3fv;
extern PFNGLUNIFORM4FVPROC g_glUniform4fv;
extern PFNGLDETACHSHADERPROC g_glDetachShader;
extern PFNGLDELETESHADERPROC g_glDeleteShader;
extern PFNGLDELETEPROGRAMPROC g_glDeleteProgram;
extern PFNGLGETPROGRAMINFOLOGPROC g_glGetProgramInfoLog;
extern PFNGLGETSHADERINFOLOGPROC g_glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC g_glGetShaderiv;
extern PFNGLGETPROGRAMIVPROC g_glGetProgramiv;

extern PFNGLENABLEVERTEXATTRIBARRAYPROC g_glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC g_glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC g_glVertexAttribPointer;
extern PFNGLBINDATTRIBLOCATIONPROC g_glBindAttribLocation;
extern PFNGLVERTEXATTRIB1FPROC g_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB4FPROC g_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC g_glVertexAttrib4fv;

extern PFNGLDEPTHRANGEFPROC g_glDepthRangef;
extern PFNGLCLEARDEPTHFPROC g_glClearDepthf;

extern PFNGLDRAWBUFFERSPROC g_glDrawBuffers;
extern PFNGLGENFRAMEBUFFERSPROC g_glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC g_glBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC g_glDeleteFramebuffers;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC g_glFramebufferTexture2D;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC g_glTexImage2DMultisample;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC g_glTexStorage2DMultisample;
extern PFNGLGENRENDERBUFFERSPROC g_glGenRenderbuffers;
extern PFNGLBINDRENDERBUFFERPROC g_glBindRenderbuffer;
extern PFNGLRENDERBUFFERSTORAGEPROC g_glRenderbufferStorage;
extern PFNGLDELETERENDERBUFFERSPROC g_glDeleteRenderbuffers;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC g_glFramebufferRenderbuffer;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC g_glCheckFramebufferStatus;
extern PFNGLBLITFRAMEBUFFERPROC g_glBlitFramebuffer;
extern PFNGLGENVERTEXARRAYSPROC g_glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC g_glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC g_glDeleteVertexArrays;
extern PFNGLGENBUFFERSPROC g_glGenBuffers;
extern PFNGLBINDBUFFERPROC g_glBindBuffer;
extern PFNGLBUFFERDATAPROC g_glBufferData;
extern PFNGLMAPBUFFERPROC g_glMapBuffer;
extern PFNGLMAPBUFFERRANGEPROC g_glMapBufferRange;
extern PFNGLUNMAPBUFFERPROC g_glUnmapBuffer;
extern PFNGLDELETEBUFFERSPROC g_glDeleteBuffers;
extern PFNGLBINDIMAGETEXTUREPROC g_glBindImageTexture;
extern PFNGLMEMORYBARRIERPROC g_glMemoryBarrier;
extern PFNGLGETSTRINGIPROC g_glGetStringi;
extern PFNGLINVALIDATEFRAMEBUFFERPROC g_glInvalidateFramebuffer;
extern PFNGLBUFFERSTORAGEPROC g_glBufferStorage;
extern PFNGLFENCESYNCPROC g_glFenceSync;
extern PFNGLCLIENTWAITSYNCPROC g_glClientWaitSync;
extern PFNGLDELETESYNCPROC g_glDeleteSync;

extern PFNGLGETUNIFORMBLOCKINDEXPROC g_glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC g_glUniformBlockBinding;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC g_glGetActiveUniformBlockiv;
extern PFNGLGETUNIFORMINDICESPROC g_glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC g_glGetActiveUniformsiv;
extern PFNGLBINDBUFFERBASEPROC g_glBindBufferBase;
extern PFNGLBUFFERSUBDATAPROC g_glBufferSubData;

extern PFNGLGETPROGRAMBINARYPROC g_glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC g_glProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC g_glProgramParameteri;

extern PFNGLTEXSTORAGE2DPROC g_glTexStorage2D;
extern PFNGLTEXTURESTORAGE2DPROC g_glTextureStorage2D;
extern PFNGLTEXTURESUBIMAGE2DPROC g_glTextureSubImage2D;
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC g_glTextureStorage2DMultisample;
extern PFNGLTEXTUREPARAMETERIPROC g_glTextureParameteri;
extern PFNGLTEXTUREPARAMETERFPROC g_glTextureParameterf;
extern PFNGLCREATETEXTURESPROC g_glCreateTextures;
extern PFNGLCREATEBUFFERSPROC g_glCreateBuffers;
extern PFNGLCREATEFRAMEBUFFERSPROC g_glCreateFramebuffers;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC g_glNamedFramebufferTexture;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC g_glDrawRangeElementsBaseVertex;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC g_glFlushMappedBufferRange;
extern PFNGLTEXTUREBARRIERPROC g_glTextureBarrier;
extern PFNGLTEXTUREBARRIERNVPROC g_glTextureBarrierNV;
extern PFNGLCLEARBUFFERFVPROC g_glClearBufferfv;
extern PFNGLENABLEIPROC g_glEnablei;
extern PFNGLDISABLEIPROC g_glDisablei;

typedef void (APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, void* image);
extern PFNGLEGLIMAGETARGETTEXTURE2DOESPROC g_glEGLImageTargetTexture2DOES;

void initGLFunctions();

#include "Graphics/OpenGLContext/ThreadedOpenGl/opengl_Wrapper.h"

#endif // GLFUNCTIONS_H
