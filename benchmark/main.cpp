#include <benchmark/benchmark.h>
// Alternatively, can add libraries using linker options.
#ifdef _WIN32
#pragma comment ( lib, "Shlwapi.lib" )
#endif

#include <xvm/Intrinsics.h>
using namespace xvm;

#include <limits>
#include <numbers>

static constexpr float g_FloatEpsilon = 1e-2f;

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Quaternion.h"
#include "Matrix4x4.h"

static void BM_StringCreation(benchmark::State& state)
{
	for (auto _ : state)
		std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state)
{
	std::string x = "hello";
	for (auto _ : state)
		std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
