#pragma once

#include "vec3.hpp"
#include "material.hpp"

class metal : public material {
  vec3 albedo;
  float fuzz;
  vec3 reflect(const vec3& v, const vec3& n) const {
    return v - 2*dot(v, n)*n;
  }
  vec3 random_in_unit_sphere() const {
    vec3 p;
    do {
      p = 2*vec3(brandom(), brandom(), brandom()) - vec3(1, 1, 1);
    } while(dot(p,p) >= 1.0);
    return p;
  }

  public:
  metal(const vec3& a, float f) : albedo(a) { if (f<1) { fuzz = f; } else {fuzz=1;}  }
  virtual bool scatter(const ray& r_in, const collision_record& rec, vec3& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.direction().unit(), rec.normal);
    scattered = ray(rec.p, reflected + fuzz* random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

};
