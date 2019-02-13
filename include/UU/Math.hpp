#pragma once
#include <cmath>

namespace NMath
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

	template <typename T, size_t dim>
	class CVector;

	using CVec2f = CVector<float, 2>;
	using CVec3f = CVector<float, 3>;
	using CVec4f = CVector<float, 4>;

	using CVec2d = CVector<double, 2>;
	using CVec3d = CVector<double, 3>;
	using CVec4d = CVector<double, 4>;

	using CVec2i = CVector<int, 2>;
	using CVec3i = CVector<int, 3>;
	using CVec4i = CVector<int, 4>;

	template <typename T, size_t dim, bool radian = true>
	class CAngle;

	template <bool radians = true>
	using CAng2f = CAngle<float, 2, radians>;
	template <bool radians = true>
	using CAng3f = CAngle<float, 3, radians>;
	template <bool radians = true>
	using CAng4f = CAngle<float, 4, radians>;

	template <bool radians = true>
	using CAng2d = CAngle<double, 2, radians>;
	template <bool radians = true>
	using CAng3d = CAngle<double, 3, radians>;
	template <bool radians = true>
	using CAng4d = CAngle<double, 4, radians>;
				   
	template <bool radians = true>
	using CAng2i = CAngle<int, 2, radians>;
	template <bool radians = true>
	using CAng3i = CAngle<int, 3, radians>;
	template <bool radians = true>
	using CAng4i = CAngle<int, 4, radians>;

	template <typename T, size_t rows, size_t columns>
	class CMatrix;

	template <typename T>
	class CRandom;

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

	inline float Mod(float a, float b);
	inline double Mod(double a, double b);

	inline float Sin(float val);
	inline float Cos(float val);
	inline float Tan(float val);

	inline void SinCos(float val, float & sin_val, float & cos_val);

	inline double Sin(double val);
	inline double Cos(double val);
	inline double Tan(double val);

	inline void SinCos(double val, double & sin_val, double & cos_val);

	inline float ASin(float val);
	inline float ACos(float val);
	inline float ATan(float val);
	inline float ATan2(float y, float x);

	inline double ASin(double val);
	inline double ACos(double val);
	inline double ATan(double val);
	inline double ATan2(double y, double x);

	inline float Sqrt(float val);
	inline float InvSqrt(float val);

	inline double Sqrt(double val);
	inline double InvSqrt(double val);

	inline float Exp(float val);
	inline float Ln(float val);
	inline float Pow(float a, float b);

	inline double Exp(double val);
	inline double Ln(double val);
	inline double Pow(double a, double b);

	inline float Floor(float val);
	inline float Ceil(float val);
	inline float Trunc(float val);
	inline float Round(float val);

	inline double Floor(double val);
	inline double Ceil(double val);
	inline double Trunc(double val);
	inline double Round(double val);

	inline bool IsNormal(float val);
	inline bool IsFinite(float val);
	inline bool IsNan(float val);
	inline bool IsInf(float val);

	inline bool IsNormal(double val);
	inline bool IsFinite(double val);
	inline bool IsNan(double val);
	inline bool IsInf(double val);

	inline float Hypot(float x, float y);
	inline double Hypot(double x, double y);

	inline float RadToDeg(float angle);
	inline float DegToRad(float angle);

	inline double RadToDeg(double angle);
	inline double DegToRad(double angle);
}

template <class T>
T NMath::Sign(const T t)
{
	if (!t)
	{
		return 0;
	}
	return t > T(0) ? T(1) : T(-1);
}

template <class T>
T NMath::Abs(const T val)
{
	return val < 0 ? -val : val;
}

template <class T>
T NMath::Min(const T a, const T b)
{
	return a < b ? a : b;
}

template <class T>
T NMath::Max(const T a, const T b)
{
	return a > b ? a : b;
}

template <class T>
T NMath::Clamp(const T x, const T min, const T max)
{
	return x > max ? max : x < min ? min : x;
}

template<typename T>
T NMath::Lerp(T min, T max, T factor)
{
	return min + (max - min) * factor;
}

template<class T>
T NMath::NormalizeAngle(T angle)
{
	return fmod(angle + T(180), T(360)) - T(180);
}

float NMath::Mod(const float a, const float b)
{
	return fmodf(a, b);
}

double NMath::Mod(const double a, const double b)
{
	return fmod(a, b);
}

float NMath::Sin(const float val)
{
	return sinf(val);
}

float NMath::Cos(const float val)
{
	return cosf(val);
}

float NMath::Tan(const float val)
{
	return tanf(val);
}

void NMath::SinCos(float val, float & sin_val, float & cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

double NMath::Sin(const double val)
{
	return sin(val);
}

double NMath::Cos(const double val)
{
	return cos(val);
}

double NMath::Tan(const double val)
{
	return tan(val);
}

void NMath::SinCos(double val, double & sin_val, double & cos_val)
{
	sin_val = Sin(val);
	cos_val = Cos(val);
}

float NMath::ASin(const float val)
{
	return asinf(val);
}

float NMath::ACos(const float val)
{
	return acosf(val);
}

float NMath::ATan(const float val)
{
	return atanf(val);
}

float NMath::ATan2(const float y, const float x)
{
	return atan2f(y, x);
}

double NMath::ASin(const double val)
{
	return asin(val);
}

double NMath::ACos(const double val)
{
	return acos(val);
}

double NMath::ATan(const double val)
{
	return atan(val);
}

double NMath::ATan2(const double y, const double x)
{
	return atan2(y, x);
}

float NMath::Sqrt(const float val)
{
	return sqrtf(val);
}

float NMath::InvSqrt(const float val)
{
	return 1.f / sqrtf(val);
}

double NMath::Sqrt(const double val)
{
	return sqrt(val);
}

double NMath::InvSqrt(const double val)
{
	return 1.0 / sqrt(val);
}

float NMath::Exp(const float val)
{
	return expf(val);
}

float NMath::Ln(const float val)
{
	return logf(val);
}

float NMath::Pow(const float a, const float b)
{
	return powf(a, b);
}

double NMath::Exp(const double val)
{
	return exp(val);
}

double NMath::Ln(const double val)
{
	return log(val);
}

double NMath::Pow(const double a, const double b)
{
	return pow(a, b);
}

float NMath::Floor(const float val)
{
	return floorf(val);
}

float NMath::Ceil(const float val)
{
	return ceilf(val);
}

float NMath::Trunc(const float val)
{
	return truncf(val);
}

float NMath::Round(const float val)
{
	return roundf(val);
}

double NMath::Floor(const double val)
{
	return floor(val);
}

double NMath::Ceil(const double val)
{
	return ceil(val);
}

double NMath::Trunc(const double val)
{
	return trunc(val);
}

double NMath::Round(const double val)
{
	return round(val);
}

bool NMath::IsNormal(const float val)
{
	return isnormal(val);
}

bool NMath::IsFinite(const float val)
{
	return isfinite(val);
}

bool NMath::IsNan(const float val)
{
	return isnan(val);
}

bool NMath::IsInf(const float val)
{
	return isinf(val);
}

bool NMath::IsNormal(const double val)
{
	return isnormal(val);
}

bool NMath::IsFinite(const double val)
{
	return isfinite(val);
}

bool NMath::IsNan(const double val)
{
	return isnan(val);
}

bool NMath::IsInf(const double val)
{
	return isinf(val);
}

float NMath::Hypot(const float x, const float y)
{
	return hypotf(x, y);
}

double NMath::Hypot(const double x, const double y)
{
	return hypot(x, y);
}

float NMath::RadToDeg(float angle)
{
	return angle * 180.f / FLT_PI;
}

float NMath::DegToRad(float angle)
{
	return angle * FLT_PI / 180.f;
}

double NMath::RadToDeg(double angle)
{
	return angle * 180.0 / DBL_PI;
}

double NMath::DegToRad(double angle)
{
	return angle * DBL_PI / 180.0;
}

