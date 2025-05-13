//
//  matrix_utils.cpp
//  CameraApp
//
//  Created by Danil Rostov on 5/12/25.
//

#include "matrix_utils.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <cmath>

glm::mat4 customMultiply(const glm::mat4& A, const glm::mat4& B) {
    glm::mat4 result(0.0f);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int k = 0; k < 4; ++k) {
                result[col][row] += A[k][row] * B[col][k];
            }
        }
    }
    return result;
}

glm::mat4 buildManualModelMatrix() {
    glm::mat4 scale = glm::mat4(1.0f);
    scale[0][0] = 1.2f;
    scale[1][1] = 1.0f;
    scale[2][2] = 1.0f;

    glm::mat4 shear = glm::mat4(1.0f);
    shear[1][0] = 0.5f;

    glm::mat4 rotation = glm::mat4(1.0f);
    float angle = (float)glfwGetTime();
    float c = cos(angle);
    float s = sin(angle);
    rotation[0][0] = c;
    rotation[0][1] = -s;
    rotation[1][0] = s;
    rotation[1][1] = c;

    glm::mat4 model = customMultiply(scale, shear);
    model = customMultiply(model, rotation);
    return model;
}
