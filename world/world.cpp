#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include "errorPrint.hpp"
#include "log.hpp"
#include "file.hpp"

#define numVAOs 1

float x =0.0f;
float inc = 0.01f;

GLuint renderingProgram;
GLuint vao[numVAOs];

std::string path="";

GLuint createShaderProgram ()
{
    std::string vShaderStr = readShaderSource ((path + "vertShader.glsl").c_str());
    std::string fragShaderStr = readShaderSource ((path + "fragShader.glsl").c_str());
    const char *vs = vShaderStr.c_str ();
    const char *fs = fragShaderStr.c_str ();
    GLuint vShader = glCreateShader (GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader (GL_FRAGMENT_SHADER);
    GLint vertCompiled, fragCompiled, linked;

    glShaderSource (vShader, 1, &vs, NULL);
    glShaderSource (fShader, 1, &fs, NULL);
    glCompileShader (vShader);

    checkOpenGlError ();
    glGetShaderiv (vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1)
    {
        printf ("vertex compilation failed \n");
        printShaderLog (vShader);
    }

    glCompileShader (fShader);
    checkOpenGlError ();
    glGetShaderiv (fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1)
    {
        printf ("fragment compilation failed \n");
        printShaderLog (fShader);
    }

    GLuint vfProgram = glCreateProgram ();
    glAttachShader (vfProgram, vShader);
    glAttachShader (vfProgram, fShader);
    glLinkProgram (vfProgram);
    checkOpenGlError ();
    glGetProgramiv (vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1)
    {
        printf ("linking failed \n");
        printProgramLog (vfProgram);
    }
    return vfProgram;
}

void init (GLFWwindow *window)
{
    renderingProgram = createShaderProgram ();
    glGenVertexArrays (numVAOs, vao);
    glBindVertexArray (vao[0]);
}

void display (GLFWwindow *window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram (renderingProgram);
    x+=inc;
    if(x > 1.0f)
    {
        inc = -0.01f;
    }

    if(x<-1.0f)
    {
        inc = 0.01f;
    }

    GLuint offsetLoc = glGetUniformLocation(renderingProgram,"offset");//获取glsl里的offset项
    glProgramUniform1f(renderingProgram,offsetLoc,x);
    glDrawArrays (GL_TRIANGLES, 0, 3);
    //glPointSize (30);
}

int main (int argc, char *argv[])
{
    int ret = 0;
    ret = swlog::getInstance ().init ();
    if (ret != 0)
    {
        printf ("log init error");
        return -1;
    }

    char* temp = nullptr;
    temp = getenv("GLSL_PATH");
    if (temp == nullptr)
    {
        LOG(ERROR)<<"GLSL_PATH 没有设置";
        return -1;
    }

    path=temp;
    LOG(INFO) << "GLSL_PATH is " << path;
    const GLubyte *name = glGetString (GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
    const GLubyte *biaoshifu = glGetString (GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
    const GLubyte *OpenGLVersion = glGetString (GL_VERSION); //返回当前OpenGL实现的版本号
    const GLubyte *gluVersion = gluGetString (GLU_VERSION); //返回当前GLU工具库版本
    LOG(INFO) << "OpenGL实现厂商的名字：" << name;
    LOG(INFO) << "渲染器标识符：" << biaoshifu;
    LOG(INFO) << "OOpenGL实现的版本号：" << OpenGLVersion;
    LOG(INFO) << "OGLU工具库版本：" << gluVersion;

    if (!glfwInit ())
    {
        LOG(ERROR) << "glfwInit failed";
        return -1;
    }

    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    GLFWwindow *window = glfwCreateWindow (600, 600, "my-world", nullptr,
                                           nullptr);
    glfwMakeContextCurrent (window);
    if (glewInit () != GLEW_OK)
    {
        LOG(ERROR) << "glewinit failed";
        return -1;
    }

    glfwSwapInterval (1); //开启垂直同步
    init (window);
    while (!glfwWindowShouldClose (window))
    {
        display (window, glfwGetTime ());
        glfwSwapBuffers (window); //开启垂直同步
        glfwPollEvents ();
    }

    glfwDestroyWindow (window);
    glfwTerminate ();
    return 0;
}
