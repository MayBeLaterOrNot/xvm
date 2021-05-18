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
	constexpr float episilon = 1e-2f;

	float3 v1(0.1f, 0.2f, 0.3f);
	float3 v2(0.3f);
	float3 result = v1 / v2;

	EXPECT_NEAR(result.x, 0.33f, episilon);
	EXPECT_NEAR(result.y, 0.66f, episilon);
	EXPECT_NEAR(result.z, 1.0f, episilon);
}
