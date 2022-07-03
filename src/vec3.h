#ifndef VEC4_H
#define VEC4_H

#include <float.h>
#include <math.h>
#include <assert.h>

struct vec3 {
    union {
        double x = 0, r;
    };
    union {
        double y = 0, g;
    };
    union {
        double z = 0, b;
    };

    inline vec3() = default;
    inline vec3(double f) : x(f), y(f), z(f) {}
    inline vec3(double x, double y, double z) : x(x), y(y), z(z) {}
    inline vec3(double v[3]) : x(v[0]), y(v[1]), z(v[2]) {}
    inline vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {}

    inline vec3 operator=(double f) {
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
    inline double& operator[](int i) {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }
    inline const double& operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (&x)[i];
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
    inline vec3 operator*=(double s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    inline vec3 operator/=(double s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    inline double lensq() {
        return (x * x) + (y * y) + (z * z);
    }

    inline double len() {
        return sqrt(lensq());
    }
};

inline vec3 operator+(const vec3 a, const vec3 b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}
inline vec3 operator-(const vec3 a, const vec3 b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}
inline vec3 operator*(const vec3 v, double s) {
    return { v.x * s, v.y * s, v.z * s };
}
inline vec3 operator*(double s, const vec3 v) {
    return { v.x * s, v.y * s, v.z * s };
}
inline vec3 operator/(double s, const vec3 v) {
    return (1 / s) * v;
}
inline vec3 operator/(const vec3 v, double s) {
    return (1 / s) * v;
}

inline double dot(vec3 a, vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline vec3 cross(vec3 a, vec3 b) {
    return {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
}

inline vec3 normalize(vec3 v) {
    // little hack to avoid division by zero
    // courtesy of Chipmunk Physics
    //   https://github.com/slembcke/Chipmunk2D/blob/edf83e5603c5a0a104996bd816fca6d3facedd6a/include/chipmunk/cpVect.h
    return v * ( 1.0f / (v.len() + FLT_MIN) );
}


using point3 = vec3;
using color = vec3;

#endif
