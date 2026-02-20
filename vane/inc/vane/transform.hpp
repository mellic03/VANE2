#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/gtx/matrix_decompose.hpp>

struct VaneTransform;
class Transformable;



struct VaneTransform
{
private:
    friend class Transformable;
    glm::vec3 mPos;
    glm::quat mRot;
    float mScale;

public:
    VaneTransform(): VaneTransform(glm::vec3(0.0f)) {  }
    VaneTransform(const glm::vec3 &p): mPos(p), mRot(glm::vec3(0.0f)), mScale(1.0f) {  }

    glm::mat4 to_mat4() const
    {
        glm::mat4 mat = glm::translate(glm::mat4(1.0f), mPos);
        mat = glm::rotate(mat, glm::radians(mRot.x), glm::vec3(1,0,0));
        mat = glm::rotate(mat, glm::radians(mRot.y), glm::vec3(0,1,0));
        mat = glm::rotate(mat, glm::radians(mRot.z), glm::vec3(0,0,1));
        mat = glm::scale(mat, glm::vec3(mScale));
        return mat;
    }

    const glm::vec3 &getPos() { return mPos; }
    const glm::quat &getRot() { return mRot; }
    const float getScale() { return mScale; }

    void setPos(const glm::vec3 &p) { mPos = p; }
    void setRot(const glm::quat &q) { mRot = q; }
    void setScl(float s) { mScale = s; }

    void translate(float x, float y, float z) { mPos += glm::vec3(x, y, z); }
    void translate(const glm::vec3 &delta) { mPos += delta; }

    void rotate(float radTheta, const glm::vec3 &axis)
    {
        mRot = glm::normalize(mRot * glm::angleAxis(radTheta, axis));
    }

};



class Transformable
{
private:
    VaneTransform mT;

public:
    VaneTransform &getTransform() { return mT; }

    const glm::vec3 &getPos() { return mT.mPos; }
    const glm::quat &getRot() { return mT.mRot; }
    const float getScale() { return mT.mScale; }

    void setPos(const glm::vec3 &p) { mT.mPos = p; }
    void setRot(const glm::quat &q) { mT.mRot = q; }
    void setScl(float s) { mT.mScale = s; }

    void translate(float x, float y, float z) { mT.mPos += glm::vec3(x, y, z); }
    void translate(const glm::vec3 &delta) { mT.mPos += delta; }

    void rotate(float radTheta, const glm::vec3 &axis)
    {
        mT.mRot = glm::normalize(mT.mRot * glm::angleAxis(radTheta, axis));
    }

};

