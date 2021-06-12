namespace xvm
{
INTRINSICS_INLINE Matrix4x4::Matrix4x4()
{
	r[0] = XVMIdentityR0;
	r[1] = XVMIdentityR1;
	r[2] = XVMIdentityR2;
	r[3] = XVMIdentityR3;
}

INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV conjugate(Quaternion q)
{
	return _mm_xor_ps(q.vec, XVMMaskXYZNegative);
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV inverse(Quaternion q)
{
	// q*qq^-1 = q*
	// |q|^2q^-1 = q*
	// q^-1 = q* / |q|^2
	Quaternion qstar	= conjugate(q);
	Vec4	   lengthSq = length(q);
	lengthSq *= lengthSq;

	return _mm_div_ps(qstar.vec, lengthSq.vec);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV operator-(Vec2 v)
{
	return _mm_xor_ps(v.vec, XVMMaskNegative);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV operator-(Vec3 v)
{
	return _mm_xor_ps(v.vec, XVMMaskNegative);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV operator-(Vec4 v)
{
	return _mm_xor_ps(v.vec, XVMMaskNegative);
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator-(Matrix4x4 m)
{
	__m128 nx = _mm_xor_ps(m.r[0], XVMMaskNegative);
	__m128 ny = _mm_xor_ps(m.r[1], XVMMaskNegative);
	__m128 nz = _mm_xor_ps(m.r[2], XVMMaskNegative);
	__m128 nw = _mm_xor_ps(m.r[3], XVMMaskNegative);
	return Matrix4x4(nx, ny, nz, nw);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV operator+(Vec2 v1, Vec2 v2)
{
	return { _mm_add_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV operator+(Vec3 v1, Vec3 v2)
{
	return { _mm_add_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV operator+(Vec4 v1, Vec4 v2)
{
	return { _mm_add_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV operator+(Quaternion q1, Quaternion q2)
{
	return { _mm_add_ps(q1.vec, q2.vec) };
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator+(Matrix4x4 m1, Matrix4x4 m2)
{
	__m128 r0 = _mm_add_ps(m1.r[0], m2.r[0]);
	__m128 r1 = _mm_add_ps(m1.r[1], m2.r[1]);
	__m128 r2 = _mm_add_ps(m1.r[2], m2.r[2]);
	__m128 r3 = _mm_add_ps(m1.r[3], m2.r[3]);
	return Matrix4x4(r0, r1, r2, r3);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV operator-(Vec2 v1, Vec2 v2)
{
	return { _mm_sub_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV operator-(Vec3 v1, Vec3 v2)
{
	return { _mm_sub_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV operator-(Vec4 v1, Vec4 v2)
{
	return { _mm_sub_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV operator-(Quaternion q1, Quaternion q2)
{
	return { _mm_sub_ps(q1.vec, q2.vec) };
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator-(Matrix4x4 m1, Matrix4x4 m2)
{
	__m128 r0 = _mm_sub_ps(m1.r[0], m2.r[0]);
	__m128 r1 = _mm_sub_ps(m1.r[1], m2.r[1]);
	__m128 r2 = _mm_sub_ps(m1.r[2], m2.r[2]);
	__m128 r3 = _mm_sub_ps(m1.r[3], m2.r[3]);
	return Matrix4x4(r0, r1, r2, r3);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV operator*(Vec2 v1, Vec2 v2)
{
	return { _mm_mul_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV operator*(Vec3 v1, Vec3 v2)
{
	return { _mm_mul_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV operator*(Vec4 v1, Vec4 v2)
{
	return { _mm_mul_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV operator*(Quaternion q1, Quaternion q2)
{
#if 0
		// [s_a, a] [s_b, b] = [s_a * s_b − a · b, s_a * b + s_b * a + a×b]
		// where s_ is the real part, a,b is vector part

		// Splat q1.w
		__m128 s_a = INTRINSICS_SWIZZLE_PS(q1.vec, _MM_SHUFFLE(3, 3, 3, 3));
		// Splat q2.w
		__m128 s_b = INTRINSICS_SWIZZLE_PS(q2.vec, _MM_SHUFFLE(3, 3, 3, 3));

		// a o b, copy-pasta from dot(Vec3, Vec3) to keep consistency
		__m128 dot = _mm_mul_ps(q1.vec, q2.vec);
		__m128 shuff = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(2, 2, 2, 1)); // { y, z, z, z }
		dot = _mm_add_ss(dot, shuff); // { x+y, ?, ?, ? }
		shuff = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(2, 2, 2, 2)); // { z, z, z, z }
		dot = _mm_add_ss(dot, shuff); // { x+y+z, ?, ?, ? }
		__m128 aob = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0)); // splat fp0

		// s_a * s_b − a · b
		// real part
		__m128 real = _mm_sub_ps(_mm_mul_ps(s_a, s_b), aob);

		// a x b, copy-pasta from cross(Vec3, Vec3) to keep consistency
		__m128 v1_yzx = INTRINSICS_SWIZZLE_PS(q1.vec, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 v2_yzx = INTRINSICS_SWIZZLE_PS(q2.vec, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 cross = _mm_sub_ps(_mm_mul_ps(q1.vec, v2_yzx), _mm_mul_ps(v1_yzx, q2.vec));
		__m128 axb = INTRINSICS_SWIZZLE_PS(cross, _MM_SHUFFLE(3, 0, 2, 1));

		// vector part
		__m128 s_ab = _mm_mul_ps(s_a, q2.vec);
		__m128 s_ba = _mm_mul_ps(s_b, q1.vec);
		__m128 vect = _mm_add_ps(s_ab, s_ba);
		vect = _mm_add_ps(vect, axb);

		real = INTRINSICS_SHUFFLE_PS(real, vect, _MM_SHUFFLE(2, 2, 0, 0)); // { w, w, z, z }

		vect = INTRINSICS_SWIZZLE_PS(vect, _MM_SHUFFLE(2, 2, 1, 0)); // { x, y, z, z }

		return INTRINSICS_SHUFFLE_PS(vect, real, _MM_SHUFFLE(0, 2, 1, 0)); // { x, y, z, w }
#endif
	// Matrix implementation, refer to Eq 5.14, Section 5.17
	// [q1.w -q1.x -q1.y -q1.z] [q2.w]
	// [q1.x  q1.w -q1.z  q1.y] [q2.x]
	// [q1.y  q1.z  q1.w -q1.x] [q2.y]
	// [q1.z -q1.y  q1.x  q1.w] [q2.z]

	// Moved real part to last row and switched col0 and col3
	// [ q1.w -q1.z  q1.y q1.x] [q2.x]
	// [ q1.z  q1.w -q1.x q1.y] [q2.y]
	// [-q1.y  q1.x  q1.w q1.z] [q2.z]
	// [-q1.x -q1.y -q1.z q1.w] [q2.w]

	// Transpose matrices
	//							 [ q1.w  q1.z -q1.y -q1.x]
	// [q2.x, q2.y, q2.z q2.w] * [-q1.z  q1.w  q1.x -q1.y]
	//							 [ q1.y -q1.x  q1.w -q1.z]
	//							 [ q1.x  q1.y  q1.z  q1.w]

	constexpr XVM_UI32 R0SignMask = { { { 0x00000000, 0x00000000, 0x80000000, 0x80000000 } } };
	constexpr XVM_UI32 R1SignMask = { { { 0x80000000, 0x00000000, 0x00000000, 0x80000000 } } };
	constexpr XVM_UI32 R2SignMask = { { { 0x00000000, 0x80000000, 0x00000000, 0x80000000 } } };

	// Splat all q2 components
	__m128 x = INTRINSICS_SWIZZLE_PS(q2.vec, _MM_SHUFFLE(0, 0, 0, 0)); // [x, x, x, x]
	__m128 y = INTRINSICS_SWIZZLE_PS(q2.vec, _MM_SHUFFLE(1, 1, 1, 1)); // [y, y, y, y]
	__m128 z = INTRINSICS_SWIZZLE_PS(q2.vec, _MM_SHUFFLE(2, 2, 2, 2)); // [z, z, z, z]
	__m128 w = INTRINSICS_SWIZZLE_PS(q2.vec, _MM_SHUFFLE(3, 3, 3, 3)); // [w, w, w, w]

	__m128 r0 = INTRINSICS_SWIZZLE_PS(q1.vec, _MM_SHUFFLE(0, 1, 2, 3));
	r0		  = _mm_xor_ps(r0, R0SignMask);
	__m128 r1 = INTRINSICS_SWIZZLE_PS(q1.vec, _MM_SHUFFLE(1, 0, 3, 2));
	r1		  = _mm_xor_ps(r1, R1SignMask);
	__m128 r2 = INTRINSICS_SWIZZLE_PS(q1.vec, _MM_SHUFFLE(2, 3, 0, 1));
	r2		  = _mm_xor_ps(r2, R2SignMask);
	__m128 r3 = q1.vec;

	x = _mm_mul_ps(x, r0); // mul x by r0
	y = _mm_mul_ps(y, r1); // mul y by r1
	z = _mm_mul_ps(z, r2); // mul z by r2
	w = _mm_mul_ps(w, r3); // mul w by r3
	// sum
	x = _mm_add_ps(x, y);	 // x+y
	z = _mm_add_ps(z, w);	 // z+w;
	return _mm_add_ps(x, z); // x+y+z+w
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV operator*(Quaternion q, float scalar)
{
	// q = [s, v]
	// λ = [λ, 0]
	// λq = [λ, 0][s, v]
	// = [λs, λv]
	return { _mm_mul_ps(q.vec, _mm_set1_ps(scalar)) };
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV operator*(float scalar, Quaternion q)
{
	// scalar multiplication is commutative
	return q * scalar;
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator*(Matrix4x4 m, float scalar)
{
	__m128 s  = _mm_set1_ps(scalar);
	__m128 r0 = _mm_mul_ps(m.r[0], s);
	__m128 r1 = _mm_mul_ps(m.r[1], s);
	__m128 r2 = _mm_mul_ps(m.r[2], s);
	__m128 r3 = _mm_mul_ps(m.r[3], s);
	return Matrix4x4(r0, r1, r2, r3);
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator*(float scalar, Matrix4x4 m)
{
	// scalar multiplication is commutative
	return m * scalar;
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator*(Matrix4x4 m1, Matrix4x4 m2)
{
	return mul(m1, m2);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV operator/(Vec2 v1, Vec2 v2)
{
	return { _mm_div_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV operator/(Vec3 v1, Vec3 v2)
{
	return { _mm_div_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV operator/(Vec4 v1, Vec4 v2)
{
	return { _mm_div_ps(v1.vec, v2.vec) };
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV operator/(Matrix4x4 m, float scalar)
{
	__m128 s  = _mm_set1_ps(scalar);
	__m128 r0 = _mm_div_ps(m.r[0], s);
	__m128 r1 = _mm_div_ps(m.r[1], s);
	__m128 r2 = _mm_div_ps(m.r[2], s);
	__m128 r3 = _mm_div_ps(m.r[3], s);
	return Matrix4x4(r0, r1, r2, r3);
}

INTRINSICS_INLINE Vec2& INTRINSICS_CALLCONV operator+=(Vec2& v1, Vec2 v2)
{
	v1 = v1 + v2;
	return v1;
}
INTRINSICS_INLINE Vec3& INTRINSICS_CALLCONV operator+=(Vec3& v1, Vec3 v2)
{
	v1 = v1 + v2;
	return v1;
}
INTRINSICS_INLINE Vec4& INTRINSICS_CALLCONV operator+=(Vec4& v1, Vec4 v2)
{
	v1 = v1 + v2;
	return v1;
}
INTRINSICS_INLINE Quaternion& INTRINSICS_CALLCONV operator+=(Quaternion& q1, Quaternion q2)
{
	q1 = q1 + q2;
	return q1;
}
INTRINSICS_INLINE Matrix4x4& INTRINSICS_CALLCONV operator+=(Matrix4x4& m1, Matrix4x4 m2)
{
	m1 = m1 + m2;
	return m1;
}

INTRINSICS_INLINE Vec2& INTRINSICS_CALLCONV operator-=(Vec2& v1, Vec2 v2)
{
	v1 = v1 - v2;
	return v1;
}
INTRINSICS_INLINE Vec3& INTRINSICS_CALLCONV operator-=(Vec3& v1, Vec3 v2)
{
	v1 = v1 - v2;
	return v1;
}
INTRINSICS_INLINE Vec4& INTRINSICS_CALLCONV operator-=(Vec4& v1, Vec4 v2)
{
	v1 = v1 - v2;
	return v1;
}
INTRINSICS_INLINE Quaternion& INTRINSICS_CALLCONV operator-=(Quaternion& q1, Quaternion q2)
{
	q1 = q1 - q2;
	return q1;
}
INTRINSICS_INLINE Matrix4x4& INTRINSICS_CALLCONV operator-=(Matrix4x4& m1, Matrix4x4 m2)
{
	m1 = m1 - m2;
	return m1;
}

INTRINSICS_INLINE Vec2& INTRINSICS_CALLCONV operator*=(Vec2& v1, Vec2 v2)
{
	v1 = v1 * v2;
	return v1;
}
INTRINSICS_INLINE Vec3& INTRINSICS_CALLCONV operator*=(Vec3& v1, Vec3 v2)
{
	v1 = v1 * v2;
	return v1;
}
INTRINSICS_INLINE Vec4& INTRINSICS_CALLCONV operator*=(Vec4& v1, Vec4 v2)
{
	v1 = v1 * v2;
	return v1;
}
INTRINSICS_INLINE Quaternion& INTRINSICS_CALLCONV operator*=(Quaternion& q1, Quaternion q2)
{
	q1 = q1 * q2;
	return q1;
}
INTRINSICS_INLINE Quaternion& INTRINSICS_CALLCONV operator*=(Quaternion& q, float scalar)
{
	q = q * scalar;
	return q;
}
INTRINSICS_INLINE Matrix4x4& INTRINSICS_CALLCONV operator*=(Matrix4x4& m, float scalar)
{
	m = m * scalar;
	return m;
}
INTRINSICS_INLINE Matrix4x4& INTRINSICS_CALLCONV operator*=(Matrix4x4& m1, Matrix4x4 m2)
{
	m1 = m1 * m2;
	return m1;
}

INTRINSICS_INLINE Vec2& INTRINSICS_CALLCONV operator/=(Vec2& v1, Vec2 v2)
{
	v1 = v1 / v2;
	return v1;
}
INTRINSICS_INLINE Vec3& INTRINSICS_CALLCONV operator/=(Vec3& v1, Vec3 v2)
{
	v1 = v1 / v2;
	return v1;
}
INTRINSICS_INLINE Vec4& INTRINSICS_CALLCONV operator/=(Vec4& v1, Vec4 v2)
{
	v1 = v1 / v2;
	return v1;
}
INTRINSICS_INLINE Matrix4x4& INTRINSICS_CALLCONV operator/=(Matrix4x4& m, float scalar)
{
	m = m / scalar;
	return m;
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV abs(Vec2 v)
{
	// & the sign bit
	return _mm_and_ps(XVMMaskAbsoluteValue, v.vec);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV abs(Vec3 v)
{
	// & the sign bit
	return _mm_and_ps(XVMMaskAbsoluteValue, v.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV abs(Vec4 v)
{
	// & the sign bit
	return _mm_and_ps(XVMMaskAbsoluteValue, v.vec);
}

INTRINSICS_INLINE bool INTRINSICS_CALLCONV all(Vec2 v)
{
	// v != 0
	__m128 dst = _mm_cmpneq_ps(v.vec, _mm_setzero_ps());
	// If all is non-zero, the mask is exactly 0x00000003
	int mask = _mm_movemask_ps(dst) & 0x00000003;
	return mask == 0x00000003;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV all(Vec3 v)
{
	// v != 0
	__m128 dst = _mm_cmpneq_ps(v.vec, _mm_setzero_ps());
	// If all is non-zero, the mask is exactly 0x00000007
	int mask = _mm_movemask_ps(dst) & 0x00000007;
	return mask == 0x00000007;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV all(Vec4 v)
{
	// v != 0
	__m128 dst = _mm_cmpneq_ps(v.vec, _mm_setzero_ps());
	// If all is non-zero, the mask is exactly 0x0000000F
	int mask = _mm_movemask_ps(dst) & 0x0000000F;
	return mask == 0x0000000F;
}

INTRINSICS_INLINE bool INTRINSICS_CALLCONV any(Vec2 v)
{
	// v != 0
	__m128 dst = _mm_cmpneq_ps(v.vec, _mm_setzero_ps());
	// If x or y are non-zero, the mask is non-zero
	int mask = _mm_movemask_ps(dst) & 0x00000003;
	return mask != 0;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV any(Vec3 v)
{
	// v != 0
	__m128 dst = _mm_cmpneq_ps(v.vec, _mm_setzero_ps());
	// If x or y or z are non-zero, the mask is non-zero
	int mask = _mm_movemask_ps(dst) & 0x00000007;
	return mask != 0;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV any(Vec4 v)
{
	// v != 0
	__m128 dst = _mm_cmpneq_ps(v.vec, _mm_setzero_ps());
	// If x or y or z or w are non-zero, the mask is non-zero
	int mask = _mm_movemask_ps(dst) & 0x0000000F;
	return mask != 0;
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV clamp(Vec2 v, Vec2 min, Vec2 max)
{
	__m128 xmm0 = _mm_min_ps(v.vec, max.vec);
	__m128 xmm1 = _mm_max_ps(xmm0, min.vec);
	return xmm1;
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV clamp(Vec3 v, Vec3 min, Vec3 max)
{
	__m128 xmm0 = _mm_min_ps(v.vec, max.vec);
	__m128 xmm1 = _mm_max_ps(xmm0, min.vec);
	return xmm1;
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV clamp(Vec4 v, Vec4 min, Vec4 max)
{
	__m128 xmm0 = _mm_min_ps(v.vec, max.vec);
	__m128 xmm1 = _mm_max_ps(xmm0, min.vec);
	return xmm1;
}

INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV cross(Vec3 v1, Vec3 v2)
{
	/*
	 * http://threadlocalmutex.com/?p=8
	 * (v1 x v2).x = v1.y * v2.z - v1.z * v2.y;
	 * (v1 x v2).y = v1.z * v2.x - v1.x * v2.z;
	 * (v1 x v2).z = v1.x * v2.y - v1.y * v2.x;
	 *
	 * moving the 3rd operation to top yields this
	 *
	 * (v1 x v2).z = v1.x * v2.y - v1.y * v2.x;
	 * (v1 x v2).x = v1.y * v2.z - v1.z * v2.y;
	 * (v1 x v2).y = v1.z * v2.x - v1.x * v2.z;
	 *
	 * we can perform swizzling here
	 *
	 * (v1 x v2).zxy = v1 * v2.yzx - v1.yzx * v2;
	 *
	 * swizzle zxy on both sides gives us the cross product again
	 *
	 * (v1 x v2) = (v1 * v2.yzx - v1.yzx * v2).yzx;
	 */
	__m128 v1_yzx = INTRINSICS_SWIZZLE_PS(v1.vec, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 v2_yzx = INTRINSICS_SWIZZLE_PS(v2.vec, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 cross  = _mm_sub_ps(_mm_mul_ps(v1.vec, v2_yzx), _mm_mul_ps(v1_yzx, v2.vec));
	return INTRINSICS_SWIZZLE_PS(cross, _MM_SHUFFLE(3, 0, 2, 1));
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV dot(Vec2 v1, Vec2 v2)
{
	__m128 dot	 = _mm_mul_ps(v1.vec, v2.vec);
	__m128 shuff = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(1, 1, 1, 1)); // { y, y, y, y }
	dot			 = _mm_add_ss(dot, shuff);								// { x+y, ?, ?, ? }
	return INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0));			// splat fp0
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV dot(Vec3 v1, Vec3 v2)
{
	__m128 dot	 = _mm_mul_ps(v1.vec, v2.vec);
	__m128 shuff = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(2, 2, 2, 1)); // { y, z, z, z }
	dot			 = _mm_add_ss(dot, shuff);								// { x+y, ?, ?, ? }
	shuff		 = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(2, 2, 2, 2)); // { z, z, z, z }
	dot			 = _mm_add_ss(dot, shuff);								// { x+y+z, ?, ?, ? }
	return INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0));			// splat fp0
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV dot(Vec4 v1, Vec4 v2)
{
	__m128 dot	 = _mm_mul_ps(v1.vec, v2.vec);
	__m128 shuff = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(2, 3, 0, 1)); // { y, x, w, z }
	dot			 = _mm_add_ps(dot, shuff);								// { x+y, y+x, z+w, w+z }
	shuff		 = _mm_movehl_ps(shuff, dot);							// { dot.fp2, dot.fp3, shuff.fp2, shuff.fp3 }
	dot			 = _mm_add_ss(dot, shuff);								// { x+y+z+w, ?, ?, ? }
	return INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0));			// splat fp0
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV dot(Quaternion q1, Quaternion q2)
{
	__m128 dot	 = _mm_mul_ps(q1.vec, q2.vec);
	__m128 shuff = INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(2, 3, 0, 1)); // { y, x, w, z }
	dot			 = _mm_add_ps(dot, shuff);								// { x+y, y+x, z+w, w+z }
	shuff		 = _mm_movehl_ps(shuff, dot);							// { dot.fp2, dot.fp3, shuff.fp2, shuff.fp3 }
	dot			 = _mm_add_ss(dot, shuff);								// { x+y+z+w, ?, ?, ? }
	return INTRINSICS_SWIZZLE_PS(dot, _MM_SHUFFLE(0, 0, 0, 0));			// splat fp0
}

INTRINSICS_INLINE bool INTRINSICS_CALLCONV isfinite(Vec2 v)
{
	// Mask off the sign bit
	__m128 and = _mm_and_ps(v.vec, XVMMaskAbsoluteValue);
	// v != infinity
	__m128 cmp = _mm_cmpneq_ps(and, XVMInfinity);
	// If x, y is finite, the mask is exactly 0x00000003
	int mask = _mm_movemask_ps(cmp) & 0x00000003;
	return mask == 0x00000003;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV isfinite(Vec3 v)
{
	// Mask off the sign bit
	__m128 and = _mm_and_ps(v.vec, XVMMaskAbsoluteValue);
	// v != infinity
	__m128 cmp = _mm_cmpneq_ps(and, XVMInfinity);
	// If x, y, z is finite, the mask is exactly 0x00000007
	int mask = _mm_movemask_ps(cmp) & 0x00000007;
	return mask == 0x00000007;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV isfinite(Vec4 v)
{
	// Mask off the sign bit
	__m128 and = _mm_and_ps(v.vec, XVMMaskAbsoluteValue);
	// v != infinity
	__m128 cmp = _mm_cmpneq_ps(and, XVMInfinity);
	// If x, y, z, w is finite, the mask is exactly 0x0000000F
	int mask = _mm_movemask_ps(cmp) & 0x0000000F;
	return mask == 0x0000000F;
}

INTRINSICS_INLINE bool INTRINSICS_CALLCONV isinf(Vec2 v)
{
	// Mask off the sign bit then compare to infinity
	__m128 and = _mm_and_ps(v.vec, XVMMaskAbsoluteValue);
	// v == infinity
	__m128 cmp = _mm_cmpeq_ps(and, XVMInfinity);
	// If x or y is infinity, the mask is non-zero
	int mask = _mm_movemask_ps(cmp) & 0x00000003;
	return mask != 0;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV isinf(Vec3 v)
{
	// Mask off the sign bit then compare to infinity
	__m128 and = _mm_and_ps(v.vec, XVMMaskAbsoluteValue);
	// v == infinity
	__m128 cmp = _mm_cmpeq_ps(and, XVMInfinity);
	// If x or y or z is infinity, the mask is non-zero
	int mask = _mm_movemask_ps(cmp) & 0x00000007;
	return mask != 0;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV isinf(Vec4 v)
{
	// Mask off the sign bit then compare to infinity
	__m128 and = _mm_and_ps(v.vec, XVMMaskAbsoluteValue);
	// v == infinity
	__m128 cmp = _mm_cmpeq_ps(and, XVMInfinity);
	// If x or y or z or w is infinity, the mask is non-zero
	int mask = _mm_movemask_ps(cmp) & 0x0000000F;
	return mask != 0;
}

INTRINSICS_INLINE bool INTRINSICS_CALLCONV isnan(Vec2 v)
{
	// v != v
	__m128 dst = _mm_cmpneq_ps(v.vec, v.vec);
	// If x or y are nan, the mask is non-zero
	int mask = _mm_movemask_ps(dst) & 0x00000003;
	return mask != 0;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV isnan(Vec3 v)
{
	// v != v
	__m128 dst = _mm_cmpneq_ps(v.vec, v.vec);
	// If x or y or z are nan, the mask is non-zero
	int mask = _mm_movemask_ps(dst) & 0x00000007;
	return mask != 0;
}
INTRINSICS_INLINE bool INTRINSICS_CALLCONV isnan(Vec4 v)
{
	// v != v
	__m128 dst = _mm_cmpneq_ps(v.vec, v.vec);
	// If x or y or z or w are NaN, the mask is non-zero
	int mask = _mm_movemask_ps(dst) & 0x0000000F;
	return mask != 0;
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV length(Vec2 v)
{
	Vec2 v2 = dot(v, v);
	return _mm_sqrt_ps(v2.vec);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV length(Vec3 v)
{
	Vec3 v2 = dot(v, v);
	return _mm_sqrt_ps(v2.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV length(Vec4 v)
{
	Vec4 v2 = dot(v, v);
	return _mm_sqrt_ps(v2.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV length(Quaternion q)
{
	Vec4 v2 = dot(q, q);
	return _mm_sqrt_ps(v2.vec);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV lerp(Vec2 v1, Vec2 v2, Vec2 s)
{
	// x + s(y-x)
	__m128 sub = _mm_sub_ps(v2.vec, v1.vec);
	__m128 mul = _mm_mul_ps(sub, s.vec);
	return _mm_add_ps(v1.vec, mul);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV lerp(Vec3 v1, Vec3 v2, Vec3 s)
{
	// x + s(y-x)
	__m128 sub = _mm_sub_ps(v2.vec, v1.vec);
	__m128 mul = _mm_mul_ps(sub, s.vec);
	return _mm_add_ps(v1.vec, mul);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV lerp(Vec4 v1, Vec4 v2, Vec4 s)
{
	// x + s(y-x)
	__m128 sub = _mm_sub_ps(v2.vec, v1.vec);
	__m128 mul = _mm_mul_ps(sub, s.vec);
	return _mm_add_ps(v1.vec, mul);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV max(Vec2 v1, Vec2 v2)
{
	return _mm_max_ps(v1.vec, v2.vec);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV max(Vec3 v1, Vec3 v2)
{
	return _mm_max_ps(v1.vec, v2.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV max(Vec4 v1, Vec4 v2)
{
	return _mm_max_ps(v1.vec, v2.vec);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV min(Vec2 v1, Vec2 v2)
{
	return _mm_min_ps(v1.vec, v2.vec);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV min(Vec3 v1, Vec3 v2)
{
	return _mm_min_ps(v1.vec, v2.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV min(Vec4 v1, Vec4 v2)
{
	return _mm_min_ps(v1.vec, v2.vec);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV normalize(Vec2 v)
{
	Vec2 l = length(v);
	return _mm_div_ps(v.vec, l.vec);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV normalize(Vec3 v)
{
	Vec3 l = length(v);
	return _mm_div_ps(v.vec, l.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV normalize(Vec4 v)
{
	Vec4 l = length(v);
	return _mm_div_ps(v.vec, l.vec);
}
INTRINSICS_INLINE Quaternion INTRINSICS_CALLCONV normalize(Quaternion q)
{
	Vec4 l = length(q);
	return _mm_div_ps(q.vec, l.vec);
}

INTRINSICS_INLINE Vec2 INTRINSICS_CALLCONV sqrt(Vec2 v)
{
	return _mm_sqrt_ps(v.vec);
}
INTRINSICS_INLINE Vec3 INTRINSICS_CALLCONV sqrt(Vec3 v)
{
	return _mm_sqrt_ps(v.vec);
}
INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV sqrt(Vec4 v)
{
	return _mm_sqrt_ps(v.vec);
}

INTRINSICS_INLINE Vec4 INTRINSICS_CALLCONV mul(Vec4 v, Matrix4x4 m)
{
	//				[a b c d]
	// [x y z w] *	[e f g h]
	//				[i j k l]
	//				[m n o p]
	//
	// x' = x * a + y * e + z * i + w * m
	// y' = x * b + y * f + z * j + w * n
	// z' = x * c + y * g + z * k + w * o
	// w' = x * d + y * h + z * l + w * p
	// Splat all vector components
	__m128 x = INTRINSICS_SWIZZLE_PS(v.vec, _MM_SHUFFLE(0, 0, 0, 0)); // [x, x, x, x]
	__m128 y = INTRINSICS_SWIZZLE_PS(v.vec, _MM_SHUFFLE(1, 1, 1, 1)); // [y, y, y, y]
	__m128 z = INTRINSICS_SWIZZLE_PS(v.vec, _MM_SHUFFLE(2, 2, 2, 2)); // [z, z, z, z]
	__m128 w = INTRINSICS_SWIZZLE_PS(v.vec, _MM_SHUFFLE(3, 3, 3, 3)); // [w, w, w, w]

	x = _mm_mul_ps(x, m.r[0]); // mul x by r0
	y = _mm_mul_ps(y, m.r[1]); // mul y by r1
	z = _mm_mul_ps(z, m.r[2]); // mul z by r2
	w = _mm_mul_ps(w, m.r[3]); // mul w by r3
	// sum
	x = _mm_add_ps(x, y);	 // x+y
	z = _mm_add_ps(z, w);	 // z+w;
	return _mm_add_ps(x, z); // x+y+z+w
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV mul(Matrix4x4 m1, Matrix4x4 m2)
{
	__m128 r[4];

	// See mul(Vec4, Matrix4x4)
	for (int i = 0; i < 4; ++i)
	{
		__m128 x = INTRINSICS_SWIZZLE_PS(m1.r[i], _MM_SHUFFLE(0, 0, 0, 0)); // [x, x, x, x]
		__m128 y = INTRINSICS_SWIZZLE_PS(m1.r[i], _MM_SHUFFLE(1, 1, 1, 1)); // [y, y, y, y]
		__m128 z = INTRINSICS_SWIZZLE_PS(m1.r[i], _MM_SHUFFLE(2, 2, 2, 2)); // [z, z, z, z]
		__m128 w = INTRINSICS_SWIZZLE_PS(m1.r[i], _MM_SHUFFLE(3, 3, 3, 3)); // [w, w, w, w]

		x = _mm_mul_ps(x, m2.r[0]); // mul x by r0
		y = _mm_mul_ps(y, m2.r[1]); // mul y by r1
		z = _mm_mul_ps(z, m2.r[2]); // mul z by r2
		w = _mm_mul_ps(w, m2.r[3]); // mul w by r3
		// sum
		x	 = _mm_add_ps(x, y); // x+y
		z	 = _mm_add_ps(z, w); // z+w;
		r[i] = _mm_add_ps(x, z); // x+y+z+w
	}

	return Matrix4x4(r[0], r[1], r[2], r[3]);
}

INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV transpose(Matrix4x4 m)
{
	// I worked this out on paper, is pretty interesting on how they arrived at the solution
	_MM_TRANSPOSE4_PS(m.r[0], m.r[1], m.r[2], m.r[3]);
	return m;
}

INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV translation(float x, float y, float z)
{
	// row-major | col-major
	// [1 0 0 0] | [1 0 0 x]
	// [0 1 0 0] | [0 1 0 y]
	// [0 0 1 0] | [0 0 1 z]
	// [x y z 1] | [0 0 0 1]
	__m128 r[4];
	r[0] = XVMIdentityR0;
	r[1] = XVMIdentityR1;
	r[2] = XVMIdentityR2;
	r[3] = _mm_set_ps(1.0f, z, y, x);
	return Matrix4x4(r[0], r[1], r[2], r[3]);
}

INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV scale(float x, float y, float z)
{
	// row-major, actually it doesnt matter lol, transpose is same
	// [x 0 0 0]
	// [0 y 0 0]
	// [0 0 z 0]
	// [0 0 0 1]
	__m128 r[4];
	r[0] = _mm_set_ps(0, 0, 0, x);
	r[1] = _mm_set_ps(0, 0, y, 0);
	r[2] = _mm_set_ps(0, z, 0, 0);
	r[3] = XVMIdentityR3;
	return Matrix4x4(r[0], r[1], r[2], r[3]);
}

INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV rotationX(float angle)
{
	float sinTheta = std::sin(angle);
	float cosTheta = std::cos(angle);

	return Matrix4x4(1, 0, 0, 0, 0, cosTheta, sinTheta, 0, 0, -sinTheta, cosTheta, 0, 0, 0, 0, 1);
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV rotationY(float angle)
{
	float sinTheta = std::sin(angle);
	float cosTheta = std::cos(angle);

	return Matrix4x4(cosTheta, 0, -sinTheta, 0, 0, 1, 0, 0, sinTheta, 0, cosTheta, 0, 0, 0, 0, 1);
}
INTRINSICS_INLINE Matrix4x4 INTRINSICS_CALLCONV rotationZ(float angle)
{
	float sinTheta = std::sin(angle);
	float cosTheta = std::cos(angle);

	return Matrix4x4(cosTheta, sinTheta, 0, 0, -sinTheta, cosTheta, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
} // namespace xvm
