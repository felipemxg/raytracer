#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Ray {
    point3 origin;
    vec3   direction;

    Ray() {}
    Ray(const point3& origin, const vec3& direction)
        : origin(origin), direction(direction)
    {}

    point3 At(double t) const {
        return origin + t * direction;
    }
};

#endif

