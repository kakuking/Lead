#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tinyformat.h>
#include <memory>
#include <limits>

class Scene;
class Shape;
class Sampler;

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

inline double degrees_to_radians(double degrees) {
    return degrees * M_PI/180.0;
}

#include <lead/leadexception.h>
#include <lead/proplist.h>
#include <lead/euclidean.h>

extern std::string indent(const std::string &string, int amount = 2);