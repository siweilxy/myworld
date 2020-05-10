/*
 * errorPrint.hpp
 *
 *  Created on: 10 May 2020
 *      Author: siwei
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.hpp"

void printShaderLog(GLuint shader)
{
    int len = 0;
    int chWrittn = 0;
    char* temp;
    glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&len);
    if(len > 0)
    {
        temp = (char*)malloc(len);
        glGetShaderInfoLog(shader,len,&chWrittn,temp);
        LOG(INFO)<<"shader info log: "<<temp;
        free(temp);
    }
}

void printProgramLog(int prog)
{
    int len = 0;
    int chWrittn = 0;
    char* temp;
    glGetProgramiv(prog,GL_INFO_LOG_LENGTH,&len);
    if(len > 0)
    {
        temp = (char*)malloc(len);
        glGetShaderInfoLog(prog,len,&chWrittn,temp);
        LOG(INFO)<<"program info log:"<<temp;
        free(temp);
    }
}

bool checkOpenGlError()
{
    bool foundError = false;
    int glErr = glGetError();
    while(glErr != GL_NO_ERROR)
    {
        LOG(INFO)<<"glError:"<<glErr;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}
