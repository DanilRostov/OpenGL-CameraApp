//
//  matrix_utils.hpp
//  CameraApp
//
//  Created by Danil Rostov on 5/12/25.
//

#ifndef matrix_utils_hpp
#define matrix_utils_hpp

#include <glm/glm.hpp>

glm::mat4 customMultiply(const glm::mat4& A, const glm::mat4& B);
glm::mat4 buildManualModelMatrix();

#endif /* matrix_utils_hpp */
