#include <iostream>
#include "float.h"

#include "sphere.hpp"
#include "collidable_list.hpp"
#include "camera.hpp"
#include "random.hpp"

vec3 unit_vector(const vec3 &v1) {
  return v1 / v1.length();
}

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2*vec3(brandom(), brandom(), brandom()) - vec3(1, 1, 1);
  } while(dot(p,p) >= 1.0);
  return p;
}

vec3 colour(const ray &r, collidable_list* world) {
  collision_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5*colour(ray(rec.p, target - rec.p), world);
  }
  else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
  }
}

int main(int argc, char** argv) {
  int image_width   = 800;
  int image_height  = 400;
  int samples       = 10;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  camera cam;

  collidable* list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  collidable_list listx(list, 2);

  for (int column = image_height; column >= 0; column--) {
    for (int row = 0; row < image_width; row++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < samples; s++) {
        float u = float(row + unif(rng)) / float(image_width);
        float v = float(column + unif(rng)) / float(image_height);

        ray r = cam.get_ray(u, v);
        col += colour(r, &listx);
      }
      col /= float(samples);
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int ir =  int(255.99*col.r());
      int ig =  int(255.99*col.g());
      int ib =  int(255.99*col.b());

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}
