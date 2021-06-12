#pragma once

TEST(Quaternion, arithmetic_multiply)
{
	Quaternion q1(2.0f, 3.0f, 4.0f, 1.0f);
	Quaternion q2(3.0f, 4.0f, 5.0f, 2.0f);
	Quaternion result = q1 * q2;

	EXPECT_FLOAT_EQ(result.x, 6.0f);
	EXPECT_FLOAT_EQ(result.y, 12.0f);
	EXPECT_FLOAT_EQ(result.z, 12.0f);
	EXPECT_FLOAT_EQ(result.w, -36.0f);
}

TEST(Quaternion, intrinsics_conjugate)
{
	Quaternion q(2.0f, 3.0f, 4.0f, 1.0f);
	Quaternion result = conjugate(q);

	EXPECT_NEAR(result.x, -2.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, -3.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, -4.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 1.0f, g_FloatEpsilon);
}

TEST(Quaternion, intrinsics_inverse)
{
	Quaternion q(0.577f, 0.577f, 0.577f, 1.0f);
	Quaternion result = inverse(q);

	EXPECT_NEAR(result.x, -0.288f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, -0.288f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, -0.288f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 0.5003f, g_FloatEpsilon);
}

TEST(Quaternion, intrinsics_dot)
{
	Quaternion q1(2.0f, 3.0f, 4.0f, 1.0f);
	Quaternion q2(3.0f, 4.0f, 5.0f, 2.0f);
	Vec4	   result = dot(q1, q2);

	EXPECT_NEAR(result.x, 40.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 40.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 40.0f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 40.0f, g_FloatEpsilon);
}

TEST(Quaternion, intrinsics_length)
{
	{
		Quaternion q(4.0f, 4.0f, 4.0f, 1.0f);
		Vec4	   result = length(q);

		EXPECT_NEAR(result.x, 7.0f, g_FloatEpsilon);
		EXPECT_NEAR(result.y, 7.0f, g_FloatEpsilon);
		EXPECT_NEAR(result.z, 7.0f, g_FloatEpsilon);
		EXPECT_NEAR(result.w, 7.0f, g_FloatEpsilon);
	}
	{
		Quaternion q(-2.0f, 3.0f, -4.0f, 2.0f);
		Vec4	   result = length(q);

		float answer = std::sqrt(33.0f);
		EXPECT_NEAR(result.x, answer, g_FloatEpsilon);
		EXPECT_NEAR(result.y, answer, g_FloatEpsilon);
		EXPECT_NEAR(result.z, answer, g_FloatEpsilon);
		EXPECT_NEAR(result.w, answer, g_FloatEpsilon);
	}
	{
		Quaternion q(-2.0f, 5.0f, -6.0f, 1.0f);
		Vec4	   result = length(q);

		float answer = std::sqrt(66.0f);
		EXPECT_NEAR(result.x, answer, g_FloatEpsilon);
		EXPECT_NEAR(result.y, answer, g_FloatEpsilon);
		EXPECT_NEAR(result.z, answer, g_FloatEpsilon);
		EXPECT_NEAR(result.w, answer, g_FloatEpsilon);
	}
}

TEST(Quaternion, intrinsics_normalize)
{
	Quaternion q(4.0f, 4.0f, 4.0f, 1.0f);
	Quaternion result = normalize(q);

	EXPECT_NEAR(result.x, 0.571f, g_FloatEpsilon);
	EXPECT_NEAR(result.y, 0.571f, g_FloatEpsilon);
	EXPECT_NEAR(result.z, 0.571f, g_FloatEpsilon);
	EXPECT_NEAR(result.w, 0.142f, g_FloatEpsilon);
}
