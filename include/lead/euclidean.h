#pragma once

#include <lead/common.h>

class Vector3f {
public:
    float x, y, z;

    Vector3f() {}
    Vector3f(float a): x{a}, y{a}, z{a} {}
    Vector3f(const Vector3f &o): x{o.x}, y{o.y}, z{o.z} {}
    Vector3f(float x, float y, float z): x{x}, y{y}, z{z} {}

    Vector3f(std::vector<std::string> values) {
        if(values.size() < 1)
            throw LeadException("Too few values provided for vector!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for vector!");
        
        x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
        z = values.size() > 2 ? std::stof(values[2]) : 0.0f;
    }

    std::string toString() const {
        return tfm::format("(%f, %f, %f)", x, y, z);
    }

    float dot(const Vector3f &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3f cross(const Vector3f &o) const {
        return Vector3f(y*o.z - o.y*z, o.x*z - x*o.z, x*o.y - o.x*y);
    }

    Vector3f normalized() const {
        float n = norm();
        return Vector3f(x/n, y/n, z/n);
    }

    float norm() const { return std::sqrt(x*x + y*y + z*z); }


    Vector3f operator-(const Vector3f &other) const {
        return Vector3f(x - other.x, y - other.y, z - other.z);
    }

    bool operator<=(const Vector3f &o) const {
        return x <= o.x && y <= o.y && z <= o.z;
    }

    bool operator<(const Vector3f &o) const {
        return x < o.x && y < o.y && z < o.z;
    }

    bool operator>=(const Vector3f &o) const {
        return x >= o.x && y >= o.y && z >= o.z;
    }

    bool operator>(const Vector3f &o) const {
        return x > o.x && y > o.y && z > o.z;
    }

    float operator[](const int idx) const {
        switch (idx) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
        }
    }

    Vector3f operator*(const float &o) const {
        return Vector3f(x * o, y * o, z * o);
    }

    Vector3f operator/(const float &o) const {
        return Vector3f(x / o, y / o, z / o);
    }
    
    Vector3f operator*(const Vector3f &o) const {
        return Vector3f(x * o.x, y * o.y, z * o.z);
    }

    friend Vector3f operator*(float scalar, const Vector3f& vec) {
        return vec * scalar;
    }

    
};

typedef Vector3f Point3f;

inline Vector3f operator+(const Point3f &u, const Point3f &v) {
    return Vector3f(u.x - v.x, u.y - v.y, u.z - v.z);
}

class Point2f {
public:
    float x, y;

    Point2f() {}
    Point2f(float x): x{x}, y{x} {}
    Point2f(float x, float y): x{x}, y{y} {}
    Point2f(const Point2f &o): x{o.x}, y{o.y} {}

    Point2f(std::vector<std::string> values) {
        if(values.size() < 1)
            throw LeadException("Too few values provided for point!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for point!");
        
        x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
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
