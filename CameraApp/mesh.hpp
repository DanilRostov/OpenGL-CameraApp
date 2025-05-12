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

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class Mesh {
public:
    void init();
    void draw() const;
    void cleanup();

private:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

#endif /* mesh_hpp */
