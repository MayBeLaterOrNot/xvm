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
	float3 v1(-0.1f, -0.2f, -0.3f);
	float3 result = abs(v1);

	EXPECT_FLOAT_EQ(result.x, 0.1f);
	EXPECT_FLOAT_EQ(result.y, 0.2f);
	EXPECT_FLOAT_EQ(result.z, 0.3f);
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
