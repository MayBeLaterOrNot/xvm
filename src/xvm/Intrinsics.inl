#pragma once

namespace xvm
{
	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV operator-(float2 v)
	{
		//return _mm_sub_ps(_mm_setzero_ps(), v.vec);
		return _mm_xor_ps(v.vec, XVMMaskNegative);
	}
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV operator-(float3 v)
	{
		//return _mm_sub_ps(_mm_setzero_ps(), v.vec);
		return _mm_xor_ps(v.vec, XVMMaskNegative);
	}
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV operator-(float4 v)
	{
		//return _mm_sub_ps(_mm_setzero_ps(), v.vec);
		return _mm_xor_ps(v.vec, XVMMaskNegative);
	}

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV operator+(float2 v1, float2 v2) { return { _mm_add_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV operator+(float3 v1, float3 v2) { return { _mm_add_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV operator+(float4 v1, float4 v2) { return { _mm_add_ps(v1.vec, v2.vec) }; }

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV operator-(float2 v1, float2 v2) { return { _mm_sub_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV operator-(float3 v1, float3 v2) { return { _mm_sub_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV operator-(float4 v1, float4 v2) { return { _mm_sub_ps(v1.vec, v2.vec) }; }

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV operator*(float2 v1, float2 v2) { return { _mm_mul_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV operator*(float3 v1, float3 v2) { return { _mm_mul_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV operator*(float4 v1, float4 v2) { return { _mm_mul_ps(v1.vec, v2.vec) }; }

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV operator/(float2 v1, float2 v2) { return { _mm_div_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV operator/(float3 v1, float3 v2) { return { _mm_div_ps(v1.vec, v2.vec) }; }
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV operator/(float4 v1, float4 v2) { return { _mm_div_ps(v1.vec, v2.vec) }; }

	INTRINSICS_INLINE float2& INTRINSICS_CALLCONV operator+=(float2& v1, float2 v2) { v1 = v1 + v2; return v1; }
	INTRINSICS_INLINE float3& INTRINSICS_CALLCONV operator+=(float3& v1, float3 v2) { v1 = v1 + v2; return v1; }
	INTRINSICS_INLINE float4& INTRINSICS_CALLCONV operator+=(float4& v1, float4 v2) { v1 = v1 + v2; return v1; }

	INTRINSICS_INLINE float2& INTRINSICS_CALLCONV operator-=(float2& v1, float2 v2) { v1 = v1 - v2; return v1; }
	INTRINSICS_INLINE float3& INTRINSICS_CALLCONV operator-=(float3& v1, float3 v2) { v1 = v1 - v2; return v1; }
	INTRINSICS_INLINE float4& INTRINSICS_CALLCONV operator-=(float4& v1, float4 v2) { v1 = v1 - v2; return v1; }

	INTRINSICS_INLINE float2& INTRINSICS_CALLCONV operator*=(float2& v1, float2 v2) { v1 = v1 * v2; return v1; }
	INTRINSICS_INLINE float3& INTRINSICS_CALLCONV operator*=(float3& v1, float3 v2) { v1 = v1 * v2; return v1; }
	INTRINSICS_INLINE float4& INTRINSICS_CALLCONV operator*=(float4& v1, float4 v2) { v1 = v1 * v2; return v1; }

	INTRINSICS_INLINE float2& INTRINSICS_CALLCONV operator/=(float2& v1, float2 v2) { v1 = v1 / v2; return v1; }
	INTRINSICS_INLINE float3& INTRINSICS_CALLCONV operator/=(float3& v1, float3 v2) { v1 = v1 / v2; return v1; }
	INTRINSICS_INLINE float4& INTRINSICS_CALLCONV operator/=(float4& v1, float4 v2) { v1 = v1 / v2; return v1; }

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV abs(float2 v)
	{
		// & the sign bit
		return _mm_and_ps(XVMMaskAbsoluteValue, v.vec);
	}
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV abs(float3 v)
	{
		// & the sign bit
		return _mm_and_ps(XVMMaskAbsoluteValue, v.vec);
	}
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV abs(float4 v)
	{
		// & the sign bit
		return _mm_and_ps(XVMMaskAbsoluteValue, v.vec);
	}

	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV cross(float3 v1, float3 v2)
	{
		/*
		* http://threadlocalmutex.com/?p=8
		* (v1 x v2).x = v1.y * v2.z - v1.z * v2.y;
		* (v1 x v2).y = v1.z * v2.x - v1.x * v2.z;
		* (v1 x v2).z = v1.x * v2.y - v1.y * v2.x;
		*
		* moving the 3rd operation to top yields this
		*
		* (v1 x v2).z = v1.x * v2.y - v1.y * v2.x;
		* (v1 x v2).x = v1.y * v2.z - v1.z * v2.y;
		* (v1 x v2).y = v1.z * v2.x - v1.x * v2.z;
		*
		* we can perform swizzling here
		*
		* (v1 x v2).zxy = v1 * v2.yzx - v1.yzx * v2;
		*
		* swizzle zxy on both sides gives us the cross product again
		*
		* (v1 x v2) = (v1 * v2.yzx - v1.yzx * v2).yzx;
		*/
		__m128 v1_yzx = INTRINSICS_SHUFFLE_PS(v1.vec, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 v2_yzx = INTRINSICS_SHUFFLE_PS(v2.vec, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 cross = _mm_sub_ps(_mm_mul_ps(v1.vec, v2_yzx), _mm_mul_ps(v1_yzx, v2.vec));
		return INTRINSICS_SHUFFLE_PS(cross, _MM_SHUFFLE(3, 0, 2, 1));
	}

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV dot(float2 v1, float2 v2)
	{
		__m128 dot = _mm_mul_ps(v1.vec, v2.vec);
		__m128 shuff = INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(1, 1, 1, 1)); // { y, y, y, y }
		dot = _mm_add_ss(dot, shuff); // { x+y, ?, ?, ? }
		return INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0)); // splat fp0
	}
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV dot(float3 v1, float3 v2)
	{
		__m128 dot = _mm_mul_ps(v1.vec, v2.vec);
		__m128 shuff = INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(2, 2, 2, 1)); // { y, z, z, z }
		dot = _mm_add_ss(dot, shuff); // { x+y, ?, ?, ? }
		shuff = INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(2, 2, 2, 2)); // { z, z, z, z }
		dot = _mm_add_ss(dot, shuff); // { x+y+z, ?, ?, ? }
		return INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0)); // splat fp0
	}
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV dot(float4 v1, float4 v2)
	{
		__m128 dot = _mm_mul_ps(v1.vec, v2.vec);
		__m128 shuff = INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(2, 3, 0, 1)); // { y, x, w, z }
		dot = _mm_add_ps(dot, shuff); // { x+y, y+x, z+w, w+z }
		shuff = _mm_movehl_ps(shuff, dot); // { dot.fp2, dot.fp3, shuff.fp2, shuff.fp3 }
		dot = _mm_add_ss(dot, shuff); // { x+y+z+w, ?, ?, ? }
		return INTRINSICS_SHUFFLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0)); // splat fp0
	}

	INTRINSICS_INLINE bool INTRINSICS_CALLCONV isnan(float2 v)
	{
		__m128 dst = _mm_cmpneq_ps(v.vec, v.vec); // v != v
		int mask = _mm_movemask_ps(dst) & 0x00000003;
		// If x or y are NaN, the mask is non-zero
		return mask != 0;
	}
	INTRINSICS_INLINE bool INTRINSICS_CALLCONV isnan(float3 v)
	{
		__m128 dst = _mm_cmpneq_ps(v.vec, v.vec); // v != v
		int mask = _mm_movemask_ps(dst) & 0x00000007;
		// If x or y or z are NaN, the mask is non-zero
		return mask != 0;
	}
	INTRINSICS_INLINE bool INTRINSICS_CALLCONV isnan(float4 v)
	{
		__m128 dst = _mm_cmpneq_ps(v.vec, v.vec); // v != v
		int mask = _mm_movemask_ps(dst) & 0x0000000F;
		// If x or y or z or w are NaN, the mask is non-zero
		return mask != 0;
	}

	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV length(float2 v)
	{
		float2 v2 = dot(v, v);
		return _mm_sqrt_ps(v2.vec);
	}
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV length(float3 v)
	{
		float3 v2 = dot(v, v);
		return _mm_sqrt_ps(v2.vec);
	}
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV length(float4 v)
	{
		float4 v2 = dot(v, v);
		return _mm_sqrt_ps(v2.vec);
	}
}
