#pragma once

#include <lead/euclidean.h>
#include <lead/color.h>

#include <string>
#include <vector>
#include <map>



class PropertyList {
public:
    enum PropertyType {
        LFloat = 0,
        LInt,
        LPoint,
        LVector,
        LColor,
        LString,
        LUnkown
    };

    static PropertyType classNameToPropertyType(std::string key) {
        if(key.compare("float") == 0)    return LFloat;
        if(key.compare("int") == 0)      return LInt;
        if(key.compare("point") == 0)    return LPoint;
        if(key.compare("vector") == 0)   return LVector;
        if(key.compare("color") == 0)    return LColor;
        if(key.compare("string") == 0)   return LString;

        return PropertyType::LUnkown;
    }

    static std::string propertyTypeToClassName(PropertyType value) {
        switch (value) {
        case LFloat:    return "float";
        case LInt:      return "int";
        case LPoint:    return "point";
        case LVector:   return "vector";
        case LColor:    return "color";
        case LString:   return "string";        
        }

        return "Unknown PropertyType";
    }

    PropertyList() {}

    void setFloat(std::string key, float val)           { floats[key] = val; }
    void setInt(std::string key, int val)               { ints[key] = val; }
    void setPoint(std::string key, Point3f val)         { points[key] = val; }
    void setVector(std::string key, Vector3f val)       { vectors[key] = val; }
    void setColor(std::string key, Color3f val)         { colors[key] = val; }
    void setString(std::string key, std::string val)    { strings[key] = val; }

    float getFloat(std::string key, float def) const  {
        if(auto search = floats.find(key); search != floats.end())
            return search->second;
        return def;
    }
    int getInt(std::string key, int def) const  {
        if(auto search = ints.find(key); search != ints.end())
            return search->second;
        return def;
    }
    Point3f getPoint(std::string key, Point3f def) const  {
        if(auto search = points.find(key); search != points.end())
            return search->second;
        return def;
    }
    Vector3f getVector(std::string key, Vector3f def) const  {
        if(auto search = vectors.find(key); search != vectors.end())
            return search->second;
        return def;
    }
    Color3f getColor(std::string key, Color3f def) const  {
        if(auto search = colors.find(key); search != colors.end())
            return search->second;
        return def;
    }
    std::string getString(std::string key, std::string def) const  {
        if(auto search = strings.find(key); search != strings.end())
            return search->second;
        return def;
    }

    std::string toString() const {
        std::string final_str = "";
        for (const auto& keyval: floats)
            final_str.append(tfm::format("%s: %f\n", keyval.first, keyval.second));
        for (const auto& keyval: ints)
            final_str.append(tfm::format("%s: %d\n", keyval.first, keyval.second));
        for (const auto& keyval: points)
            final_str.append(tfm::format("%s: %s\n", keyval.first, keyval.second.toString()));
        for (const auto& keyval: vectors)
            final_str.append(tfm::format("%s: %s\n", keyval.first, keyval.second.toString()));
        for (const auto& keyval: colors)
            final_str.append(tfm::format("%s: %s\n", keyval.first, keyval.second.toString()));
        for (const auto& keyval: strings)
            final_str.append(tfm::format("%s: %s\n", keyval.first, keyval.second));
        
        return final_str;
    }

protected:
    std::map<std::string, float> floats;
    std::map<std::string, int> ints;
    std::map<std::string, Point3f> points;
    std::map<std::string, Vector3f> vectors;
    std::map<std::string, Color3f> colors;
    std::map<std::string, std::string> strings;
};

