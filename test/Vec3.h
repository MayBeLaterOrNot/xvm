#pragma once

TEST(Vec3, ctor)
{
    Vec3 v;

    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vec3, ctor_component)
{
    Vec3 v(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vec3, ctor_scalar)
{
    Vec3 v(1.0f);

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
    EXPECT_FLOAT_EQ(v.z, 1.0f);
}

TEST(Vec3, ctor_array)
{
    float array[3] = {1.0f, 2.0f, 3.0f};
    Vec3 v(array);

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vec3, negation)
{
    Vec3 v(1.0f, 2.0f, 3.0f);
    v = -v;

    EXPECT_FLOAT_EQ(v.x, -1.0f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
    EXPECT_FLOAT_EQ(v.z, -3.0f);
}

TEST(Vec3, arithmetic_add)
{
    Vec3 v1(1.0f, 2.0f, 3.0f);
    Vec3 v2(4.0f, 3.0f, 2.0f);
    Vec3 result = v1 + v2;

    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 5.0f);
    EXPECT_FLOAT_EQ(result.z, 5.0f);
}

TEST(Vec3, arithmetic_subtract)
{
    Vec3 v1(1.0f, 2.0f, 3.0f);
    Vec3 v2(0.1f, 0.2f, 0.3f);
    Vec3 result = v1 - v2;

    EXPECT_FLOAT_EQ(result.x, 0.9f);
    EXPECT_FLOAT_EQ(result.y, 1.8f);
    EXPECT_FLOAT_EQ(result.z, 2.7f);
}

TEST(Vec3, arithmetic_multiply)
{
    Vec3 v1(0.1f, 0.2f, 0.3f);
    Vec3 v2(0.3f);
    Vec3 result = v1 * v2;

    EXPECT_FLOAT_EQ(result.x, 0.03f);
    EXPECT_FLOAT_EQ(result.y, 0.06f);
    EXPECT_FLOAT_EQ(result.z, 0.09f);
}

TEST(Vec3, arithmetic_divide)
{
    Vec3 v1(0.1f, 0.2f, 0.3f);
    Vec3 v2(0.3f);
    Vec3 result = v1 / v2;

    EXPECT_NEAR(result.x, 0.33f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 0.66f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 1.0f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_abs)
{
    Vec3 v(-0.1f, -0.2f, -0.3f);
    Vec3 result = abs(v);

    EXPECT_FLOAT_EQ(result.x, 0.1f);
    EXPECT_FLOAT_EQ(result.y, 0.2f);
    EXPECT_FLOAT_EQ(result.z, 0.3f);
}

TEST(Vec3, intrinsics_all)
{
    Vec3 v1(0.0f, 0.0f, 0.0f);
    Vec3 v2(0.0f, 0.0f, 1.0f);
    Vec3 v3(1.0f, 2.0f, 3.0f);
    bool result1 = all(v1);
    bool result2 = all(v2);
    bool result3 = all(v3);

    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
    EXPECT_TRUE(result3);
}

TEST(Vec3, intrinsics_any)
{
    Vec3 v1(0.0f, 0.0f, 0.0f);
    Vec3 v2(0.0f, 0.0f, 1.0f);
    Vec3 v3(1.0f, 2.0f, 3.0f);
    bool result1 = any(v1);
    bool result2 = any(v2);
    bool result3 = any(v3);

    EXPECT_FALSE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
}

TEST(Vec3, intrinsics_clamp)
{
    Vec3 v1(2.0f);
    Vec3 v2(-1.0f, 2.0f, 0.5f);

    Vec3 result1 = clamp(v1, 0.0f, 1.0f);
    Vec3 result2 = clamp(v2, 0.0f, 1.0f);

    EXPECT_NEAR(result1.x, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result1.y, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result1.z, 1.0f, g_FloatEpsilon);

    EXPECT_NEAR(result2.x, 0.0f, g_FloatEpsilon);
    EXPECT_NEAR(result2.y, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result2.z, 0.5f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_cross)
{
    Vec3 v1     = {5.2f, 3.4f, 2.0f};
    Vec3 v2     = {0.2f, 1.0f, 2.5f};

    Vec3 result = cross(v1, v2);

    EXPECT_NEAR(result.x, 6.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, -12.6f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 4.52f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_dot)
{
    Vec3 v1(1.0f, 2.0f, 3.0f);
    Vec3 v2(0.1f, 0.2f, 0.3f);

    Vec3 result = dot(v1, v2);

    EXPECT_NEAR(result.x, 1.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 1.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 1.4f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_isfinite)
{
    Vec3 v1(0.0f);
    Vec3 v2(XVMInfinity);
    Vec3 v3(XVMNegativeInfinity);
    Vec3 v4(0.0f, 0.0f, XVMFP32Infinity.f);

    bool result1 = isfinite(v1);
    bool result2 = isfinite(v2);
    bool result3 = isfinite(v3);
    bool result4 = isfinite(v4);

    EXPECT_TRUE(result1);
    EXPECT_FALSE(result2);
    EXPECT_FALSE(result3);
    EXPECT_FALSE(result4);
}

TEST(Vec3, intrinsics_isinf)
{
    Vec3 v1(0.0f);
    Vec3 v2(XVMInfinity);
    Vec3 v3(XVMNegativeInfinity);
    Vec3 v4(0.0f, 0.0f, XVMFP32Infinity.f);

    bool result1 = isinf(v1);
    bool result2 = isinf(v2);
    bool result3 = isinf(v3);
    bool result4 = isinf(v4);

    EXPECT_FALSE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
    EXPECT_TRUE(result4);
}

TEST(Vec3, intrinsics_isnan)
{
    Vec3 v1(XVMNaNQ);
    Vec3 v2(XVMInfinity);

    bool result1 = isnan(v1);
    bool result2 = isnan(v2);

    EXPECT_TRUE(result1);
    EXPECT_FALSE(result2);
}

TEST(Vec3, intrinsics_length)
{
    Vec3 v(1.0f, 2.0f, 3.0f);

    Vec3 result = length(v);

    EXPECT_NEAR(result.x, 3.741f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 3.741f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 3.741f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_lerp)
{
    Vec3 v1(1.0f, 3.0f, 5.0f);
    Vec3 v2(2.0f, 4.0f, 6.0f);

    Vec3 result = lerp(v1, v2, 0.5f);

    EXPECT_NEAR(result.x, 1.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 3.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 5.5f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_max)
{
    Vec3 v1(1.0f, 3.0f, 5.0f);
    Vec3 v2(2.0f, 4.0f, 6.0f);

    Vec3 result = max(v1, v2);

    EXPECT_NEAR(result.x, 2.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 4.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 6.0f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_min)
{
    Vec3 v1(1.0f, 3.0f, 5.0f);
    Vec3 v2(2.0f, 4.0f, 6.0f);

    Vec3 result = min(v1, v2);

    EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 3.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 5.0f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_normalize)
{
    Vec3 v(1.0f, 2.0f, 3.0f);

    Vec3 result = normalize(v);
    Vec3 len    = length(result);

    EXPECT_NEAR(result.x, 0.267f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 0.535f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 0.802f, g_FloatEpsilon);

    EXPECT_NEAR(len.x, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(len.y, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(len.z, 1.0f, g_FloatEpsilon);
}

TEST(Vec3, intrinsics_sqrt)
{
    Vec3 v(1.0f, 2.0f, 3.0f);

    Vec3 result = sqrt(v);

    EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 1.414f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 1.732f, g_FloatEpsilon);
}
