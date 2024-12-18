#pragma once

#include <lead/common.h>
#include <lead/object.h>

class Integrator: public LeadObject {
public:
    virtual void preprocess(const Scene* scene) {}

    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const = 0;

    virtual LeadObject::ObjectType getClassType() const override { return LeadObject::LIntegrator; }
};
