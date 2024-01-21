// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_STANDARD_HASHING_H
#define SOLID_MACROS_STANDARD_HASHING_H

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

namespace Solid
{
	FORCEINLINE NO_DISCARD int32 Match(const uint8 Byte, const uint8* Data)
	{
		const __m128i M = _mm_set1_epi8(Byte);
		const __m128i Control = _mm_load_si128(reinterpret_cast<const __m128i*>(Data));
		return _mm_movemask_epi8(_mm_cmpeq_epi8(M, Control));
	}
	
	FORCEINLINE static NO_DISCARD uint32 GetTypeHashUniversal(const void* Ptr, uint32 Size)
	{
		using SIMDType = __m256i;
		
		static CONSTEXPR uint32 SIMD_SIZE = sizeof(SIMDType);
		
		uint32_t Hash = 2166136261U;

		// Use SIMD for larger blocks of memory
		if (Size >= SIMD_SIZE)
		{
			size_t Processed = 0;
			while (Processed + SIMD_SIZE <= Size)
			{
				SIMDType Data;
				std::memcpy(&Data, static_cast<const uint8_t*>(Ptr) + Processed, SIMD_SIZE);
				
				for (int32 Index = 0; Index < 8; ++Index)
				{
					Hash ^= _mm256_extract_epi32(Data, Index);
				}
				
				Processed += SIMD_SIZE;
			}

			// Update pointer and size for remaining bytes
			Ptr = static_cast<const uint8_t*>(Ptr) + Processed;
			Size -= Processed;
		}
		
		const uint8_t* Bytes = static_cast<const uint8_t*>(Ptr);
		
		for (size_t Index = 0; Index < Size; ++Index)
		{
			Hash = (Hash * 16777619U) ^ Bytes[Index];
		}

		return Hash;
	}

	template <uint32 Count = 2>
	FORCEINLINE static NO_DISCARD uint32 HashCombineUniversal(const uint32 (&Hashes)[Count])
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

template <>
struct std::hash<FName>
{
	FORCEINLINE NO_DISCARD size_t operator()(const FName& Name) const NOEXCEPT
	{
		return GetTypeHash(Name);
	}
}; // struct std::hash<FName>

#endif // SOLID_MACROS_STANDARD_HASHING_H