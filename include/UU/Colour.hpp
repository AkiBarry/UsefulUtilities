#pragma once
#include <cstdint>
#include "UU.hpp"

class UU::CColour final
{
public:

	uint8_t							r, g, b, a;

	constexpr CColour() : r(0), g(0), b(0), a(255) {}
	CColour(const CColour & col) = default;
	CColour(CColour && col) = default;
	~CColour() = default;

	CColour(uint8_t x, uint8_t y, uint8_t z, uint8_t w = 255)
		: r(x), g(y), b(z), a(w) {}

	CColour(int32_t x, int32_t y, int32_t z, int32_t w = 255)
		: CColour(static_cast<uint8_t>(x), static_cast<uint8_t>(y), static_cast<uint8_t>(z), static_cast<uint8_t>(w)) {}

	CColour(uint32_t c);

	uint8_t &						operator[](int i);
	uint8_t							operator[](int i) const;

	uint8_t *						Base();
	uint8_t const *					Base() const;

	void							CopyToArray(uint8_t * col) const;

	CColour &						operator=(const CColour & col) = default;
	CColour &						operator=(CColour && col) = default;

	bool							operator==(CColour col) const;
	bool							operator!=(CColour col) const;

	uint32_t						ToD3DColour() const;
	CHSB							ToHSB() const;
	CVec4f							ToVector() const;

	uint32_t &						AsRawColour();
	const uint32_t &				AsRawColour() const;

	float							Hue() const;
	float							Saturation() const;
	float							Brightness() const;

	static const		CColour		Black;
	static const		CColour		White;
	static const		CColour		Red;
	static const		CColour		Green;
	static const		CColour		Blue;
	static const		CColour		Yellow;
	static const		CColour		Cyan;
	static const		CColour		Magenta;
};

class UU::CHSB final
{
public:

	float			h, s, b;

	CHSB() : h(0.f), s(0.f), b(0.f) {}
	CHSB(const CHSB & col) = default;
	CHSB(CHSB && col) = default;
	~CHSB() = default;

	CHSB(float x, float y, float z) : h(x), s(y), b(z) {}

	float &			operator[](int i);
	float			operator[](int i) const;

	float *			Base();
	float const *	Base() const;

	void			CopyToArray(float* f) const;

	CHSB &			operator=(const CHSB & hsb) = default;
	CHSB &			operator=(CHSB && hsb) = default;

	bool			operator==(const CHSB & hsb) const;
	bool			operator!=(const CHSB & hsb) const;

	CColour			ToColour() const;
};

#include "Vector.hpp"

// CColour - Static Values

const UU::CColour UU::CColour::Black(0, 0, 0);
const UU::CColour UU::CColour::White(255, 255, 255);
const UU::CColour UU::CColour::Red(255, 0, 0);
const UU::CColour UU::CColour::Green(0, 255, 0);
const UU::CColour UU::CColour::Blue(0, 0, 255);
const UU::CColour UU::CColour::Yellow(255, 255, 0);
const UU::CColour UU::CColour::Cyan(0, 255, 255);
const UU::CColour UU::CColour::Magenta(255, 0, 255);


// CColour - Function Definitions

inline UU::CColour::CColour(uint32_t c)
{
	*reinterpret_cast<uint32_t *>(this) = c;
}

inline uint8_t & UU::CColour::operator[](int i)
{
	return reinterpret_cast<uint8_t *>(this)[i];
}

inline uint8_t UU::CColour::operator[](int i) const
{
	return reinterpret_cast<const uint8_t *>(this)[i];
}

inline uint8_t * UU::CColour::Base()
{
	return reinterpret_cast<uint8_t *>(this);
}

inline uint8_t const * UU::CColour::Base() const
{
	return reinterpret_cast<uint8_t const *>(this);
}

inline void UU::CColour::CopyToArray(uint8_t * col) const
{
	*reinterpret_cast<uint32_t *>(col) = *reinterpret_cast<uint32_t const *>(this);
}

inline bool UU::CColour::operator==(CColour col) const
{
	return *reinterpret_cast<const uint32_t *>(this) == *reinterpret_cast<const uint32_t *>(&col);
}

inline bool UU::CColour::operator!=(CColour col) const
{
	return *reinterpret_cast<const uint32_t *>(this) != *reinterpret_cast<const uint32_t*>(&col);
}

inline uint32_t UU::CColour::ToD3DColour() const
{
	return static_cast<uint32_t>((a << 24) | (r << 16) | (g << 8) | b);
}

inline UU::CHSB UU::CColour::ToHSB() const
{
	CHSB temp;
	const float _r = r / 255.0f,
		_g = g / 255.0f,
		_b = b / 255.0f;

	const float max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;

	temp.b = (max + min) / 2.0f;

	if (max != min)
	{
		if (temp.b <= 0.5f)
			temp.s = (max - min) / (max + min);
		else
			temp.s = (max - min) / (2 - max - min);
	}
	else
		temp.s = 0;

	const float delta = max - min;
	float hue = 0.0f;

	if (_r == max)
		hue = (_g - _b) / delta;
	else if (_g == max)
		hue = 2 + (_b - _r) / delta;
	else if (_b == max)
		hue = 4 + (_r - _g) / delta;

	hue *= 60;

	if (hue < 0.f)
		hue += 360.0f;

	temp.h = hue;

	return temp;
}

inline UU::CVec4f UU::CColour::ToVector() const
{
	return CVec4f(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

inline uint32_t & UU::CColour::AsRawColour()
{
	return *reinterpret_cast<uint32_t *>(this);
}

inline const uint32_t & UU::CColour::AsRawColour() const
{
	return *reinterpret_cast<const uint32_t *>(this);
}

inline float UU::CColour::Hue() const
{
	if (r == g && g == b)
		return 0.f;

	const float _r = r / 255.0f,
		_g = g / 255.0f,
		_b = b / 255.0f;

	const float max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;
	const float delta = max - min;
	float hue = 0.f;

	if (_r == max)
	{
		hue = (_g - _b) / delta;
	}
	else if (_g == max)
	{
		hue = 2 + (_b - _r) / delta;
	}
	else if (_b == max)
	{
		hue = 4 + (_r - _g) / delta;
	}
	hue *= 60.f;

	if (hue < 0.f)
	{
		hue += 360.0f;
	}
	return hue;
}

inline float UU::CColour::Saturation() const
{
	const float _r = r / 255.0f,
		_g = g / 255.0f,
		_b = b / 255.0f;

	const float max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;
	float l, s = 0;

	if (max != min)
	{
		l = (max + min) / 2;
		if (l <= 0.5f)
			s = (max - min) / (max + min);
		else
			s = (max - min) / (2 - max - min);
	}
	return s;
}

inline float UU::CColour::Brightness() const
{
	const float _r = r / 255.0f,
		_g = g / 255.0f,
		_b = b / 255.0f;

	const float	max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;
	return (max + min) / 2.0f;
}

// CHSB - Function Definitions

inline float & UU::CHSB::operator[](const int i)
{
	return reinterpret_cast<float *>(this)[i];
}

inline float UU::CHSB::operator[](const int i) const
{
	return reinterpret_cast<const float *>(this)[i];
}

inline float * UU::CHSB::Base()
{
	return reinterpret_cast<float*>(this);
}

inline float const * UU::CHSB::Base() const
{
	return reinterpret_cast<float const*>(this);
}

inline void UU::CHSB::CopyToArray(float* f) const
{
	f[0] = h;
	f[1] = s;
	f[2] = b;
}

inline bool UU::CHSB::operator==(const CHSB & hsb) const
{
	return h == hsb.h
		&& s == hsb.s
		&& b == hsb.b;
}

inline bool UU::CHSB::operator!=(const CHSB & hsb) const
{
	return h != hsb.h
		|| s != hsb.s
		|| b != hsb.b;
}

inline UU::CColour UU::CHSB::ToColour() const
{
	float	hue = h == 1.0f ? 0.0f : h * 6.0f;
	float	f = hue - static_cast<int>(hue);
	float	_r = b * 255.0f;
	const auto	r = static_cast<uint8_t>(_r),
		p = static_cast<uint8_t>(_r * (1.0f - s)),
		q = static_cast<uint8_t>(_r * (1.0f - s * f));
	const auto	t = static_cast<uint8_t>(_r * (1.0f - (s * (1.0f - f))));

	if (hue < 1.0f)
		return CColour(r, t, p);

	if (hue < 2.0f)
		return CColour(q, r, p);

	if (hue < 3.0f)
		return CColour(p, r, t);

	if (hue < 4.0f)
		return CColour(p, q, r);

	if (hue < 5.0f)
		return CColour(t, p, r);

	return CColour(r, p, q);
}