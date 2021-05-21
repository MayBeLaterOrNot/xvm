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

	float3 INTRINSICS_CALLCONV cross(float3 v1, float3 v2);

	// Dot product, (also known as scalar product) of 2 vectors u and v is defined as the sum of
	// the product of their corresponding vector components, value of dot product is splatted across the sse registers
	float2 INTRINSICS_CALLCONV dot(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV dot(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV dot(float4 v1, float4 v2);

	bool INTRINSICS_CALLCONV isnan(float2 v);
	bool INTRINSICS_CALLCONV isnan(float3 v);
	bool INTRINSICS_CALLCONV isnan(float4 v);

	// Sqrt of sum of each component squared, value of length is splatted across the sse registers
	float2 INTRINSICS_CALLCONV length(float2 v);
	float3 INTRINSICS_CALLCONV length(float3 v);
	float4 INTRINSICS_CALLCONV length(float4 v);

	float2 INTRINSICS_CALLCONV max(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV max(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV max(float4 v1, float4 v2);

	float2 INTRINSICS_CALLCONV min(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV min(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV min(float4 v1, float4 v2);

	float2 INTRINSICS_CALLCONV normalize(float2 v);
	float3 INTRINSICS_CALLCONV normalize(float3 v);
	float4 INTRINSICS_CALLCONV normalize(float4 v);

	float2 INTRINSICS_CALLCONV sqrt(float2 v);
	float3 INTRINSICS_CALLCONV sqrt(float3 v);
	float4 INTRINSICS_CALLCONV sqrt(float4 v);
}

namespace xvm
{
#ifndef XVM_GLOBALCONST
#define XVM_GLOBALCONST extern const __declspec(selectany)
#endif

	__declspec(align(16)) struct XVM_FP32
	{
		union
		{
			float fp32[4];
			__m128 v;
		};

		inline operator __m128() const noexcept { return v; }
		inline operator const float* () const noexcept { return fp32; }
		inline operator __m128i() const noexcept { return _mm_castps_si128(v); }
		inline operator __m128d() const noexcept { return _mm_castps_pd(v); }
	};

	__declspec(align(16)) struct XVM_I32
	{
		union
		{
			int32_t i32[4];
			__m128 v;
		};

		inline operator __m128() const { return v; }
		inline operator __m128i() const { return _mm_castps_si128(v); }
		inline operator __m128d() const { return _mm_castps_pd(v); }
	};

	__declspec(align(16)) struct XVM_UI32
	{
		union
		{
			uint32_t i32[4];
			__m128 v;
		};

		inline operator __m128() const { return v; }
		inline operator __m128i() const { return _mm_castps_si128(v); }
		inline operator __m128d() const { return _mm_castps_pd(v); }
	};

	XVM_GLOBALCONST XVM_I32		XVMMaskAbsoluteValue	= { { { 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff } } };
	XVM_GLOBALCONST XVM_UI32	XVMMaskNegative			= { { { 0x80000000, 0x80000000, 0x80000000, 0x80000000 } } };
	XVM_GLOBALCONST XVM_UI32	XVMInfinity				= { { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } };
	XVM_GLOBALCONST XVM_UI32	XVMNegativeInfinity		= { { { 0xFF800000, 0xFF800000, 0xFF800000, 0xFF800000 } } };
	XVM_GLOBALCONST XVM_I32		XVMNaNS					= { { { 0x7F800001, 0x7F800001, 0x7F800001, 0x7F800001 } } };
	XVM_GLOBALCONST XVM_I32		XVMNaNQ					= { { { 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 } } };

#undef XVM_GLOBALCONST
}

#include "Intrinsics.inl"

#undef INTRINSICS_SHUFFLE_PS
#undef INTRINSICS_CALLCONV
#undef INTRINSICS_INLINE