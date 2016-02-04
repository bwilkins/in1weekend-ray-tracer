#include <iostream>
#include "float.h"

#include "sphere.hpp"
#include "collidable_list.hpp"
#include "camera.hpp"
#include "random.hpp"
#include "lambertian.hpp"
#include "metal.hpp"

vec3 colour(const ray &r, collidable_list* world, int depth) {
  collision_record rec;
  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation*colour(scattered, world, depth+1);
    }
    else {
      return vec3(0, 0, 0);
    }
  }
  else {
    vec3 unit_direction = r.direction().unit();
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
  }
}

int main(int argc, char** argv) {
  int image_width   = 800;
  int image_height  = 400;
  int samples       = 10;

  init_random();

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  camera cam;

  collidable* list[4];
  list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.6, 0.3, 0.3)));
  list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
  list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1.0));
  collidable_list listx(list, 4);

  for (int column = image_height; column >= 0; column--) {
    for (int row = 0; row < image_width; row++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < samples; s++) {
        float u = float(row + brandom()) / float(image_width);
        float v = float(column + brandom()) / float(image_height);

        ray r = cam.get_ray(u, v);
        col += colour(r, &listx, 0);
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
