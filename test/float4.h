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