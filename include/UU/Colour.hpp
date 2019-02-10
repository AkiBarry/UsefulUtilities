#pragma once
#include <cstdint>
#include "Vector.hpp"

class CHSB;

class CColour
{
public:

	uint8_t				r{}, g{}, b{}, a{};

	CColour() : r(0), g(0), b(0), a(0) {}

	CColour(int x, int y, int z)
		: r(static_cast<uint8_t>(x)), g(static_cast<uint8_t>(y)), b(static_cast<uint8_t>(z)), a(255) {}

	CColour(int x, int y, int z, int w)
		: r(static_cast<uint8_t>(x)), g(static_cast<uint8_t>(y)), b(static_cast<uint8_t>(z)), a(static_cast<uint8_t>(w)) {}

	CColour(const uint32_t c);

	uint8_t &					operator[](const int i);
	uint8_t						operator[](const int i) const;

	uint8_t *					Base();
	uint8_t const *				Base() const;

	void						CopyToArray(uint8_t* c) const;

	CColour &					operator=(const CColour c);

	bool						operator==(const CColour c) const;
	bool						operator!=(const CColour c) const;

	uint32_t					ToD3DColour() const;
	CHSB						ToHSB() const;
	NMath::CVec4f				ToVector() const;

	uint32_t &					AsRawColour();
	const uint32_t &			AsRawColour() const;

	float						Hue() const;
	float						Saturation() const;
	float						Brightness() const;

	static CColour				Black;
	static CColour				White;
	static CColour				Red;
	static CColour				Green;
	static CColour				Blue;
	static CColour				Yellow;
	static CColour				Cyan;
	static CColour				Magenta;
};

class CHSB
{
public:

	float			h, s, b;

	CHSB() : h(0.0f), s(0.0f), b(0.0f) {}

	CHSB(const float x, const float y, const float z) : h(x), s(y), b(z) {}

	float &			operator[](const int i);
	float			operator[](const int i) const;

	float *			Base();
	float const *	Base() const;

	void			CopyToArray(float* f) const;

	CHSB &			operator=(const CHSB c);

	bool			operator==(const CHSB c) const;
	bool			operator!=(const CHSB c) const;

	CColour			ToColour() const;
};

// CColour - Static Values

CColour CColour::Black(0, 0, 0);
CColour CColour::White(255, 255, 255);
CColour CColour::Red(255, 0, 0);
CColour CColour::Green(0, 255, 0);
CColour CColour::Blue(0, 0, 255);
CColour CColour::Yellow(255, 255, 0);
CColour CColour::Cyan(0, 255, 255);
CColour CColour::Magenta(255, 0, 255);

// CColour - Function Definitions

inline CColour::CColour(const uint32_t c)
{
	*reinterpret_cast<uint32_t *>(this) = c;
}

inline uint8_t & CColour::operator[](const int i)
{
	return reinterpret_cast<uint8_t *>(this)[i];
}

inline uint8_t CColour::operator[](const int i) const
{
	return reinterpret_cast<const uint8_t *>(this)[i];
}

inline uint8_t * CColour::Base()
{
	return reinterpret_cast<uint8_t *>(this);
}

inline uint8_t const * CColour::Base() const
{
	return reinterpret_cast<uint8_t const *>(this);
}

inline void CColour::CopyToArray(uint8_t* c) const
{
	*reinterpret_cast<uint32_t *>(c) = *reinterpret_cast<uint32_t const *>(this);
}

inline CColour & CColour::operator=(const CColour c)
{
	*reinterpret_cast<uint32_t *>(this) = *reinterpret_cast<const uint32_t *>(&c);

	return *this;
}

inline bool CColour::operator==(const CColour c) const
{
	return *reinterpret_cast<const uint32_t *>(this) == *reinterpret_cast<const uint32_t *>(&c);
}

inline bool CColour::operator!=(const CColour c) const
{
	return *reinterpret_cast<const uint32_t *>(this) != *reinterpret_cast<const uint32_t*>(&c);
}

inline uint32_t CColour::ToD3DColour() const
{
	return static_cast<uint32_t>(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

inline CHSB CColour::ToHSB() const
{
	CHSB temp;
	const float _r = r / 255.0f;
	const float _g = g / 255.0f;
	const float _b = b / 255.0f;

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

	if (hue < 0.0f)
		hue += 360.0f;

	temp.h = hue;

	return temp;
}

inline NMath::CVec4f CColour::ToVector() const
{
	return NMath::CVector<float, 4>(r / 255.f, g / 255.f, b / 255.f);
}

inline uint32_t & CColour::AsRawColour()
{
	return *reinterpret_cast<uint32_t *>(this);
}

inline const uint32_t & CColour::AsRawColour() const
{
	return *reinterpret_cast<const uint32_t *>(this);
}

inline float CColour::Hue() const
{
	if (r == g && g == b)
		return 0.0f;

	float _r = r / 255.0f;
	float _g = g / 255.0f;
	float _b = b / 255.0f;

	float max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;
	float delta = max - min;
	float hue = 0.0f;

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
	hue *= 60;

	if (hue < 0.0f)
	{
		hue += 360.0f;
	}
	return hue;
}

inline float CColour::Saturation() const
{
	float _r = r / 255.0f;
	float _g = g / 255.0f;
	float _b = b / 255.0f;

	float max = _r > _g ? _r : _g > _b ? _g : _b,
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

inline float CColour::Brightness() const
{
	float _r = r / 255.0f;
	float _g = g / 255.0f;
	float _b = b / 255.0f;

	float max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;
	return (max + min) / 2.0f;
}

// CHSB - Function Definitions

inline float & CHSB::operator[](const int i)
{
	return reinterpret_cast<float *>(this)[i];
}

inline float CHSB::operator[](const int i) const
{
	return reinterpret_cast<const float *>(this)[i];
}

inline float * CHSB::Base()
{
	return reinterpret_cast<float*>(this);
}

inline float const * CHSB::Base() const
{
	return reinterpret_cast<float const*>(this);
}

inline void CHSB::CopyToArray(float* f) const
{
	f[0] = h;
	f[1] = s;
	f[2] = b;
}

inline CHSB & CHSB::operator=(const CHSB hsb)
{
	h = hsb.h;
	s = hsb.s;
	b = hsb.b;

	return *this;
}

inline bool CHSB::operator==(const CHSB hsb) const
{
	return h == hsb.h
		&& s == hsb.s
		&& b == hsb.b;
}

inline bool CHSB::operator!=(const CHSB hsb) const
{
	return h != hsb.h
		|| s != hsb.s
		|| b != hsb.b;
}

inline CColour CHSB::ToColour() const
{
	float hue = h == 1.0f ? 0.0f : h * 6.0f;
	float f = hue - static_cast<int>(hue);
	float _r = b * 255.0f;
	uint8_t r = static_cast<uint8_t>(_r);
	uint8_t p = static_cast<uint8_t>(_r * (1.0f - s));
	uint8_t q = static_cast<uint8_t>(_r * (1.0f - s * f));
	uint8_t t = static_cast<uint8_t>(_r * (1.0f - (s * (1.0f - f))));

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
