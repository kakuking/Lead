#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <iostream>

class Scene: public LeadObject{
public:
    Scene(const PropertyList &propList) {
        std::cout << "Printing proplist in Scene!\n";
        std::cout << propList.toString();
    }

    virtual void activate() override { }

    virtual void addChild(LeadObject *obj) override {
        LeadObject::ObjectType classType = obj->getClassType();
        std::string className = obj->objectTypeToClassName(classType);

        switch(classType){
            case LShape:
                std::cout << "Adding shape to scene!\n";
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
};

LEAD_REGISTER_CLASS(Scene, "scene")