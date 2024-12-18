#pragma once

#include <lead/common.h>

class Vector3f: public glm::vec3 {
public:
    using glm::vec3::vec3;

    Vector3f(std::vector<std::string> values) {
        if(values.size() < 1)
            throw LeadException("Too few values provided for vector!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for vector!");
        
        float x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        float y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
        float z = values.size() > 2 ? std::stof(values[2]) : 0.0f;

        *static_cast<glm::vec3*>(this) = glm::vec3(x, y, z);
    }

    std::string toString() const {
        return tfm::format("(%f, %f, %f)", x, y, z);
    }

    float dot(const Vector3f &other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

class Point3f: public glm::vec3 {
public:
    using glm::vec3::vec3;

    Point3f(std::vector<std::string> values) {
        if(values.size() < 1)
            throw LeadException("Too few values provided for point!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for point!");
        
        float x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        float y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
        float z = values.size() > 2 ? std::stof(values[2]) : 0.0f;

        *static_cast<glm::vec3*>(this) = glm::vec3(x, y, z);
    }
    
    std::string toString() const {
        return tfm::format("(%f, %f, %f)", x, y, z);
    }

    float dot(const Point3f &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3f operator-(const Point3f &other) const {
        return Vector3f(x- other.x, y - other.y, z - other.z);
    }

    bool operator<=(const Point3f &other) const {
        return *this <= other;
    }

    bool operator>=(const Point3f &other) const {
        return *this >= other;
    }
};

class Point2f: public glm::vec2 {
public:
    using glm::vec2::vec2;

    Point2f(std::vector<std::string> values) {
        if(values.size() < 1)
            throw LeadException("Too few values provided for point!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for point!");
        
        float x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        float y = values.size() > 1 ? std::stof(values[1]) : 0.0f;

        *static_cast<glm::vec2*>(this) = glm::vec2(x, y);
    }
    
    std::string toString() const {
        return tfm::format("(%f, %f)", x, y);
    }

    Vector3f operator-(const Point2f &other) {
        return Vector3f(*this - other);
    }
};

class Ray3f {
public:
    Ray3f(Point3f o, Vector3f d): o{o}, d{d}, minT{EPSILON}, maxT{INFINITY} {}
    Ray3f(Point3f o, Vector3f d, float minT, float maxT): o{o}, d{d}, minT{minT}, maxT{maxT} {}
    Ray3f(const Ray3f &cp) {
        o = cp.o;
        d = cp.d;
        minT = cp.minT;
        maxT = cp.maxT;
    }

    Point3f at(float t) const {
        return o + d * t;
    }

    Point3f o;
    Vector3f d;
    float minT, maxT;
};
