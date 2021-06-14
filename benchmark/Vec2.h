#pragma once

#include <cmath>
#include <compare>
#include <algorithm>
#include <type_traits>

template<typename T>
struct Vector2
{
	constexpr Vector2() noexcept { x = y = static_cast<T>(0); }

	constexpr Vector2(T v) noexcept
		: x(v)
		, y(v)
	{
	}

	constexpr Vector2(T x, T y) noexcept
		: x(x)
		, y(y)
	{
	}

	auto operator<=>(const Vector2&) const = default;

	[[nodiscard]] Vector2 operator-() const noexcept { return Vector2(-x, -y); }

	[[nodiscard]] Vector2 operator+(const Vector2& v) const noexcept { return Vector2(x + v.x, y + v.y); }

	Vector2& operator+=(const Vector2& v) noexcept
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	[[nodiscard]] Vector2 operator-(const Vector2& v) const noexcept { return Vector2(x - v.x, y - v.y); }

	Vector2& operator-=(const Vector2& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	[[nodiscard]] Vector2 operator*(const Vector2& v) const noexcept { return Vector2(x * v.x, y * v.y); }

	Vector2& operator*=(const Vector2& v) noexcept
	{
		x *= v.x, y *= v.y;
		return *this;
	}

	[[nodiscard]] Vector2 operator*(T s) const noexcept { return Vector2(x * s, y * s); }

	Vector2& operator*=(T s) noexcept
	{
		x *= s;
		y *= s;
		return *this;
	}

	[[nodiscard]] Vector2 operator/(T s) const noexcept
	{
		float inv = static_cast<T>(1) / s;
		return Vector2<T>(x * inv, y * inv);
	}

	Vector2& operator/=(T s) noexcept
	{
		float inv = static_cast<T>(1) / s;
		x *= inv;
		y *= inv;
		return *this;
	}

	T x, y;
};

template<typename T>
[[nodiscard]] inline Vector2<T> operator*(T s, const Vector2<T>& v) noexcept
{
	return v * s;
}

template<typename T>
[[nodiscard]] inline T length(const Vector2<T>& v) noexcept
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
[[nodiscard]] inline Vector2<T> abs(const Vector2<T>& v) noexcept
{
	return Vector2<T>(std::abs(v.x), std::abs(v.y));
}

template<typename T>
[[nodiscard]] inline T dot(const Vector2<T>& v1, const Vector2<T>& v2) noexcept
{
	return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
[[nodiscard]] inline Vector2<T> normalize(const Vector2<T>& v) noexcept
{
	return v / length(v);
}

template<typename T>
[[nodiscard]] inline bool isnan(const Vector2<T>& v) noexcept
{
	return std::isnan(v.x) || std::isnan(v.y);
}

template<typename T>
[[nodiscard]] inline Vector2<T> clamp(const Vector2<T>& v, T min, T max) noexcept
{
	return Vector2(std::clamp(v.x, min, max), std::clamp(v.y, min, max));
}

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

static void BM_Vector2f_arithmetic_add(benchmark::State& state)
{
	for (auto _ : state)
	{
		Vector2f v1(1.0f, 2.0f);
		Vector2f v2(4.0f, 3.0f);
		Vector2f result = v1 + v2;
	}
}
BENCHMARK(BM_Vector2f_arithmetic_add)->Iterations(g_Iterations);

static void BM_Vec2_arithmetic_add(benchmark::State& state)
{
	for (auto _ : state)
	{
		Vec2 v1(1.0f, 2.0f);
		Vec2 v2(4.0f, 3.0f);
		Vec2 result = v1 + v2;
	}
}
BENCHMARK(BM_Vec2_arithmetic_add)->Iterations(g_Iterations);

static void BM_m128_arithmetic_add(benchmark::State& state)
{
	for (auto _ : state)
	{
		__m128 v1	  = _mm_set_ps(0.0f, 0.0f, 2.0f, 1.0f);
		__m128 v2	  = _mm_set_ps(0.0f, 0.0f, 4.0f, 3.0f);
		__m128 result = _mm_add_ps(v1, v2);
	}
}
BENCHMARK(BM_m128_arithmetic_add)->Iterations(g_Iterations);
