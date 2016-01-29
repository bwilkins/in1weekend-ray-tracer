#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"

vec3 unit_vector(const vec3 &v1) {
  return v1 / v1.length();
}

float hit_sphere(const vec3& center, float radius, const ray& r) {
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - 4*a*c;
  if (discriminant < 0) {
    return -1.0;
  }
  else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

vec3 colour(const ray &r) {
  vec3 sphere_center = vec3(0, 0, -1);
  float t = hit_sphere(sphere_center, 0.5, r);
  if (t > 0.0) {
    vec3 n = unit_vector(r.point_at_parameter(t) - sphere_center);
    return 0.5*vec3(n.x()+1, n.y()+1, n.z()+1);
  }
  vec3 unit_direction = unit_vector(r.direction());
  t = 0.5 * (unit_direction.y() + 1.0);
  return vec3(1.0, 1.0, 1.0) * (1.0-t) + vec3(0.5, 0.7, 1.0) * t;
}

int main(int argc, char** argv) {
  int image_width = 800;
  int image_height = 400;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for (int column = image_height; column >= 0; column--) {
    for (int row = 0; row < image_width; row++) {
      float u = float(row) / float(image_width);
      float v = float(column) / float(image_height);

      ray r(origin, lower_left_corner + horizontal*u + vertical*v);
      vec3 col = colour(r);

      int ir =  int(255.99*col.r());
      int ig =  int(255.99*col.g());
      int ib =  int(255.99*col.b());

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}
