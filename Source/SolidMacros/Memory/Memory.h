// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_MEMORY_H
#define SOLID_MACROS_MEMORY_H

#include "CoreMinimal.h"

namespace Solid
{
	/**
	 * Compile-time variant of the prefetching.
	 * 
	 * @tparam Offset The offset to apply to the address.
	 * @param Address The address to prefetch.
	 */
	template <int32 Offset>
	FORCEINLINE CONSTEXPR static void Prefetch(const void* Address)
	{
		FPlatformMisc::Prefetch(reinterpret_cast<const void*>(reinterpret_cast<UPTRINT>(Address) + Offset));
	}

	/**
	 * Compile-time variant of the prefetching of a span of memory.
	 * 
	 * @tparam Size The number of bytes to prefetch.
	 * @param Address The address to prefetch.
	 */
	template <int32 Size>
	FORCEINLINE CONSTEXPR static void PrefetchBlock(const void* Address)
	{
		static constexpr int32 LinesNum = (Size + PLATFORM_CACHE_LINE_SIZE - 1) / PLATFORM_CACHE_LINE_SIZE;
		for (int32 LineIdx = 0; LineIdx < LinesNum; LineIdx += 1)
		{
			FPlatformMisc::Prefetch(Address, LineIdx * PLATFORM_CACHE_LINE_SIZE);
		}
	}
} // namespace Solid

#endif //SOLID_MACROS_MEMORY_H