#pragma once

#include <lead/common.h>

class Color3f: public glm::vec3 {
public:
    using glm::vec3::vec;

    Color3f(std::vector<std::string> values) {
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
};

