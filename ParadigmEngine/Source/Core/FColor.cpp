#include <FColor.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Utility
		{
			const UColor UColor::Black = UColor(0.f, 0.f, 0.f, 1.f);
			const UColor UColor::Navy = UColor(0.f, 0.f, 0.5f, 1.f);
			const UColor UColor::Blue = UColor(0.f, 0.f, 1.f, 1.f);
			const UColor UColor::Green = UColor(0.f, 0.5f, 0.f, 1.f);
			const UColor UColor::Teal = UColor(0.f, 0.5f, 0.5f, 1.f);
			const UColor UColor::Lime = UColor(0.f, 1.f, 0.f, 1.f);
			const UColor UColor::Aqua = UColor(0.f, 1.f, 1.f, 1.f);
			const UColor UColor::Maroon = UColor(0.5f, 0.f, 0.f, 1.f);
			const UColor UColor::Purple = UColor(0.5f, 0.f, 0.5f, 1.f);
			const UColor UColor::Olive = UColor(0.5f, 0.5f, 0.f, 1.f);
			const UColor UColor::Gray = UColor(0.5f, 0.5f, 0.5f, 1.f);
			const UColor UColor::Silver = UColor(0.75f, 0.75f, 0.75f, 1.f);
			const UColor UColor::Red = UColor(1.f, 0.f, 0.f, 1.f);
			const UColor UColor::Magenta = UColor(1.f, 0.f, 1.f, 1.f);
			const UColor UColor::Yellow = UColor(1.f, 1.f, 0.f, 1.f);
			const UColor UColor::White = UColor(1.f, 1.f, 1.f, 1.f);
			
			const UColor UColor::ParadigmGold = UColor(1.f, .718f, .071f, 1.f);
			const UColor UColor::ParadigmDarkGray = UColor(0.075f, .078f, .078f, 1.f);

			UColor::UColor(float _r, float _g, float _b, float _a)
				: r{ _r }, g{ _g }, b{ _b }, a{ _a }
			{}
		}
	}
}