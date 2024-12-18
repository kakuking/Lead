#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/shape.h>

class Scene: public LeadObject{
public:
    Scene(const PropertyList &propList) {
        m_sampleCount = propList.getInt("samples", 32);
    }

    virtual void activate() override { }

    virtual void addChild(LeadObject *obj) override {
        LeadObject::ObjectType classType = obj->getClassType();
        std::string className = obj->objectTypeToClassName(classType);

        switch(classType){
            case LShape:
                m_shapes.push_back(static_cast<Shape *>(obj));
                break;
            
            case LCamera:
                std::cout << "Adding camera to scene\n";
                break;
            
            case LIntegrator:
                std::cout << "Adding integrator to scene!\n";
                break;
            
            default:
                std::cout << tfm::format("Class %s cannot be added to a scene!\n", className);
                break;
        }
    }

    virtual LeadObject::ObjectType getClassType() const override { return LeadObject::LScene; }

    virtual std::string toString() const override {
        std::string all_shapes = "\n";

        for(auto const& shape: m_shapes)
            all_shapes = all_shapes + shape->toString() + "\n";
        
        return tfm::format(
            "Scene: [%s]",
            indent(all_shapes)
        );
    }

protected:
    std::vector<Shape *> m_shapes;
    int m_sampleCount;
};

LEAD_REGISTER_CLASS(Scene, "scene")