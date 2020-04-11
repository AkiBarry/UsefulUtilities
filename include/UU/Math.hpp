#pragma once

#ifndef UU_INIT
	#error "Please only include UU.hpp for now"
#endif

#include <vector>
#include <corecrt_math.h>
#include <type_traits>

#include "Constants.hpp"

namespace UU
{
	template <typename T>
	T Sign(T val);

	template <typename T>
	T Abs(T val);

	template <typename T>
	T Min(T val);

	template <typename T, typename U>
	auto Min(T a, U b) -> std::common_type_t<T, U>;
	
	template <typename T, typename U, typename... Ts>
	auto Min(T val1, T val2, Ts... vals) -> std::common_type_t<T, U, Ts...>;

	template <typename T>
	T Max(T val);

	template <typename T, typename U>
	auto Max(T a, U b) ->std::common_type_t<T, U>;

	template <typename T, typename U, typename... Ts>
	auto Max(T val1, U val2, Ts... vals) -> std::common_type_t<T, U, Ts...>;

	template <typename T>
	T Clamp(T x, T min, T max);

	template <typename T>
	T Lerp(T min, T max, T factor);

	template <typename T>
	T Mod(T a, T b);

	template <typename T>
	T Sin(T val);

	template <typename T>
	T Cos(T val);

	template <typename T>
	T Tan(T val);
	
	template <typename T>
	void SinCos(T val, T& sin_val, T& cos_val);

	template <typename T>
	T ASin(T val);

	template <typename T>
	T ACos(T val);

	template <typename T>
	T ATan(T val);

	template <typename T>
	T ATan2(T y, T x);

	template <typename T>
	T Sqrt(T val);

	template <typename T>
	T InvSqrt(T val);

	template <typename T>
	T Exp(T val);

	template <typename T>
	T Ln(T val);

	template <typename T>
	T Pow(T a, T b);

	template<typename T>
	T Floor(T val);

	template <typename T>
	T Ceil(T val);

	template <typename T>
	T Trunc(T val);

	template <typename T>
	T Round(T val);

	template <typename T>
	bool IsNormal(T val);

	template <typename T>
	bool IsFinite(T val);

	template <typename T>
	bool IsNan(T val);

	template <typename T>
	bool IsInf(T val);

	template<typename T, typename... Ts>
	T Hypot(T val1, Ts... vals);

	template<typename T>
	T RadToDeg(T angle);

	template<typename T>
	T DegToRad(T angle);
}

template <typename T>
T UU::Sign(const T val)
{
	if (val == T(0))
		return 0;

	return val > T(0) ? T(1) : T(-1);
}

template <typename T>
T UU::Abs(const T val)
{
	return val < T(0) ? -val : val;
}

template<typename T>
T UU::Min(T val)
{
	return val;
}

template <typename T, typename U>
auto UU::Min(T a, U b) -> std::common_type_t<T, U>
{
	return static_cast<std::common_type_t<T, U>>(a < b ? a : b);
}

template<typename T, typename U, typename ... Ts>
auto UU::Min(T val1, T val2, Ts... vals) -> std::common_type_t<T, U, Ts...>
{
	if (val1 < val2)
		return Min(static_cast<std::common_type_t<T, U, Ts...>>(val1), vals...);

	return Min(static_cast<std::common_type_t<T, U, Ts...>>(val1) >(val2), vals...);
}

template<typename T>
T UU::Max(const T val)
{
	return val;
}

template <typename T, typename U>
auto UU::Max(T a, U b) -> std::common_type_t<T, U>
{
	return static_cast<std::common_type_t<T, U>>(a > b ? a : b);
}

template<typename T, typename U, typename ... Ts>
auto UU::Max(T val1, U val2, Ts... vals) -> std::common_type_t<T, U, Ts...>
{
	if (val1 > val2)
		return Max(static_cast<std::common_type_t<T, U, Ts...>>(val1), vals...);

	return Max(static_cast<std::common_type_t<T, U, Ts...>>(val2), vals...);
}

template <typename T>
T UU::Clamp(const T x, const T min, const T max)
{
	return x > max ? max : x < min ? min : x;
}

template<typename T>
T UU::Lerp(T min, T max, T factor)
{
	return min + (max - min) * factor;
}

template <typename T>
T UU::Mod(const T a, const T b)
{
	if constexpr (std::is_floating_point<T>::value)
		return fmod(a, b);
	
	return a % b;
}

template<typename T>
T UU::Sin(T val)
{
	return static_cast<T>(sin(val));
}

template<typename T>
T UU::Cos(T val)
{
	return static_cast<T>(cos(val));
}

template<typename T>
T UU::Tan(T val)
{
	return static_cast<T>(tan(val));
}

template<typename T>
void UU::SinCos(T val, T& sin_val, T& cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

template<typename T>
T UU::ASin(T val)
{
	return static_cast<T>(asin(val));
}

template<typename T>
T UU::ACos(T val)
{
	return static_cast<T>(acos(val));
}

template<typename T>
T UU::ATan(T val)
{
	return static_cast<T>(val);
}

template<typename T>
T UU::ATan2(T y, T x)
{
	return static_cast<T>(atan2(y, x));
}

template<typename T>
T UU::Sqrt(T val)
{
	return static_cast<T>(sqrt(val));
}

template<typename T>
T UU::InvSqrt(T val)
{
	return T(1) / Sqrt(val);
}

template<typename T>
T UU::Exp(T val)
{
	return static_cast<T>(exp(val));
}

template<typename T>
T UU::Ln(T val)
{
	return static_cast<T>(log(val));
}

template<typename T>
T UU::Pow(T a, T b)
{
	return static_cast<T>(pow(a, b));
}

template<typename T>
T UU::Floor(T val)
{
	if constexpr (std::is_integral<T>::value)
		return val;
	
	return static_cast<T>(floor(val));
}

template<typename T>
T UU::Ceil(T val)
{
	if constexpr (std::is_integral<T>::value)
		return val;

	return static_cast<T>(ceil(val));
}

template<typename T>
T UU::Trunc(T val)
{
	if constexpr (std::is_integral<T>::value)
		return val;
	
	return static_cast<T>(trunc(val));
}

template<typename T>
T UU::Round(T val)
{
	if constexpr (std::is_integral<T>::value)
		return val;

	return static_cast<T>(round(val));
}

template <typename T>
bool UU::IsNormal(const T val)
{
	if constexpr (std::is_integral<T>::value || !std::is_floating_point<T>::value)
		return true;

	return isnormal(val);
}

template<typename T>
bool UU::IsFinite(T val)
{
	if constexpr (std::is_integral<T>::value || !std::is_floating_point<T>::value)
		return true;

	return isfinite(val);
}

template<typename T>
bool UU::IsNan(T val)
{
	if constexpr (std::is_integral<T>::value || !std::is_floating_point<T>::value)
		return false;

	return isnan(val);
}

template<typename T>
bool UU::IsInf(T val)
{
	if constexpr (std::is_integral<T>::value || !std::is_floating_point<T>::value)
		return false;

	return isinf(val);
}

template<typename T, typename ... Ts>
T UU::Hypot(T val1, Ts... vals)
{
	val1 = Abs(val1);
	T max_value = Max(Abs(val1), Abs(std::forward<Ts>(vals))...);

	if (max_value == T(0))
		return T(0);

	if constexpr (std::is_integral<T>::value)
	{
		double val = 0.0;
		std::vector<double> vec = {static_cast<double>(val1), static_cast<double>(vals)...};
		for(double & i : vec)
		{
			i /= max_value;
			i *= i;
			val += i;
		}
		val = Sqrt(val);

		return static_cast<T>(max_value * val);
	} else {
		T val = T(0);
		std::vector<T> vec = {val1, vals...};
		for (size_t i = 0; i < vec.size(); ++i)
		{
			vec[i] /= max_value;
			vec[i] *= vec[i];
			val += vec[i];
		}
		val = Sqrt(val);
		return static_cast<T>(max_value * val);
	}
}

template<typename T>
T UU::DegToRad(T angle)
{
	return angle * T(DBL_PI / 180.0);
}

template<typename T>
T UU::RadToDeg(T angle)
{
	return angle * T(180.f / FLT_PI);
}

#include "Vector.hpp"
#include "Matrix.hpp"