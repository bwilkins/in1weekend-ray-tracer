#include <random>
#include <iostream>
#include "float.h"

#include "sphere.hpp"
#include "collidable_list.hpp"
#include "camera.hpp"

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
  int image_width = 1600;
  int image_height = 800;

  std::mt19937_64 rng;
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss = {uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);
  std::uniform_real_distribution<double> unif(0, 1);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  camera cam;

  collidable* list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  collidable_list listx(list, 2);

  for (int column = image_height; column >= 0; column--) {
    for (int row = 0; row < image_width; row++) {
      float u = float(row + unif(rng)) / float(image_width);
      float v = float(column + unif(rng)) / float(image_height);

      ray r = cam.get_ray(u, v);
      vec3 col = colour(r, &listx);

      int ir =  int(255.99*col.r());
      int ig =  int(255.99*col.g());
      int ib =  int(255.99*col.b());

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}
