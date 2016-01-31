#pragma once

#include "collidable.hpp"

class collidable_list: public collidable {
  collidable** list;
  int list_size;
public:
  collidable_list() {};
  collidable_list(collidable** l, int n) { list = l; list_size = n; };
  virtual bool hit(const ray& r, float t_min, float t_max, collision_record& rec) const;
};

bool collidable_list::hit(const ray& r, float t_min, float t_max, collision_record& rec) const {
  collision_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  for (int i = 0; i < list_size; i++) {
    if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}
