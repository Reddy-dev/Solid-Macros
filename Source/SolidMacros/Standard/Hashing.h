// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_STANDARD_HASHING_H
#define SOLID_MACROS_STANDARD_HASHING_H

#include <immintrin.h>
#include <vector>

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

namespace Solid
{
	static FORCEINLINE NO_DISCARD int32 Match(const uint8 Byte, const uint8* Data)
	{
		const __m128i M = _mm_set1_epi8(Byte);
		const __m128i Control = _mm_load_si128(reinterpret_cast<const __m128i*>(Data));
		return _mm_movemask_epi8(_mm_cmpeq_epi8(M, Control));
	}

	#if 0
	static FORCEINLINE NO_DISCARD uint64 GetTypeHashUniversal(const void* Ptr, uint32 Size)
	{
		using SIMDType = __m256i;
		
		CONSTEXPR uint64 SIMD_SIZE = sizeof(SIMDType);
		
		uint64 Hash = 2166136261ULL;

		// Use SIMD only for larger blocks of memory
		if (Size >= SIMD_SIZE)
		{
			size_t Processed = 0;
			while (Processed + SIMD_SIZE <= Size)
			{
				SIMDType Data;
				std::memcpy(&Data, static_cast<const uint8*>(Ptr) + Processed, SIMD_SIZE);
				
				for (uint64 Index = 0; Index < 8; ++Index)
				{
					Hash ^= _mm256_extract_epi32(Data, Index);
				}
				
				Processed += SIMD_SIZE;
			}

			// Update pointer and size for remaining bytes
			Ptr = static_cast<const uint8*>(Ptr) + Processed;
			Size -= Processed;
		}
		
		const uint8* Bytes = static_cast<const uint8*>(Ptr);
		
		for (uint64 Index = 0; Index < Size; ++Index)
		{
			Hash = (Hash * 16777619U) ^ Bytes[Index];
		}

		return Hash;
	}
	#endif // 0

	static FORCEINLINE NO_DISCARD uint64 GetHash64(const void* const Data) NOEXCEPT
	{
		uint64 Hash = 0xcbf29ce484222325ULL;

		FString String = FString::Printf(TEXT("%p"), Data);

		uint64 Index = 0;

		while (String[Index] != '\0')
		{
			Hash = (Hash ^ String[Index]) * 1099511628211ULL;
			++Index;
		}

		return Hash;
	}

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

#define DEFINE_STD_HASH(TYPE) \
	template <> \
	class std::hash<TYPE> \
	{ \
	public: \
		SOLID_INLINE std::size_t operator()(const TYPE& Value) const NOEXCEPT \
		{ \
			return GetTypeHash(Value); \
		} \
		\
	}; // class std::hash<TYPE>

#define DEFINE_STD_HASH_CUSTOM_FUNC(TYPE, FUNC) \
	template <> \
	class std::hash<TYPE> \
	{ \
	public: \
		SOLID_INLINE std::size_t operator()(const TYPE& Value) const NOEXCEPT \
		{ \
			return FUNC(Value); \
		} \
		\
	}; // class std::hash<TYPE>

DEFINE_STD_HASH(FName)
DEFINE_STD_HASH(FString);

#endif // SOLID_MACROS_STANDARD_HASHING_H