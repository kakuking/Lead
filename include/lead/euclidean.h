#pragma once

#include <lead/common.h>
#include <lead/leadexception.h>

LEAD_NAMESPACE_BEGIN
template <typename _Scalar, int _Dimension> struct TVector: public Eigen::Matrix<_Scalar, _Dimension, 1> {
public: 
    enum {
        Dimension = _Dimension
    };

    typedef _Scalar                             Scalar;
    typedef Eigen::Matrix<Scalar, Dimension, 1> Base;
    typedef TVector<Scalar, Dimension>          VectorType;
    typedef TPoint<Scalar, Dimension>           PointType;

    TVector(Scalar val = (Scalar) 0) { Base::setConstant(val); }

    TVector(Scalar x, Scalar y): Base(x, y) {}

    TVector(Scalar x, Scalar y, Scalar z): Base(x, y, z) {}

    TVector(Scalar x, Scalar y, Scalar z, Scalar w): Base(x, y, z, w) {}

    template <typename Derived> TVector(const Eigen::MatrixBase<Derived>& p): Base(p) {}

    template <typename Derived> TVector &operator=(const Eigen::MatrixBase<Derived>& p) {
        this->Base::operator=(p);
        return *this;
    }

    std::string toString() const {
        std::string result;

        for(size_t i = 0; i < Dimension; i++) {
            result += std::to_string(this->coeffRef(i));
            if(i+1 < Dimension)
                result += ", ";
        }

        return "[" + result + "]";
    }
};

template <typename _Scalar, int _Dimension> struct TPoint : public Eigen::Matrix<_Scalar, _Dimension, 1> {
public:
    enum {
        Dimension = _Dimension
    };

    typedef _Scalar                             Scalar;
    typedef Eigen::Matrix<Scalar, Dimension, 1> Base;
    typedef TVector<Scalar, Dimension>          VectorType;
    typedef TPoint<Scalar, Dimension>           PointType;

    TPoint(Scalar value = (Scalar) 0) { Base::setConstant(value); }

    TPoint(Scalar x, Scalar y) : Base(x, y) { }

    TPoint(Scalar x, Scalar y, Scalar z) : Base(x, y, z) { }

    TPoint(Scalar x, Scalar y, Scalar z, Scalar w) : Base(x, y, z, w) { }

    template <typename Derived> TPoint(const Eigen::MatrixBase<Derived>& p)
        : Base(p) { }

    template <typename Derived> TPoint &operator=(const Eigen::MatrixBase<Derived>& p) {
        this->Base::operator=(p);
        return *this;
    }

    std::string toString() const {
        std::string result;
        for (size_t i=0; i<Dimension; ++i) {
            result += std::to_string(this->coeff(i));
            if (i + 1 < Dimension)
                result += ", ";
        }
        return "[" + result + "]";
    }
};

struct Normal3f : public Eigen::Matrix<float, 3, 1> {
public:
    enum {
        Dimension = 3
    };

    typedef float                               Scalar;
    typedef Eigen::Matrix<Scalar, Dimension, 1> Base;
    typedef TVector<Scalar, Dimension>          VectorType;
    typedef TPoint<Scalar, Dimension>           PointType;


    Normal3f(Scalar value = 0.0f) { Base::setConstant(value); }

    Normal3f(Scalar x, Scalar y, Scalar z) : Base(x, y, z) { }

    template <typename Derived> Normal3f(const Eigen::MatrixBase<Derived>& p)
        : Base(p) { }

    template <typename Derived> Normal3f &operator=(const Eigen::MatrixBase<Derived>& p) {
        this->Base::operator=(p);
        return *this;
    }

    std::string toString() const {
        return tfm::format("[%f, %f, %f]", coeff(0), coeff(1), coeff(2));
    }
};

extern void coordinateSystem(const Vector3f &a, Vector3f &b, Vector3f &c);

class Ray3f {
public:
    Ray3f(Point3f o, Vector3f d): o{o}, d{d}, minT{EPSILON}, maxT{INFINITY} {}
    Ray3f(Point3f o, Vector3f d, float minT, float maxT): o{o}, d{d}, minT{minT}, maxT{maxT} {}
    Ray3f(const Ray3f &cp) {
        o = cp.o;
        d = cp.d;
        minT = cp.minT;
        maxT = cp.maxT;
    }

    Point3f at(float t) const {
        return o + t * d;
    }

    Point3f o;
    Vector3f d;
    float minT, maxT;

    std::string toString(){
        return tfm::format(
            "Ray["
            "  Origin: %s, "
            "  Direction: %s, "
            "  minT: %f, "
            "  maxT: %f"
            "]",
            o.toString(),
            d.toString(),
            minT, maxT
        );
    }
};

class RayDifferential: public Ray3f {
public:
    RayDifferential(Point3f o, Vector3f d, float minT, float maxT): Ray3f(o, d, minT, maxT) {}
    explicit RayDifferential(const Ray3f &r): Ray3f(r) {}

    void scaleDifferentials(float s) {
        rxOrigin = o + (rxOrigin - o) * s;
        ryOrigin = o + (ryOrigin - o) * s;
        rxDir = d + (rxDir - d) * s;
        ryDir = d + (ryDir - d) * s;
    }

    std::string toString() const {
        return tfm::format(
            "RayDifferential[\n"
            "  Origin: %s\n"
            "  Direction: %s\n"
            "  minT: %f\n"
            "  maxT: %f\n"
            "  rxOrigin: %s\n"
            "  ryOrigin: %s\n"
            "  rxDirection: %s\n"
            "  ryDirection: %s\n"
            "]",
            o.toString(),
            d.toString(),
            minT, maxT,
            rxOrigin.toString(), ryOrigin.toString(),
            rxDir.toString(), ryDir.toString()
        );
    }

    bool hasDifferetials = false;
    Point3f rxOrigin, ryOrigin;
    Vector3f rxDir, ryDir;
};

LEAD_NAMESPACE_END