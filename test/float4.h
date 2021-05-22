#pragma once

TEST(float4, ctor)
{
	float4 v;

	EXPECT_FLOAT_EQ(v.x, 0.0f);
	EXPECT_FLOAT_EQ(v.y, 0.0f);
	EXPECT_FLOAT_EQ(v.z, 0.0f);
	EXPECT_FLOAT_EQ(v.w, 0.0f);
}

TEST(float4, ctor_component)
{
	float4 v(1.0f, 2.0f, 3.0f, 4.0f);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 2.0f);
	EXPECT_FLOAT_EQ(v.z, 3.0f);
	EXPECT_FLOAT_EQ(v.w, 4.0f);
}

TEST(float4, ctor_scalar)
{
	float4 v(1.0f);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 1.0f);
	EXPECT_FLOAT_EQ(v.z, 1.0f);
	EXPECT_FLOAT_EQ(v.w, 1.0f);
}

TEST(float4, ctor_array)
{
	float array[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	float4 v(array);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 2.0f);
	EXPECT_FLOAT_EQ(v.z, 3.0f);
	EXPECT_FLOAT_EQ(v.w, 4.0f);
}

TEST(float4, negation)
{
	float4 v(1.0f, 2.0f, 3.0f, 4.0f);
	v = -v;

	EXPECT_FLOAT_EQ(v.x, -1.0f);
	EXPECT_FLOAT_EQ(v.y, -2.0f);
	EXPECT_FLOAT_EQ(v.z, -3.0f);
	EXPECT_FLOAT_EQ(v.w, -4.0f);
}

TEST(float4, arithmetic_add)
{
	float4 v1(1.0f, 2.0f, 3.0f, 4.0f);
	float4 v2(4.0f, 3.0f, 2.0f, 1.0f);
	float4 result = v1 + v2;

	EXPECT_FLOAT_EQ(result.x, 5.0f);
	EXPECT_FLOAT_EQ(result.y, 5.0f);
	EXPECT_FLOAT_EQ(result.z, 5.0f);
	EXPECT_FLOAT_EQ(result.w, 5.0f);
}

TEST(float4, arithmetic_subtract)
{
	float4 v1(1.0f, 2.0f, 3.0f, 4.0f);
	float4 v2(0.1f, 0.2f, 0.3f, 0.4f);
	float4 result = v1 - v2;

	EXPECT_FLOAT_EQ(result.x, 0.9f);
	EXPECT_FLOAT_EQ(result.y, 1.8f);
	EXPECT_FLOAT_EQ(result.z, 2.7f);
	EXPECT_FLOAT_EQ(result.w, 3.6f);
}

TEST(float4, arithmetic_multiply)
{
	float4 v1(0.1f, 0.2f, 0.3f, 0.4f);
	float4 v2(0.3f);
	float4 result = v1 * v2;

	EXPECT_FLOAT_EQ(result.x, 0.03f);
	EXPECT_FLOAT_EQ(result.y, 0.06f);
	EXPECT_FLOAT_EQ(result.z, 0.09f);
	EXPECT_FLOAT_EQ(result.w, 0.12f);
}

TEST(float4, arithmetic_divide)
{
	float4 v1(0.1f, 0.2f, 0.3f, 0.4f);
	float4 v2(0.3f);
	float4 result = v1 / v2;

	EXPECT_NEAR(result.x, 0.33f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.66f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 1.33f, g_FloatEpsilon);
}

TEST(float4, intrinsics_abs)
{
	float4 v(-0.1f, -0.2f, -0.3f, -0.4f);
	float4 result = abs(v);

	EXPECT_FLOAT_EQ(result.x, 0.1f);
	EXPECT_FLOAT_EQ(result.y, 0.2f);
	EXPECT_FLOAT_EQ(result.z, 0.3f);
	EXPECT_FLOAT_EQ(result.w, 0.4f);
}

TEST(float4, intrinsics_dot)
{
	float4 v1(1.0f, 2.0f, 3.0f, 4.0f);
	float4 v2(0.1f, 0.2f, 0.3f, 0.4f);

	float4 result = dot(v1, v2);

	EXPECT_NEAR(result.x, 3.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 3.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 3.0f, g_FloatEpsilon);
}

TEST(float4, intrinsics_isinf)
{
	float4 v1(0.0f);
	float4 v2(XVMInfinity);
	float4 v3(XVMNegativeInfinity);
	float4 v4(0.0f, 0.0f, 0.0f, XVMFP32Infinity.f);

	bool result1 = isinf(v1);
	bool result2 = isinf(v2);
	bool result3 = isinf(v3);
	bool result4 = isinf(v4);

	EXPECT_FALSE(result1);
	EXPECT_TRUE(result2);
	EXPECT_TRUE(result3);
	EXPECT_TRUE(result4);
}

TEST(float4, intrinsics_isnan)
{
	float4 v1(XVMNaNQ);
	float4 v2(XVMInfinity);

	bool result1 = isnan(v1);
	bool result2 = isnan(v2);

	EXPECT_TRUE(result1);
	EXPECT_FALSE(result2);
}

TEST(float4, intrinsics_length)
{
	float4 v(1.0f, 2.0f, 3.0f, 4.0f);

	float4 result = length(v);

	EXPECT_NEAR(result.x, 5.477f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 5.477f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 5.477f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 5.477f, g_FloatEpsilon);
}

TEST(float4, intrinsics_lerp)
{
	float4 v1(1.0f, 3.0f, 5.0f, 7.0f);
	float4 v2(2.0f, 4.0f, 6.0f, 8.0f);

	float4 result = lerp(v1, v2, 0.5f);

	EXPECT_NEAR(result.x, 1.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 5.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 7.5f, g_FloatEpsilon);
}

TEST(float4, intrinsics_max)
{
	float4 v1(1.0f, 3.0f, 5.0f, 7.0f);
	float4 v2(2.0f, 4.0f, 6.0f, 8.0f);

	float4 result = max(v1, v2);

	EXPECT_NEAR(result.x, 2.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 4.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 6.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 8.0f, g_FloatEpsilon);
}

TEST(float4, intrinsics_min)
{
	float4 v1(1.0f, 3.0f, 5.0f, 7.0f);
	float4 v2(2.0f, 4.0f, 6.0f, 8.0f);

	float4 result = min(v1, v2);

	EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 5.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 7.0f, g_FloatEpsilon);
}

TEST(float4, intrinsics_normalize)
{
	float4 v(1.0f, 2.0f, 3.0f, 4.0f);

	float4 result = normalize(v);
	float4 len = length(result);

	EXPECT_NEAR(result.x, 0.183f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.365f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 0.548f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 0.730f, g_FloatEpsilon);

	EXPECT_NEAR(len.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(len.y, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(len.z, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(len.w, 1.0f, g_FloatEpsilon);
}

TEST(float4, intrinsics_sqrt)
{
	float4 v(1.0f, 2.0f, 3.0f, 4.0f);

	float4 result = sqrt(v);

	EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 1.414f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 1.732f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 2.0f, g_FloatEpsilon);
}
