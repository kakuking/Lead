#include <lead/common.h>
#include <lead/integrator.h>

class directIntegrator: public Integrator {
public:
    virtual Color3f Li(const Scene* scene, Sampler *sampler, const Ray3f &ray) const {
        
    }
};