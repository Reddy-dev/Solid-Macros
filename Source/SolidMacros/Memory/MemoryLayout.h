// Solstice Games © 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Memory.h"
#include "SolidMacros/Macros.h"
#include "Standard/For.h"
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
    concept IsSoAConcept = Layout == EMemoryLayout::SoA
        || Layout == EMemoryLayout::SoA8
        || Layout == EMemoryLayout::SoA16;

    template <typename T>
    concept IsMemoryLayout = IsAoSConcept<T> || IsSoAConcept<T>;

    template <EMemoryLayout Layout, typename T>
    struct TDataLayoutProperties
    {
        static_assert(IsMemoryLayout<Layout>, "Layout must be AoS, SoA, SoA8, or SoA16.");
    }; // struct TDataLayoutProperties

    template <typename T>
    struct TDataLayoutProperties<EMemoryLayout::AoS, T>
    {
        static CONSTEXPR EMemoryLayout Layout = EMemoryLayout::AoS;
        static CONSTEXPR uint64 PackSize = 1;

        static CONSTEXPR uint64 ElementAlignment = GetAlignment<T>();
        static CONSTEXPR uint64 ArrayAlignment = 0;
    }; // struct TDataLayoutProperties<EMemoryLayout::AoS, T>

    template <typename T>
    struct TDataLayoutProperties<EMemoryLayout::SoA, T>
    {
        static CONSTEXPR EMemoryLayout Layout = EMemoryLayout::SoA;
        static CONSTEXPR uint64 PackSize = 4;

        static CONSTEXPR uint64 ElementAlignment = PackSize * 4;
        static CONSTEXPR uint64 ArrayAlignment = ElementAlignment;
    }; // struct TDataLayoutProperties<EMemoryLayout::SoA, T>

    template <typename T>
    struct TDataLayoutProperties<EMemoryLayout::SoA8, T>
    {
        static CONSTEXPR EMemoryLayout Layout = EMemoryLayout::SoA8;
        static CONSTEXPR uint64 PackSize = 8;

        static CONSTEXPR uint64 ElementAlignment = PackSize * 4;
        static CONSTEXPR uint64 ArrayAlignment = ElementAlignment;
    }; // struct TDataLayoutProperties<EMemoryLayout::SoA8, T>
    
    template <typename T>
    struct TDataLayoutProperties<EMemoryLayout::SoA16, T>
    {
        static CONSTEXPR EMemoryLayout Layout = EMemoryLayout::SoA16;
        static CONSTEXPR uint64 PackSize = 16;

        static CONSTEXPR uint64 ElementAlignment = PackSize * 4;
        static CONSTEXPR uint64 ArrayAlignment = ElementAlignment;
    }; // struct TDataLayoutProperties<EMemoryLayout::SoA16, T>

    template <EMemoryLayout Layout, typename T>
    struct TDataViewPolicy
    {
        static_assert(IsMemoryLayout<Layout>, "Layout must be AoS, SoA, SoA8, or SoA16.");
    }; // struct TDataViewPolicy

    template <EMemoryLayout Layout, typename T>
    struct TDataViewPolicyGetter
    {
        static_assert(IsMemoryLayout<Layout>, "Layout must be AoS, SoA, SoA8, or SoA16.");
    }; // struct TDataViewPolicyGetter

    template <EMemoryLayout Layout, typename T>
    struct TDataViewPolicySetter
    {
        static_assert(IsMemoryLayout<Layout>, "Layout must be AoS, SoA, SoA8, or SoA16.");
    }; // struct TDataViewPolicySetter

    template <EMemoryLayout Layout, typename T>
    struct TDataViewPolicyGetIndex
    {
        static_assert(IsMemoryLayout<Layout>, "Layout must be AoS, SoA, SoA8, or SoA16.");
    }; // struct TDataViewPolicyGetIndex

    template <EMemoryLayout Layout, typename T>
    struct TDataViewPolicySetIndex
    {
        static_assert(IsMemoryLayout<Layout>, "Layout must be AoS, SoA, SoA8, or SoA16.");
    }; // struct TDataViewPolicySetIndex

    template <typename T>
    struct TDataViewPolicy<EMemoryLayout::AoS, T>
    {
        using Type = T;
        using TargetCaseType = std::add_pointer_t<Type>;

        static CONSTEXPR EMemoryLayout Layout = TDataLayoutProperties<EMemoryLayout::AoS, Type>::Layout;
        static CONSTEXPR uint64 ElementAlignment = TDataLayoutProperties<EMemoryLayout::AoS, Type>::ElementAlignment;
        static CONSTEXPR uint64 ArrayAlignment = TDataLayoutProperties<EMemoryLayout::AoS, Type>::ArrayAlignment;

    public:


        FORCEINLINE CONSTEXPR NO_DISCARD static uint32 GetMinByteSize(const uintptr_t Ptr, const uint32 Count) NOEXCEPT
        {
            const uint64 Offset = GetAlignedByteOffset<Type, ElementAlignment>(Ptr, Count);
            return Offset + Count * sizeof(Type);
        }

        FORCEINLINE NO_DISCARD static uint8* AllocateMemory(const uint32 Count) NOEXCEPT
        {
            const uint64 ByteCount = GetMinByteSize(Count);
            
        }
        
    }; // struct TDataViewPolicy<EMemoryLayout::AoS, T>

    template <EMemoryLayout Layout>
    requires (IsAoSConcept<Layout>)
    FORCEINLINE void CopyElements(const uint8* Source, uint8* Dest, const uint32 IndexSource,
        const uint32 IndexDest, const uint32 Count, const uint32 ElementSize)
    {
        Solid::For(IndexSource, IndexDest, [&](const uint32 Index)
        {
            
        });
    }

    template <EMemoryLayout Layout, typename T>
    requires (IsAoSConcept<Layout>)
    FORCEINLINE void CopyElements(const T* Source, T* Dest, const uint32 IndexSource,
        const uint32 IndexDest, const uint32 Count)
    {
        Solid::For(IndexSource, IndexDest, [&](const uint32 Index)
        {
            Dest[Index] = Source[Index];
        });
    }
    
} // namespace Solid::Memory
