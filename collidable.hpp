#pragma once

#include "vec3.hpp"
#include "ray.hpp"

struct collision_record {
  float t;
  vec3 p;
  vec3 normal;
};

class collidable {
  public:
    virtual bool hit(const ray& r, float t_min, float t_max, collision_record& rec) const = 0;
};
