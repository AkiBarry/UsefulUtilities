#pragma once

#ifndef UU_INIT
	#error "Please only include UU.hpp for now"
#endif

#include "Constants.hpp"
#include "Math.hpp"

#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <random>

namespace UU
{
	template<typename T, size_t size, bool radians /* = true */>
	class CAngle;
	
	template<typename T, size_t size>
	class CVector
	{
	private:
		T data[size];
	public:
		CVector() = default;

		template<typename... Args>
		CVector(Args... args) : CVector({std::forward<T>(static_cast<T>(args))...}) {}

		CVector(std::initializer_list<T> init_list);

		template<typename Y>
		CVector(CVector<Y, size> vec);

		constexpr void Zero();

		T & operator[](size_t i);
		T operator[](size_t i) const;

		T * Base();
		T const * Base() const;

		void CopyToArray(T * t) const;

		CVector & operator=(const CVector & v);

		CVector & operator+=(const CVector & v);
		CVector & operator-=(const CVector & v);
		CVector & operator*=(T t);
		CVector & operator/=(T t);

		CVector operator+(const CVector & v) const;
		CVector operator-(const CVector & v) const;
		CVector operator-() const;
		CVector operator*(T t) const;
		CVector operator/(T t) const;

		bool operator==(const CVector & v) const;
		bool operator!=(const CVector & v) const;

		T Length() const;
		T LengthSqr() const;

		bool IsLengthGreaterThan(T val) const;
		bool IsLengthLesserThan(T val) const;

		T DistTo(const CVector & v) const;
		T DistToSqr(const CVector & v) const;

		template<typename U, bool radians = true>
		CVector Rotated(const CAngle<U, size * (size - 1) / 2, radians> & a) const;

		template<typename U, bool radians = true>
		void RotateInPlace(const CAngle<U, size * (size - 1) / 2, radians> & a);

		bool WithinAABox(const CVector & min, const CVector & max) const;

		template <typename U, bool radians = true>
		CAngle <U, size * (size - 1) / 2, radians> ToCAngle() const;
		//CColour						ToColour() const;

		template <size_t N>
		CVector<T, N> AsCVector() const;

		template<size_t N>
		CVector<T, N> & AsCVector();

		void Negate();
		bool IsZero(T tolerance = T()) const;

		template <typename = std::enable_if_t<size == 3>>
		CVector Cross(const CVector & v) const;
		T Dot(const CVector & v) const;

		CVector Min(const CVector & v) const;
		CVector Max(const CVector & v) const;
		CVector Clamp(const CVector & min, const CVector & max) const;

		void Randomize(const CVector & min, const CVector & max);
		void Lerp(const CVector & v, T factor);

		CVector Normalized() const;
		T NormalizeInPlace();

		friend std::ostream & operator<<(std::ostream & os, const CVector<T, size> & v)
		{
			os << "(";

			for(size_t i = 0; i < size - 1; ++i)
			{
				os << v.data[i] << ", ";
			}

			os << v.data[size - 1] << ")";

			return os;
		}

		template<typename U, size_t size1, bool radians = true>
		friend class CAngle;
	};

	using CVec2f = CVector<float, 2>;
	using CVec3f = CVector<float, 3>;
	using CVec4f = CVector<float, 4>;

	using CVec2d = CVector<double, 2>;
	using CVec3d = CVector<double, 3>;
	using CVec4d = CVector<double, 4>;

	using CVec2i = CVector<int, 2>;
	using CVec3i = CVector<int, 3>;
	using CVec4i = CVector<int, 4>;

	using CVec2ui = CVector<unsigned int, 2>;
	using CVec3ui = CVector<unsigned int, 3>;
	using CVec4ui = CVector<unsigned int, 4>;

	using CVec2l = CVector<long, 2>;
	using CVec3l = CVector<long, 3>;
	using CVec4l = CVector<long, 4>;

	template<typename T, size_t size, bool radians /* = true */>
	class CAngle
	{
	private:
		T data[size];
	public:
		CAngle() = default;

		template<typename... Args>
		CAngle(Args ... args) : CAngle({static_cast<T>(args)...}) {}

		CAngle(std::initializer_list<T> init_list);

		T & operator[](size_t i);
		T operator[](size_t i) const;

		T * Base();
		T const * Base() const;

		void CopyToArray(T * t) const;

		CAngle & operator=(const CAngle & a);

		CAngle & operator+=(const CAngle & a);
		CAngle & operator-=(const CAngle & a);
		CAngle & operator*=(T t);
		CAngle & operator/=(T t);

		CAngle operator+(const CAngle & a) const;
		CAngle operator-(const CAngle & a) const;
		CAngle operator*(T t) const;
		CAngle operator/(T t) const;

		bool operator==(const CAngle & a) const;
		bool operator!=(const CAngle & a) const;

		T Length() const;
		T LengthSqr() const;

		CVector<T, size> ToCVector() const;
		CVector<T, size> Forward() const;
		CVector<T, size> Right() const;
		CVector<T, size> Up() const;
		//CMatrix3x4				ToMatrix3x4() const;

		void Negate();
		bool IsValid() const;

		CAngle Min(const CAngle & a) const;
		CAngle Max(const CAngle & a) const;
		CAngle Clamp(const CAngle & min, const CAngle & max) const;

		void Randomize(const CAngle & min, const CAngle & max);
		void Lerp(const CAngle & a, T factor);

		CAngle Normalized() const;
		void NormalizeInPlace();

		friend std::ostream & operator<<(std::ostream & os, const CAngle<T, size, radians> & a)
		{
			os << "(";

			for(size_t i = 0; i < size - 1; ++i)
			{
				os << a.data[i] << ", ";
			}

			os << a.data[size - 1] << ")";

			return os;
		}

		template<typename U, size_t size1>
		friend class CVector;
	};

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
}

template<typename T, size_t size>
UU::CVector<T, size>::CVector(std::initializer_list<T> init_list)
{
	auto it = init_list.begin();
	for (size_t i = 0; it != init_list.end(); ++i, ++it)
	{
		data[i] = *it;
	}
}

template<typename T, size_t size>
template<typename Y>
UU::CVector<T, size>::CVector(UU::CVector<Y, size> vec)
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = static_cast<T>(vec[i]);
	}
}

template<typename T, size_t size>
constexpr void UU::CVector<T, size>::Zero()
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = T();
	}
}

template<typename T, size_t size>
T& UU::CVector<T, size>::operator[](size_t i)
{
	return data[i];
}

template<typename T, size_t size>
T UU::CVector<T, size>::operator[](size_t i) const
{
	return data[i];
}

template<typename T, size_t size>
T* UU::CVector<T, size>::Base()
{
	return reinterpret_cast<T*>(this);
}

template<typename T, size_t size>
T const* UU::CVector<T, size>::Base() const
{
	return reinterpret_cast<const T*>(this);
}

template<typename T, size_t size>
void UU::CVector<T, size>::CopyToArray(T* t) const
{
	for (size_t i = 0; i < size; ++i)
	{
		t[i] = data[i];
	}
}

template<typename T, size_t size>
UU::CVector<T, size>& UU::CVector<T, size>::operator=(const CVector& v)
{
	for (int i = 0; i < size; ++i)
		data[i] = v.data[i];

	return *this;
}

template<typename T, size_t size>
UU::CVector<T, size>& UU::CVector<T, size>::operator+=(const CVector & v)
{
	for (int i = 0; i < size; ++i)
		data[i] += v.data[i];

	return *this;
}

template<typename T, size_t size>
UU::CVector<T, size>& UU::CVector<T, size>::operator-=(const CVector & v)
{
	for (int i = 0; i < size; ++i)
		data[i] -= v.data[i];

	return *this;
}

template<typename T, size_t size>
UU::CVector<T, size>& UU::CVector<T, size>::operator*=(T t)
{
	for (int i = 0; i < size; ++i)
		data[i] *= t;

	return *this;
}

template<typename T, size_t size>
UU::CVector<T, size>& UU::CVector<T, size>::operator/=(T t)
{
	if constexpr (std::is_floating_point<T>::value)
	{
		const T inv_t = static_cast<T>(1) / t;

		for (int i = 0; i < size; ++i)
			data[i] *= inv_t;
	}
	else
	{
		for (int i = 0; i < size; ++i)
			data[i] /= t;
	}


	return *this;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::operator+(const CVector & v) const
{
	CVector<T, size> temp;

	for (size_t i = 0; i < size; ++i)
		temp.data[i] = data[i] + v.data[i];

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::operator-(const CVector & v) const
{
	CVector<T, size> temp;

	for (int i = 0; i < size; ++i)
		temp.data[i] = data[i] - v.data[i];

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::operator-() const
{
	CVector<T, size> temp;

	for (int i = 0; i < size; ++i)
		temp.data[i] = -data[i];

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::operator*(T t) const
{
	CVector<T, size> temp;

	for (size_t i = 0; i < size; ++i)
		temp.data[i] = data[i] * t;

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::operator/(T t) const
{
	CVector<T, size> temp;

	if constexpr (std::is_floating_point<T>::value)
	{
		const T inv_t = static_cast<T>(1) / t;

		for (int i = 0; i < size; ++i)
			temp.data[i] = data[i] * inv_t;
	}
	else
	{
		for (int i = 0; i < size; ++i)
			temp.data[i] = data[i] / t;
	}

	return temp;
}

template<typename T, size_t size>
bool UU::CVector<T, size>::operator==(const CVector & v) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] != v.data[i])
			return false;
	}

	return true;
}

template<typename T, size_t size>
bool UU::CVector<T, size>::operator!=(const CVector & v) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] != v.data[i])
			return true;
	}

	return false;
}

template<typename T, size_t size>
T UU::CVector<T, size>::Length() const
{
	T temp = T();

	for (int i = 0; i < size; ++i)
		temp += data[i] * data[i];

	return UU::Sqrt(temp);
}

template<typename T, size_t size>
T UU::CVector<T, size>::LengthSqr() const
{
	T temp = T();

	for (int i = 0; i < size; ++i)
		temp += data[i] * data[i];

	return temp;
}

template<typename T, size_t size>
bool UU::CVector<T, size>::IsLengthGreaterThan(T val) const
{
	return LengthSqr() > val* val;
}

template<typename T, size_t size>
bool UU::CVector<T, size>::IsLengthLesserThan(T val) const
{
	return LengthSqr() < val* val;
}

template<typename T, size_t size>
T UU::CVector<T, size>::DistTo(const CVector & v) const
{
	CVector temp = v - *this;

	return temp.Length();
}

template<typename T, size_t size>
T UU::CVector<T, size>::DistToSqr(const CVector & v) const
{
	CVector temp = v - *this;

	return temp.Length();
}

template<typename T, size_t size>
template<typename U, bool radians>
UU::CVector<T, size> UU::CVector<T, size>::Rotated(
	const CAngle<U, size * (size - 1) / 2, radians> & a) const
{
	CVector<T, size> temp = *this;

	if constexpr (size == 2)
	{
		float s, c;

		UU::SinCos(a[0], s, c);

		temp[0] = (*this).Dot(CVec2f(c, -s));
		temp[1] = (*this).Dot(CVec2f(s, c));
	}
	else if constexpr (size == 3)
	{
		float sp, sy, sr, cp, cy, cr;

		UU::SinCos(DegToRad(a[0]), sp, cp);
		UU::SinCos(DegToRad(a[1]), sy, cy);
		UU::SinCos(DegToRad(a[2]), sr, cr);

		const float cr_cy = cr * cy;
		const float cr_sy = cr * sy;
		const float sr_cy = sr * cy;
		const float sr_sy = sr * sy;

		temp[0] = (*this).Dot(CVec3f(cp * cy, sp * sr_cy - cr_sy, sp * cr_cy + sr_sy));
		temp[1] = (*this).Dot(CVec3f(cp * sy, sp * sr_sy + cr_cy, sp * cr_sy - sr_cy));
		temp[2] = (*this).Dot(CVec3f(-sp, sr * cp, cr * cp));
	}

	return temp;
}

template<typename T, size_t size>
template<typename U, bool radians>
void UU::CVector<T, size>::RotateInPlace(const CAngle<U, size * (size - 1) / 2, radians> & a)
{
	*this = Rotated(a);
}

template<typename T, size_t size>
bool UU::CVector<T, size>::WithinAABox(const CVector & min, const CVector & max) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] < min.data[i] || data[i] > max.data[i])
			return false;
	}

	return true;
}

template<typename T, size_t size>
template<typename U, bool radians>
UU::CAngle<U, size * (size - 1) / 2, radians> UU::CVector<T, size>::ToCAngle() const
{
	auto normalized_vec = this->Normalized();
	CAngle<U, size * (size - 1) / 2, radians> temp;

	if constexpr (size == 1)
	{
		temp = CAngle<U, size * (size - 1) / 2, radians>();
	}
	else if constexpr (size == 2)
	{
		temp = CAngle<U, size * (size - 1) / 2, radians>(UU::ATan2(U(normalized_vec.data[1])));
	}
	else if constexpr (size == 3)
	{
		temp = CAngle<U, size * (size - 1) / 2, radians>(UU::ASin(U(normalized_vec.data[2])),
			UU::ATan2(U(normalized_vec.data[1]), U(normalized_vec.data[0])));
	}
	else
	{
		temp.Zero();
	}

	if constexpr (!radians)
		return temp * U(DBL_RAD2DEG);

	return temp;
}

template<typename T, size_t size>
template<size_t N>
auto UU::CVector<T, size>::AsCVector() const -> CVector<T, N>
{
	static_assert(N <= size);

	return *reinterpret_cast<const CVector<T, N>*>(this);
}

template<typename T, size_t size>
template<size_t N>
auto UU::CVector<T, size>::AsCVector() -> CVector<T, N> &
{
	static_assert(N <= size);

	return *reinterpret_cast<CVector<T, N>*>(this);
}

template<typename T, size_t size>
void UU::CVector<T, size>::Negate()
{
	if constexpr (!std::is_signed<T>::type)
		return;

	for (int i = 0; i < size; ++i)
	{
		data[i] = -data[i];
	}
}

template<typename T, size_t size>
bool UU::CVector<T, size>::IsZero(T tolerance) const
{
	for (int i = 0; i < size; ++i)
	{
		if (Abs(data[i]) > tolerance)
			return false;
	}

	return true;
}

template<typename T, size_t size>
template<typename>
UU::CVector<T, size> UU::CVector<T, size>::Cross(const CVector & v) const
{
	static_assert(size == 3);

	CVector<T, size> temp;

	temp.data[0] = data[1] * v.data[2] - data[2] * v.data[1];
	temp.data[1] = data[2] * v.data[0] - data[0] * v.data[2];
	temp.data[2] = data[0] * v.data[1] - data[1] * v.data[0];

	return temp;
}

template<typename T, size_t size>
T UU::CVector<T, size>::Dot(const CVector & v) const
{
	T temp = T();

	for (int i = 0; i < size; ++i)
		temp += data[i] * v.data[i];

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::Min(const CVector & v) const
{
	CVector temp;

	for (int i = 0; i < size; ++i)
		temp[i] = UU::Min(data[i], v.data[i]);

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::Max(const CVector & v) const
{
	CVector temp;

	for (int i = 0; i < size; ++i)
		temp[i] = UU::Max(data[i], v.data[i]);

	return temp;
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::Clamp(const CVector & min, const CVector & max) const
{
	CVector temp;

	for (int i = 0; i < size; ++i)
		temp[i] = UU::Clamp(data[i], min.data[i], max.data[i]);

	return temp;
}

template<typename T, size_t size>
void UU::CVector<T, size>::Randomize(const CVector & min, const CVector & max)
{
	std::random_device pure;
	std::mt19937 gen(pure());

	for (int i = 0; i < size; ++i)
	{
		std::uniform_real_distribution<T> dist(min.data[i], max.data[i]);
		data[i] = dist(gen);
	}
}

template<typename T, size_t size>
void UU::CVector<T, size>::Lerp(const CVector & v, T factor)
{
	for (int i = 0; i < size; ++i)
		data[i] = Lerp(data[i], v.data[i], factor);
}

template<typename T, size_t size>
UU::CVector<T, size> UU::CVector<T, size>::Normalized() const
{
	CVector temp = *this;

	T len = Length();

	temp /= len;

	return temp;
}

template<typename T, size_t size>
T UU::CVector<T, size>::NormalizeInPlace()
{
	T len = Length();

	*this /= len;

	return len;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians>::CAngle(std::initializer_list<T> init_list)
{
	auto it = init_list.begin();

	for (auto i = 0; it != init_list.end(); ++i, ++it)
	{
		data[i] = *it;
	}
}

template<typename T, size_t size, bool radians>
T& UU::CAngle<T, size, radians>::operator[](size_t i)
{
	return data[i];
}

template<typename T, size_t size, bool radians>
T UU::CAngle<T, size, radians>::operator[](size_t i) const
{
	return data[i];
}

template<typename T, size_t size, bool radians>
T* UU::CAngle<T, size, radians>::Base()
{
	return reinterpret_cast<T*>(this);
}

template<typename T, size_t size, bool radians>
T const* UU::CAngle<T, size, radians>::Base() const
{
	return reinterpret_cast<const T*>(this);
}

template<typename T, size_t size, bool radians>
void UU::CAngle<T, size, radians>::CopyToArray(T * t) const
{
	for (size_t i = 0; i < size; ++i)
	{
		t[i] = data[i];
	}
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians>& UU::CAngle<T, size, radians>::operator=(const CAngle & a)
{
	for (int i = 0; i < size; ++i)
		data[i] = a.data[i];

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians>& UU::CAngle<T, size, radians>::operator+=(const CAngle & a)
{
	for (int i = 0; i < size; ++i)
		data[i] += a.data[i];

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians>& UU::CAngle<T, size, radians>::operator-=(const CAngle & a)
{
	for (int i = 0; i < size; ++i)
		data[i] -= a.data[i];

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians>& UU::CAngle<T, size, radians>::operator*=(T t)
{
	for (int i = 0; i < size; ++i)
		data[i] *= t;

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians>& UU::CAngle<T, size, radians>::operator/=(T t)
{
	for (int i = 0; i < size; ++i)
		data[i] /= t;

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::operator+(const CAngle & a) const
{
	CAngle<T, size, radians> temp;

	for (int i = 0; i < size; ++i)
		temp.data[i] = data[i] + a.data[i];

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::operator-(const CAngle & a) const
{
	CAngle<T, size, radians> temp;

	for (int i = 0; i < size; ++i)
		temp.data[i] = data[i] - a.data[i];

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::operator*(T t) const
{
	CAngle<T, size, radians> temp;

	for (size_t i = 0; i < size; ++i)
		temp.data[i] = data[i] * t;

	return temp;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::operator/(T t) const
{
	CAngle<T, size, radians> temp;

	for (int i = 0; i < size; ++i)
		temp.data[i] = data[i] / t;

	return *this;
}

template<typename T, size_t size, bool radians>
bool UU::CAngle<T, size, radians>::operator==(const CAngle & a) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] != a.data[i])
			return false;
	}

	return true;
}

template<typename T, size_t size, bool radians>
bool UU::CAngle<T, size, radians>::operator!=(const CAngle & a) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] != a.data[i])
			return true;
	}

	return false;
}

template<typename T, size_t size, bool radians>
T UU::CAngle<T, size, radians>::Length() const
{
	T temp = T();

	for (int i = 0; i < size; ++i)
		temp += data[i] * data[i];

	return Sqrt(temp);
}

template<typename T, size_t size, bool radians>
T UU::CAngle<T, size, radians>::LengthSqr() const
{
	T temp = T();

	for (int i = 0; i < size; ++i)
		temp += data[i] * data[i];

	return temp;
}

template<typename T, size_t size, bool radians>
UU::CVector<T, size> UU::CAngle<T, size, radians>::ToCVector() const
{
	return Forward();
}

template<typename T, size_t size, bool radians>
UU::CVector<T, size> UU::CAngle<T, size, radians>::Forward() const
{
	CVector<T, size> temp;

	if constexpr (size == 2)
	{
		T sx, cx;

		SinCos(radians ? data[0] : DegToRad(data[0]), sx, cx);

		temp.data[0] = sx;
		temp.data[1] = -cx;
	}

	if constexpr (size == 3)
	{
		T sx, cx, sy, cy;

		SinCos(radians ? data[0] : DegToRad(data[0]), sx, cx);
		SinCos(radians ? data[1] : DegToRad(data[1]), sy, cy);

		temp.data[0] = sx * cy;
		temp.data[1] = sx * sy;
		temp.data[2] = cx;
	}

	return temp;
}

template<typename T, size_t size, bool radians>
UU::CVector<T, size> UU::CAngle<T, size, radians>::Right() const
{
	CVector<T, size> temp;

	if constexpr (size == 3)
	{
		T sx, cx, sy, cy, sz, cz;

		SinCos(radians ? data[0] : DegToRad(data[0]), sx, cx);
		SinCos(radians ? data[1] : DegToRad(data[1]), sy, cy);
		SinCos(radians ? data[2] : DegToRad(data[2]), sz, cz);

		temp.data[0] = cx * sy;
		temp.data[1] = (sx * sy * sz) + (cy * cz);
		temp.data[2] = (sx * sy * cz) - (cy * sz);
	}

	return temp;
}

template<typename T, size_t size, bool radians>
UU::CVector<T, size> UU::CAngle<T, size, radians>::Up() const
{
	CVector<T, size> temp;

	if constexpr (size == 3)
	{
		T sx, cx, sy, cy, sz, cz;

		SinCos(radians ? data[0] : DegToRad(data[0]), sx, cx);
		SinCos(radians ? data[1] : DegToRad(data[1]), sy, cy);
		SinCos(radians ? data[2] : DegToRad(data[2]), sz, cz);

		temp.data[0] = -sx;
		temp.data[1] = cx * sz;
		temp.data[2] = cx * cz;
	}

	return temp;
}

template<typename T, size_t size, bool radians>
void UU::CAngle<T, size, radians>::Negate()
{
	for (int i = 0; i < size; ++i)
		data[i] = -data[i];
}

template<typename T, size_t size, bool radians>
bool UU::CAngle<T, size, radians>::IsValid() const
{
	if constexpr (!std::is_floating_point<T>::value)
		return true;

	for (int i = 0; i < size; ++i)
	{
		if (!std::isfinite(data[i]))
			return false;
	}

	return true;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::Min(const CAngle & a) const
{
	CAngle<T, size, radians> temp;

	for (size_t i = 0; i < size; ++i)
		temp.data[i] = Min(data[i], a.data[i]);

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::Max(const CAngle & a) const
{
	CAngle<T, size, radians> temp;

	for (size_t i = 0; i < size; ++i)
		temp.data[i] = Max(data[i], a.data[i]);

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::Clamp(
	const CAngle & min, const CAngle & max) const
{
	CAngle<T, size, radians> temp;

	for (int i = 0; i < size; ++i)
		temp[i] = Clamp(data[i], min.data[i], max.data[i]);

	return *this;
}

template<typename T, size_t size, bool radians>
void UU::CAngle<T, size, radians>::Randomize(const CAngle & min, const CAngle & max)
{
	std::random_device pure;
	std::mt19937 gen(pure());

	for (int i = 0; i < size; ++i)
	{
		std::uniform_real_distribution<T> dist(min.data[i], max.data[i]);
		data[i] = dist(gen);
	}
}

template<typename T, size_t size, bool radians>
void UU::CAngle<T, size, radians>::Lerp(const CAngle & a, T factor)
{
	for (size_t i = 0; i < size; ++i)
		data[i] = Lerp(data[i], a.data[i], factor);

	return *this;
}

template<typename T, size_t size, bool radians>
UU::CAngle<T, size, radians> UU::CAngle<T, size, radians>::Normalized() const
{
	CAngle temp = *this;
	temp.NormalizeInPlace();

	return temp;
}

template<typename T, size_t size, bool radians>
void UU::CAngle<T, size, radians>::NormalizeInPlace()
{
	for (size_t i = 0; i < size; ++i)
	{
		Mod(data[i], radians ? T(DBL_PI * 2) : T(360));
	}
}

/*
CMatrix3x4 CAng::ToMatrix3x4() const
{
	CMatrix3x4 temp;

	float sp, sy, sr, cp, cy, cr;

	SinCos(DegToRad(x), sp, cp);
	SinCos(DegToRad(y), sy, cy);
	SinCos(DegToRad(z), sr, cr);

	temp[0][0] = cp * cy;
	temp[1][0] = cp * sy;
	temp[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	temp[0][1] = sp * srcy - crsy;
	temp[1][1] = sp * srsy + crcy;
	temp[2][1] = sr * cp;

	temp[0][2] = sp * crcy + srsy;
	temp[1][2] = sp * crsy - srcy;
	temp[2][2] = cr * cp;

	temp[0][3] = 0.0f;
	temp[1][3] = 0.0f;
	temp[2][3] = 0.0f;

	return temp;
}
*/
