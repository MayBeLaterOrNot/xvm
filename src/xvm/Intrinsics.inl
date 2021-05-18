#pragma once

namespace xvm
{
	INTRINSICS_INLINE float2 INTRINSICS_CALLCONV operator-(float2 v)
	{
		//return _mm_sub_ps(_mm_setzero_ps(), v.vec);
		return _mm_xor_ps(v.vec, XMV_NEGATIVE_MASK);
	}
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV operator-(float3 v)
	{
		//return _mm_sub_ps(_mm_setzero_ps(), v.vec);
		return _mm_xor_ps(v.vec, XMV_NEGATIVE_MASK);
	}
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV operator-(float4 v)
	{
		//return _mm_sub_ps(_mm_setzero_ps(), v.vec);
		return _mm_xor_ps(v.vec, XMV_NEGATIVE_MASK);
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
		return _mm_and_ps(XVM_ABS_MASK, v.vec);
	}
	INTRINSICS_INLINE float3 INTRINSICS_CALLCONV abs(float3 v)
	{
		// & the sign bit
		return _mm_and_ps(XVM_ABS_MASK, v.vec);
	}
	INTRINSICS_INLINE float4 INTRINSICS_CALLCONV abs(float4 v)
	{
		// & the sign bit
		return _mm_and_ps(XVM_ABS_MASK, v.vec);
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
}
