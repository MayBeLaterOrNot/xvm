#pragma once

TEST(float4x4, ctor)
{
	float4x4 m;

	// row 0
	EXPECT_FLOAT_EQ(m.r0.x, 1.0f);
	EXPECT_FLOAT_EQ(m.r0.y, 0.0f);
	EXPECT_FLOAT_EQ(m.r0.z, 0.0f);
	EXPECT_FLOAT_EQ(m.r0.w, 0.0f);
	// row 1
	EXPECT_FLOAT_EQ(m.r1.x, 0.0f);
	EXPECT_FLOAT_EQ(m.r1.y, 1.0f);
	EXPECT_FLOAT_EQ(m.r1.z, 0.0f);
	EXPECT_FLOAT_EQ(m.r1.w, 0.0f);
	// row 2
	EXPECT_FLOAT_EQ(m.r2.x, 0.0f);
	EXPECT_FLOAT_EQ(m.r2.y, 0.0f);
	EXPECT_FLOAT_EQ(m.r2.z, 1.0f);
	EXPECT_FLOAT_EQ(m.r2.w, 0.0f);
	// row 3
	EXPECT_FLOAT_EQ(m.r3.x, 0.0f);
	EXPECT_FLOAT_EQ(m.r3.y, 0.0f);
	EXPECT_FLOAT_EQ(m.r3.z, 0.0f);
	EXPECT_FLOAT_EQ(m.r3.w, 1.0f);
}

TEST(float4x4, ctor_elements)
{
	float4x4 m(
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f);

	// row 0
	EXPECT_FLOAT_EQ(m.r0.x, 1.0f);
	EXPECT_FLOAT_EQ(m.r0.y, 2.0f);
	EXPECT_FLOAT_EQ(m.r0.z, 3.0f);
	EXPECT_FLOAT_EQ(m.r0.w, 4.0f);
	// row 1
	EXPECT_FLOAT_EQ(m.r1.x, 5.0f);
	EXPECT_FLOAT_EQ(m.r1.y, 6.0f);
	EXPECT_FLOAT_EQ(m.r1.z, 7.0f);
	EXPECT_FLOAT_EQ(m.r1.w, 8.0f);
	// row 2
	EXPECT_FLOAT_EQ(m.r2.x, 9.0f);
	EXPECT_FLOAT_EQ(m.r2.y, 10.0f);
	EXPECT_FLOAT_EQ(m.r2.z, 11.0f);
	EXPECT_FLOAT_EQ(m.r2.w, 12.0f);
	// row 3
	EXPECT_FLOAT_EQ(m.r3.x, 13.0f);
	EXPECT_FLOAT_EQ(m.r3.y, 14.0f);
	EXPECT_FLOAT_EQ(m.r3.z, 15.0f);
	EXPECT_FLOAT_EQ(m.r3.w, 16.0f);
}

TEST(float4x4, ctor_array)
{
	float array[16] =
	{
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	};
	float4x4 m(array);

	// row 0
	EXPECT_FLOAT_EQ(m.r0.x, 1.0f);
	EXPECT_FLOAT_EQ(m.r0.y, 2.0f);
	EXPECT_FLOAT_EQ(m.r0.z, 3.0f);
	EXPECT_FLOAT_EQ(m.r0.w, 4.0f);
	// row 1
	EXPECT_FLOAT_EQ(m.r1.x, 5.0f);
	EXPECT_FLOAT_EQ(m.r1.y, 6.0f);
	EXPECT_FLOAT_EQ(m.r1.z, 7.0f);
	EXPECT_FLOAT_EQ(m.r1.w, 8.0f);
	// row 2
	EXPECT_FLOAT_EQ(m.r2.x, 9.0f);
	EXPECT_FLOAT_EQ(m.r2.y, 10.0f);
	EXPECT_FLOAT_EQ(m.r2.z, 11.0f);
	EXPECT_FLOAT_EQ(m.r2.w, 12.0f);
	// row 3
	EXPECT_FLOAT_EQ(m.r3.x, 13.0f);
	EXPECT_FLOAT_EQ(m.r3.y, 14.0f);
	EXPECT_FLOAT_EQ(m.r3.z, 15.0f);
	EXPECT_FLOAT_EQ(m.r3.w, 16.0f);
}
