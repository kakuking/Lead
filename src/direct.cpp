#include <lead/common.h>
#include <lead/integrator.h>

class DirectIntegrator: public Integrator {
public:
    DirectIntegrator(const PropertyList &propList) {}

    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const override {
        return Color3f(0.f);
    }

    virtual std::string toString() const {
        return tfm::format(
            "DirectIntegrator[]"
        );
    }
};

LEAD_REGISTER_CLASS(DirectIntegrator, "direct")