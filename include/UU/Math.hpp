#pragma once
#include <cmath>

namespace UU::Math
{
	constexpr float		FLT_PI =		3.141592653f;
	constexpr float		FLT_INV_PI =	1.f / FLT_PI;
	constexpr float		FLT_E =			2.718281828f;
		
	constexpr double	DBL_PI =		3.141592653589793;
	constexpr double	DBL_INV_PI =	1.0 / DBL_PI;
	constexpr double	DBL_E =			2.718281828459045;
		
	constexpr float		FLT_RAD2DEG =	180.f / FLT_PI;
	constexpr float		FLT_DEG2RAD =	FLT_PI / 180.f;
		
	constexpr double	DBL_RAD2DEG =	180.f / DBL_PI;
	constexpr double	DBL_DEG2RAD =	DBL_PI / 180.f;

	template <class T>
	T Sign(T val);

	template <class T>
	T Abs(T val);

	template <class T>
	T Min(T a, T b);

	template <class T>
	T Max(T a, T b);

	template <class T>
	T Clamp(T x, T min, T max);

	template <class T>
	T Lerp(T min, T max, T factor);

	template <class T>
	T NormalizeAngle(T angle);

	inline float	Mod(float a, float b);
	inline double	Mod(double a, double b);

	inline float	Sin(float val);
	inline float	Cos(float val);
	inline float	Tan(float val);

	inline void		SinCos(float val, float & sin_val, float & cos_val);

	inline double	Sin(double val);
	inline double	Cos(double val);
	inline double	Tan(double val);

	inline void		SinCos(double val, double & sin_val, double & cos_val);

	inline float	ASin(float val);
	inline float	ACos(float val);
	inline float	ATan(float val);
	inline float	ATan2(float y, float x);

	inline double	ASin(double val);
	inline double	ACos(double val);
	inline double	ATan(double val);
	inline double	ATan2(double y, double x);

	inline float	Sqrt(float val);
	inline float	InvSqrt(float val);

	inline double	Sqrt(double val);
	inline double	InvSqrt(double val);

	inline float	Exp(float val);
	inline float	Ln(float val);
	inline float	Pow(float a, float b);

	inline double	Exp(double val);
	inline double	Ln(double val);
	inline double	Pow(double a, double b);

	inline float	Floor(float val);
	inline float	Ceil(float val);
	inline float	Trunc(float val);
	inline float	Round(float val);

	inline double	Floor(double val);
	inline double	Ceil(double val);
	inline double	Trunc(double val);
	inline double	Round(double val);

	inline bool		IsNormal(float val);
	inline bool		IsFinite(float val);
	inline bool		IsNan(float val);
	inline bool		IsInf(float val);

	inline bool		IsNormal(double val);
	inline bool		IsFinite(double val);
	inline bool		IsNan(double val);
	inline bool		IsInf(double val);

	inline float	Hypot(float x, float y);
	inline double	Hypot(double x, double y);

	inline float	RadToDeg(float angle);
	inline float	DegToRad(float angle);

	inline double	RadToDeg(double angle);
	inline double	DegToRad(double angle);
}

template <class T>
T UU::Math::Sign(const T t)
{
	if (!t)
	{
		return 0;
	}
	return t > T(0) ? T(1) : T(-1);
}

template <class T>
T UU::Math::Abs(const T val)
{
	return val < 0 ? -val : val;
}

template <class T>
T UU::Math::Min(const T a, const T b)
{
	return a < b ? a : b;
}

template <class T>
T UU::Math::Max(const T a, const T b)
{
	return a > b ? a : b;
}

template <class T>
T UU::Math::Clamp(const T x, const T min, const T max)
{
	return x > max ? max : x < min ? min : x;
}

template<typename T>
T UU::Math::Lerp(T min, T max, T factor)
{
	return min + (max - min) * factor;
}

template<class T>
T UU::Math::NormalizeAngle(T angle)
{
	return fmod(angle + T(180), T(360)) - T(180);
}

float UU::Math::Mod(const float a, const float b)
{
	return fmodf(a, b);
}

double UU::Math::Mod(const double a, const double b)
{
	return fmod(a, b);
}

float UU::Math::Sin(const float val)
{
	return sinf(val);
}

float UU::Math::Cos(const float val)
{
	return cosf(val);
}

float UU::Math::Tan(const float val)
{
	return tanf(val);
}

void UU::Math::SinCos(float val, float & sin_val, float & cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

double UU::Math::Sin(const double val)
{
	return sin(val);
}

double UU::Math::Cos(const double val)
{
	return cos(val);
}

double UU::Math::Tan(const double val)
{
	return tan(val);
}

void UU::Math::SinCos(double val, double & sin_val, double & cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

float UU::Math::ASin(const float val)
{
	return asinf(val);
}

float UU::Math::ACos(const float val)
{
	return acosf(val);
}

float UU::Math::ATan(const float val)
{
	return atanf(val);
}

float UU::Math::ATan2(const float y, const float x)
{
	return atan2f(y, x);
}

double UU::Math::ASin(const double val)
{
	return asin(val);
}

double UU::Math::ACos(const double val)
{
	return acos(val);
}

double UU::Math::ATan(const double val)
{
	return atan(val);
}

double UU::Math::ATan2(const double y, const double x)
{
	return atan2(y, x);
}

float UU::Math::Sqrt(const float val)
{
	return sqrtf(val);
}

float UU::Math::InvSqrt(const float val)
{
	return 1.f / sqrtf(val);
}

double UU::Math::Sqrt(const double val)
{
	return sqrt(val);
}

double UU::Math::InvSqrt(const double val)
{
	return 1.0 / sqrt(val);
}

float UU::Math::Exp(const float val)
{
	return expf(val);
}

float UU::Math::Ln(const float val)
{
	return logf(val);
}

float UU::Math::Pow(const float a, const float b)
{
	return powf(a, b);
}

double UU::Math::Exp(const double val)
{
	return exp(val);
}

double UU::Math::Ln(const double val)
{
	return log(val);
}

double UU::Math::Pow(const double a, const double b)
{
	return pow(a, b);
}

float UU::Math::Floor(const float val)
{
	return floorf(val);
}

float UU::Math::Ceil(const float val)
{
	return ceilf(val);
}

float UU::Math::Trunc(const float val)
{
	return truncf(val);
}

float UU::Math::Round(const float val)
{
	return roundf(val);
}

double UU::Math::Floor(const double val)
{
	return floor(val);
}

double UU::Math::Ceil(const double val)
{
	return ceil(val);
}

double UU::Math::Trunc(const double val)
{
	return trunc(val);
}

double UU::Math::Round(const double val)
{
	return round(val);
}

bool UU::Math::IsNormal(const float val)
{
	return isnormal(val);
}

bool UU::Math::IsFinite(const float val)
{
	return isfinite(val);
}

bool UU::Math::IsNan(const float val)
{
	return isnan(val);
}

bool UU::Math::IsInf(const float val)
{
	return isinf(val);
}

bool UU::Math::IsNormal(const double val)
{
	return isnormal(val);
}

bool UU::Math::IsFinite(const double val)
{
	return isfinite(val);
}

bool UU::Math::IsNan(const double val)
{
	return isnan(val);
}

bool UU::Math::IsInf(const double val)
{
	return isinf(val);
}

float UU::Math::Hypot(const float x, const float y)
{
	return hypotf(x, y);
}

double UU::Math::Hypot(const double x, const double y)
{
	return hypot(x, y);
}

float UU::Math::RadToDeg(float angle)
{
	return angle * 180.f / FLT_PI;
}

float UU::Math::DegToRad(float angle)
{
	return angle * FLT_PI / 180.f;
}

double UU::Math::RadToDeg(double angle)
{
	return angle * 180.0 / DBL_PI;
}

double UU::Math::DegToRad(double angle)
{
	return angle * DBL_PI / 180.0;
}

