#include <stdio.h>
#include "vec3_simd.h"

int main() {
    vec3 a = vec3 { 1, 2, 3 };
    vec3 b = vec3 { 2, 3, 4 };
    vec3 v = a + b;
    printf("x = %f, y = %f, z = %f\n", v.x, v.y, v.z);
    return 0;
}
