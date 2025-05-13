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

glm::mat4 createTransformMatrix(float time, const std::vector<glm::mat4>& transforms) {
    glm::mat4 result = glm::mat4(1.0f);
    for (const auto& t : transforms) {
        result = customMultiply(result, t);
    }
    return result;
}
