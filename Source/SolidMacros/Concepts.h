// Solstice Games © 2023. All Rights Reserved.

#ifndef SOLID_MACROS_CONCEPTS_H
#define SOLID_MACROS_CONCEPTS_H

#include "CoreMinimal.h"
#include "Macros.h"

namespace Solid
{
	template <typename T>
	concept TStaticStructConcept = requires
	{
		requires TModels_V<CStaticStructProvider, T>;
	}; // concept TStaticStructConcept

	template <typename T>
	CONSTEXPR NO_DISCARD bool IsStaticStruct()
	{
		return TModels_V<CStaticStructProvider, T>;
	}
} // namespace Solid::Macros

#endif //SOLID_MACROS_CONCEPTS_H