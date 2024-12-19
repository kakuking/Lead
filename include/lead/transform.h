#include <lead/common.h>
#include <lead/object.h>

LEAD_NAMESPACE_BEGIN

class Transform: public LeadObject {
    Transform(const PropertyList &propList) {

    }

    virtual ObjectType getClassType() const { return ObjectType::LTransform; }

    virtual std::string toString() const {
        return tfm::format(
            "Transform[]"
        );
    }
};

// LEAD_REGISTER_CLASS(Transform, "transform")
LEAD_NAMESPACE_END