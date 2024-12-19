#pragma once

#include <lead/common.h>
#include <lead/proplist.h>
#include <lead/leadexception.h>

#include <functional>

LEAD_NAMESPACE_BEGIN
class LeadObject {
public:
    enum ObjectType {
        LScene = 0,     // Added Scene class
        LShape,         // Added Shape Class
        LCamera,        // Added Camera Class
        LIntegrator,    // Added Integrator Class
        LSampler,       // Added Sampler Class
        LTransform,     // Added Transform Class
        LTexture,       
        LUnknown
    };

    static std::string objectTypeToClassName(ObjectType value) {
        switch (value){
            case ObjectType::LScene: return "scene";
            case ObjectType::LShape: return "shape";
            case ObjectType::LCamera: return "camera";
            case ObjectType::LIntegrator: return "integrator";
            case ObjectType::LSampler: return "sampler";
            default: return "Unknown ObjectType";
        }
        return "Unknown ObjectType";
    }

    static ObjectType classNameToObjectType(std::string inp) {
        if(inp.compare("scene") == 0) return ObjectType::LScene;
        else if(inp.compare("shape") == 0) return ObjectType::LShape;
        else if(inp.compare("camera") == 0) return ObjectType::LCamera;
        else if(inp.compare("integrator") == 0) return ObjectType::LIntegrator;
        else if(inp.compare("sampler") == 0) return ObjectType::LSampler;

        return ObjectType::LUnknown;
    }

    virtual ~LeadObject() = default;

    virtual void activate() {};

    virtual ObjectType getClassType() const = 0;

    virtual std::string toString() const = 0;

    virtual void addChild(LeadObject *obj) {}

    virtual void setId(std::string newId) { m_id = newId; }
    virtual std::string getId() { return m_id; }


protected:
    std::string m_id;
    PropertyList m_propList;
};

class LeadObjectFactory {
public:
    typedef std::function<LeadObject *(const PropertyList &)> Constructor;

    static void registerClass(const std::string &name, const Constructor &constructor);

    static LeadObject *createInstance(const std::string &name, const PropertyList &propList) {
        if(!m_constructors || m_constructors->find(name) == m_constructors->end())
            throw LeadException(tfm::format("A constructor for the '%s' class could not be found!", name));
        
        return (*m_constructors)[name](propList);
    }

    static void printRegisteredClasses(){
        if(m_constructors)
            for(const auto& v: *m_constructors)
                std::cout << v.first << std::endl;
    }

private:
    static std::map<std::string, Constructor> *m_constructors;
};

#define LEAD_REGISTER_CLASS(cls, name) \
    cls *cls ##_create(const PropertyList &list) { \
        return new cls(list); \
    } \
    static struct cls ##_{ \
        cls ##_() { \
            LeadObjectFactory::registerClass(name, cls ##_create); \
        } \
    } cls ##__LEAD_;

#define LEAD_REGISTER_TEMPLATED_CLASS(cls, T, name) \
    cls<T> * cls ##_## T ##_create(const PropertyList &list) { \
        return new cls<T>(list); \
    } \
    static struct cls ##_## T ##_{ \
        cls ##_## T ##_() { \
            LeadObjectFactory::registerClass(name, cls ##_## T ##_create); \
        } \
    } cls ## T ##__LEAD_;

LEAD_NAMESPACE_END