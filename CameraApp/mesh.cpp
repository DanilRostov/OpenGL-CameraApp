//
//  mesh.cpp
//  CameraApp
//
//  Created by Danil Rostov on 4/23/25.
//

#include "mesh.hpp"

void Mesh::init() {
    vertices = {
        {{-1, -1, -1}, {1, 0, 0}},  // 0 - Red
        {{ 1, -1, -1}, {0, 1, 0}},  // 1 - Green
        {{ 1,  1, -1}, {0, 0, 1}},  // 2 - Blue
        {{-1,  1, -1}, {1, 1, 0}},  // 3 - Yellow
        {{-1, -1,  1}, {1, 0, 1}},  // 4 - Magenta
        {{ 1, -1,  1}, {0, 1, 1}},  // 5 - Cyan
        {{ 1,  1,  1}, {1, 1, 1}},  // 6 - White
        {{-1,  1,  1}, {0, 0, 0}},  // 7 - Black
    };

    indices = {
        0, 1, 2, 2, 3, 0,  // back face
        4, 5, 6, 6, 7, 4,  // front face
        0, 4, 7, 7, 3, 0,  // left face
        1, 5, 6, 6, 2, 1,  // right face
        3, 2, 6, 6, 7, 3,  // top face
        0, 1, 5, 5, 4, 0   // bottom face
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Set Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Set Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // Color
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
