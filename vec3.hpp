#pragma once

#include <math.h>
#include <stdlib.h>

class vec3 {
  float e[3];

public:
  vec3() { e[0] = 0.0; e[1] = 0.0; e[2] = 0.0; };
  vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
  float x() const { return e[0]; }
  float y() const { return e[1]; }
  float z() const { return e[2]; }
  float r() const { return e[0]; }
  float g() const { return e[1]; }
  float b() const { return e[2]; }

  const vec3& operator+() const { return *this; }
  const vec3 operator+(const vec3 &v2) const { return vec3(e[0]+v2[0], e[1]+v2[1], e[2]+v2[2]); }
  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  float operator[](int i) const { return e[i]; }
  float& operator[](int i) { return e[i]; }

  const vec3 operator*(float t) const { return vec3(e[0]*t, e[1]*t, e[2]*t); }
  const vec3 operator*(const vec3 &v2) const { return vec3(e[0]*v2[0], e[1]*v2[1], e[2]*v2[2]); }
  const vec3 operator/(float t) const { return vec3(e[0]/t, e[1]/t, e[2]/t); }
  const vec3 operator/(const vec3 &v2) const { return vec3(e[0]/v2[0], e[1]/v2[1], e[2]/v2[2]); }

  vec3& operator+=(const vec3 &v2) { e[0] += v2[0]; e[1] += v2[1]; e[2] += v2[2]; return *this; };
  vec3& operator-=(const vec3 &v2) { e[0] -= v2[0]; e[1] -= v2[1]; e[2] -= v2[2]; return *this; };
  vec3& operator*=(const vec3 &v2) { e[0] *= v2[0]; e[1] *= v2[1]; e[2] *= v2[2]; return *this; };
  vec3& operator/=(const vec3 &v2) { e[0] /= v2[0]; e[1] /= v2[1]; e[2] /= v2[2]; return *this; };
  vec3& operator*=(const float t) { e[0]*=t, e[1]*=t, e[2]*=t; return *this; }
  vec3& operator/=(const float t) { e[0]/=t, e[1]/=t, e[2]/=t; return *this; }

  float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
  float squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
  void make_unit_vector();
};

float dot(const vec3& v1, const vec3& v2) {
  return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
};

const vec3 operator*(float t, const vec3 v1) { return vec3(v1[0]*t, v1[1]*t, v1[2]*t); }
const vec3 operator/(float t, const vec3 v1) { return vec3(v1[0]/t, v1[1]/t, v1[2]/t); }
