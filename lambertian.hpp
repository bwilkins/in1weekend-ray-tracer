#pragma once
#include "material.hpp"
#include "random.hpp"

class lambertian: public material {
  vec3 albedo;
  vec3 random_in_unit_sphere() const {
    vec3 p;
    do {
      p = 2*vec3(brandom(), brandom(), brandom()) - vec3(1, 1, 1);
    } while(dot(p,p) >= 1.0);
    return p;
  }

  public:
  lambertian(const vec3& a) : albedo(a) {}
  virtual bool scatter(const ray& r_in, const collision_record& rec, vec3& attenuation, ray& scattered) const {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
  }
};
