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
}
