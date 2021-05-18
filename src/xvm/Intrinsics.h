#pragma once
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <immintrin.h>

#define INTRINSICS_INLINE inline

#define INTRINSICS_CALLCONV __vectorcall

#define INTRINSICS_SHUFFLE_PS(v, c) _mm_shuffle_ps(v, v, c)

// https://stackoverflow.com/questions/51641131/how-to-achieve-vector-swizzling-in-c
// https://docs.microsoft.com/en-us/cpp/cpp/m128?view=msvc-160

namespace xvm
{
	// TODO: Add swizzling to float2,float3,float4
	template<int I>
	struct scalar_swizzle
	{
		operator float() const { return fp32[I]; }
	private:
		union
		{
			__m128 vec;
			float fp32[4];
		};
	};

	struct float2
	{
		float2() : vec(_mm_setzero_ps()) { }
		float2(__m128 a) : vec(a) { }
		float2(float x, float y) : vec(_mm_set_ps(0.0f, 0.0f, y, x)) { }
		float2(float scalar) : float2(scalar, scalar) { }
		float2(float floats[2]) : float2(floats[0], floats[1]) { }

		union
		{
			__m128 vec;
			scalar_swizzle<0> x;
			scalar_swizzle<1> y;
		};
	};

	struct float3
	{
		float3() : vec(_mm_setzero_ps()) { }
		float3(__m128 a) : vec(a) { }
		float3(float x, float y, float z) : vec(_mm_set_ps(0.0f, z, y, x)) { }
		float3(float scalar) : float3(scalar, scalar, scalar) { }
		float3(float floats[3]) : float3(floats[0], floats[1], floats[2]) { }

		union
		{
			__m128 vec;
			scalar_swizzle<0> x;
			scalar_swizzle<1> y;
			scalar_swizzle<2> z;
		};
	};

	struct float4
	{
		float4() : vec(_mm_setzero_ps()) { }
		float4(__m128 a) : vec(a) { }
		float4(float x, float y, float z, float w) : vec(_mm_set_ps(w, z, y, x)) { }
		float4(float scalar) : float4(scalar, scalar, scalar, scalar) { }
		float4(float floats[4]) : float4(floats[0], floats[1], floats[2], floats[3]) { }

		union
		{
			__m128 vec;
			scalar_swizzle<0> x;
			scalar_swizzle<1> y;
			scalar_swizzle<2> z;
			scalar_swizzle<3> w;
		};
	};

	// Negate operator
	float2 INTRINSICS_CALLCONV operator-(float2 v);
	float3 INTRINSICS_CALLCONV operator-(float3 v);
	float4 INTRINSICS_CALLCONV operator-(float4 v);

	// Arithmetic operators
	float2 INTRINSICS_CALLCONV operator+(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator+(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator+(float4 v1, float4 v2);

	float2 INTRINSICS_CALLCONV operator-(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator-(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator-(float4 v1, float4 v2);

	float2 INTRINSICS_CALLCONV operator*(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator*(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator*(float4 v1, float4 v2);

	float2 INTRINSICS_CALLCONV operator/(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator/(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator/(float4 v1, float4 v2);

	// Using these function may cause code bloat on different compilers
	// because the quad-word (128-bit) fits nicely inside one SIMD register.
	// And one of the key factors of a vector library is to keep the data inside these registers as much as possible.
	// By doing that, you avoid unnecessary loads and stores operations from SIMD registers to memory or FPU registers.
	// When combining multiple vector operations the "returned by value" interface allows the compiler to optimize these loads and stores easily by minimizing SIMD to FPU or memory transfers.
	float2& INTRINSICS_CALLCONV operator+=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator+=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator+=(float4& v1, float4 v2);

	float2& INTRINSICS_CALLCONV operator-=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator-=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator-=(float4& v1, float4 v2);

	float2& INTRINSICS_CALLCONV operator*=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator*=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator*=(float4& v1, float4 v2);

	float2& INTRINSICS_CALLCONV operator/=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator/=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator/=(float4& v1, float4 v2);

	// Intrinsics
	float2 INTRINSICS_CALLCONV abs(float2 v);
	float3 INTRINSICS_CALLCONV abs(float3 v);
	float4 INTRINSICS_CALLCONV abs(float4 v);
}

namespace xvm
{
#ifndef XVM_GLOBALCONST
#define XVM_GLOBALCONST extern const __declspec(selectany)
#endif

	union FP32
	{
		uint32_t u;
		float f;
		struct
		{
			uint32_t Mantissa : 23;
			uint32_t Exponent : 8;
			uint32_t Sign : 1;
		};
	};

	extern constexpr FP32 ABS_MASK = { 0x7fffffff };
	extern constexpr FP32 NEGATIVE_MASK = { 0x80000000 };

	XVM_GLOBALCONST __m128 XVM_ABS_MASK = _mm_set1_ps(ABS_MASK.f);
	XVM_GLOBALCONST __m128 XMV_NEGATIVE_MASK = _mm_set1_ps(NEGATIVE_MASK.f);

#undef XVM_GLOBALCONST
}

#include "Intrinsics.inl"

#undef INTRINSICS_SHUFFLE_PS
#undef INTRINSICS_CALLCONV
#undef INTRINSICS_INLINE