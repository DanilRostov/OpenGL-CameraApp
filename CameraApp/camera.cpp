//
//  camera.cpp
//  CameraApp
//
//  Created by Danil Rostov on 4/21/25.
//

#include "camera.hpp"
#include <glm/glm.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>

Camera::Camera()
    : eye(0.0, 0.0, 30.0), ref(0.0), up(0.0, 1.0, 0.0),
      xmin(-5), xmax(5), ymin(-5), ymax(5), zmin(-10), zmax(10),
      preserveAspect(true), projectionType(ProjectionType::Perspective) {}

void Camera::setProjectionType(ProjectionType type)
{
    projectionType = type;
}

void Camera::setPreserveAspect(bool preserve)
{
    preserveAspect = preserve;
}

void Camera::setLimits(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
{
    xmin = xMin;
    xmax = xMax;
    ymin = yMin;
    ymax = yMax;
    zmin = zMin;
    zmax = zMax;
}

void Camera::setScale(double limit)
{
    setLimits(-limit, limit, -limit, limit, -2 * limit, 2 * limit);
}

void Camera::lookAt(const glm::vec3 &eyePos, const glm::vec3 &target, const glm::vec3 &upVec)
{
    eye = eyePos;
    ref = target;
    up = upVec;
}

void Camera::setDragging(bool dragging)
{
    this->dragging = dragging;
}

void Camera::apply(GLuint shaderProgram)
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    double xMin = xmin, xMax = xmax, yMin = ymin, yMax = ymax;
    if (preserveAspect)
    {
        double aspect = static_cast<double>(height) / width;
        double desired = (ymax - ymin) / (xmax - xmin);

        if (desired > aspect)
        {
            double extra = ((desired / aspect) - 1.0) * (xMax - xMin) / 2.0;
            xMin -= extra;
            xMax += extra;
        }
        else
        {
            double extra = ((aspect / desired) - 1.0) * (yMax - yMin) / 2.0;
            yMin -= extra;
            yMax += extra;
        }
    }

    double viewDist = glm::length(eye - ref);

    glm::mat4 projection;
    if (projectionType == ProjectionType::Orthographic)
    {
        projection = glm::ortho(static_cast<float>(xMin), static_cast<float>(xMax),
                                static_cast<float>(yMin), static_cast<float>(yMax),
                                static_cast<float>(viewDist - zmax), static_cast<float>(viewDist - zmin));
    }
    else
    {
        double near = std::max(viewDist - zmax, 0.1);
        double fovY = glm::degrees(2.0 * atan((yMax - yMin) / (2.0 * viewDist)));
        double aspect = static_cast<double>(width) / height;
        projection = glm::perspective(glm::radians(static_cast<float>(fovY)), static_cast<float>(aspect),
                                      static_cast<float>(near), static_cast<float>(viewDist - zmin));
    }

    glm::mat4 view = glm::lookAt(eye, ref, up);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uView"), 1, GL_FALSE, glm::value_ptr(view));
}

glm::vec3 Camera::screenToArcball(int x, int y)
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    float cx = width / 2.0f, cy = height / 2.0f;
    float scale = 0.8f * std::min(cx, cy);
    float dx = (x - cx);
    float dy = (cy - y);
    float len = std::sqrt(dx * dx + dy * dy);
    float dz = (len >= scale) ? 0 : std::sqrt(scale * scale - dx * dx - dy * dy);
    glm::vec3 v(dx, dy, dz);
    return glm::normalize(v);
}

void Camera::onMouseDown(int x, int y)
{
    dragging = true;
    prevRay = screenToArcball(x, y);
}

void Camera::onMouseMove(int x, int y)
{
    if (!dragging)
        return;
    glm::vec3 currRay = screenToArcball(x, y);
    applyArcballRotation(prevRay, currRay);
    prevRay = currRay;
}

void Camera::applyArcballRotation(const glm::vec3 &from, const glm::vec3 &to)
{
    glm::vec3 axis = glm::cross(from, to);
    float angle = acosf(glm::dot(from, to));
    if (glm::length(axis) < 0.0001f)
        return;

    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, axis);
    glm::vec4 newDir = rot * glm::vec4(eye - ref, 0.0f);
    glm::vec4 newUp = rot * glm::vec4(up, 0.0f);
    eye = ref + glm::vec3(newDir);
    up = glm::normalize(glm::vec3(newUp));
}
