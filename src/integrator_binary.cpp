#include <lead/common.h>
#include <lead/integrator.h>
#include <lead/scene.h>

LEAD_NAMESPACE_BEGIN

class BinaryIntegrator: public Integrator {
public:
    BinaryIntegrator(const PropertyList &propList) {
        activeColor = propList.getColor("active", Color3f(1.f));
        bgColor = propList.getColor("bg", Color3f(1.f) - activeColor);
    }

    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const override {
        Interaction its;
        if(scene->rayIntersect(ray))
            return activeColor;

        return bgColor;
    }

    virtual std::string toString() const {
        return tfm::format(
            "BinaryIntegrator[\n"
            "  active: %s\n"
            "  bg: %s\n"
            "]",
            activeColor.toString(),
            bgColor.toString()
        );
    }

protected:
    Color3f activeColor, bgColor;
};

LEAD_REGISTER_CLASS(BinaryIntegrator, "binary")
LEAD_NAMESPACE_END