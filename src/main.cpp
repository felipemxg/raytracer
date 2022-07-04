#include <iostream>
#include "vec3.h"
#include "ray.h"

double HitSphere(const point3 center, double radius, const Ray r) {
    vec3 oc = r.origin - center;
    auto a = dot(r.direction, r.direction);
    auto b = 2.0 * dot(oc, r.direction);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
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

void WriteColor(std::ostream &out, color px_color) {
    out << static_cast<int>(255.999 * px_color.r) << ' '
        << static_cast<int>(255.999 * px_color.g) << ' '
        << static_cast<int>(255.999 * px_color.b) << '\n';
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;

    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);


    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color px_color = RayColor(ray);
            WriteColor(std::cout, px_color);
        }
    }

    return 0;
}
