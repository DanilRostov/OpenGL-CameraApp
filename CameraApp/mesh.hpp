//
//  mesh.hpp
//  CameraApp
//
//  Created by Danil Rostov on 4/23/25.
//

#ifndef mesh_hpp
#define mesh_hpp

#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
    void init();
    void draw() const;
    void cleanup();

private:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
};

#endif /* mesh_hpp */
