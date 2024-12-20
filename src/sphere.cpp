#include <lead/common.h>
#include <lead/euclidean.h>
#include <lead/shape.h>

LEAD_NAMESPACE_BEGIN

class Sphere: public Shape {
public:
    Sphere(const PropertyList &propList) {
        m_radius = propList.getFloat("radius", 1.f);
        m_center = propList.getPoint("center", Point3f(0.f));

        Point3f bbox_max = m_center + Point3f(m_radius);
        Point3f bbox_min = m_center - Point3f(m_radius);

        m_bbox.expandBy(m_transform.apply(bbox_max));
        m_bbox.expandBy(m_transform.apply(bbox_min));
    }

    bool rayIntersect(const Ray3f &ray, float &t, float &u, float &v) const override {
        Point3f newOrigin = m_invTransform * ray.o;
        Vector3f newDir = m_invTransform * ray.d;

        Ray3f cur_ray(newOrigin, newDir, ray.minT, ray.maxT);

        // Solution of the equation d2t2 + 2*t*d*(o-c) + c2 + o2 -2*o*c - r2 = 0;
        float dSqr = cur_ray.d.dot(cur_ray.d);
        float oSqr = cur_ray.o.dot(cur_ray.o);
        float cSqr = m_center.dot(m_center);
        float oc = m_center.dot(cur_ray.o);
        float r2 = m_radius*m_radius;
        Vector3f oMinusC = (cur_ray.o - m_center);
        float dDotOMinusC = cur_ray.d.dot(oMinusC);

        float a = dSqr;
        float b = 2*dDotOMinusC;
        float c = cSqr + oSqr - 2*oc - r2;  // Different from c in cSqr

        float determinant = b*b - 4*a*c;

        // No roots
        if(determinant < 0)
            return false;

        float rootDet = sqrtf(determinant);

        float lessT = 0.5*(-b - rootDet)/a;
        float moreT = 0.5*(-b + rootDet)/a;

        // case where intersection is outside acceptable range of t
        if(lessT > cur_ray.maxT || moreT < cur_ray.minT)
            return false;

        bool flag = false;
        // if moreT is in range
        if(moreT >= cur_ray.minT && moreT <= cur_ray.maxT){
            t = moreT;
            flag = true;
        }

        // If lessT is in range, it is the closer root so we set t to it
        if(lessT >= cur_ray.minT && lessT <= cur_ray.maxT){
            t = lessT;
            flag = true;
        }

        if(!flag)
            return false;
        
        // Convert point to spherical coordinates to find u, v
        Point3f p = cur_ray.o + t * cur_ray.d;
        p = p - m_center;

        // Corner case of 0, 0
        if(p.x() == 0 && p.y() == 0){
            u = 0;
            v = 0;

            return true;
        }

        calculateUV(u, v, p);

        return true;
    }

    void calculateUV(float &u, float &v, Point3f p) const {
        float theta = atan2f(p.x(), p.y());
        float length = sqrt(p.dot(p));
        float psi = acosf(p.z()/length);

        // Shift Theta
        theta = theta + M_PI;

        u = theta/(2*M_PI);
        u = u + 0.25 > 1 ? u - 0.75 : u + 0.25;
        u = 1 - u;

        v = psi/(M_PI);
    }

    void setHitInformation(const Ray3f &ray, Interaction &its) const override {
        float t, u, v;

        rayIntersect(ray, t, u, v);

        its.p = ray.at(t);

        Normal3f n((m_invTransform * its.p - m_center).normalized());
        Frame localFrame(n);
        n = m_invTransform * n;
        
        its.n = n;
        its.t = t;
        its.uv = Point2f(0, 0);
        its.geoFrame = localFrame;
        its.shFrame = localFrame;
    }

    std::string toString() const override {
        return tfm::format(
            "Sphere: [\n"
            "   center: %s\n"
            "   radius: %f\n"
            "]",
            m_center.toString(),
            m_radius
        );
    }

protected:
    float m_radius;
    Point3f m_center;
};

LEAD_REGISTER_CLASS(Sphere, "sphere")
LEAD_NAMESPACE_END