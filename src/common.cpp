#include <lead/common.h>
#include <lead/euclidean.h>

LEAD_NAMESPACE_BEGIN

std::string indent(const std::string &string, int amount) {
    /* This could probably be done faster (it's not
       really speed-critical though) */
    std::istringstream iss(string);
    std::ostringstream oss;
    std::string spacer(amount, ' ');
    bool firstLine = true;
    for (std::string line; std::getline(iss, line); ) {
        if (!firstLine)
            oss << spacer;
        oss << line;
        if (!iss.eof())
            oss << std::endl;
        firstLine = false;
    }
    return oss.str();
}

Eigen::Matrix4f createScaling(const Vector3f scale) {
    Eigen::Matrix4f t = Eigen::Matrix4f::Identity();
    t.block<3, 3>(0, 0) = Eigen::Scaling(scale.x(), scale.y(), scale.z());
    return t;
}

Eigen::Matrix4f createTranslation(const Vector3f translate) {
    Eigen::Matrix4f t = Eigen::Matrix4f::Identity();
    t(0, 3) = translate.x();
    t(1, 3) = translate.y();
    t(2, 3) = translate.z();

    return t;
}

Eigen::Matrix4f createRotation(const Vector3f axis, const float angle) {
    float ang = degrees_to_radians(angle);

    Eigen::Matrix4f t = Eigen::Matrix4f::Identity();
    t.block<3, 3>(0, 0) = Eigen::AngleAxisf(ang, axis).matrix();

    return t;
}

LEAD_NAMESPACE_END