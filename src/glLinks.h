// glLinks.h 该文件包含到主函数所在的cpp文件。项目中只引用一次
#ifndef _GLLINKS_H_INCLUDED_ 
#define _GLLINKS_H_INCLUDED_ 1
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glm.lib")
#pragma comment(lib,"soil2.lib")
#if defined(NDEBUG) || !defined(_DEBUG) //Release模式
#if defined(_USE_GLEW)
#pragma comment(lib,"glew32.lib")
#else
#pragma comment(lib,"glad.lib")
#endif
#else //Debug模式
#if defined(_USE_GLEW)
#pragma comment(lib,"glew32d.lib")
#else
#pragma comment(lib,"glad.lib")
#endif
#endif
#endif //_GLLINKS_H_INCLUDED_