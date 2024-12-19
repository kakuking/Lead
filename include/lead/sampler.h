#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/block.h>

LEAD_NAMESPACE_BEGIN

class Sampler: public LeadObject {
public:
    virtual void initialize() {}

    virtual void prepare(const Block &block) {}

    virtual void generate() {}

    virtual float next1D() = 0;

    virtual Point2f next2D() = 0;

    virtual Point3f next3D() = 0;

    virtual ObjectType getClassType() const override { return ObjectType::LSampler; }

    virtual int getSampleCount() { return m_sampleCount; }

protected:
    int m_sampleCount;
};

LEAD_NAMESPACE_END