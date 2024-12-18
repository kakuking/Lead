#pragma once
#include <lead/common.h>
#include <lead/object.h>
#include <lead/render.h>

class Sampler: public LeadObject {
public:
    virtual void initialize() {}

    virtual void prepare(const Block &block) {}

    virtual void generate() {}

    virtual float next1D() = 0;

    virtual Point2f next2D() = 0;

    virtual Point3f next3D() = 0;

    virtual ObjectType getClassType() const override { return ObjectType::LSampler; }

protected:
    int m_sampleCount;
};