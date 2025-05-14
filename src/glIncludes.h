//glIncludes.h 包含OpenGL必要的头文件。
#ifndef _GLINCLUDES_H_INCLUDED_
#define _GLINCLUDES_H_INCLUDED_ 1
#if defined(_USE_GLEW)
#include <GL/glew.h>
#else
#include <GLAD/glad.h>
#include <GL/glext.h>
#endif
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
//可能用到的OpenGL数学库、图像加载库
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SOIL2/SOIL2.h>
#endif //_GLINCLUDES_H_INCLUDED_