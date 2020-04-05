#pragma once

#ifndef UU_INIT
	#error "Please only include UU.hpp for now"
#endif

#include <array>
inline int nextval = 0;

namespace UU
{
	template <typename T, size_t rows, size_t columns>
	class CMatrix
	{
	public:
		T** data;

		CMatrix();
		
		template<typename U>
		CMatrix(const CMatrix<U, rows, columns>& init_mat);
		CMatrix(CMatrix<T, rows, columns>&& init_mat) noexcept : data(std::exchange(init_mat.data, nullptr)) {}
		
		CMatrix(std::array<std::array<T, columns>, rows> init_mat);

		~CMatrix();

		constexpr void									Zero();

		T*												operator[](size_t i);
		const T*										operator[](size_t i) const;

		CMatrix&										operator=(const CMatrix<T, rows, columns>& m);
		CMatrix&										operator=(CMatrix<T, rows, columns>&& m) noexcept;

		CMatrix&										operator+=(const CMatrix& m);
		CMatrix&										operator-=(const CMatrix& m);

		template<typename U, typename = std::enable_if_t<rows == columns>>
		CMatrix&										operator*=(const CMatrix<U, rows, columns>& m);

		CMatrix&										operator*=(T t);
		CMatrix&										operator/=(T t);

		CMatrix											operator+(const CMatrix& m) const;
		CMatrix											operator-(const CMatrix& m) const;

		template<typename U, size_t columns1>
		CMatrix<decltype(T() * U()), rows, columns1>	operator*(const CMatrix<U, columns, columns1> & m) const;

		template<typename U>
		CMatrix<decltype(T() * U()), rows, columns>		operator*(U val) const;
		
		template<typename U>
		CMatrix<decltype(T() * U()), rows, columns>		operator/(U val) const;

		bool											operator==(const CMatrix& m) const;
		bool											operator!=(const CMatrix& m) const;

		template<typename = std::enable_if_t<(rows > 0 && columns > 0)>>
		T												Det() const;

		void											Randomize(T min, T max);

		CMatrix<T, rows - 1, columns - 1>				Cofactor(size_t row_index, size_t col_index) const;

		CMatrix<T, rows, columns>						Transpose() const;
		void											TransposeInPlace();

		void											Negate();
		bool											IsZero() const;

		friend std::ostream & operator<<(std::ostream & os, const CMatrix & v)
		{
			for(size_t i = 0; i < rows; ++i)
			{
				for (size_t j = 0; j < columns; ++j)
				{
					os << v.data[i][j] << " ";
				}
				os << "\n";
			}

			return os;
		}

		template <typename U, size_t rows1, size_t columns1>
		friend class CMatrix;
	};
}

template<typename T, size_t rows, size_t columns>
constexpr void UU::CMatrix<T, rows, columns>::Zero()
{
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			data[i][j] = T();
}

template<typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns>::CMatrix()
{
	data = new T*[rows];
	for (size_t i = 0; i < rows; ++i)
		data[i] = new T[columns];
}

template<typename T, size_t rows, size_t columns>
template<typename U>
UU::CMatrix<T, rows, columns>::CMatrix(const CMatrix<U, rows, columns>& init_mat)
{
	CMatrix();
	
	for (int i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			data[i][j] = T(init_mat[i][j]);
}

template<typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns>::CMatrix(std::array<std::array<T, columns>, rows> init_mat)
{
	CMatrix();
	
	for (int i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			data[i][j] = init_mat[i][j];
}

template<typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns>::~CMatrix()
{
	if(data == nullptr)
		return;
	
	for (size_t i = 0; i < rows; ++i)
	{
		delete[] data[i];
	}

	delete[] data;
}

template <typename T, size_t rows, size_t columns>
T* UU::CMatrix<T, rows, columns>::operator[](size_t i)
{
	return data[i];
}

template <typename T, size_t rows, size_t columns>
const T* UU::CMatrix<T, rows, columns>::operator[](size_t i) const
{
	return data[i];
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns>& UU::CMatrix<T, rows, columns>::operator=(const CMatrix & m)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			data[i][j] = m.data[i][j];

	return *this;
}

template<typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> & UU::CMatrix<T, rows, columns>::operator=(CMatrix<T, rows, columns> && m) noexcept
{
	 data = std::exchange(m.data, nullptr);
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> & UU::CMatrix<T, rows, columns>::operator+=(const CMatrix & m)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			data[i][j] += m.data[i][j];

	return *this;
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> & UU::CMatrix<T, rows, columns>::operator-=(const CMatrix & m)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			data[i][j] -= m.data[i][j];

	return *this;
}

template<typename T, size_t rows, size_t columns>
template<typename U, typename>
UU::CMatrix<T, rows, columns> & UU::CMatrix<T, rows, columns>::operator*=(const CMatrix<U, rows, columns> & m)
{
	CMatrix<T, rows, columns> temp;
	temp.Zero();

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			for (size_t k = 0; k < columns; ++k)
				temp.data[i][j] += data[i][k] * m.data[k][j];

	*this = std::move(temp);

	return *this;
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> & UU::CMatrix<T, rows, columns>::operator*=(T t)
{
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			data[i][j] *= t;

	return *this;
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> & UU::CMatrix<T, rows, columns>::operator/=(T t)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			data[i][j] /= t;

	return *this;
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> UU::CMatrix<T, rows, columns>::operator+(const CMatrix & m) const
{
	CMatrix temp;

	temp += std::forward<CMatrix>(m);

	return temp;
}

template <typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> UU::CMatrix<T, rows, columns>::operator-(const CMatrix & m) const
{
	CMatrix temp;

	temp -= std::forward<CMatrix>(m);

	return temp;
}

template<typename T, size_t rows, size_t columns>
template<typename U, size_t columns1>
UU::CMatrix<decltype(T() * U()), rows, columns1> UU::CMatrix<T, rows, columns>::operator*(
	const CMatrix<U, columns, columns1> & m) const
{
	CMatrix<decltype(T() * U()), rows, columns1> temp;
	temp.Zero();
	
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns1; ++j)
			for (size_t k = 0; k < columns; ++k)
				temp.data[i][j] += data[i][k] * m.data[k][j];

	return temp;
}

template <typename T, size_t rows, size_t columns>
template<typename U>
UU::CMatrix<decltype(T() * U()), rows, columns> UU::CMatrix<T, rows, columns>::operator*(U val) const
{
	CMatrix<decltype(T() * U()), rows, columns> temp = *this;

	temp *= val;

	return temp;
}

template <typename T, size_t rows, size_t columns>
template<typename U>
UU::CMatrix<decltype(T() * U()), rows, columns> UU::CMatrix<T, rows, columns>::operator/(U val) const
{
	CMatrix<decltype(T() * U()), rows, columns> temp = *this;

	temp /= val;

	return *this;
}

template <typename T, size_t rows, size_t columns>
bool UU::CMatrix<T, rows, columns>::operator==(const CMatrix & m) const
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
		{
			if (data[i][j] != m.data[i][j])
				return false;
		}

	return true;
}

template <typename T, size_t rows, size_t columns>
bool UU::CMatrix<T, rows, columns>::operator!=(const CMatrix & m) const
{
	return !(*this == m);
}

template<typename T, size_t size>
T DetHelper(UU::CMatrix<T, size, size> m)
{
	if constexpr (size == 1)
	{
		return m[0][0];
	}
	else
	{
		T val = T(0);

		bool sign = true;

		for (size_t i = 0; i < size; ++i)
		{
			val += (sign ? T(1) : T(-1)) * m[0][i] * m.Cofactor(0, i).Det();

			sign = !sign;
		}

		return val;
	}
}

	

template<typename T, size_t rows, size_t columns>
template<typename>
T UU::CMatrix<T, rows, columns>::Det() const
{
	static_assert(rows == columns, "Matrix must be square");

	constexpr size_t size = rows;

	if constexpr (size == 1)
		return data[0][0];
	
	if constexpr (size == 2)
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];

	return DetHelper<T, size>(*this);
}

template<typename T, size_t rows, size_t columns>
void UU::CMatrix<T, rows, columns>::Randomize(T min, T max)
{
	std::random_device pure;
	std::mt19937 gen(pure());
	std::uniform_real_distribution<T> dist(min, max);
	
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			data[i][j] = dist(gen);
}

template<typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows - 1, columns - 1>
		UU::CMatrix<T, rows, columns>::Cofactor(size_t row_index, size_t col_index) const
{
	static_assert(rows > 1 || columns > 1);
	
	CMatrix<T, rows - 1, columns - 1> temp{};

	for (size_t i = 0, m = 0; i < rows; ++i)
	{
		if (i == row_index)
			continue;

		for (size_t j = 0, n = 0; j < columns; ++j)
		{
			if (j == col_index)
				continue;

			temp.data[m][n] = this->data[i][j];

			++n;
		}
		++m;
	}
	
	return temp;
}

template<typename T, size_t rows, size_t columns>
UU::CMatrix<T, rows, columns> UU::CMatrix<T, rows, columns>::Transpose() const
{
	CMatrix<T, columns, rows> temp = *this;

	temp.TransposeInPlace();

	return std::move(temp);
}

template<typename T, size_t rows, size_t columns>
void UU::CMatrix<T, rows, columns>::TransposeInPlace()
{
	static_assert(rows == columns);

	for (int i = 0; i < rows; ++i)
		for (int j = i + 1; j < columns; ++j)
			data[i][j] = data[j][i];
}

template <typename T, size_t rows, size_t columns>
void UU::CMatrix<T, rows, columns>::Negate()
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			data[i][j] = -data[i][j];
}

template <typename T, size_t rows, size_t columns>
bool UU::CMatrix<T, rows, columns>::IsZero() const
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
		{
			if (data[i][j] != T())
				return false;
		}

	return true;
}
