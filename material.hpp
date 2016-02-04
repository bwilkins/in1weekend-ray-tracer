#pragma once

#include "vec3.hpp"
#include "ray.hpp"

struct collision_record; //FUCKING CIRCULAR DEPENDENCIES

class material {
public:
  virtual bool scatter(const ray& r_in, const collision_record& rec, vec3& attenuation, ray& scattered) const = 0;
};
