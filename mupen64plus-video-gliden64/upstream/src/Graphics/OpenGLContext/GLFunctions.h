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

#define IS_GL_FUNCTION_VALID(proc_name) Real##proc_name != nullptr

#if defined(EGL) || defined(OS_IOS)

extern PFNGLBLENDFUNCPROC RealBlendFunc;
extern PFNGLPIXELSTOREIPROC RealPixelStorei;
extern PFNGLCLEARCOLORPROC RealClearColor;
extern PFNGLCULLFACEPROC RealCullFace;
extern PFNGLDEPTHFUNCPROC RealDepthFunc;
extern PFNGLDEPTHMASKPROC RealDepthMask;
extern PFNGLDISABLEPROC RealDisable;
extern PFNGLENABLEPROC RealEnable;
extern PFNGLPOLYGONOFFSETPROC RealPolygonOffset;
extern PFNGLSCISSORPROC RealScissor;
extern PFNGLVIEWPORTPROC RealViewport;
extern PFNGLBINDTEXTUREPROC RealBindTexture;
extern PFNGLTEXIMAGE2DPROC RealTexImage2D;
extern PFNGLTEXPARAMETERIPROC RealTexParameteri;
extern PFNGLGETINTEGERVPROC RealGetIntegerv;
extern PFNGLGETSTRINGPROC RealGetString;
extern PFNGLREADPIXELSPROC RealReadPixels;
extern PFNGLTEXSUBIMAGE2DPROC RealTexSubImage2D;
extern PFNGLDRAWARRAYSPROC RealDrawArrays;
extern PFNGLGETERRORPROC RealGetError;
extern PFNGLDRAWELEMENTSPROC RealDrawElements;
extern PFNGLLINEWIDTHPROC RealLineWidth;
extern PFNGLCLEARPROC RealClear;
extern PFNGLGETFLOATVPROC RealGetFloatv;
extern PFNGLDELETETEXTURESPROC RealDeleteTextures;
extern PFNGLGENTEXTURESPROC RealGenTextures;
extern PFNGLTEXPARAMETERFPROC RealTexParameterf;
extern PFNGLACTIVETEXTUREPROC RealActiveTexture;
extern PFNGLBLENDCOLORPROC RealBlendColor;
extern PFNGLREADBUFFERPROC RealReadBuffer;
extern PFNGLFINISHPROC RealFinish;
#if defined(OS_ANDROID)
extern PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC RealGetNativeClientBufferANDROID;
#endif
#endif

#ifdef OS_WINDOWS
extern PFNGLACTIVETEXTUREPROC RealActiveTexture;
extern PFNGLBLENDCOLORPROC RealBlendColor;
#endif

#define glGetError RealGetError
#define glBlendFunc(...) FunctionWrapper::wrBlendFunc(__VA_ARGS__)
#define glPixelStorei(...) FunctionWrapper::wrPixelStorei(__VA_ARGS__)
#define glClearColor(...) FunctionWrapper::wrClearColor(__VA_ARGS__)
#define glCullFace(...) FunctionWrapper::wrCullFace(__VA_ARGS__)
#define glDepthFunc(...) FunctionWrapper::wrDepthFunc(__VA_ARGS__)
#define glDepthMask(...) FunctionWrapper::wrDepthMask(__VA_ARGS__)
#define glDisable(...) FunctionWrapper::wrDisable(__VA_ARGS__)
#define glEnable(...) FunctionWrapper::wrEnable(__VA_ARGS__)
#define glPolygonOffset(...) FunctionWrapper::wrPolygonOffset(__VA_ARGS__)
#define glScissor(...) FunctionWrapper::wrScissor(__VA_ARGS__)
#define glViewport(...) FunctionWrapper::wrViewport(__VA_ARGS__)
#define glBindTexture(...) FunctionWrapper::wrBindTexture(__VA_ARGS__)
#define glTexImage2D(...) FunctionWrapper::wrTexImage2D(__VA_ARGS__)
#define glTexParameteri(...) FunctionWrapper::wrTexParameteri(__VA_ARGS__)
#define glGetIntegerv(...) FunctionWrapper::wrGetIntegerv(__VA_ARGS__)
#define glGetString(...) FunctionWrapper::wrGetString(__VA_ARGS__)
#define glReadPixels(...) FunctionWrapper::wrReadPixels(__VA_ARGS__)
#define glTexSubImage2D(...) FunctionWrapper::wrTexSubImage2D(__VA_ARGS__)
#define glDrawArrays(...) FunctionWrapper::wrDrawArrays(__VA_ARGS__)
#define glDrawElements(...) FunctionWrapper::wrDrawElements(__VA_ARGS__)
#define glLineWidth(...) FunctionWrapper::wrLineWidth(__VA_ARGS__)
#define glClear(...) FunctionWrapper::wrClear(__VA_ARGS__)
#define glGetFloatv(...) FunctionWrapper::wrGetFloatv(__VA_ARGS__)
#define glDeleteTextures(...) FunctionWrapper::wrDeleteTextures(__VA_ARGS__)
#define glGenTextures(...) FunctionWrapper::wrGenTextures(__VA_ARGS__)
#define glTexParameterf(...) FunctionWrapper::wrTexParameterf(__VA_ARGS__)
#define glActiveTexture(...) FunctionWrapper::wrActiveTexture(__VA_ARGS__)
#define glBlendColor(...) FunctionWrapper::wrBlendColor(__VA_ARGS__)
#define glReadBuffer(...) FunctionWrapper::wrReadBuffer(__VA_ARGS__)
#define glFinish(...) FunctionWrapper::wrFinish(__VA_ARGS__)
#if defined(OS_ANDROID)
#define eglGetNativeClientBufferANDROID(...) FunctionWrapper::ewrGetNativeClientBufferANDROID(__VA_ARGS__)
#endif
#define glCreateShader(...) FunctionWrapper::wrCreateShader(__VA_ARGS__)
#define glCompileShader(...) FunctionWrapper::wrCompileShader(__VA_ARGS__)
#define glShaderSource(...) FunctionWrapper::wrShaderSource(__VA_ARGS__)
#define glCreateProgram(...) FunctionWrapper::wrCreateProgram(__VA_ARGS__)
#define glAttachShader(...) FunctionWrapper::wrAttachShader(__VA_ARGS__)
#define glLinkProgram(...) FunctionWrapper::wrLinkProgram(__VA_ARGS__)
#define glUseProgram(...) FunctionWrapper::wrUseProgram(__VA_ARGS__)
#define glGetUniformLocation(...) FunctionWrapper::wrGetUniformLocation(__VA_ARGS__)
#define glUniform1i(...) FunctionWrapper::wrUniform1i(__VA_ARGS__)
#define glUniform1f(...) FunctionWrapper::wrUniform1f(__VA_ARGS__)
#define glUniform2f(...) FunctionWrapper::wrUniform2f(__VA_ARGS__)
#define glUniform2i(...) FunctionWrapper::wrUniform2i(__VA_ARGS__)
#define glUniform4i(...) FunctionWrapper::wrUniform4i(__VA_ARGS__)

#define glUniform4f(...) FunctionWrapper::wrUniform4f(__VA_ARGS__)
#define glUniform3fv(...) FunctionWrapper::wrUniform3fv(__VA_ARGS__)
#define glUniform4fv(...) FunctionWrapper::wrUniform4fv(__VA_ARGS__)
#define glDetachShader(...) FunctionWrapper::wrDetachShader(__VA_ARGS__)
#define glDeleteShader(...) FunctionWrapper::wrDeleteShader(__VA_ARGS__)
#define glDeleteProgram(...) FunctionWrapper::wrDeleteProgram(__VA_ARGS__)
#define glGetProgramInfoLog(...) FunctionWrapper::wrGetProgramInfoLog(__VA_ARGS__)
#define glGetShaderInfoLog(...) FunctionWrapper::wrGetShaderInfoLog(__VA_ARGS__)
#define glGetShaderiv(...) FunctionWrapper::wrGetShaderiv(__VA_ARGS__)
#define glGetProgramiv(...) FunctionWrapper::wrGetProgramiv(__VA_ARGS__)

#define glEnableVertexAttribArray(...) FunctionWrapper::wrEnableVertexAttribArray(__VA_ARGS__)
#define glDisableVertexAttribArray(...) FunctionWrapper::wrDisableVertexAttribArray(__VA_ARGS__)
#define glVertexAttribPointer(...) FunctionWrapper::wrVertexAttribPointer(__VA_ARGS__)
#define glBindAttribLocation(...) FunctionWrapper::wrBindAttribLocation(__VA_ARGS__)
#define glVertexAttrib1f(...) FunctionWrapper::wrVertexAttrib1f(__VA_ARGS__)
#define glVertexAttrib4f(...) FunctionWrapper::wrVertexAttrib4f(__VA_ARGS__)
#define glVertexAttrib4fv(...) FunctionWrapper::wrVertexAttrib4fv(__VA_ARGS__)

#define glDepthRangef(...) FunctionWrapper::wrDepthRangef(__VA_ARGS__)
#define glClearDepthf(...) FunctionWrapper::wrClearDepthf(__VA_ARGS__)

#define glBindBuffer(...) FunctionWrapper::wrBindBuffer(__VA_ARGS__)
#define glBindFramebuffer(...) FunctionWrapper::wrBindFramebuffer(__VA_ARGS__)
#define glBindRenderbuffer(...) FunctionWrapper::wrBindRenderbuffer(__VA_ARGS__)
#define glDrawBuffers(...) FunctionWrapper::wrDrawBuffers(__VA_ARGS__)
#define glGenFramebuffers(...) FunctionWrapper::wrGenFramebuffers(__VA_ARGS__)
#define glDeleteFramebuffers(...) FunctionWrapper::wrDeleteFramebuffers(__VA_ARGS__)
#define glFramebufferTexture2D(...) FunctionWrapper::wrFramebufferTexture2D(__VA_ARGS__)
#define glTexImage2DMultisample(...) FunctionWrapper::wrTexImage2DMultisample(__VA_ARGS__)
#define glTexStorage2DMultisample(...) FunctionWrapper::wrTexStorage2DMultisample(__VA_ARGS__)
#define glGenRenderbuffers(...) FunctionWrapper::wrGenRenderbuffers(__VA_ARGS__)
#define glRenderbufferStorage(...) FunctionWrapper::wrRenderbufferStorage(__VA_ARGS__)
#define glDeleteRenderbuffers(...) FunctionWrapper::wrDeleteRenderbuffers(__VA_ARGS__)
#define glFramebufferRenderbuffer(...) FunctionWrapper::wrFramebufferRenderbuffer(__VA_ARGS__)
#define glCheckFramebufferStatus(...) FunctionWrapper::wrCheckFramebufferStatus(__VA_ARGS__)
#define glBlitFramebuffer(...) FunctionWrapper::wrBlitFramebuffer(__VA_ARGS__)
#define glGenVertexArrays(...) FunctionWrapper::wrGenVertexArrays(__VA_ARGS__)
#define glBindVertexArray(...) FunctionWrapper::wrBindVertexArray(__VA_ARGS__)
#define glDeleteVertexArrays(...) FunctionWrapper::wrDeleteVertexArrays(__VA_ARGS__);
#define glGenBuffers(...) FunctionWrapper::wrGenBuffers(__VA_ARGS__)
#define glBufferData(...) FunctionWrapper::wrBufferData(__VA_ARGS__)
#define glMapBuffer(...) FunctionWrapper::wrMapBuffer(__VA_ARGS__)
#define glMapBufferRange(...) FunctionWrapper::wrMapBufferRange(__VA_ARGS__)
#define glUnmapBuffer(...) FunctionWrapper::wrUnmapBuffer(__VA_ARGS__)
#define glDeleteBuffers(...) FunctionWrapper::wrDeleteBuffers(__VA_ARGS__)
#define glBindImageTexture(...) FunctionWrapper::wrBindImageTexture(__VA_ARGS__)
#define glMemoryBarrier(...) FunctionWrapper::wrMemoryBarrier(__VA_ARGS__)
#define glGetStringi(...) FunctionWrapper::wrGetStringi(__VA_ARGS__)
#define glInvalidateFramebuffer(...) FunctionWrapper::wrInvalidateFramebuffer(__VA_ARGS__)
#define glBufferStorage(...) FunctionWrapper::wrBufferStorage(__VA_ARGS__)
#define glFenceSync(...) FunctionWrapper::wrFenceSync(__VA_ARGS__)
#define glClientWaitSync(...) FunctionWrapper::wrClientWaitSync(__VA_ARGS__)
#define glDeleteSync(...) FunctionWrapper::wrDeleteSync(__VA_ARGS__)

#define glGetUniformBlockIndex(...) FunctionWrapper::wrGetUniformBlockIndex(__VA_ARGS__)
#define glUniformBlockBinding(...) FunctionWrapper::wrUniformBlockBinding(__VA_ARGS__)
#define glGetActiveUniformBlockiv(...) FunctionWrapper::wrGetActiveUniformBlockiv(__VA_ARGS__)
#define glGetUniformIndices(...) FunctionWrapper::wrGetUniformIndices(__VA_ARGS__)
#define glGetActiveUniformsiv(...) FunctionWrapper::wrGetActiveUniformsiv(__VA_ARGS__)
#define glBindBufferBase(...) FunctionWrapper::wrBindBufferBase(__VA_ARGS__)
#define glBufferSubData(...) FunctionWrapper::wrBufferSubData(__VA_ARGS__)

#define glGetProgramBinary(...) FunctionWrapper::wrGetProgramBinary(__VA_ARGS__)
#define glProgramBinary(...) FunctionWrapper::wrProgramBinary(__VA_ARGS__)
#define glProgramParameteri(...) FunctionWrapper::wrProgramParameteri(__VA_ARGS__)

#define glTexStorage2D(...) FunctionWrapper::wrTexStorage2D(__VA_ARGS__)
#define glTextureStorage2D(...) FunctionWrapper::wrTextureStorage2D(__VA_ARGS__)
#define glTextureSubImage2D(...) FunctionWrapper::wrTextureSubImage2D(__VA_ARGS__)
#define glTextureStorage2DMultisample(...) FunctionWrapper::wrTextureStorage2DMultisample(__VA_ARGS__)
#define glTextureParameteri(...) FunctionWrapper::wrTextureParameteri(__VA_ARGS__)
#define glTextureParameterf(...) FunctionWrapper::wrTextureParameterf(__VA_ARGS__)
#define glCreateTextures(...) FunctionWrapper::wrCreateTextures(__VA_ARGS__)
#define glCreateBuffers(...) FunctionWrapper::wrCreateBuffers(__VA_ARGS__)
#define glCreateFramebuffers(...) FunctionWrapper::wrCreateFramebuffers(__VA_ARGS__)
#define glNamedFramebufferTexture(...) FunctionWrapper::wrNamedFramebufferTexture(__VA_ARGS__)
#define glDrawRangeElementsBaseVertex(...) FunctionWrapper::wrDrawRangeElementsBaseVertex(__VA_ARGS__)
#define glFlushMappedBufferRange(...) FunctionWrapper::wrFlushMappedBufferRange(__VA_ARGS__)
#define glTextureBarrier(...) FunctionWrapper::wrTextureBarrier(__VA_ARGS__)
#define glTextureBarrierNV(...) FunctionWrapper::wrTextureBarrierNV(__VA_ARGS__)
#define glClearBufferfv(...) FunctionWrapper::wrClearBufferfv(__VA_ARGS__)
#define glEnablei(...) FunctionWrapper::wrEnablei(__VA_ARGS__)
#define glDisablei(...) FunctionWrapper::wrDisablei(__VA_ARGS__)
#define glEGLImageTargetTexture2DOES(...) FunctionWrapper::wrEGLImageTargetTexture2DOES(__VA_ARGS__)

extern PFNGLCREATESHADERPROC RealCreateShader;
extern PFNGLCOMPILESHADERPROC RealCompileShader;
extern PFNGLSHADERSOURCEPROC RealShaderSource;
extern PFNGLCREATEPROGRAMPROC RealCreateProgram;
extern PFNGLATTACHSHADERPROC RealAttachShader;
extern PFNGLLINKPROGRAMPROC RealLinkProgram;
extern PFNGLUSEPROGRAMPROC RealUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC RealGetUniformLocation;
extern PFNGLUNIFORM1IPROC RealUniform1i;
extern PFNGLUNIFORM1FPROC RealUniform1f;
extern PFNGLUNIFORM2FPROC RealUniform2f;
extern PFNGLUNIFORM2IPROC RealUniform2i;
extern PFNGLUNIFORM4IPROC RealUniform4i;

extern PFNGLUNIFORM4FPROC RealUniform4f;
extern PFNGLUNIFORM3FVPROC RealUniform3fv;
extern PFNGLUNIFORM4FVPROC RealUniform4fv;
extern PFNGLDETACHSHADERPROC RealDetachShader;
extern PFNGLDELETESHADERPROC RealDeleteShader;
extern PFNGLDELETEPROGRAMPROC RealDeleteProgram;
extern PFNGLGETPROGRAMINFOLOGPROC RealGetProgramInfoLog;
extern PFNGLGETSHADERINFOLOGPROC RealGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC RealGetShaderiv;
extern PFNGLGETPROGRAMIVPROC RealGetProgramiv;

extern PFNGLENABLEVERTEXATTRIBARRAYPROC RealEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC RealDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC RealVertexAttribPointer;
extern PFNGLBINDATTRIBLOCATIONPROC RealBindAttribLocation;
extern PFNGLVERTEXATTRIB1FPROC RealVertexAttrib1f;
extern PFNGLVERTEXATTRIB4FPROC RealVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC RealVertexAttrib4fv;

extern PFNGLDEPTHRANGEFPROC RealDepthRangef;
extern PFNGLCLEARDEPTHFPROC RealClearDepthf;

extern PFNGLDRAWBUFFERSPROC RealDrawBuffers;
extern PFNGLGENFRAMEBUFFERSPROC RealGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC RealBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC RealDeleteFramebuffers;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC RealFramebufferTexture2D;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC RealTexImage2DMultisample;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC RealTexStorage2DMultisample;
extern PFNGLGENRENDERBUFFERSPROC RealGenRenderbuffers;
extern PFNGLBINDRENDERBUFFERPROC RealBindRenderbuffer;
extern PFNGLRENDERBUFFERSTORAGEPROC RealRenderbufferStorage;
extern PFNGLDELETERENDERBUFFERSPROC RealDeleteRenderbuffers;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC RealFramebufferRenderbuffer;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC RealCheckFramebufferStatus;
extern PFNGLBLITFRAMEBUFFERPROC RealBlitFramebuffer;
extern PFNGLGENVERTEXARRAYSPROC RealGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC RealBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC RealDeleteVertexArrays;
extern PFNGLGENBUFFERSPROC RealGenBuffers;
extern PFNGLBINDBUFFERPROC RealBindBuffer;
extern PFNGLBUFFERDATAPROC RealBufferData;
extern PFNGLMAPBUFFERPROC RealMapBuffer;
extern PFNGLMAPBUFFERRANGEPROC RealMapBufferRange;
extern PFNGLUNMAPBUFFERPROC RealUnmapBuffer;
extern PFNGLDELETEBUFFERSPROC RealDeleteBuffers;
extern PFNGLBINDIMAGETEXTUREPROC RealBindImageTexture;
extern PFNGLMEMORYBARRIERPROC RealMemoryBarrier;
extern PFNGLGETSTRINGIPROC RealGetStringi;
extern PFNGLINVALIDATEFRAMEBUFFERPROC RealInvalidateFramebuffer;
extern PFNGLBUFFERSTORAGEPROC RealBufferStorage;
extern PFNGLFENCESYNCPROC RealFenceSync;
extern PFNGLCLIENTWAITSYNCPROC RealClientWaitSync;
extern PFNGLDELETESYNCPROC RealDeleteSync;

extern PFNGLGETUNIFORMBLOCKINDEXPROC RealGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC RealUniformBlockBinding;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC RealGetActiveUniformBlockiv;
extern PFNGLGETUNIFORMINDICESPROC RealGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC RealGetActiveUniformsiv;
extern PFNGLBINDBUFFERBASEPROC RealBindBufferBase;
extern PFNGLBUFFERSUBDATAPROC RealBufferSubData;

extern PFNGLGETPROGRAMBINARYPROC RealGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC RealProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC RealProgramParameteri;

extern PFNGLTEXSTORAGE2DPROC RealTexStorage2D;
extern PFNGLTEXTURESTORAGE2DPROC RealTextureStorage2D;
extern PFNGLTEXTURESUBIMAGE2DPROC RealTextureSubImage2D;
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC RealTextureStorage2DMultisample;
extern PFNGLTEXTUREPARAMETERIPROC RealTextureParameteri;
extern PFNGLTEXTUREPARAMETERFPROC RealTextureParameterf;
extern PFNGLCREATETEXTURESPROC RealCreateTextures;
extern PFNGLCREATEBUFFERSPROC RealCreateBuffers;
extern PFNGLCREATEFRAMEBUFFERSPROC RealCreateFramebuffers;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC RealNamedFramebufferTexture;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC RealDrawRangeElementsBaseVertex;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC RealFlushMappedBufferRange;
extern PFNGLTEXTUREBARRIERPROC RealTextureBarrier;
extern PFNGLTEXTUREBARRIERNVPROC RealTextureBarrierNV;
extern PFNGLCLEARBUFFERFVPROC RealClearBufferfv;
extern PFNGLENABLEIPROC RealEnablei;
extern PFNGLDISABLEIPROC RealDisablei;

typedef void (APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, void* image);
extern PFNGLEGLIMAGETARGETTEXTURE2DOESPROC RealEGLImageTargetTexture2DOES;

void initGLFunctions();

#include "Graphics/OpenGLContext/ThreadedOpenGl/opengl_Wrapper.h"

#endif // GLFUNCTIONS_H
