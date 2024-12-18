#pragma once

#include <lead/common.h>

class Color3f {
public:
    float x, y, z;

    Color3f() {}
    Color3f(float a): x{a}, y{a}, z{a} {}
    Color3f(const Color3f &o): x{o.x}, y{o.y}, z{o.z} {}
    Color3f(float x, float y, float z): x{x}, y{y}, z{z} {}


    Color3f(std::vector<std::string> values) {
        if(values.size() < 1)
            throw LeadException("Too few values provided for point!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for point!");
        
        x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
        z = values.size() > 2 ? std::stof(values[2]) : 0.0f;
    }
    
    std::string toString() const {
        return tfm::format("(%f, %f, %f)", x, y, z);
    }
};

