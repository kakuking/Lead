#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/color.h>

LEAD_NAMESPACE_BEGIN

class Integrator: public LeadObject {
public:
    virtual void preprocess(const Scene* scene) {}

    virtual void activate() {}

    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const = 0;

    virtual LeadObject::ObjectType getClassType() const override { return LeadObject::LIntegrator; }
};

LEAD_NAMESPACE_END