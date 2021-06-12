#pragma once

TEST(Matrix4x4, ctor)
{
    Matrix4x4 m;

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

TEST(Matrix4x4, ctor_elements)
{
    Matrix4x4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

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

TEST(Matrix4x4, ctor_array)
{
    float array[16] = {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                       9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    Matrix4x4 m(array);

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

TEST(Matrix4x4, negation)
{
    Matrix4x4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 result = -m;

    // row 0
    EXPECT_FLOAT_EQ(result.r0.x, -1.0f);
    EXPECT_FLOAT_EQ(result.r0.y, -2.0f);
    EXPECT_FLOAT_EQ(result.r0.z, -3.0f);
    EXPECT_FLOAT_EQ(result.r0.w, -4.0f);
    // row 1
    EXPECT_FLOAT_EQ(result.r1.x, -5.0f);
    EXPECT_FLOAT_EQ(result.r1.y, -6.0f);
    EXPECT_FLOAT_EQ(result.r1.z, -7.0f);
    EXPECT_FLOAT_EQ(result.r1.w, -8.0f);
    // row 2
    EXPECT_FLOAT_EQ(result.r2.x, -9.0f);
    EXPECT_FLOAT_EQ(result.r2.y, -10.0f);
    EXPECT_FLOAT_EQ(result.r2.z, -11.0f);
    EXPECT_FLOAT_EQ(result.r2.w, -12.0f);
    // row 3
    EXPECT_FLOAT_EQ(result.r3.x, -13.0f);
    EXPECT_FLOAT_EQ(result.r3.y, -14.0f);
    EXPECT_FLOAT_EQ(result.r3.z, -15.0f);
    EXPECT_FLOAT_EQ(result.r3.w, -16.0f);
}

TEST(Matrix4x4, arithmetic_add)
{
    Matrix4x4 m1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 m2 =
        Matrix4x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
    Matrix4x4 result = m1 + m2;

    // row 0
    EXPECT_NEAR(result.r0.x, 1.1f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.y, 2.2f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.z, 3.3f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.w, 4.4f, g_FloatEpsilon);
    // row 1
    EXPECT_NEAR(result.r1.x, 5.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.y, 6.6f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.z, 7.7f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.w, 8.8f, g_FloatEpsilon);
    // row 2
    EXPECT_NEAR(result.r2.x, 9.9f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.y, 11.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.z, 12.1f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.w, 13.2f, g_FloatEpsilon);
    // row 3
    EXPECT_NEAR(result.r3.x, 14.3f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.y, 15.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.z, 16.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.w, 17.6f, g_FloatEpsilon);
}

TEST(Matrix4x4, arithmetic_subtract)
{
    Matrix4x4 m1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 m2 =
        Matrix4x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
    Matrix4x4 result = m1 - m2;

    // row 0
    EXPECT_NEAR(result.r0.x, 0.9f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.y, 1.8f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.z, 2.7f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.w, 3.6f, g_FloatEpsilon);
    // row 1
    EXPECT_NEAR(result.r1.x, 4.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.y, 5.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.z, 6.3f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.w, 7.2f, g_FloatEpsilon);
    // row 2
    EXPECT_NEAR(result.r2.x, 8.1f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.y, 9.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.z, 9.9f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.w, 10.8f, g_FloatEpsilon);
    // row 3
    EXPECT_NEAR(result.r3.x, 11.7f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.y, 12.6f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.z, 13.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.w, 14.4f, g_FloatEpsilon);
}

TEST(Matrix4x4, arithmetic_scalar_matrix_multiply)
{
    Matrix4x4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 result = m * 2.0f;

    // row 0
    EXPECT_NEAR(result.r0.x, 2.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.y, 4.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.z, 6.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.w, 8.0f, g_FloatEpsilon);
    // row 1
    EXPECT_NEAR(result.r1.x, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.y, 12.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.z, 14.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.w, 16.0f, g_FloatEpsilon);
    // row 2
    EXPECT_NEAR(result.r2.x, 18.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.y, 20.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.z, 22.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.w, 24.0f, g_FloatEpsilon);
    // row 3
    EXPECT_NEAR(result.r3.x, 26.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.y, 28.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.z, 30.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.w, 32.0f, g_FloatEpsilon);
}

TEST(Matrix4x4, arithmetic_vector_matrix_multiply)
{
    Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    Matrix4x4 m =
        Matrix4x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
    Vec4 result = mul(v, m);

    EXPECT_NEAR(result.x, 9.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 11.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.w, 12.0f, g_FloatEpsilon);
}

TEST(Matrix4x4, arithmetic_matrix_matrix_multiply)
{
    Matrix4x4 m1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 m2 =
        Matrix4x4(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
    Matrix4x4 result = m1 * m2;

    // row 0
    EXPECT_NEAR(result.r0.x, 9.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.y, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.z, 11.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.w, 12.0f, g_FloatEpsilon);
    // row 1
    EXPECT_NEAR(result.r1.x, 20.2f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.y, 22.8f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.z, 25.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.w, 28.0f, g_FloatEpsilon);
    // row 2
    EXPECT_NEAR(result.r2.x, 31.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.y, 35.6f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.z, 39.8f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.w, 44.0f, g_FloatEpsilon);
    // row 3
    EXPECT_NEAR(result.r3.x, 42.6f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.y, 48.4f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.z, 54.2f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.w, 60.0f, g_FloatEpsilon);
}

TEST(Matrix4x4, arithmetic_matrix_scalar_divide)
{
    Matrix4x4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 result = m / 2.0f;

    // row 0
    EXPECT_NEAR(result.r0.x, 0.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.y, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.z, 1.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.w, 2.0f, g_FloatEpsilon);
    // row 1
    EXPECT_NEAR(result.r1.x, 2.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.y, 3.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.z, 3.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.w, 4.0f, g_FloatEpsilon);
    // row 2
    EXPECT_NEAR(result.r2.x, 4.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.y, 5.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.z, 5.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.w, 6.0f, g_FloatEpsilon);
    // row 3
    EXPECT_NEAR(result.r3.x, 6.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.y, 7.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.z, 7.5f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.w, 8.0f, g_FloatEpsilon);
}

TEST(Matrix4x4, intrinsics_transpose)
{
    Matrix4x4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4x4 result = transpose(m);

    // row 0
    EXPECT_NEAR(result.r0.x, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.y, 5.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.z, 9.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r0.w, 13.0f, g_FloatEpsilon);
    // row 1
    EXPECT_NEAR(result.r1.x, 2.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.y, 6.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.z, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r1.w, 14.0f, g_FloatEpsilon);
    // row 2
    EXPECT_NEAR(result.r2.x, 3.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.y, 7.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.z, 11.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r2.w, 15.0f, g_FloatEpsilon);
    // row 3
    EXPECT_NEAR(result.r3.x, 4.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.y, 8.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.z, 12.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.r3.w, 16.0f, g_FloatEpsilon);
}

TEST(Matrix4x4, intrinsics_translation)
{
    Vec4 v      = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
    Matrix4x4 m = translation(1.0f, 2.0f, 3.0f);
    Vec4 result = mul(v, m);

    EXPECT_NEAR(result.x, 1.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 2.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 3.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.w, 1.0f, g_FloatEpsilon);
}

TEST(Matrix4x4, intrinsics_scale)
{
    Vec4 v      = Vec4(5.0f, 5.0f, 5.0f, 1.0f);
    Matrix4x4 m = scale(2.0f, 2.0f, 2.0f);
    Vec4 result = mul(v, m);

    EXPECT_NEAR(result.x, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.y, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.z, 10.0f, g_FloatEpsilon);
    EXPECT_NEAR(result.w, 1.0f, g_FloatEpsilon);
}
