#pragma once

TEST(float3, ctor)
{
	float3 v;

	EXPECT_FLOAT_EQ(v.x, 0.0f);
	EXPECT_FLOAT_EQ(v.y, 0.0f);
	EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(float3, ctor_component)
{
	float3 v(1.0f, 2.0f, 3.0f);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 2.0f);
	EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(float3, ctor_scalar)
{
	float3 v(1.0f);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 1.0f);
	EXPECT_FLOAT_EQ(v.z, 1.0f);
}

TEST(float3, ctor_array)
{
	float array[3] = { 1.0f, 2.0f, 3.0f };
	float3 v(array);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 2.0f);
	EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(float3, negation)
{
	float3 v(1.0f, 2.0f, 3.0f);
	v = -v;

	EXPECT_FLOAT_EQ(v.x, -1.0f);
	EXPECT_FLOAT_EQ(v.y, -2.0f);
	EXPECT_FLOAT_EQ(v.z, -3.0f);
}

TEST(float3, arithmetic_add)
{
	float3 v1(1.0f, 2.0f, 3.0f);
	float3 v2(4.0f, 3.0f, 2.0f);
	float3 result = v1 + v2;

	EXPECT_FLOAT_EQ(result.x, 5.0f);
	EXPECT_FLOAT_EQ(result.y, 5.0f);
	EXPECT_FLOAT_EQ(result.z, 5.0f);
}

TEST(float3, arithmetic_subtract)
{
	float3 v1(1.0f, 2.0f, 3.0f);
	float3 v2(0.1f, 0.2f, 0.3f);
	float3 result = v1 - v2;

	EXPECT_FLOAT_EQ(result.x, 0.9f);
	EXPECT_FLOAT_EQ(result.y, 1.8f);
	EXPECT_FLOAT_EQ(result.z, 2.7f);
}

TEST(float3, arithmetic_multiply)
{
	float3 v1(0.1f, 0.2f, 0.3f);
	float3 v2(0.3f);
	float3 result = v1 * v2;

	EXPECT_FLOAT_EQ(result.x, 0.03f);
	EXPECT_FLOAT_EQ(result.y, 0.06f);
	EXPECT_FLOAT_EQ(result.z, 0.09f);
}

TEST(float3, arithmetic_divide)
{
	float3 v1(0.1f, 0.2f, 0.3f);
	float3 v2(0.3f);
	float3 result = v1 / v2;

	EXPECT_NEAR(result.x, 0.33f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.66f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 1.0f, g_FloatEpsilon);
}

TEST(float3, intrinsics_abs)
{
	float3 v(-0.1f, -0.2f, -0.3f);
	float3 result = abs(v);

	EXPECT_FLOAT_EQ(result.x, 0.1f);
	EXPECT_FLOAT_EQ(result.y, 0.2f);
	EXPECT_FLOAT_EQ(result.z, 0.3f);
}

TEST(float3, intrinsics_all)
{
	float3 v1(0.0f, 0.0f, 0.0f);
	float3 v2(0.0f, 0.0f, 1.0f);
	float3 v3(1.0f, 2.0f, 3.0f);
	bool result1 = all(v1);
	bool result2 = all(v2);
	bool result3 = all(v3);

	EXPECT_FALSE(result1);
	EXPECT_FALSE(result2);
	EXPECT_TRUE(result3);
}

TEST(float3, intrinsics_any)
{
	float3 v1(0.0f, 0.0f, 0.0f);
	float3 v2(0.0f, 0.0f, 1.0f);
	float3 v3(1.0f, 2.0f, 3.0f);
	bool result1 = any(v1);
	bool result2 = any(v2);
	bool result3 = any(v3);

	EXPECT_FALSE(result1);
	EXPECT_TRUE(result2);
	EXPECT_TRUE(result3);
}

TEST(float3, intrinsics_clamp)
{
	float3 v1(2.0f);
	float3 v2(-1.0f, 2.0f, 0.5f);

	float3 result1 = clamp(v1, 0.0f, 1.0f);
	float3 result2 = clamp(v2, 0.0f, 1.0f);

	EXPECT_NEAR(result1.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result1.y, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result1.z, 1.0f, g_FloatEpsilon);

	EXPECT_NEAR(result2.x, 0.0f, g_FloatEpsilon);
	EXPECT_NEAR(result2.y, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result2.z, 0.5f, g_FloatEpsilon);
}

TEST(float3, intrinsics_cross)
{
	float3 v1 = { 5.2f, 3.4f, 2.0f };
	float3 v2 = { 0.2f, 1.0f, 2.5f };

	float3 result = cross(v1, v2);

	EXPECT_NEAR(result.x, 6.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, -12.6f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 4.52f, g_FloatEpsilon);
}

TEST(float3, intrinsics_dot)
{
	float3 v1(1.0f, 2.0f, 3.0f);
	float3 v2(0.1f, 0.2f, 0.3f);

	float3 result = dot(v1, v2);

	EXPECT_NEAR(result.x, 1.4f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 1.4f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 1.4f, g_FloatEpsilon);
}

TEST(float3, intrinsics_isfinite)
{
	float3 v1(0.0f);
	float3 v2(XVMInfinity);
	float3 v3(XVMNegativeInfinity);
	float3 v4(0.0f, 0.0f, XVMFP32Infinity.f);

	bool result1 = isfinite(v1);
	bool result2 = isfinite(v2);
	bool result3 = isfinite(v3);
	bool result4 = isfinite(v4);

	EXPECT_TRUE(result1);
	EXPECT_FALSE(result2);
	EXPECT_FALSE(result3);
	EXPECT_FALSE(result4);
}

TEST(float3, intrinsics_isinf)
{
	float3 v1(0.0f);
	float3 v2(XVMInfinity);
	float3 v3(XVMNegativeInfinity);
	float3 v4(0.0f, 0.0f, XVMFP32Infinity.f);

	bool result1 = isinf(v1);
	bool result2 = isinf(v2);
	bool result3 = isinf(v3);
	bool result4 = isinf(v4);

	EXPECT_FALSE(result1);
	EXPECT_TRUE(result2);
	EXPECT_TRUE(result3);
	EXPECT_TRUE(result4);
}

TEST(float3, intrinsics_isnan)
{
	float3 v1(XVMNaNQ);
	float3 v2(XVMInfinity);

	bool result1 = isnan(v1);
	bool result2 = isnan(v2);

	EXPECT_TRUE(result1);
	EXPECT_FALSE(result2);
}

TEST(float3, intrinsics_length)
{
	float3 v(1.0f, 2.0f, 3.0f);

	float3 result = length(v);

	EXPECT_NEAR(result.x, 3.741f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.741f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 3.741f, g_FloatEpsilon);
}

TEST(float3, intrinsics_lerp)
{
	float3 v1(1.0f, 3.0f, 5.0f);
	float3 v2(2.0f, 4.0f, 6.0f);

	float3 result = lerp(v1, v2, 0.5f);

	EXPECT_NEAR(result.x, 1.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 5.5f, g_FloatEpsilon);
}

TEST(float3, intrinsics_max)
{
	float3 v1(1.0f, 3.0f, 5.0f);
	float3 v2(2.0f, 4.0f, 6.0f);

	float3 result = max(v1, v2);

	EXPECT_NEAR(result.x, 2.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 4.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 6.0f, g_FloatEpsilon);
}

TEST(float3, intrinsics_min)
{
	float3 v1(1.0f, 3.0f, 5.0f);
	float3 v2(2.0f, 4.0f, 6.0f);

	float3 result = min(v1, v2);

	EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 5.0f, g_FloatEpsilon);
}

TEST(float3, intrinsics_normalize)
{
	float3 v(1.0f, 2.0f, 3.0f);

	float3 result = normalize(v);
	float3 len = length(result);

	EXPECT_NEAR(result.x, 0.267f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.535f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 0.802f, g_FloatEpsilon);

	EXPECT_NEAR(len.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(len.y, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(len.z, 1.0f, g_FloatEpsilon);
}

TEST(float3, intrinsics_sqrt)
{
	float3 v(1.0f, 2.0f, 3.0f);

	float3 result = sqrt(v);

	EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 1.414f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 1.732f, g_FloatEpsilon);
}
