#pragma once

static void BM_Vec2_arithmetic_add(benchmark::State& state)
{
	for (auto _ : state)
	{
		Vec2 v1(1.0f, 2.0f);
		Vec2 v2(4.0f, 3.0f);
		Vec2 result = v1 + v2;
	}
}
BENCHMARK(BM_Vec2_arithmetic_add)->Iterations(g_Iterations);

static void BM_m128_arithmetic_add(benchmark::State& state)
{
	for (auto _ : state)
	{
		__m128 v1	  = _mm_set_ps(0.0f, 0.0f, 2.0f, 1.0f);
		__m128 v2	  = _mm_set_ps(0.0f, 0.0f, 4.0f, 3.0f);
		__m128 result = _mm_add_ps(v1, v2);
	}
}
BENCHMARK(BM_m128_arithmetic_add)->Iterations(g_Iterations);
