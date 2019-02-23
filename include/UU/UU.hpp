#pragma once

namespace UU
{
	class CColour;
	class CHSB;

	template <typename T, size_t dim>
	class CVector;

	template <typename T, size_t dim, bool radian = false>
	class CAngle;

	template <typename T, size_t rows, size_t columns>
	class CMatrix;

	template <typename T>
	class CRandom;

	using CVec2f = CVector<float, 2>;
	using CVec3f = CVector<float, 3>;
	using CVec4f = CVector<float, 4>;

	using CVec2d = CVector<double, 2>;
	using CVec3d = CVector<double, 3>;
	using CVec4d = CVector<double, 4>;

	using CVec2i = CVector<int, 2>;
	using CVec3i = CVector<int, 3>;
	using CVec4i = CVector<int, 4>;

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