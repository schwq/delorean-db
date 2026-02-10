#include <chrono>
#include <print>
#include <ratio>
#include "deloreandb/common.hpp"
#include "deloreandb/core/types.hpp"
#include "deloreandb/impl/vector.hpp"
#include "deloreandb/mem/arena_alloc.hpp"

int main()
{

  Delorean::ArenaAllocator arena(MB(256));
  const u64 n = 1000000;
  auto a = arena.AllocType_SIMD<f32>(n, 64);
  auto b = arena.AllocType_SIMD<f32>(n, 64);
  for (u64 i = 0; i < n; i++) {
    a[i] = i * 1.0f;
    b[i] = 2.0f;
  }

  Delorean::VectorBase va{a, n, Delorean::ValueType::Float32};
  Delorean::VectorBase vb{b, n, Delorean::ValueType::Float32};
  Delorean::VectorBase vo{};

  FOR(i, 100)
  {
    Delorean::OpVectors<Delorean::AddOP>(arena, va, vb, vo);
  }

  double best = 1e9;
  FOR(iter, 1000)
  {

    auto start = std::chrono::high_resolution_clock::now();
    Delorean::OpVectors<Delorean::AddOP>(arena, va, vb, vo);
    auto end = std::chrono::high_resolution_clock::now();
    double t = std::chrono::duration<double, std::milli>(end - start).count();
    best = std::min(best, t);
  }

  std::print("Best time is {}ms", best);
  return 0;
}