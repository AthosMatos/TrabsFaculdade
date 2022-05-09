#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <glew.h>
#include "stb_image.h"
#include <glfw3.h>

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

GLuint loadAnyFile(const char* imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);


#endif