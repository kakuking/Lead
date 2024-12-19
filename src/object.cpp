#include <lead/object.h>
#include <lead/color.h>

LEAD_NAMESPACE_BEGIN

std::map<std::string, LeadObjectFactory::Constructor> *LeadObjectFactory::m_constructors = nullptr;

void LeadObjectFactory::registerClass(const std::string &name, const Constructor &constructor){
    if(!m_constructors)
        m_constructors = new std::map<std::string, Constructor>();
    
    (*m_constructors)[name] = constructor;
}

LEAD_NAMESPACE_END