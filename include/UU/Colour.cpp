#include "UU/Colour.hpp"

// CColour - Static Values

const UU::CColour UU::CColour::Black(0, 0, 0);
const UU::CColour UU::CColour::White(255, 255, 255);
const UU::CColour UU::CColour::Red(255, 0, 0);
const UU::CColour UU::CColour::Green(0, 255, 0);
const UU::CColour UU::CColour::Blue(0, 0, 255);
const UU::CColour UU::CColour::Yellow(255, 255, 0);
const UU::CColour UU::CColour::Cyan(0, 255, 255);
const UU::CColour UU::CColour::Magenta(255, 0, 255);
const UU::CColour UU::CColour::Orange(255, 128, 0);
const UU::CColour UU::CColour::Purple(128, 0, 128);

// CColour - Function Definitions

UU::CColour::CColour(uint32_t c)
{
	*this = *reinterpret_cast<CColour*>(&c);
}

uint8_t & UU::CColour::operator[](int i)
{
	return reinterpret_cast<uint8_t *>(this)[i];
}

uint8_t UU::CColour::operator[](int i) const
{
	return reinterpret_cast<const uint8_t *>(this)[i];
}

uint8_t * UU::CColour::Base()
{
	return reinterpret_cast<uint8_t *>(this);
}

uint8_t const * UU::CColour::Base() const
{
	return reinterpret_cast<uint8_t const *>(this);
}

void UU::CColour::CopyToArray(uint8_t * col) const
{
	col[0] = r;
	col[1] = g;
	col[2] = b;
	col[3] = a;
}

bool UU::CColour::operator==(CColour col) const
{
	return *reinterpret_cast<const uint32_t *>(this) == *reinterpret_cast<const uint32_t *>(&col);
}

bool UU::CColour::operator!=(CColour col) const
{
	return *reinterpret_cast<const uint32_t *>(this) != *reinterpret_cast<const uint32_t*>(&col);
}

uint32_t UU::CColour::ToD3DColour() const
{
	return static_cast<uint32_t>((a << 24) | (r << 16) | (g << 8) | b);
}

UU::CHSB UU::CColour::ToHSB() const
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

uint32_t & UU::CColour::AsRawColour()
{
	return *reinterpret_cast<uint32_t *>(this);
}

const uint32_t & UU::CColour::AsRawColour() const
{
	return *reinterpret_cast<const uint32_t *>(this);
}

UU::CColour UU::CColour::WithAlpha(uint8_t a) const
{
	CColour temp = *this;
	temp.a = a;

	return temp;
}

float UU::CColour::Hue() const
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

float UU::CColour::Saturation() const
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

float UU::CColour::Brightness() const
{
	const float _r = r / 255.0f,
		_g = g / 255.0f,
		_b = b / 255.0f;

	const float	max = _r > _g ? _r : _g > _b ? _g : _b,
		min = _r < _g ? _r : _g < _b ? _g : _b;
	return (max + min) / 2.0f;
}

// CHSB - Function Definitions

float & UU::CHSB::operator[](const int i)
{
	return reinterpret_cast<float *>(this)[i];
}

float UU::CHSB::operator[](const int i) const
{
	return reinterpret_cast<const float *>(this)[i];
}

float * UU::CHSB::Base()
{
	return reinterpret_cast<float*>(this);
}

float const * UU::CHSB::Base() const
{
	return reinterpret_cast<float const*>(this);
}

void UU::CHSB::CopyToArray(float* f) const
{
	f[0] = h;
	f[1] = s;
	f[2] = b;
}

bool UU::CHSB::operator==(const CHSB & hsb) const
{
	return h == hsb.h
		&& s == hsb.s
		&& b == hsb.b;
}

bool UU::CHSB::operator!=(const CHSB & hsb) const
{
	return h != hsb.h
		|| s != hsb.s
		|| b != hsb.b;
}

UU::CColour UU::CHSB::ToColour() const
{
	const float hue = h == 1.0f ? 0.0f : h * 6.0f;
	const float f = hue - static_cast<int>(hue);
	const float _r = b * 255.0f;
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