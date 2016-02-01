#include <random>

std::mt19937_64 rng;
std::uniform_real_distribution<double> unif(0, 1);

void init_random() {
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss = {uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);
}

float brandom() {
  return unif(rng);
}
