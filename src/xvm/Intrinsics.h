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

// TODO: implement trig functions

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

	struct float4x4
	{
		float4x4();
		float4x4(
			__m128 r0,
			__m128 r1,
			__m128 r2,
			__m128 r3)
		{
			r[0] = r0;
			r[1] = r1;
			r[2] = r2;
			r[3] = r3;
		}
		float4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			r[0] = _mm_set_ps(m03, m02, m01, m00);
			r[1] = _mm_set_ps(m13, m12, m11, m10);
			r[2] = _mm_set_ps(m23, m22, m21, m20);
			r[3] = _mm_set_ps(m33, m32, m31, m30);
		}
		float4x4(float floats[16]) : float4x4(
			floats[0], floats[1], floats[2], floats[3],
			floats[4], floats[5], floats[6], floats[7], 
			floats[8], floats[9], floats[10], floats[11], 
			floats[12], floats[13], floats[14], floats[15]) { }

		union
		{
			__m128 r[4];
			struct
			{
				union
				{
					__m128 vec;
					scalar_swizzle<0> x;
					scalar_swizzle<1> y;
					scalar_swizzle<2> z;
					scalar_swizzle<3> w;
				} r0;
				union
				{
					__m128 vec;
					scalar_swizzle<0> x;
					scalar_swizzle<1> y;
					scalar_swizzle<2> z;
					scalar_swizzle<3> w;
				} r1;
				union
				{
					__m128 vec;
					scalar_swizzle<0> x;
					scalar_swizzle<1> y;
					scalar_swizzle<2> z;
					scalar_swizzle<3> w;
				} r2;
				union
				{
					__m128 vec;
					scalar_swizzle<0> x;
					scalar_swizzle<1> y;
					scalar_swizzle<2> z;
					scalar_swizzle<3> w;
				} r3;
			};
		};
	};

	// Negate operator
	float2 INTRINSICS_CALLCONV operator-(float2 v);
	float3 INTRINSICS_CALLCONV operator-(float3 v);
	float4 INTRINSICS_CALLCONV operator-(float4 v);
	float4x4 INTRINSICS_CALLCONV operator-(float4x4 m);

	// Arithmetic operators
	float2 INTRINSICS_CALLCONV operator+(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator+(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator+(float4 v1, float4 v2);
	float4x4 INTRINSICS_CALLCONV operator+(float4x4 m1, float4x4 m2);

	float2 INTRINSICS_CALLCONV operator-(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator-(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator-(float4 v1, float4 v2);
	float4x4 INTRINSICS_CALLCONV operator-(float4x4 m1, float4x4 m2);

	float2 INTRINSICS_CALLCONV operator*(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator*(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator*(float4 v1, float4 v2);
	float4x4 INTRINSICS_CALLCONV operator*(float4x4 m, float scalar);
	float4x4 INTRINSICS_CALLCONV operator*(float scalar, float4x4 m);
	float4x4 INTRINSICS_CALLCONV operator*(float4x4 m1, float4x4 m2);

	float2 INTRINSICS_CALLCONV operator/(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV operator/(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV operator/(float4 v1, float4 v2);
	float4x4 INTRINSICS_CALLCONV operator/(float4x4 m, float scalar);

	// Using these function may cause code bloat on different compilers
	// because the quad-word (128-bit) fits nicely inside one SIMD register.
	// And one of the key factors of a vector library is to keep the data inside these registers as much as possible.
	// By doing that, you avoid unnecessary loads and stores operations from SIMD registers to memory or FPU registers.
	// When combining multiple vector operations the "returned by value" interface allows the compiler to optimize these loads and stores easily by minimizing SIMD to FPU or memory transfers.
	float2& INTRINSICS_CALLCONV operator+=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator+=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator+=(float4& v1, float4 v2);
	float4x4& INTRINSICS_CALLCONV operator+=(float4x4& m1, float4x4 m2);

	float2& INTRINSICS_CALLCONV operator-=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator-=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator-=(float4& v1, float4 v2);
	float4x4& INTRINSICS_CALLCONV operator-=(float4x4& m1, float4x4 m2);

	float2& INTRINSICS_CALLCONV operator*=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator*=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator*=(float4& v1, float4 v2);
	float4x4& INTRINSICS_CALLCONV operator*=(float4x4& m, float scalar);
	float4x4& INTRINSICS_CALLCONV operator*=(float4x4& m1, float4x4 m2);

	float2& INTRINSICS_CALLCONV operator/=(float2& v1, float2 v2);
	float3& INTRINSICS_CALLCONV operator/=(float3& v1, float3 v2);
	float4& INTRINSICS_CALLCONV operator/=(float4& v1, float4 v2);
	float4x4& INTRINSICS_CALLCONV operator/=(float4x4& m, float scalar);

	// Intrinsics
	float2 INTRINSICS_CALLCONV abs(float2 v);
	float3 INTRINSICS_CALLCONV abs(float3 v);
	float4 INTRINSICS_CALLCONV abs(float4 v);

	// Determines if all components of the specified value are non-zero.
	bool INTRINSICS_CALLCONV all(float2 v);
	bool INTRINSICS_CALLCONV all(float3 v);
	bool INTRINSICS_CALLCONV all(float4 v);

	// Determines if any components of the specified value are non-zero.
	bool INTRINSICS_CALLCONV any(float2 v);
	bool INTRINSICS_CALLCONV any(float3 v);
	bool INTRINSICS_CALLCONV any(float4 v);

	float2 INTRINSICS_CALLCONV clamp(float2 v, float2 min, float2 max);
	float3 INTRINSICS_CALLCONV clamp(float3 v, float3 min, float3 max);
	float4 INTRINSICS_CALLCONV clamp(float4 v, float4 min, float4 max);

	float3 INTRINSICS_CALLCONV cross(float3 v1, float3 v2);

	// Dot product, (also known as scalar product) of 2 vectors u and v is defined as the sum of
	// the product of their corresponding vector components, value of dot product is splatted across the sse registers
	float2 INTRINSICS_CALLCONV dot(float2 v1, float2 v2);
	float3 INTRINSICS_CALLCONV dot(float3 v1, float3 v2);
	float4 INTRINSICS_CALLCONV dot(float4 v1, float4 v2);

	// Determines if the specified floating-point value is finite.
	bool INTRINSICS_CALLCONV isfinite(float2 v);
	bool INTRINSICS_CALLCONV isfinite(float3 v);
	bool INTRINSICS_CALLCONV isfinite(float4 v);

	// Determines if the specified floating-point value is infinite.
	bool INTRINSICS_CALLCONV isinf(float2 v);
	bool INTRINSICS_CALLCONV isinf(float3 v);
	bool INTRINSICS_CALLCONV isinf(float4 v);

	// Determines if the specified floating-point value is nan.
	bool INTRINSICS_CALLCONV isnan(float2 v);
	bool INTRINSICS_CALLCONV isnan(float3 v);
	bool INTRINSICS_CALLCONV isnan(float4 v);

	// Sqrt of sum of each component squared, value of length is splatted across the sse registers
	float2 INTRINSICS_CALLCONV length(float2 v);
	float3 INTRINSICS_CALLCONV length(float3 v);
	float4 INTRINSICS_CALLCONV length(float4 v);

	float2 INTRINSICS_CALLCONV lerp(float2 v1, float2 v2, float2 s);
	float3 INTRINSICS_CALLCONV lerp(float3 v1, float3 v2, float3 s);
	float4 INTRINSICS_CALLCONV lerp(float4 v1, float4 v2, float4 s);

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

	// Treats v as a row vector matrix [1x4] * [4x4]
	// returns a row vector
	float4 INTRINSICS_CALLCONV mul(float4 v, float4x4 m);
	float4x4 INTRINSICS_CALLCONV mul(float4x4 m1, float4x4 m2);

	float4x4 INTRINSICS_CALLCONV transpose(float4x4 m);
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

	XVM_GLOBALCONST FP32		XVMFP32Infinity			= { 0x7F800000 };
	XVM_GLOBALCONST FP32		XVMFP32NegativeInfinity = { 0xFF800000 };

	XVM_GLOBALCONST XVM_FP32	XVMIdentityR0			= { { { 1.0f, 0.0f, 0.0f, 0.0f } } };
	XVM_GLOBALCONST XVM_FP32	XVMIdentityR1			= { { { 0.0f, 1.0f, 0.0f, 0.0f } } };
	XVM_GLOBALCONST XVM_FP32	XVMIdentityR2			= { { { 0.0f, 0.0f, 1.0f, 0.0f } } };
	XVM_GLOBALCONST XVM_FP32	XVMIdentityR3			= { { { 0.0f, 0.0f, 0.0f, 1.0f } } };

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