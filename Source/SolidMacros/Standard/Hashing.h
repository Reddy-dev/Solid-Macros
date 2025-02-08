// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_STANDARD_HASHING_H
#define SOLID_MACROS_STANDARD_HASHING_H

#include <immintrin.h>
#include <vector>

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

namespace Solid
{
	
	template <uint32 Count = 2>
	static FORCEINLINE NO_DISCARD uint32 HashCombine(const uint32 (&Hashes)[Count])
	{
		uint32 Hash = 2166136261U;
		
		for (uint32 Index = 0; Index < Count; ++Index)
		{
			Hash ^= Hashes[Index];
			Hash *= 16777619U;
		}

		return Hash;
	}
	
} // namespace Solid

#define DEFINE_STD_HASH(x) \
	template <> \
	class std::hash<x> \
	{ \
	public: \
		SOLID_INLINE std::size_t operator()(const x& Value) const NOEXCEPT \
		{ \
			return GetTypeHash(Value); \
		} \
		\
	}; // class std::hash<x>

#define DEFINE_STD_HASH_CUSTOM_FUNC(x, FUNC) \
	template <> \
	class std::hash<x> \
	{ \
	public: \
		SOLID_INLINE std::size_t operator()(const x& Value) const NOEXCEPT \
		{ \
			return FUNC(Value); \
		} \
		\
	}; // class std::hash<x>

DEFINE_STD_HASH(FName)
DEFINE_STD_HASH(FString);
DEFINE_STD_HASH(FStringView);

template <typename T>
class std::hash<TObjectKey<T>>
{
public:
	SOLID_INLINE std::size_t operator()(const TObjectKey<T>& Value) const NOEXCEPT
	{
		return GetTypeHash(Value);
	}
	
}; // class std::hash<TObjectKey<T>>

#endif // SOLID_MACROS_STANDARD_HASHING_H