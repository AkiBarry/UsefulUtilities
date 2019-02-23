#pragma once
#include <cmath>

namespace UU::NMath
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
T UU::NMath::Sign(const T t)
{
	if (!t)
	{
		return 0;
	}
	return t > T(0) ? T(1) : T(-1);
}

template <class T>
T UU::NMath::Abs(const T val)
{
	return val < 0 ? -val : val;
}

template <class T>
T UU::NMath::Min(const T a, const T b)
{
	return a < b ? a : b;
}

template <class T>
T UU::NMath::Max(const T a, const T b)
{
	return a > b ? a : b;
}

template <class T>
T UU::NMath::Clamp(const T x, const T min, const T max)
{
	return x > max ? max : x < min ? min : x;
}

template<typename T>
T UU::NMath::Lerp(T min, T max, T factor)
{
	return min + (max - min) * factor;
}

template<class T>
T UU::NMath::NormalizeAngle(T angle)
{
	return fmod(angle + T(180), T(360)) - T(180);
}

float UU::NMath::Mod(const float a, const float b)
{
	return fmodf(a, b);
}

double UU::NMath::Mod(const double a, const double b)
{
	return fmod(a, b);
}

float UU::NMath::Sin(const float val)
{
	return sinf(val);
}

float UU::NMath::Cos(const float val)
{
	return cosf(val);
}

float UU::NMath::Tan(const float val)
{
	return tanf(val);
}

void UU::NMath::SinCos(float val, float & sin_val, float & cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

double UU::NMath::Sin(const double val)
{
	return sin(val);
}

double UU::NMath::Cos(const double val)
{
	return cos(val);
}

double UU::NMath::Tan(const double val)
{
	return tan(val);
}

void UU::NMath::SinCos(double val, double & sin_val, double & cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

float UU::NMath::ASin(const float val)
{
	return asinf(val);
}

float UU::NMath::ACos(const float val)
{
	return acosf(val);
}

float UU::NMath::ATan(const float val)
{
	return atanf(val);
}

float UU::NMath::ATan2(const float y, const float x)
{
	return atan2f(y, x);
}

double UU::NMath::ASin(const double val)
{
	return asin(val);
}

double UU::NMath::ACos(const double val)
{
	return acos(val);
}

double UU::NMath::ATan(const double val)
{
	return atan(val);
}

double UU::NMath::ATan2(const double y, const double x)
{
	return atan2(y, x);
}

float UU::NMath::Sqrt(const float val)
{
	return sqrtf(val);
}

float UU::NMath::InvSqrt(const float val)
{
	return 1.f / sqrtf(val);
}

double UU::NMath::Sqrt(const double val)
{
	return sqrt(val);
}

double UU::NMath::InvSqrt(const double val)
{
	return 1.0 / sqrt(val);
}

float UU::NMath::Exp(const float val)
{
	return expf(val);
}

float UU::NMath::Ln(const float val)
{
	return logf(val);
}

float UU::NMath::Pow(const float a, const float b)
{
	return powf(a, b);
}

double UU::NMath::Exp(const double val)
{
	return exp(val);
}

double UU::NMath::Ln(const double val)
{
	return log(val);
}

double UU::NMath::Pow(const double a, const double b)
{
	return pow(a, b);
}

float UU::NMath::Floor(const float val)
{
	return floorf(val);
}

float UU::NMath::Ceil(const float val)
{
	return ceilf(val);
}

float UU::NMath::Trunc(const float val)
{
	return truncf(val);
}

float UU::NMath::Round(const float val)
{
	return roundf(val);
}

double UU::NMath::Floor(const double val)
{
	return floor(val);
}

double UU::NMath::Ceil(const double val)
{
	return ceil(val);
}

double UU::NMath::Trunc(const double val)
{
	return trunc(val);
}

double UU::NMath::Round(const double val)
{
	return round(val);
}

bool UU::NMath::IsNormal(const float val)
{
	return isnormal(val);
}

bool UU::NMath::IsFinite(const float val)
{
	return isfinite(val);
}

bool UU::NMath::IsNan(const float val)
{
	return isnan(val);
}

bool UU::NMath::IsInf(const float val)
{
	return isinf(val);
}

bool UU::NMath::IsNormal(const double val)
{
	return isnormal(val);
}

bool UU::NMath::IsFinite(const double val)
{
	return isfinite(val);
}

bool UU::NMath::IsNan(const double val)
{
	return isnan(val);
}

bool UU::NMath::IsInf(const double val)
{
	return isinf(val);
}

float UU::NMath::Hypot(const float x, const float y)
{
	return hypotf(x, y);
}

double UU::NMath::Hypot(const double x, const double y)
{
	return hypot(x, y);
}

float UU::NMath::RadToDeg(float angle)
{
	return angle * 180.f / FLT_PI;
}

float UU::NMath::DegToRad(float angle)
{
	return angle * FLT_PI / 180.f;
}

double UU::NMath::RadToDeg(double angle)
{
	return angle * 180.0 / DBL_PI;
}

double UU::NMath::DegToRad(double angle)
{
	return angle * DBL_PI / 180.0;
}

