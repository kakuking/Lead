#pragma once

#include <lead/common.h>
#include <lead/object.h>

class Camera: public LeadObject {
public:
    virtual Ray3f sampleRay(const Point2f sampledPosition) const = 0;

    virtual LeadObject::ObjectType getClassType() const override { return LeadObject::LCamera; }

protected:
    Point3f m_outputSize;
};