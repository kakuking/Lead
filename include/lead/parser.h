#pragma once

#include <lead/common.h>
#include <lead/scene.h>
#include <lead/object.h>
#include <lead/leadexception.h>

#include <rapidxml/rapidxml.hpp>

LEAD_NAMESPACE_BEGIN

class Parser{
public:
    Parser() {}

    Scene* parseFile(std::string filename) {
        if(filename.empty())
            throw LeadException("No file provided to parser!");
        
        // Load XML file
        std::ifstream file(filename);
        std::stringstream buf;
        buf << file.rdbuf();
        std::string xml_string = buf.str();

        rapidxml::xml_document<> doc;
        doc.parse<0>(&xml_string[0]);

        rapidxml::xml_node<> *root_node = doc.first_node();

        if(!root_node)
            throw LeadException("No root node found in file!");
        
        LeadObject* obj = traverseNode(root_node, nullptr);

        Scene *scene = (Scene *)(obj);

        std::cout << "Finished parsing\n";

        return scene;
    }
    
    // Returns the LeadObject for a scene
    LeadObject* traverseNode(rapidxml::xml_node<> *node, PropertyList *parentPropList) {
        if(node->type() != rapidxml::node_element)
            return nullptr;
        
        std::string node_type(node->name());    // <scene/> --> scene

        // Override type is set if there is a type attribute, in that case the constructor for the value of that attribute is called
        // <scene/> ---------> scene
        // <shape type="sphere"/> ------> sphere
        std::string override_type = node_type;
        getAttr(node, "type", override_type);


        // If it is a LeadObject
        LeadObject::ObjectType leadObjType = LeadObject::classNameToObjectType(node_type);

        if(leadObjType != LeadObject::LUnknown){
            PropertyList curPropList;
            std::vector<LeadObject *> childObjects;

            // Go through each child, if it is a child object it is appended to the vector, otherwise it is added to the current properties
            for(rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling()){
                LeadObject* childObject = traverseNode(child, &curPropList);
                if(childObject != nullptr)
                    childObjects.push_back(childObject);
            }

            LeadObject* curObj = LeadObjectFactory::createInstance(override_type, curPropList);

            for(LeadObject* childObject: childObjects)
                curObj->addChild(childObject);

            std::string objName;
            if(getAttr(node, "name", objName))
                curObj->setId(objName);

            return curObj;
        }

        // Otherwise, process a whatever and add to the propList
        bool isPropertyTransform = node_type.compare("scale") == 0 ||  node_type.compare("rotate") == 0 || node_type.compare("translate") == 0;

        std::string propKey, propValue;
        bool setKey = false, setVal = false;

        setKey = getAttr(node, "name", propKey);
        setVal = getAttr(node, "value", propValue);

        if(!isPropertyTransform && !(setKey & setVal))
            throw LeadException(tfm::format("Attribute %s does not have name/value!", node_type));

        PropertyList::PropertyType pType = PropertyList::classNameToPropertyType(node_type);
        if(pType == PropertyList::PropertyType::LUnkown)
            throw LeadException("Unknown property type found");

        std::string angle, axis;    // For rotation
        switch (pType){
            case PropertyList::PropertyType::LFloat:
                parentPropList->setFloat(propKey, std::stof(propValue));
                break;

            case PropertyList::PropertyType::LInt:
                parentPropList->setInt(propKey, std::stoi(propValue));
                break;
            
            case PropertyList::PropertyType::LPoint:
                parentPropList->setPoint(propKey,
                    toPoint3f(parseCommaSeparated(propValue))
                );
                break;
            case PropertyList::PropertyType::LVector:
                parentPropList->setVector(propKey,
                    toVector3f(parseCommaSeparated(propValue))
                );
                break;
            case PropertyList::PropertyType::LColor:
                parentPropList->setColor(propKey,
                    Color3f(parseCommaSeparated(propValue))
                );
                break;
            case PropertyList::PropertyType::LString:
                parentPropList->setString(propKey, propValue);
                break;
            case PropertyList::PropertyType::LScale:
                parentPropList->setScale(
                    toVector3f(parseCommaSeparated(propValue))
                );
                break;
            case PropertyList::PropertyType::LTranslate:
                parentPropList->setTranslate(
                    toVector3f(parseCommaSeparated(propValue))
                );
                break;
            case PropertyList::PropertyType::LRotate:
                getAttr(node, "angle", angle);
                getAttr(node, "axis", axis);
                parentPropList->setRotate(std::stof(angle),
                    toVector3f(parseCommaSeparated(axis))
                );
                break;

            default:
                throw LeadException("Unknown property type found!");
        }

        // If it is a property, return a nullptr after it is done!
        return nullptr;
    }

    bool getAttr(const rapidxml::xml_node<> *node, std::string attrName, std::string &attrVal) const {
        for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()){
            std::string attr_name(attr->name());
            std::string attr_val(attr->value());

            if (attr_name.compare(attrName) == 0){
                attrVal = attr_val; 
                return true;
            }
        }

        return false;
    }

    Vector3f toVector3f(std::vector<std::string> values) const {
        if(values.size() < 1)
            throw LeadException("Too few values provided for vector!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for vector!");
        
        float x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        float y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
        float z = values.size() > 2 ? std::stof(values[2]) : 0.0f;

        return Vector3f(x, y, z);
    }

    Point3f toPoint3f(std::vector<std::string> values) const {
        if(values.size() < 1)
            throw LeadException("Too few values provided for vector!");

        if(values.size() > 3)
            throw LeadException("Too many values provided for vector!");
        
        float x = values.size() > 0 ? std::stof(values[0]) : 0.0f;
        float y = values.size() > 1 ? std::stof(values[1]) : 0.0f;
        float z = values.size() > 2 ? std::stof(values[2]) : 0.0f;

        return Point3f(x, y, z);
    }

    std::vector<std::string> parseCommaSeparated(std::string value) const {
        std::vector<std::string> v;
        std::stringstream ss(value);
    
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            v.push_back(substr);
        }

        return v;
    }
};


LEAD_NAMESPACE_END