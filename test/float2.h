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