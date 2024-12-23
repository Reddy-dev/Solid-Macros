// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_MEMORY_H
#define SOLID_MACROS_MEMORY_H

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

namespace Solid::Memory
{
	template <typename T>
	FORCEINLINE constexpr NO_DISCARD uint32 GetAlignment()
	{
		if constexpr (!std::is_empty_v<T>)
		{
			return std::min(sizeof(uintptr_t), alignof(T));
		}
		
		return 0;
	}
	
	template <typename U, typename T>
	FORCEINLINE constexpr NO_DISCARD void* OffsetOf(const T* Ptr, const U Offset)
	{
		return reinterpret_cast<T*>(reinterpret_cast<uint8*>(Ptr) + Offset);
	}
	
	template <int32 Offset>
	FORCEINLINE constexpr static void Prefetch(const void* Address)
	{
		FPlatformMisc::Prefetch(reinterpret_cast<const void*>(reinterpret_cast<UPTRINT>(Address) + Offset));
	}
	
	template <int32 Size>
	FORCEINLINE constexpr static void PrefetchBlock(const void* Address)
	{
		static constexpr int32 LinesNum = (Size + PLATFORM_CACHE_LINE_SIZE - 1) / PLATFORM_CACHE_LINE_SIZE;
		for (int32 LineIdx = 0; LineIdx < LinesNum; LineIdx += 1)
		{
			FPlatformMisc::Prefetch(Address, LineIdx * PLATFORM_CACHE_LINE_SIZE);
		}
	}

	template <typename T, typename V>
	FORCEINLINE constexpr T Align(T Num, V Alignment)
	{
		return Alignment == 0 ? Num : ((Num + (Alignment - 1)) / Alignment) * Alignment;
	}

	template <uint64 Alignment, typename T>
	FORCEINLINE constexpr T Align(T Num)
	{
		return (Num + (Alignment - 1)) & ~(Alignment - 1);
	}

	template <typename T, typename V>
	FORCEINLINE constexpr NO_DISCARD uint32 Padding(T Num, V Alignment)
	{
		return static_cast<uint32>(Align(Num, Alignment) - Num);
	}

	template <uint64 Alignment, typename T>
	FORCEINLINE constexpr NO_DISCARD uint32 Padding(T Num)
	{
		return static_cast<uint32>(Align<Alignment>(Num) - Num);
	}

	template <typename DestinationType, typename SourceType>
	FORCEINLINE constexpr NO_DISCARD DestinationType BitCast(const SourceType& Source)
	{
		static_assert(sizeof(DestinationType) == sizeof(SourceType),
			"BitCast requires the types to have the same size.");
		
		DestinationType Destination;
		FMemory::Memmove(static_cast<void*>(&Destination), static_cast<const void*>(&Source), sizeof(DestinationType));
		return Destination;
	}

	template <typename T>
	struct TUnalignedReference
	{
		using Type = T;
		
	public:
		FORCEINLINE TUnalignedReference(void* InPtr)
			: Ptr(InPtr)
		{
		}

		FORCEINLINE TUnalignedReference& operator=(const T& Value)
		{
			FMemory::Memmove(Ptr, static_cast<const void*>(&Value), sizeof(T));
			return *this;
		}

		FORCEINLINE operator T() const
		{
			T Value;
			FMemory::Memmove(static_cast<void*>(&Value), Ptr, sizeof(T));
			return Value;
		}

	private:
		void* Ptr;
	}; // struct TUnalignedReference

	FORCEINLINE constexpr NO_DISCARD uint64 GetAlignedByteOffset(uintptr_t Ptr,
		const uint64 ElementAlignment, const uint64 ElementSize, const uint64 Count)
	{
		const uint64 Padding = Memory::Padding(Ptr, ElementAlignment);
		Ptr += Padding + ElementSize * Count;
		return Ptr;
	}

	template <typename T, uint64 Alignment>
	FORCEINLINE constexpr NO_DISCARD uint64 GetAlignedByteOffset(uintptr_t Ptr, const uint64 Count)
	{
		const uint64 Padding = Memory::Padding<Alignment>(Ptr);
		Ptr += Padding + sizeof(T) * Count;
		return Ptr;
	}
	
} // namespace Solid::Memory

#endif //SOLID_MACROS_MEMORY_H