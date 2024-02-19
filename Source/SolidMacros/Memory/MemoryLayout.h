// Solstice Games © 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"
#include "MemoryLayout.generated.h"

UENUM(BlueprintType)
enum class EMemoryLayout : uint8
{
    AoS = 0,
    SoA,
    SoA8,
    SoA16,

    Count UMETA(Hidden),
}; // enum class EMemoryLayout

namespace Solid::Memory
{
    template <EMemoryLayout Layout>
    concept IsAoSConcept = Layout == EMemoryLayout::AoS;

    template <EMemoryLayout Layout>
    concept IsSoAConcept = Layout == EMemoryLayout::SoA || Layout == EMemoryLayout::SoA8 || Layout == EMemoryLayout::SoA16;

    template <EMemoryLayout Layout>
    requires (IsAoSConcept<Layout>)
    FORCEINLINE void CopyElements(void* Dest, const void* Source, const uint32 IndexSource,
        const uint32 IndexDest, const uint32 Count, const uint32 ElementSize)
    {
        
    }
    
    FORCEINLINE CONSTEXPR NO_DISCARD uint64 GetAlignedByteOffset(uint8* Ptr,
        const uint64 ElementAlignment, const uint64 ElementSize, const uint64 Count)
    {
        const uint64 Padding = ElementAlignment - (reinterpret_cast<uint64>(Ptr) % ElementAlignment);
        return Padding;
    }

    
} // namespace Solid::Memory
