// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_FOR_H
#define SOLID_FOR_H

#include "CoreMinimal.h"

namespace Solid
{
    template <typename MaxType, typename FunctionType>
    FORCEINLINE CONSTEXPR void For(const MaxType Max, FunctionType Function)
    {
        for (MaxType Index = 0; Index < Max; ++Index)
        {
            Function(Index);
        }
    }

    template <typename MinType, typename MaxType, typename FunctionType>
    FORCEINLINE CONSTEXPR void For(const MinType Min, const MaxType Max, FunctionType Function)
    {
        for (MinType Index = Min; Index < Max; ++Index)
        {
            Function(Index);
        }
    }

    template <typename, typename = std::void_t<>>
    struct THasSizeMethod : std::false_type {};

    template <typename T>
    struct THasSizeMethod<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type {};

    template <typename, typename = std::void_t<>>
    struct THasNumMethod : std::false_type {};

    template <typename T>
    struct THasNumMethod<T, std::void_t<decltype(std::declval<T>().Num())>> : std::true_type {};

    template <typename ContainerType, typename FunctionType>
    FORCEINLINE CONSTEXPR void For(const ContainerType& Container, FunctionType Function)
    {
        static_assert(THasSizeMethod<ContainerType>::value || THasNumMethod<ContainerType>::value,
            "ContainerType must have a size() or Num() method.");
        
        using IndexType = decltype(Container.size());

        IndexType Size = THasSizeMethod<ContainerType>::value ? Container.size() : Container.Num();
        
        for (IndexType Index = 0; Index < Size; ++Index)
        {
            Function(Index, Container[Index]);
        }
    }
    
} // namespace Solid

#endif // SOLID_FOR_H
