#pragma once
#include <cmath>
#include <cstdint>
#include <immintrin.h>
#include <intrin.h>
#include <xmmintrin.h>

#define INTRINSICS_INLINE				 inline

#define INTRINSICS_CALLCONV				 __vectorcall

// _MM_SHUFFLE(3, 2, 1, 0) -> [x, y, z, w]
#define INTRINSICS_SWIZZLE_PS(v, c)		 _mm_shuffle_ps(v, v, c)

// { v1[fp0], v1[fp1], v2[fp2], v2[fp3] }
#define INTRINSICS_SHUFFLE_PS(v1, v2, c) _mm_shuffle_ps(v1, v2, c)

// https://stackoverflow.com/questions/51641131/how-to-achieve-vector-swizzling-in-c
// https://docs.microsoft.com/en-us/cpp/cpp/m128?view=msvc-160

namespace xvm
{
// TODO: Add swizzling to Vec2,Vec3,Vec4
template<int I>
struct scalar_swizzle
{
	operator float() const { return fp32[I]; }

private:
	union
	{
		__m128 vec;
		float  fp32[4];
	};
};

struct Vec2
{
	Vec2()
		: vec(_mm_setzero_ps())
	{
	}
	Vec2(__m128 a)
		: vec(a)
	{
	}
	Vec2(float x, float y)
		: vec(_mm_set_ps(0.0f, 0.0f, y, x))
	{
	}
	Vec2(float scalar)
		: Vec2(scalar, scalar)
	{
	}
	Vec2(float floats[2])
		: Vec2(floats[0], floats[1])
	{
	}

	__m128 vec;
};

struct Vec3
{
	Vec3()
		: vec(_mm_setzero_ps())
	{
	}
	Vec3(__m128 a)
		: vec(a)
	{
	}
	Vec3(float x, float y, float z)
		: vec(_mm_set_ps(0.0f, z, y, x))
	{
	}
	Vec3(float scalar)
		: Vec3(scalar, scalar, scalar)
	{
	}
	Vec3(float floats[3])
		: Vec3(floats[0], floats[1], floats[2])
	{
	}

	union
	{
		__m128			  vec;
		scalar_swizzle<0> x;
		scalar_swizzle<1> y;
		scalar_swizzle<2> z;
	};
};

struct Vec4
{
	Vec4()
		: vec(_mm_setzero_ps())
	{
	}
	Vec4(__m128 a)
		: vec(a)
	{
	}
	Vec4(float x, float y, float z, float w)
		: vec(_mm_set_ps(w, z, y, x))
	{
	}
	Vec4(float scalar)
		: Vec4(scalar, scalar, scalar, scalar)
	{
	}
	Vec4(float floats[4])
		: Vec4(floats[0], floats[1], floats[2], floats[3])
	{
	}

	union
	{
		__m128			  vec;
		scalar_swizzle<0> x;
		scalar_swizzle<1> y;
		scalar_swizzle<2> z;
		scalar_swizzle<3> w;
	};
};

// q = s + ia + jb + kc			 s, a, b, c ∈ R
// Identities:
// i^2 = j^2 = k^2 = ijk = −1
// ij = k, jk = i, ki = j
// ji = −k, kj = −i, ik = −j
// ij = -ji = k
// jk = -kj = i
// ki = -ik = j
// i×j = k, j×k = i, k×i = j cross product of 2 unit cartesian vectors

// When a unit quaternion takes the form
// q = [cos theta/2, sin theta/2 * v^hat]
// and a pure quaternion storing a vector to be rotated takes the form
// p = [0, p]
// the pure quaternion
// p' = q*p*q^-1
// stores the rotated vector p'
struct Quaternion
{
	Quaternion()
		: vec(_mm_setzero_ps())
	{
	}
	Quaternion(__m128 a)
		: vec(a)
	{
	}
	Quaternion(float x, float y, float z, float w)
		: vec(_mm_set_ps(w, z, y, x))
	{
	}

	union
	{
		__m128 vec;
		// vector part
		scalar_swizzle<0> x;
		scalar_swizzle<1> y;
		scalar_swizzle<2> z;
		// real part
		scalar_swizzle<3> w;
	};
};

struct Matrix4x4
{
	Matrix4x4();
	Matrix4x4(__m128 r0, __m128 r1, __m128 r2, __m128 r3)
	{
		r[0] = r0;
		r[1] = r1;
		r[2] = r2;
		r[3] = r3;
	}
	// clang-format off
	Matrix4x4(
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
	Matrix4x4(float floats[16])
		: Matrix4x4(
			floats[0], floats[1], floats[2], floats[3],
			floats[4], floats[5], floats[6], floats[7],
			floats[8], floats[9], floats[10], floats[11],
			floats[12], floats[13], floats[14], floats[15])
	{
	}
	// clang-format on

	union
	{
		__m128 r[4];
		struct
		{
			union
			{
				__m128			  vec;
				scalar_swizzle<0> x;
				scalar_swizzle<1> y;
				scalar_swizzle<2> z;
				scalar_swizzle<3> w;
			} r0;
			union
			{
				__m128			  vec;
				scalar_swizzle<0> x;
				scalar_swizzle<1> y;
				scalar_swizzle<2> z;
				scalar_swizzle<3> w;
			} r1;
			union
			{
				__m128			  vec;
				scalar_swizzle<0> x;
				scalar_swizzle<1> y;
				scalar_swizzle<2> z;
				scalar_swizzle<3> w;
			} r2;
			union
			{
				__m128			  vec;
				scalar_swizzle<0> x;
				scalar_swizzle<1> y;
				scalar_swizzle<2> z;
				scalar_swizzle<3> w;
			} r3;
		};
	};
};

// Negate operator
Vec2 INTRINSICS_CALLCONV	  operator-(Vec2 v);
Vec3 INTRINSICS_CALLCONV	  operator-(Vec3 v);
Vec4 INTRINSICS_CALLCONV	  operator-(Vec4 v);
Matrix4x4 INTRINSICS_CALLCONV operator-(Matrix4x4 m);

// Arithmetic operators
Vec2 INTRINSICS_CALLCONV	   operator+(const Vec2& v1, const Vec2& v2);
Vec3 INTRINSICS_CALLCONV	   operator+(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV	   operator+(Vec4 v1, Vec4 v2);
Quaternion INTRINSICS_CALLCONV operator+(Quaternion q1, Quaternion q2);
Matrix4x4 INTRINSICS_CALLCONV  operator+(Matrix4x4 m1, Matrix4x4 m2);

Vec2 INTRINSICS_CALLCONV	   operator-(Vec2 v1, Vec2 v2);
Vec3 INTRINSICS_CALLCONV	   operator-(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV	   operator-(Vec4 v1, Vec4 v2);
Quaternion INTRINSICS_CALLCONV operator-(Quaternion q1, Quaternion q2);
Matrix4x4 INTRINSICS_CALLCONV  operator-(Matrix4x4 m1, Matrix4x4 m2);

Vec2 INTRINSICS_CALLCONV	   operator*(Vec2 v1, Vec2 v2);
Vec3 INTRINSICS_CALLCONV	   operator*(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV	   operator*(Vec4 v1, Vec4 v2);
Quaternion INTRINSICS_CALLCONV operator*(Quaternion q1,
										 Quaternion q2); // Quaternion product
Quaternion INTRINSICS_CALLCONV operator*(Quaternion q, float scalar);
Quaternion INTRINSICS_CALLCONV operator*(float scalar, Quaternion q);
Matrix4x4 INTRINSICS_CALLCONV  operator*(Matrix4x4 m, float scalar);
Matrix4x4 INTRINSICS_CALLCONV  operator*(float scalar, Matrix4x4 m);
Matrix4x4 INTRINSICS_CALLCONV  operator*(Matrix4x4 m1, Matrix4x4 m2);

Vec2 INTRINSICS_CALLCONV	  operator/(Vec2 v1, Vec2 v2);
Vec3 INTRINSICS_CALLCONV	  operator/(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV	  operator/(Vec4 v1, Vec4 v2);
Matrix4x4 INTRINSICS_CALLCONV operator/(Matrix4x4 m, float scalar);

// Using these function may cause code bloat on different compilers
// because the quad-word (128-bit) fits nicely inside one SIMD register.
// And one of the key factors of a vector library is to keep the data inside
// these registers as much as possible. By doing that, you avoid unnecessary
// loads and stores operations from SIMD registers to memory or FPU registers.
// When combining multiple vector operations the "returned by value" interface
// allows the compiler to optimize these loads and stores easily by minimizing
// SIMD to FPU or memory transfers.
Vec2& INTRINSICS_CALLCONV		operator+=(Vec2& v1, Vec2 v2);
Vec3& INTRINSICS_CALLCONV		operator+=(Vec3& v1, Vec3 v2);
Vec4& INTRINSICS_CALLCONV		operator+=(Vec4& v1, Vec4 v2);
Quaternion& INTRINSICS_CALLCONV operator+=(Quaternion& q1, Quaternion q2);
Matrix4x4& INTRINSICS_CALLCONV	operator+=(Matrix4x4& m1, Matrix4x4 m2);

Vec2& INTRINSICS_CALLCONV		operator-=(Vec2& v1, Vec2 v2);
Vec3& INTRINSICS_CALLCONV		operator-=(Vec3& v1, Vec3 v2);
Vec4& INTRINSICS_CALLCONV		operator-=(Vec4& v1, Vec4 v2);
Quaternion& INTRINSICS_CALLCONV operator-=(Quaternion& q1, Quaternion q2);
Matrix4x4& INTRINSICS_CALLCONV	operator-=(Matrix4x4& m1, Matrix4x4 m2);

Vec2& INTRINSICS_CALLCONV		operator*=(Vec2& v1, Vec2 v2);
Vec3& INTRINSICS_CALLCONV		operator*=(Vec3& v1, Vec3 v2);
Vec4& INTRINSICS_CALLCONV		operator*=(Vec4& v1, Vec4 v2);
Quaternion& INTRINSICS_CALLCONV operator*=(Quaternion& q1, Quaternion q2);
Quaternion& INTRINSICS_CALLCONV operator*=(Quaternion& q, float scalar);
Matrix4x4& INTRINSICS_CALLCONV	operator*=(Matrix4x4& m, float scalar);
Matrix4x4& INTRINSICS_CALLCONV	operator*=(Matrix4x4& m1, Matrix4x4 m2);

Vec2& INTRINSICS_CALLCONV	   operator/=(Vec2& v1, Vec2 v2);
Vec3& INTRINSICS_CALLCONV	   operator/=(Vec3& v1, Vec3 v2);
Vec4& INTRINSICS_CALLCONV	   operator/=(Vec4& v1, Vec4 v2);
Matrix4x4& INTRINSICS_CALLCONV operator/=(Matrix4x4& m, float scalar);

// Intrinsics
Quaternion INTRINSICS_CALLCONV conjugate(Quaternion q);
Quaternion INTRINSICS_CALLCONV inverse(Quaternion q);

Vec2 INTRINSICS_CALLCONV abs(Vec2 v);
Vec3 INTRINSICS_CALLCONV abs(Vec3 v);
Vec4 INTRINSICS_CALLCONV abs(Vec4 v);

// Determines if all components of the specified value are non-zero.
bool INTRINSICS_CALLCONV all(Vec2 v);
bool INTRINSICS_CALLCONV all(Vec3 v);
bool INTRINSICS_CALLCONV all(Vec4 v);

// Determines if any components of the specified value are non-zero.
bool INTRINSICS_CALLCONV any(Vec2 v);
bool INTRINSICS_CALLCONV any(Vec3 v);
bool INTRINSICS_CALLCONV any(Vec4 v);

Vec2 INTRINSICS_CALLCONV clamp(Vec2 v, Vec2 min, Vec2 max);
Vec3 INTRINSICS_CALLCONV clamp(Vec3 v, Vec3 min, Vec3 max);
Vec4 INTRINSICS_CALLCONV clamp(Vec4 v, Vec4 min, Vec4 max);

Vec3 INTRINSICS_CALLCONV cross(Vec3 v1, Vec3 v2);

// Dot product, (also known as scalar product) of 2 vectors u and v is defined
// as the sum of the product of their corresponding vector components, value of
// dot product is splatted across the sse registers
Vec2 INTRINSICS_CALLCONV dot(Vec2 v1, Vec2 v2);
Vec3 INTRINSICS_CALLCONV dot(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV dot(Vec4 v1, Vec4 v2);
Vec4 INTRINSICS_CALLCONV dot(Quaternion q1, Quaternion q2);

// Determines if the specified floating-point value is finite.
bool INTRINSICS_CALLCONV isfinite(Vec2 v);
bool INTRINSICS_CALLCONV isfinite(Vec3 v);
bool INTRINSICS_CALLCONV isfinite(Vec4 v);

// Determines if the specified floating-point value is infinite.
bool INTRINSICS_CALLCONV isinf(Vec2 v);
bool INTRINSICS_CALLCONV isinf(Vec3 v);
bool INTRINSICS_CALLCONV isinf(Vec4 v);

// Determines if the specified floating-point value is nan.
bool INTRINSICS_CALLCONV isnan(Vec2 v);
bool INTRINSICS_CALLCONV isnan(Vec3 v);
bool INTRINSICS_CALLCONV isnan(Vec4 v);

// Sqrt of sum of each component squared, value of length is splatted across the
// sse registers
Vec2 INTRINSICS_CALLCONV length(Vec2 v);
Vec3 INTRINSICS_CALLCONV length(Vec3 v);
Vec4 INTRINSICS_CALLCONV length(Vec4 v);
Vec4 INTRINSICS_CALLCONV length(Quaternion q);

Vec2 INTRINSICS_CALLCONV lerp(Vec2 v1, Vec2 v2, Vec2 s);
Vec3 INTRINSICS_CALLCONV lerp(Vec3 v1, Vec3 v2, Vec3 s);
Vec4 INTRINSICS_CALLCONV lerp(Vec4 v1, Vec4 v2, Vec4 s);

Vec2 INTRINSICS_CALLCONV max(Vec2 v1, Vec2 v2);
Vec3 INTRINSICS_CALLCONV max(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV max(Vec4 v1, Vec4 v2);

Vec2 INTRINSICS_CALLCONV min(Vec2 v1, Vec2 v2);
Vec3 INTRINSICS_CALLCONV min(Vec3 v1, Vec3 v2);
Vec4 INTRINSICS_CALLCONV min(Vec4 v1, Vec4 v2);

Vec2 INTRINSICS_CALLCONV	   normalize(Vec2 v);
Vec3 INTRINSICS_CALLCONV	   normalize(Vec3 v);
Vec4 INTRINSICS_CALLCONV	   normalize(Vec4 v);
Quaternion INTRINSICS_CALLCONV normalize(Quaternion q);

Vec2 INTRINSICS_CALLCONV sqrt(Vec2 v);
Vec3 INTRINSICS_CALLCONV sqrt(Vec3 v);
Vec4 INTRINSICS_CALLCONV sqrt(Vec4 v);

Vec3 INTRINSICS_CALLCONV mul(Vec3 v, Quaternion q);
// Treats v as a row vector matrix [1x4] * [4x4]
// returns a [1x4] row vector
Vec4 INTRINSICS_CALLCONV	  mul(Vec4 v, Matrix4x4 m);
Matrix4x4 INTRINSICS_CALLCONV mul(Matrix4x4 m1, Matrix4x4 m2);

Matrix4x4 INTRINSICS_CALLCONV transpose(Matrix4x4 m);

// Transformations
Matrix4x4 INTRINSICS_CALLCONV translation(float x, float y, float z);

Matrix4x4 INTRINSICS_CALLCONV scale(float x, float y, float z);

Matrix4x4 INTRINSICS_CALLCONV rotationX(float angle);
Matrix4x4 INTRINSICS_CALLCONV rotationY(float angle);
Matrix4x4 INTRINSICS_CALLCONV rotationZ(float angle);
} // namespace xvm

namespace xvm
{
#ifndef XVM_GLOBALCONST
#define XVM_GLOBALCONST extern const __declspec(selectany)
#endif

union FP32
{
	uint32_t u;
	float	 f;
	struct
	{
		uint32_t Mantissa : 23;
		uint32_t Exponent : 8;
		uint32_t Sign	  : 1;
	};
};

__declspec(align(16)) struct XVM_FP32
{
	union
	{
		float  fp32[4];
		__m128 v;
	};

	inline operator __m128() const noexcept { return v; }
	inline operator const float*() const noexcept { return fp32; }
	inline operator __m128i() const noexcept { return _mm_castps_si128(v); }
	inline operator __m128d() const noexcept { return _mm_castps_pd(v); }
};

__declspec(align(16)) struct XVM_I32
{
	union
	{
		int32_t i32[4];
		__m128	v;
	};

	inline operator __m128() const noexcept { return v; }
	inline operator __m128i() const noexcept { return _mm_castps_si128(v); }
	inline operator __m128d() const noexcept { return _mm_castps_pd(v); }
};

__declspec(align(16)) struct XVM_UI32
{
	union
	{
		uint32_t ui32[4];
		__m128	 v;
	};

	inline operator __m128() const noexcept { return v; }
	inline operator __m128i() const noexcept { return _mm_castps_si128(v); }
	inline operator __m128d() const noexcept { return _mm_castps_pd(v); }
};

XVM_GLOBALCONST FP32 XVMFP32Infinity		 = { 0x7F800000 };
XVM_GLOBALCONST FP32 XVMFP32NegativeInfinity = { 0xFF800000 };

XVM_GLOBALCONST XVM_FP32 XVMIdentityR0 = { { { 1.0f, 0.0f, 0.0f, 0.0f } } };
XVM_GLOBALCONST XVM_FP32 XVMIdentityR1 = { { { 0.0f, 1.0f, 0.0f, 0.0f } } };
XVM_GLOBALCONST XVM_FP32 XVMIdentityR2 = { { { 0.0f, 0.0f, 1.0f, 0.0f } } };
XVM_GLOBALCONST XVM_FP32 XVMIdentityR3 = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };

XVM_GLOBALCONST XVM_I32	 XVMMaskAbsoluteValue = { { { 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff } } };
XVM_GLOBALCONST XVM_UI32 XVMMaskNegative	  = { { { 0x80000000, 0x80000000, 0x80000000, 0x80000000 } } };
XVM_GLOBALCONST XVM_UI32 XVMMaskXYZNegative	  = { { { 0x80000000, 0x80000000, 0x80000000, 0x00000000 } } };
XVM_GLOBALCONST XVM_UI32 XVMInfinity		  = { { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } };
XVM_GLOBALCONST XVM_UI32 XVMNegativeInfinity  = { { { 0xFF800000, 0xFF800000, 0xFF800000, 0xFF800000 } } };
XVM_GLOBALCONST XVM_I32	 XVMNaNS			  = { { { 0x7F800001, 0x7F800001, 0x7F800001, 0x7F800001 } } };
XVM_GLOBALCONST XVM_I32	 XVMNaNQ			  = { { { 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 } } };

XVM_GLOBALCONST XVM_FP32 XVMQuaternionUnitI = { { { 1.0f, 0.0f, 0.0f, 0.0f } } };
XVM_GLOBALCONST XVM_FP32 XVMQuaternionUnitJ = { { { 0.0f, 1.0f, 0.0f, 0.0f } } };
XVM_GLOBALCONST XVM_FP32 XVMQuaternionUnitK = { { { 0.0f, 0.0f, 1.0f, 0.0f } } };

#undef XVM_GLOBALCONST
} // namespace xvm

#include "Intrinsics.inl"

#undef INTRINSICS_SWIZZLE_PS
#undef INTRINSICS_CALLCONV
#undef INTRINSICS_INLINE
