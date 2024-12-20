#include <lead/common.h>
#include <lead/object.h>

LEAD_NAMESPACE_BEGIN

class Transform: public LeadObject {
public:
    Transform(): Transform(Eigen::Matrix4f::Identity()) {}
    Transform(const PropertyList &propList): Transform(propList.getTransform(Eigen::Matrix4f::Identity())) {}
    Transform(const Eigen::Matrix4f trans): transformation{trans} {
        bool isInvertible;
        trans.computeInverseWithCheck(inv_transformation, isInvertible);

        if(!isInvertible)
            throw LeadException("Transformation matrix cannot be non-invertible!");
    }
    Transform(const Eigen::Matrix4f trans, const Eigen::Matrix4f inv_trans): transformation{trans}, inv_transformation{inv_trans} {}

    Eigen::Matrix4f getMatrix() const {
        return transformation;
    }

    Eigen::Matrix4f getInverseMatrix() const {
        return transformation;
    }

    Transform getInverse() const {
        return Transform(inv_transformation, transformation);
    }

    const Vector3f apply(const Vector3f &o) const {
        Eigen::Matrix3f rotation_scaling = transformation.block<3, 3>(0, 0);
        Vector3f ret = rotation_scaling * o;
        return ret;
    }

    const Vector3f operator()(const Vector3f &o) const {
        Eigen::Matrix3f rotation_scaling = transformation.block<3, 3>(0, 0);
        Vector3f ret = rotation_scaling * o;
        return ret;
    }

    const Vector3f operator*(const Vector3f &o) const {
        Eigen::Matrix3f rotation_scaling = transformation.block<3, 3>(0, 0);
        Vector3f ret = rotation_scaling * o;
        return ret;
    }

    const Point3f apply(const Point3f &o) const {
        Point4f temp(o.x(), o.y(), o.z(), 1.f);

        Point4f transformed = transformation * temp;
        if(transformed.w() == 0.f)
            throw LeadException("Transformed point has 0 as fourth coordinate");
        
        return Point3f(transformed.x(), transformed.y(), transformed.z()) / transformed.w();
    }

    const Point3f operator()(const Point3f &o) const {
        Point4f temp(o.x(), o.y(), o.z(), 1.f);

        Point4f transformed = transformation * temp;
        if(transformed.w() == 0.f)
            throw LeadException("Transformed point has 0 as fourth coordinate");
        
        return Point3f(transformed.x(), transformed.y(), transformed.z()) / transformed.w();
    }

    const Point3f operator*(const Point3f &o) const {
        Point4f temp(o.x(), o.y(), o.z(), 1.f);

        Point4f transformed = transformation * temp;
        if(transformed.w() == 0.f)
            throw LeadException("Transformed point has 0 as fourth coordinate");
        
        return Point3f(transformed.x(), transformed.y(), transformed.z()) / transformed.w();
    }

    const Normal3f apply(const Normal3f &o) const {
        Eigen::Matrix3f rotation_scaling = inv_transformation.block<3, 3>(0, 0);
        Normal3f ret = rotation_scaling * o;
        return ret;
    }

    const Normal3f operator()(const Normal3f &o) const {
        Eigen::Matrix3f rotation_scaling = inv_transformation.block<3, 3>(0, 0);
        Normal3f ret = rotation_scaling * o;
        return ret;
    }

    const Normal3f operator*(const Normal3f &o) const {
        Eigen::Matrix3f rotation_scaling = inv_transformation.block<3, 3>(0, 0);
        Normal3f ret = rotation_scaling * o;
        return ret;
    }

    Transform operator*(const Transform &o) const {
        Eigen::Matrix4f newMat = transformation * o.getMatrix();

        return Transform(newMat);
    }

    void operator*=(const Transform &o) {
        transformation = transformation * o.getMatrix();
    }

    virtual ObjectType getClassType() const override { return ObjectType::LTransform; }

    virtual std::string toString() const {
        return tfm::format(
            "Transform[]"
        );
    }

protected:
    Eigen::Matrix4f transformation, inv_transformation;
};

LEAD_NAMESPACE_END