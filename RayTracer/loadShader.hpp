//
//  loadShader.hpp
//  RayTracer
//
//  Created by Joseph Sample on 11/25/15.
//  Copyright © 2015 Joseph Sample. All rights reserved.
//

#ifndef LOAD_SHADER_HPP
#define LOAD_SHADER_HPP
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

#endif
