#ifndef VEC4_H
#define VEC4_H

#include <float.h>
#include <math.h>
#include <assert.h>

struct vec3 {
    union {
        float x = 0, r;
    };
    union {
        float y = 0, g;
    };
    union {
        float z = 0, b;
    };

    inline vec3() = default;
    inline vec3(float f) : x(f), y(f), z(f) {}
    inline vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    inline vec3(float v[3]) : x(v[0]), y(v[1]), z(v[2]) {}
    inline vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {}

    inline vec3 operator=(float f) {
        x = f;
        y = f;
        z = f;
        return *this;
    }
    inline vec3 operator=(const vec3 v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    inline float& operator[](int i) {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }
    inline const float& operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }

    inline vec3 operator+(const vec3 v) {
        return { x + v.x, y + v.y, z + v.z };
    }
    inline vec3 operator-(const vec3 v) {
        return { x - v.x, y - v.y, z - v.z };
    }
    inline vec3 operator*(float s) {
        return { x * s, y * s, z * s };
    }
    inline vec3 operator/(float s) {
        return { x / s, y / s, z / s };
    }
    inline vec3 operator+=(const vec3 v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    inline vec3 operator-=(const vec3 v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    inline vec3 operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    inline vec3 operator/=(float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    inline float lensq() {
        return (x * x) + (y * y) + (z * z);
    }

    inline float len() {
        return sqrt(lensq());
    }

    inline vec3 normalized() {
        // little hack to avoid division by zero
        // courtesy of Chipmunk Physics
        //   https://github.com/slembcke/Chipmunk2D/blob/edf83e5603c5a0a104996bd816fca6d3facedd6a/include/chipmunk/cpVect.h
        return (*this) * ( 1.0f / (len() + FLT_MIN) );
    }
};

using point3 = vec3;
using color = vec3;


inline float dot(vec3 a, vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline vec3 cross(vec3 a, vec3 b) {
    return {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
}

#endif
