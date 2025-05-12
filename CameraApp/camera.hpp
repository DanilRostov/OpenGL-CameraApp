//
//  camera.hpp
//  CameraApp
//
//  Created by Danil Rostov on 4/21/25.
//

#ifndef camera_hpp
#define camera_hpp

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    enum class ProjectionType
    {
        Perspective,
        Orthographic
    };

    Camera();

    void apply(GLuint shaderProgram);

    void setProjectionType(ProjectionType type);
    void setPreserveAspect(bool preserve);
    void setLimits(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
    void setScale(double limit);
    void lookAt(const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up);
    void setDragging(bool dragging);

    void onMouseDown(int x, int y);
    void onMouseMove(int x, int y);

private:
    glm::vec3 eye, ref, up;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    bool preserveAspect;
    ProjectionType projectionType;

    bool dragging = false;
    glm::vec3 prevRay;

    glm::vec3 screenToArcball(int x, int y);
    void applyArcballRotation(const glm::vec3 &from, const glm::vec3 &to);
};

#endif /* camera_hpp */
