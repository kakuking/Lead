#pragma once

#include <lead/scene.h>
#include <lead/common.h>
#include <lead/object.h>

#include <rapidxml/rapidxml.hpp>



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
        std::cout << scene->toString() << std::endl;

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
        for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()){
            std::string attr_name(attr->name());
            if (attr_name.compare("type") == 0)
                override_type = attr->value();
        }

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
            
            for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()){
                std::string attr_name(attr->name());
                if (attr_name.compare("name") == 0)
                    curObj->setId(attr->value());
            }

            return curObj;
        }

        // Otherwise, process a whatever and add to the propList
        std::string propKey, propValue;
        bool setKey = false, setVal = false;
        for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()){
            std::string attr_name(attr->name());
            std::string attr_val(attr->value());
            if (attr_name.compare("name") == 0){
                propKey = attr_val; 
                setKey = true;
            }
            
            if (attr_name.compare("value") == 0){
                propValue = attr_val;
                setVal = true;
            }
        }

        if(!(setKey & setVal))
            throw LeadException(tfm::format("Attribute %s does not have name/value!", node_type));

        PropertyList::PropertyType pType = PropertyList::classNameToPropertyType(node_type);
        if(pType == PropertyList::PropertyType::LUnkown)
            throw LeadException("Unknown property type found");
        
        switch (pType){
            case PropertyList::PropertyType::LFloat:
                parentPropList->setFloat(propKey, std::stof(propValue));
                break;

            case PropertyList::PropertyType::LInt:
                parentPropList->setInt(propKey, std::stoi(propValue));
                break;
            
            case PropertyList::PropertyType::LPoint:
                parentPropList->setPoint(propKey,
                    Point3f(parseCommaSeparated(propValue))
                );
                break;
            case PropertyList::PropertyType::LVector:
                parentPropList->setVector(propKey,
                    Vector3f(parseCommaSeparated(propValue))
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

            default:
                throw LeadException("Unknown property type found!");
        }

        // If it is a property, return a nullptr after it is done!
        return nullptr;
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

