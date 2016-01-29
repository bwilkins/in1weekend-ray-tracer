#include <iostream>
#include "vec3.hpp"

int main(int argc, char** argv) {
  int image_width = 800;
  int image_height = 600;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for(int column = 1; column <= image_height; column++) {
    for (int row = 0; row < image_width; row++) {
      vec3 colour(float(row) / float(image_width), float(image_height - column) / float(image_height), 0.2f);
      int ir = int(255.99*colour.r());
      int ig = int(255.99*colour.g());
      int ib = int(255.99*colour.b());

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}
