#pragma once
#include <cstdint>

namespace UU {
	class CHSB;
	
	class CColour final
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

		uint32_t &						AsRawColour();
		const uint32_t &				AsRawColour() const;

		float							Hue() const;
		float							Saturation() const;
		float							Brightness() const;

		static const					CColour		Black;
		static const					CColour		White;
		static const					CColour		Red;
		static const					CColour		Green;
		static const					CColour		Blue;
		static const					CColour		Yellow;
		static const					CColour		Cyan;
		static const					CColour		Magenta;
	};

	class CHSB final
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
}