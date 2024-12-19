#include <lead/common.h>
#include <lead/euclidean.h>

LEAD_NAMESPACE_BEGIN

class Frame {
public:
    Frame() {}
    Frame(Normal3f n, Vector3f t, Vector3f s): n{n}, t{t}, s{s} { }
    Frame(const Frame &f): n{f.n}, t{f.t}, s{f.s} { }
    Frame(Normal3f normal) {
        float sign = normal.z() < 0.f ? -1 : 1;

        float a = -1 / (sign + normal.z());
        float b = normal.x() * normal.y() * a;

        s = Vector3f(1 + sign * std::sqrt(normal.x()) * a, sign * b, -sign * normal.x());
        t = Vector3f(b, sign + std::sqrt(normal.y()) * a, -normal.y()); 
    }

    Vector3f toLocal(const Vector3f &o) const {
        return Vector3f(o.dot(s), o.dot(t), o.dot(n));
    }

    Vector3f toWorld(const Vector3f &o) const {
        return o.x() * s + o.y() * t + o.z() * n;
    }
            
    Vector3f s, t, n;   // x, y, z
};

LEAD_NAMESPACE_END