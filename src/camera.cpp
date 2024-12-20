#include <lead/common.h>
#include <lead/camera.h>
#include <lead/euclidean.h>

LEAD_NAMESPACE_BEGIN

/*// The sample creates anti-aliasing
        Point3f on_plane = m_loc_00 + m_pixeldelta_u * (sampledPosition.x() + sample.x() - 0.5f) + m_pixeldelta_v * (sampledPosition.y()  + sample.y() - 0.5f);

        Vector3f dir = (on_plane - m_eye).normalized();
        Ray3f ret(m_eye, dir);

        return ret;*/

class PerspectiveCamera: public Camera {
public:
    PerspectiveCamera(const PropertyList &propList): Camera(propList) {}

    Ray3f sampleRay(const Point2f sampledPosition, const Point2f sample) const {
        Point3f on_plane = m_loc_00 + m_pixeldelta_u * (sampledPosition.x() + sample.x() - 0.5f) + m_pixeldelta_v * (sampledPosition.y()  + sample.y() - 0.5f);

        Vector3f dir = (on_plane - m_eye).normalized();
        Ray3f ret(m_eye, dir);

        return ret;
    }
};

class OrthogonalCamera: public Camera {
public:
    OrthogonalCamera(const PropertyList &propList): Camera(propList) {}

    Ray3f sampleRay(const Point2f sampledPosition, const Point2f sample) const {
        Point3f on_plane = m_loc_00 + m_pixeldelta_u * (sampledPosition.x() + sample.x() - 0.5f) + m_pixeldelta_v * (sampledPosition.y()  + sample.y() - 0.5f);

        Vector3f dir = (m_lookat - m_eye).normalized();
        Point3f origin = on_plane + w * m_focalLength;
        Ray3f ret(origin, dir);

        // std::cout << tfm::format("Emitted ray: %s\n", ret.toString());

        return ret;
    }
};

LEAD_REGISTER_CLASS(PerspectiveCamera, "perspective")
LEAD_REGISTER_CLASS(OrthogonalCamera, "orthogonal")
LEAD_NAMESPACE_END
