#include <iostream>
#include "sphere.hpp"
#include "collidable_list.hpp"
#include "float.h"

vec3 unit_vector(const vec3 &v1) {
  return v1 / v1.length();
}

vec3 colour(const ray &r, collidable_list* world) {
  collision_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  }
  else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
  }
}

int main(int argc, char** argv) {
  int image_width = 800;
  int image_height = 400;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  collidable* list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  collidable_list listx(list, 2);

  for (int column = image_height; column >= 0; column--) {
    for (int row = 0; row < image_width; row++) {
      float u = float(row) / float(image_width);
      float v = float(column) / float(image_height);

      ray r(origin, lower_left_corner + horizontal*u + vertical*v);
      vec3 col = colour(r, &listx);

      int ir =  int(255.99*col.r());
      int ig =  int(255.99*col.g());
      int ib =  int(255.99*col.b());

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}
