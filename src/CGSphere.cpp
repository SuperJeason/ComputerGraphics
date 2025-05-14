#include "pch.h"
#include "CGSphere.h"
#include "TessellationHints.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
IMPLEMENT_SERIAL(CGSphere, CGRenderable, 1)
CGSphere::CGSphere(float radius) : mRadius(radius) {}
CGSphere::CGSphere(const CGSphere& sphere)
    : CGRenderable(sphere),
    mRadius(sphere.mRadius),
    mTessellationHints(sphere.mTessellationHints) {
}
void CGSphere::setRadius(float radius) {
    if (mRadius != radius) {
        mRadius = radius;
        setDisplayListDirty(true); 
    }
}
void CGSphere::setTessellationHints(std::shared_ptr<TessellationHints> hints) {
    if (mTessellationHints.get() != hints.get()) {
        mTessellationHints = hints;
        setDisplayListDirty(true); 
    }
}
void CGSphere::buildDisplayList() {
    TessellationHints* hints = tessellationHints();
    bool createNormals = hints ? hints->createNormals() : true;
    bool createTextureCoords = hints ? hints->createTextureCoords() : true;

    unsigned int slices = hints ? hints->targetSlices() : 40;
    unsigned int stacks = hints ? hints->targetStacks() : 20;

    for (unsigned int slice = 0; slice < slices; ++slice) { 
        float theta1 = slice * glm::two_pi<float>() / slices;    
        float theta2 = (slice + 1) * glm::two_pi<float>() / slices;
        glBegin(GL_QUAD_STRIP);
        for (unsigned int stack = 0; stack <= stacks; ++stack) {
            float phi = stack * glm::pi<float>() / stacks;       
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            glm::vec3 pos1(mRadius * cos(theta1) * sinPhi, mRadius * sin(theta1) * sinPhi, mRadius * cosPhi);

            glm::vec3 pos2(mRadius * cos(theta2) * sinPhi, mRadius * sin(theta2) * sinPhi, mRadius * cosPhi);

            if (createNormals) {
                glm::vec3 normal1 = glm::normalize(pos1);
                glNormal3fv(glm::value_ptr(normal1));
            }

            if (createTextureCoords) {
                float s1 = static_cast<float>(slice) / slices;   
                float s2 = static_cast<float>(slice + 1) / slices;
                float t = static_cast<float>(stack) / stacks;   
                glTexCoord2f(s1, t);
                glVertex3fv(glm::value_ptr(pos1));
                glTexCoord2f(s2, t); 
                glVertex3fv(glm::value_ptr(pos2));
            }
            else {
                glVertex3fv(glm::value_ptr(pos1));
                glVertex3fv(glm::value_ptr(pos2));
            }
        }
        glEnd();
    }
}