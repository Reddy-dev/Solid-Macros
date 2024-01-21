// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_TYPE_TRAITS_H
#define SOLID_MACROS_TYPE_TRAITS_H

#include "CoreMinimal.h"

namespace Solid
{
	template <typename T>
	using TArrayElementType = std::decay_t<decltype(std::declval<T>().operator[](0))>;

	template <typename T>
	using TArrayValueType = std::remove_reference_t<decltype(std::declval<T>().operator[](0))>;

	template <typename T>
	struct TFlatten
		: public std::decay<std::remove_pointer_t<T>>
	{
	}; // struct TFlatten

	template <typename T>
	using TFlatten_t = typename TFlatten<T>::type;

	template <typename T1, typename T2>
	struct TIsSameFlatly
		: public std::is_same<TFlatten_t<T1>, TFlatten_t<T2>>
	{
	}; // struct TIsSameFlatly

	template <typename T1, typename T2>
	CONSTEXPR bool TIsSameFlatly_v = TIsSameFlatly<T1, T2>::value;

	template <typename Base, typename Derived>
	struct TIsBaseOfFlatly
		: public std::is_base_of<TFlatten_t<Base>, TFlatten_t<Derived>>
	{
	}; // struct TIsBaseOfFlatly

	template <typename Base, typename Derived>
	CONSTEXPR bool TIsBaseOfFlatly_v = TIsBaseOfFlatly<Base, Derived>::value;

	template <typename ...Ts>
	struct TIndexWithin;

	template <typename T>
	struct TIndexWithin<T, T>
		: public std::integral_constant<int32, 0>
	{
	}; // struct TIndexWithin<T, T>

	template <typename T, typename ...Tail>
	struct TIndexWithin<T, T, Tail...>
		: public std::integral_constant<int32, 0>
	{
	}; // struct TIndexWithin<T, T, Tail...>

	template <typename T, typename First>
	struct TIndexWithin<T, First>
		: public std::integral_constant<int32, -1>
	{
	}; // struct TIndexWithin<T, F>

	template <typename T>
	struct TIndexWithin<T>
		: public std::integral_constant<int32, -1>
	{
	}; // struct TIndexWithin<T>

	template <typename T, typename First, typename ...Tail>
	struct TIndexWithin<T, First, Tail...>
		: public std::integral_constant<int32, 1 + TIndexWithin<T, Tail...>::value>
	{
	}; // struct TIndexWithin<T, First, Tail...>

	template <typename ...Ts>
	struct TIndexWithinFlatly
		: public TIndexWithin<TFlatten_t<Ts>...>
	{
	}; // struct TIndexWithinFlatly

	template <typename ...Ts>
	CONSTEXPR int32 TIndexWithinFlatly_v = TIndexWithinFlatly<Ts...>::value;

	template <typename T, typename ...List>
	struct TIsContained;

	template <typename T, typename Head, typename ...Tail>
	struct TIsContained<T, Head, Tail...>
	{
		enum
		{
			value = std::is_same_v<T, Head> || TIsContained<T, Tail...>::value
		}; // enum value
		
	}; // struct TIsContained<T, Head, Tail...>

	template <typename T>
	struct TIsContained<T>
	{
		enum
		{
			value = false
		}; // enum value
		
	}; // struct TIsContained<T>

	template <typename T, typename ...List>
	CONSTEXPR bool TIsContained_v = TIsContained<T, List...>::value;

	template <typename T, typename ...List>
	struct TIsBaseContained;

	template <typename T, typename Head, typename ...Tail>
	struct TIsBaseContained<T, Head, Tail...>
	{
		enum
		{
			value = std::is_base_of_v<Head, T> || TIsBaseContained<T, Tail...>::value
		}; // enum value
		
	}; // struct TIsBaseContained<T, Head, Tail...>

	template <typename T>
	struct TIsBaseContained<T>
	{
		enum
		{
			value = false
		}; // enum value
		
	}; // struct TIsBaseContained<T>

	template <typename T, typename ...List>
	CONSTEXPR bool TIsBaseContained_v = TIsBaseContained<T, List...>::value;

	template <typename T, typename ...List>
	struct TIsContainedFlatly;

	template <typename T, typename Head, typename ...Tail>
	struct TIsContainedFlatly<T, Head, Tail...>
	{
		enum
		{
			value = TIsSameFlatly_v<T, Head> || TIsContainedFlatly<T, Tail...>::value
		}; // enum value
		
	}; // struct TIsContainedFlatly<T, Head, Tail...>

	template <typename T>
	struct TIsContainedFlatly<T>
	{
		enum
		{
			value = false
		}; // enum value
		
	}; // struct TIsContainedFlatly<T>

	template <typename T, typename ...List>
	CONSTEXPR bool TIsContainedFlatly_v = TIsContainedFlatly<T, List...>::value;

	template <typename T, typename ...List>
	struct TIsBaseContainedFlatly;

	template <typename T, typename Head, typename ...Tail>
	struct TIsBaseContainedFlatly<T, Head, Tail...>
	{
		enum
		{
			value = TIsBaseOfFlatly_v<T, Head> || TIsBaseContainedFlatly<T, Tail...>::value
		}; // enum value
		
	}; // struct TIsBaseContainedFlatly<T, Head, Tail...>

	template <typename T>
	struct TIsBaseContainedFlatly<T>
	{
		enum
		{
			value = false
		}; // enum value
		
	}; // struct TIsBaseContainedFlatly<T>

	template <typename ...List>
	struct THasDuplicates;

	template <typename Head, typename ...Tail>
	struct THasDuplicates<Head, Tail...>
	{
		enum
		{
			value = TIsContained_v<Head, Tail...> || THasDuplicates<Tail...>::value
		}; // enum value
		
	}; // struct THasDuplicates<Head, Tail...>

	template <>
	struct THasDuplicates<>
	{
		enum
		{
			value = false
		}; // enum value
		
	}; // struct THasDuplicates<>
	
} // namespace Solid

#endif //SOLID_MACROS_TYPE_TRAITS_H
