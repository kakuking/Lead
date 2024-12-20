#pragma once

#include <lead/common.h>
#include <lead/object.h>
#include <lead/proplist.h>
#include <lead/euclidean.h>


LEAD_NAMESPACE_BEGIN
class Camera: public LeadObject {
public:
    Camera(const PropertyList &propList) {
        Point3f tempSize = propList.getPoint("size", Point3f(800, 600, 0));
        m_outputSize = Point2f(tempSize.x(), tempSize.y());

        m_FOV = propList.getFloat("FOV", 20.f);
        m_focalLength = propList.getFloat("focalLength", 10.f);

        m_eye = propList.getPoint("eye", Point3f(0.f, 0.f, -2.f));
        m_lookat = propList.getPoint("lookat", Point3f(0.f, 0.f, 0.f));
        m_up = propList.getVector("up", Vector3f(0.f, 1.f, 0.f));

        w = (m_eye - m_lookat).normalized();
        u = m_up.cross(w).normalized();
        v = u.cross(w).normalized();

        float theta = degrees_to_radians(m_FOV);
        float h = std::tan(theta/2);
        float viewport_height = 2 * h * m_focalLength;
        float viewport_width = viewport_height * m_outputSize.x() / m_outputSize.y();

        Vector3f viewport_u = viewport_width * u;
        Vector3f viewport_v = viewport_height * v;
        m_pixeldelta_u = viewport_u / m_outputSize.x();
        m_pixeldelta_v = viewport_v / m_outputSize.y();

        Point3f viewport_upper_left = m_eye - w * m_focalLength - 0.5f * viewport_u - 0.5f * viewport_v;
        m_loc_00 = viewport_upper_left + 0.5 * (m_pixeldelta_u + m_pixeldelta_v);
    }

    // Sampled position is int of pixel indecis, x and y
    virtual Ray3f sampleRay(const Point2f sampledPosition, const Point2f sample) const = 0;

    virtual LeadObject::ObjectType getClassType() const override { return LeadObject::LCamera; }

    virtual void activate() override {}

    virtual std::string toString() const {
        return tfm::format(
            "Camera: [\n"
            "  Eye: %s\n"
            "  LookAt: %s\n"
            "  Up: %s\n"
            "  FOV: %f\n"
            "  Focal Length: %f\n"
            "]",
            m_eye.toString(),
            m_lookat.toString(),
            m_up.toString(),
            m_FOV,
            m_focalLength
        );
    }

    Point2f getOutputSize() const { return m_outputSize; }

protected:
    Point2f m_outputSize;
    Vector3f m_pixeldelta_u, m_pixeldelta_v;
    Point3f m_loc_00;

    float m_FOV;
    float m_focalLength;

    Point3f m_eye, m_lookat;
    Vector3f m_up;

    Vector3f u, v, w;
};
LEAD_NAMESPACE_END