#include <lead/common.h>
#include <lead/integrator.h>
#include <lead/scene.h>

LEAD_NAMESPACE_BEGIN

class DirectIntegrator: public Integrator {
public:
    DirectIntegrator(const PropertyList &propList) {}

    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const override {
        if(scene->rayIntersect(ray))
            return Color3f(0.f, 0.5f, 0.f);

        return Color3f(0.5f, 0.f, 0.5f);
    }

    virtual std::string toString() const {
        return tfm::format(
            "DirectIntegrator[]"
        );
    }
};

LEAD_REGISTER_CLASS(DirectIntegrator, "direct")
LEAD_NAMESPACE_END