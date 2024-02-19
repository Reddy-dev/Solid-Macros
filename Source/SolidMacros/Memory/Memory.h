// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_MEMORY_H
#define SOLID_MACROS_MEMORY_H

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

namespace Solid::Memory
{
	/**
	 * Returns the address of the object at the given offset from the given pointer.
	 * 
	 * @tparam U The type of the offset.
	 * @tparam T The type of the pointer.
	 * @param Ptr The pointer to the object.
	 * @param Offset The offset from the pointer.
	 * @return The address of the object at the given offset from the given pointer.
	 */
	template <typename U, typename T>
	FORCEINLINE CONSTEXPR NO_DISCARD void* OffsetOf(const T* Ptr, const U Offset)
	{
		return reinterpret_cast<T*>(reinterpret_cast<uint8*>(Ptr) + Offset);
	}
	
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
	
} // namespace Solid::Memory

#endif //SOLID_MACROS_MEMORY_H