#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/shape.h>
#include <lead/integrator.h>
#include <lead/camera.h>
#include <lead/sampler.h>

LEAD_NAMESPACE_BEGIN

class Scene: public LeadObject{
public:
    Scene(const PropertyList &propList) { }

    virtual void activate() override { }

    bool rayIntersect(const Ray3f &ray) const {
        for(const Shape* shape: m_shapes) {
            float t, u, v;
            if(shape->rayIntersect(ray, t, u, v))
                return true;
        }

        return false;
    }

    virtual void addChild(LeadObject *obj) override {
        LeadObject::ObjectType classType = obj->getClassType();
        std::string className = obj->objectTypeToClassName(classType);

        switch(classType){
            case LShape:
                m_shapes.push_back(static_cast<Shape *>(obj));
                break;
            
            case LCamera:
                m_camera = static_cast<Camera *>(obj);
                break;
            
            case LIntegrator:
                m_integrator = static_cast<Integrator *>(obj);
                break;
            
            case LSampler:
                m_sampler = static_cast<Sampler *>(obj);
                break;

            default:
                std::cout << tfm::format("Class %s cannot be added to a scene!\n", className);
                break;
        }
    }

    virtual LeadObject::ObjectType getClassType() const override { return LeadObject::LScene; }

    virtual std::string toString() const override {
        std::string all_shapes = "";

        for(auto const& shape: m_shapes)
            all_shapes = all_shapes + shape->toString() + "\n";
        
        return tfm::format(
            "Scene: [\n"
            "  %s\n"
            "  Integrator: %s\n"
            "  Sampler: %s\n"
            "  %s"
            "]"
            ,
            m_camera ? indent(m_camera->toString()): std::string("null"),
            m_integrator ? indent(m_integrator->toString()): std::string("null"),
            m_sampler ? indent(m_sampler->toString()): std::string("null"),
            indent(all_shapes)
        );
    }

    const Integrator* getIntegrator() const { return m_integrator; }

    const Camera* getCamera() const { return m_camera; }

    Sampler* getSampler() const { return m_sampler; }

protected:
    std::vector<Shape *> m_shapes;
    Integrator *m_integrator;
    Camera *m_camera;
    Sampler *m_sampler;
};

LEAD_NAMESPACE_END