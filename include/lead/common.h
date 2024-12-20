#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tinyformat.h>
#include <memory>
#include <limits>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <ImathPlatform.h>

#define LEAD_NAMESPACE_BEGIN namespace Lead {
#define LEAD_NAMESPACE_END }

#undef INFINITY
#define INFINITY std::numeric_limits<float>::max()
#define NEG_INFINITY std::numeric_limits<float>::min()
#define EPSILON 1e-4

#undef M_PI
#define M_PI         3.14159265358979323846f
#define INV_PI       0.31830988618379067154f
#define INV_TWOPI    0.15915494309189533577f
#define INV_FOURPI   0.07957747154594766788f
#define SQRT_TWO     1.41421356237309504880f
#define INV_SQRT_TWO 0.70710678118654752440f

LEAD_NAMESPACE_BEGIN

template <typename Scalar, int Dimension>  struct TVector;
template <typename Scalar, int Dimension>  struct TPoint;
template <typename Point, typename Vector> struct TRay;
template <typename Point>                  struct TBoundingBox;

typedef TVector<float, 1>       Vector1f;
typedef TVector<float, 2>       Vector2f;
typedef TVector<float, 3>       Vector3f;
typedef TVector<float, 4>       Vector4f;
typedef TVector<double, 1>      Vector1d;
typedef TVector<double, 2>      Vector2d;
typedef TVector<double, 3>      Vector3d;
typedef TVector<double, 4>      Vector4d;
typedef TVector<int, 1>         Vector1i;
typedef TVector<int, 2>         Vector2i;
typedef TVector<int, 3>         Vector3i;
typedef TVector<int, 4>         Vector4i;
typedef TPoint<float, 1>        Point1f;
typedef TPoint<float, 2>        Point2f;
typedef TPoint<float, 3>        Point3f;
typedef TPoint<float, 4>        Point4f;
typedef TPoint<double, 1>       Point1d;
typedef TPoint<double, 2>       Point2d;
typedef TPoint<double, 3>       Point3d;
typedef TPoint<double, 4>       Point4d;
typedef TPoint<int, 1>          Point1i;
typedef TPoint<int, 2>          Point2i;
typedef TPoint<int, 3>          Point3i;
typedef TPoint<int, 4>          Point4i;

class Scene;
class Shape;
class Sampler;

inline double degrees_to_radians(double degrees) {
    return degrees * M_PI/180.0;
}

extern std::string indent(const std::string &string, int amount = 2);

extern Eigen::Matrix4f createScaling(const Vector3f scale);

extern Eigen::Matrix4f createTranslation(const Vector3f translate);

extern Eigen::Matrix4f createRotation(const Vector3f axis, const float angle);

LEAD_NAMESPACE_END