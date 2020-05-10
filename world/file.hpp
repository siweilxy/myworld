/*
 * fjile.hpp
 *
 *  Created on: 10 May 2020
 *      Author: siwei
 */

#ifndef WORLD_FILE_HPP_
#define WORLD_FILE_HPP_
#include <string>
#include <fstream>
#include <iostream>

std::string readShaderSource(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath,std::ios::in);
    std::string line ="";
    while(!fileStream.eof())
    {
        getline(fileStream,line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

#endif /* WORLD_FILE_HPP_ */
