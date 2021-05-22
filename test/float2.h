#pragma once

TEST(float2, ctor)
{
	float2 v;

	EXPECT_FLOAT_EQ(v.x, 0.0f);
	EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST(float2, ctor_component)
{
	float2 v(1.0f, 2.0f);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 2.0f);
}

TEST(float2, ctor_scalar)
{
	float2 v(1.0f);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 1.0f);
}

TEST(float2, ctor_array)
{
	float array[2] = { 1.0f, 2.0f };
	float2 v(array);

	EXPECT_FLOAT_EQ(v.x, 1.0f);
	EXPECT_FLOAT_EQ(v.y, 2.0f);
}

TEST(float2, negation)
{
	float2 v(1.0f, 2.0f);
	v = -v;

	EXPECT_FLOAT_EQ(v.x, -1.0f);
	EXPECT_FLOAT_EQ(v.y, -2.0f);
}

TEST(float2, arithmetic_add)
{
	float2 v1(1.0f, 2.0f);
	float2 v2(4.0f, 3.0f);
	float2 result = v1 + v2;

	EXPECT_FLOAT_EQ(result.x, 5.0f);
	EXPECT_FLOAT_EQ(result.y, 5.0f);
}

TEST(float2, arithmetic_subtract)
{
	float2 v1(1.0f, 2.0f);
	float2 v2(0.1f, 0.2f);
	float2 result = v1 - v2;

	EXPECT_FLOAT_EQ(result.x, 0.9f);
	EXPECT_FLOAT_EQ(result.y, 1.8f);
}

TEST(float2, arithmetic_multiply)
{
	float2 v1(0.1f, 0.2f);
	float2 v2(0.3f);
	float2 result = v1 * v2;

	EXPECT_FLOAT_EQ(result.x, 0.03f);
	EXPECT_FLOAT_EQ(result.y, 0.06f);
}

TEST(float2, arithmetic_divide)
{
	float2 v1(0.1f, 0.2f);
	float2 v2(0.3f);
	float2 result = v1 / v2;

	EXPECT_NEAR(result.x, 0.33f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.66f, g_FloatEpsilon);
}

TEST(float2, intrinsics_abs)
{
	float2 v(-0.1f, -0.2f);
	float2 result = abs(v);

	EXPECT_FLOAT_EQ(result.x, 0.1f);
	EXPECT_FLOAT_EQ(result.y, 0.2f);
}

TEST(float2, intrinsics_all)
{
	float2 v1(0.0f, 0.0f);
	float2 v2(0.0f, 1.0f);
	float2 v3(1.0f, 2.0f);
	bool result1 = all(v1);
	bool result2 = all(v2);
	bool result3 = all(v3);

	EXPECT_FALSE(result1);
	EXPECT_FALSE(result2);
	EXPECT_TRUE(result3);
}

TEST(float2, intrinsics_any)
{
	float2 v1(0.0f, 0.0f);
	float2 v2(0.0f, 1.0f);
	float2 v3(1.0f, 2.0f);
	bool result1 = any(v1);
	bool result2 = any(v2);
	bool result3 = any(v3);

	EXPECT_FALSE(result1);
	EXPECT_TRUE(result2);
	EXPECT_TRUE(result3);
}

TEST(float2, intrinsics_dot)
{
	float2 v1(1.0f, 2.0f);
	float2 v2(0.1f, 0.2f);

	float2 result = dot(v1, v2);

	EXPECT_NEAR(result.x, 0.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.5f, g_FloatEpsilon);
}

TEST(float2, intrinsics_isinf)
{
	float2 v1(0.0f);
	float2 v2(XVMInfinity);
	float2 v3(XVMNegativeInfinity);
	float2 v4(0.0f, XVMFP32Infinity.f);

	bool result1 = isinf(v1);
	bool result2 = isinf(v2);
	bool result3 = isinf(v3);
	bool result4 = isinf(v4);

	EXPECT_FALSE(result1);
	EXPECT_TRUE(result2);
	EXPECT_TRUE(result3);
	EXPECT_TRUE(result4);
}

TEST(float2, intrinsics_isnan)
{
	float2 v1(XVMNaNQ);
	float2 v2(XVMInfinity);

	bool result1 = isnan(v1);
	bool result2 = isnan(v2);

	EXPECT_TRUE(result1);
	EXPECT_FALSE(result2);
}

TEST(float2, intrinsics_length)
{
	float2 v(1.0f, 2.0f);

	float2 result = length(v);

	EXPECT_NEAR(result.x, 2.236f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 2.236f, g_FloatEpsilon);
}

TEST(float2, intrinsics_lerp)
{
	float2 v1(1.0f, 3.0f);
	float2 v2(2.0f, 4.0f);

	float2 result = lerp(v1, v2, 0.5f);

	EXPECT_NEAR(result.x, 1.5f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.5f, g_FloatEpsilon);
}

TEST(float2, intrinsics_max)
{
	float2 v1(1.0f, 3.0f);
	float2 v2(2.0f, 4.0f);

	float2 result = max(v1, v2);

	EXPECT_NEAR(result.x, 2.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 4.0f, g_FloatEpsilon);
}

TEST(float2, intrinsics_min)
{
	float2 v1(1.0f, 3.0f);
	float2 v2(2.0f, 4.0f);

	float2 result = min(v1, v2);

	EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 3.0f, g_FloatEpsilon);
}

TEST(float2, intrinsics_normalize)
{
	float2 v(1.0f, 2.0f);

	float2 result = normalize(v);
	float2 len = length(result);

	EXPECT_NEAR(result.x, 0.447f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.894f, g_FloatEpsilon);

	EXPECT_NEAR(len.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(len.y, 1.0f, g_FloatEpsilon);
}

TEST(float2, intrinsics_sqrt)
{
	float2 v(1.0f, 2.0f);

	float2 result = sqrt(v);

	EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 1.414f, g_FloatEpsilon);
}
