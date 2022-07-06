#include <iostream>

#ifdef WITH_AVX
  #include "vec3_simd.h"
#else
  #include "vec3.h"
#endif

#include "ray.h"


const auto aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);

double HitSphere(const point3 center, double radius, const Ray r) {
    vec3 oc = r.origin - center;
    auto a = r.direction.lensq();
    auto half_b = dot(oc, r.direction);
    auto c = oc.lensq() - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color RayColor(const Ray r) {
    auto t =  HitSphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = normalize(r.At(t) - vec3(0, 0, -1));
        return 0.5 * color(N + 1);
    }

    vec3 unit_direction = normalize(r.direction);
    t = 0.5 * ((unit_direction.y) + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void WriteColor(SDL_Surface *surface, color px_color, int x, int y) {
    uint32_t * dest_pixel = (uint32_t*) ((uint8_t *) surface->pixels
        + y * surface->pitch
        + x * surface->format->BytesPerPixel);
    uint32_t pixel = SDL_MapRGB(
        surface->format,
        static_cast<int>(255.999 * px_color.r),
        static_cast<int>(255.999 * px_color.g),
        static_cast<int>(255.999 * px_color.b));
    *dest_pixel = pixel;
}

int RaytracerRun(SDL_Surface *renderbuffer) {
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color px_color = RayColor(ray);
            WriteColor(renderbuffer, px_color, i, (image_height - 1 - j));
        }
    }

    return 0;
}
