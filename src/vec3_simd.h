#ifndef VEC4_H
#define VEC4_H

#include <float.h>
#include <math.h>
#include <assert.h>
#include <immintrin.h>

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
        double res[4];
        __m256d r = _mm256_set_pd(0, z, y, x);
        __m256d out = _mm256_mul_pd(r, r);
        _mm256_storeu_pd(res, out);
        return res[0] + res[1] + res[2];
    }

    inline double len() {
        return sqrt(lensq());
    }
};

inline vec3 operator+(const vec3 a, const vec3 b) {
    double res[4];
    __m256d r1 = _mm256_set_pd(0, a.z, a.y, a.x);
    __m256d r2 = _mm256_set_pd(0, b.z, b.y, b.x);
    __m256d out = _mm256_add_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
}
inline vec3 operator-(const vec3 a, const vec3 b) {
    double res[4];
    __m256d r1 = _mm256_set_pd(0, a.z, a.y, a.x);
    __m256d r2 = _mm256_set_pd(0, b.z, b.y, b.x);
    __m256d out = _mm256_sub_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
}
inline vec3 operator*(const vec3 v, double s) {
    double res[4];
    __m256d r1 = _mm256_set1_pd(s);
    __m256d r2 = _mm256_set_pd(0, v.z, v.y, v.x);
    __m256d out = _mm256_mul_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
}
inline vec3 operator*(double s, const vec3 v) {
    double res[4];
    __m256d r1 = _mm256_set1_pd(s);
    __m256d r2 = _mm256_set_pd(0, v.z, v.y, v.x);
    __m256d out = _mm256_mul_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
}
inline vec3 operator/(double s, const vec3 v) {
    double res[4];
    s = 1 / s;
    __m256d r1 = _mm256_set1_pd(s);
    __m256d r2 = _mm256_set_pd(0, v.z, v.y, v.x);
    __m256d out = _mm256_mul_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
}
inline vec3 operator/(const vec3 v, double s) {
    double res[4];
    s = 1.0f / s;
    __m256d r1 = _mm256_set1_pd(s);
    __m256d r2 = _mm256_set_pd(0, v.z, v.y, v.x);
    __m256d out = _mm256_mul_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
}

inline double dot(vec3 a, vec3 b) {
    double res[4];
    __m256d r1 = _mm256_set_pd(0, a.z, a.y, a.x);
    __m256d r2 = _mm256_set_pd(0, b.z, b.y, b.x);
    __m256d out = _mm256_mul_pd(r1, r2);
    _mm256_storeu_pd(res, out);
    return res[0] + res[1] + res[2];
}

inline vec3 cross(vec3 a, vec3 b) {
    double res[4];
    __m256d r1 = _mm256_set_pd(0, a.y, a.z, a.x);
    __m256d r2 = _mm256_set_pd(0, b.z, b.x, b.y);
    __m256d r3 = _mm256_set_pd(0, a.z, a.x, a.y);
    __m256d r4 = _mm256_set_pd(0, b.y, b.z, b.x);
    __m256d out = _mm256_sub_pd(_mm256_mul_pd(r1, r2), _mm256_mul_pd(r3, r4));
    _mm256_storeu_pd(res, out);
    return { res[0], res[1], res[2] };
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
