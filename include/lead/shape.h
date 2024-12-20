#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/frame.h>
#include <lead/boundingBox.h>
#include <lead/transform.h>

LEAD_NAMESPACE_BEGIN

struct MediumInterface {

};

// To pass information of intersection back and forth
struct Interaction {
    // Point of intersection
    Point3f p;
    // Normal at point of intersection (in global frame)
    Normal3f n;
    // UV coordinates
    Point2f uv;
    // time of intersection
    float t;
    // Outgoing direction
    Vector3f wo;
    // Frame at point
    Frame geoFrame;
    Frame shFrame;

    Medium *medium;
    MediumInterface mediumInterface;

    std::string toString() const {
        return tfm::format(
            "Interaction:[\n"
            "   p: %s\n"
            "   n: %s\n"
            "   uv: %s\n"
            "]",
            p.toString(), n.toString(), uv.toString()
        );
    }

    bool isSurfaceInteraction() const { return n != Normal3f(0.f, 0.f, 0.f); }
    bool isMediumInteraction() const { return !isSurfaceInteraction(); }
};

class Shape: public LeadObject {
public:
    virtual bool rayIntersect(const Ray3f &ray, float &t, float &u, float &v) const = 0;

    virtual void setHitInformation(const Ray3f &ray, Interaction &its) const = 0;

    virtual ObjectType getClassType() const override { return LShape; }

    virtual void addChild(LeadObject* obj) override {
        LeadObject::ObjectType classType = obj->getClassType();
        std::string className = obj->objectTypeToClassName(classType);

        switch(classType){
            case LeadObject::ObjectType::LTransform:
                m_transform = *(static_cast<Transform *>(obj));
                m_invTransform = m_transform.getInverse();
                break;

            default:
                std::cout << tfm::format("Class %s cannot be added to a shape!\n", className);
                break;
        }
    }

    virtual void activate() override {};

    BoundingBox getBoundingBox() const { return m_bbox; }

protected:
    Transform m_transform, m_invTransform;
    BoundingBox m_bbox;
};

LEAD_NAMESPACE_END