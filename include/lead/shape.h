#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/boundingBox.h>

// To pass information of intersection back and forth
struct Intersection {
    // Point of intersection
    Point3f p;
    // Normal at point of intersection (in global frame)
    Vector3f n;
    // UV coordinates
    Point2f uv;

    std::string toString() {
        return tfm::format(
            "Intersection:[\n"
            "   p: %s\n"
            "   n: %s\n"
            "   uv: %s\n"
            "]",
            p.toString(), n.toString(), uv.toString()
        );
    }
};

class Shape: public LeadObject {
public:
    virtual bool rayIntersect(const Ray3f &ray, float t, float u, float v) const = 0;

    virtual void setHitInformation(const Ray3f &ray, Intersection &its) const = 0;

    virtual ObjectType getClassType() const override { return LShape; }

    virtual void addChild(LeadObject* obj) override {
        LeadObject::ObjectType classType = obj->getClassType();
        std::string className = obj->objectTypeToClassName(classType);

        std::cout << tfm::format("Class %s cannot be added to this shape!\n", className);
    }

    virtual void activate() override {};

    BoundingBox getBoundingBox() const { return m_bbox; }

protected:
    BoundingBox m_bbox;
};