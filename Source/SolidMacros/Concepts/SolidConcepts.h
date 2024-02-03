// Solstice Games © 2023. All Rights Reserved.

#ifndef SOLID_CONCEPTS_H
#define SOLID_CONCEPTS_H

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"
#include "PropertyTypeCompatibility.h"

namespace Solid
{
	template <typename T>
	FORCEINLINE CONSTEXPR NO_DISCARD bool IsStaticStruct()
	{
		return TModels_V<CStaticStructProvider, T>;
	}
	
	template <typename T>
	concept TStaticStructConcept = requires
	{
		requires IsStaticStruct<T>();
	}; // concept TStaticStructConcept

	template <typename T>
	FORCEINLINE CONSTEXPR NO_DISCARD bool IsStaticClass()
	{
		return TModels_V<CStaticClassProvider, T>;
	}

	template <typename T>
	concept TStaticClassConcept = requires
	{
		requires IsStaticClass<T>();
	}; // concept TStaticClassConcept

	template <typename T>
	concept TClassConcept = requires
	{
		requires std::is_class_v<T>;
	}; // concept TClassConcept

	template <typename T>
	concept TConcreteReflectionCompConcept = requires
	{
		requires IsConcreteTypeCompatibleWithReflectedType<T>();
	}; // concept TConcreteReflectionCompConcept

	template <typename T>
	concept TIsOptionalConcept = requires
	{
		requires TIsTOptional_V<T>;
	}; // concept TIsOptionalConcept

	template<typename F, typename ...Args>
	concept TInvocableConcept = TIsInvocable<F, Args...>::Value;
	
} // namespace Solid

#endif // SOLID_CONCEPTS_H