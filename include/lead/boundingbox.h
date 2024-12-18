#pragma once

#include <lead/common.h>
#include <lead/shape.h>

#include <algorithm>

class BoundingBox {
public:
    BoundingBox() { lowerLeft = Point3f(INFINITY); upperRight = Point3f(NEG_INFINITY); }
    BoundingBox(Point3f ll, Point3f ur): lowerLeft{ll}, upperRight{ur} {}

    void expandBy(const Point3f newPt) {
        if(lowerLeft.x > newPt.x) lowerLeft.x = newPt.x;
        if(lowerLeft.y > newPt.y) lowerLeft.y = newPt.y;
        if(lowerLeft.z > newPt.z) lowerLeft.z = newPt.z;

        if(upperRight.x < newPt.x) upperRight.x = newPt.x;
        if(upperRight.y < newPt.y) upperRight.y = newPt.y;
        if(upperRight.z < newPt.z) upperRight.z = newPt.z;
    }

    bool rayIntersect(const Ray3f &ray) const {
        if (ray.o >= lowerLeft && ray.o <= upperRight)
            return true;

        float tmin = ray.minT;
        float tmax = ray.maxT;

        for (int axis = 0; axis < 3; axis++) {
            if (ray.d[axis] == 0) {
                if (ray.o[axis] < lowerLeft[axis] || ray.o[axis] > upperRight[axis])
                    return false;
            } else {
                float t1 = (lowerLeft[axis] - ray.o[axis]) / ray.d[axis];
                float t2 = (upperRight[axis] - ray.o[axis]) / ray.d[axis];

                if (t1 > t2) {
                    std::swap(t1, t2);
                }

                tmin = std::max(tmin, t1);
                tmax = std::min(tmax, t2);

                if (tmin > tmax) {
                    return false;
                }
            }
        }

        return true;
    }

    bool rayIntersectPlane(const Ray3f &ray, Point3f o, Vector3f n, float t) const {
        float dn = n.dot(ray.d);
        Vector3f delta = o - ray.o;
        float deltan = n.dot(delta);

        if(dn == 0.f){
            if(deltan == 0.f) {
                t = 0.f;
                return true;
            }
            return false;
        }

        t = deltan / dn;
        return true;
    }

    bool rayIntersectBoundedPlane(const Ray3f &ray, Point3f o, Vector3f n, float t) const {
        // If no intersection with plane return false
        if(!rayIntersectPlane(ray, o, n, t))
            return false;
        
        Point3f point = ray.at(t);

        if(point <= upperRight && point >= lowerLeft)
            return true;
        
        return false;
    }


protected:
    Point3f lowerLeft, upperRight;
};