#include <lead/common.h>
#include <lead/integrator.h>
#include <lead/scene.h>

LEAD_NAMESPACE_BEGIN

class NormalIntegrator: public Integrator {
public:
    NormalIntegrator(const PropertyList &propList) {}

    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const override {
        Intersection its;
        if(scene->rayIntersect(ray, its))
            return Color3f(its.n.cwiseAbs().x(), its.n.cwiseAbs().y(), its.n.cwiseAbs().z());

        return Color3f(0.f, 0.f, 0.f);
    }

    virtual std::string toString() const {
        return tfm::format(
            "NormalIntegrator[]"
        );
    }
};

LEAD_REGISTER_CLASS(NormalIntegrator, "normal")
LEAD_NAMESPACE_END