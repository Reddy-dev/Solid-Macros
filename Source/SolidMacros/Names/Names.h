﻿// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_NAMES_NAMES_H
#define SOLID_MACROS_NAMES_NAMES_H

#include "CoreMinimal.h"

#define DECLARE_SOLID_NAME(TName, Literal) \
    struct F##TName final \
    { \
        FORCEINLINE constexpr NO_DISCARD static FName Name() \
        { \
            static constexpr FName StaticName = FName(Literal); \
            return StaticName; \
        } \
    }; // struct F##TName

template <typename T>
concept TSolidNameConcept = requires
{
    T::Name();
}; // concept TSolidNameConcept

#endif //SOLID_MACROS_NAMES_NAMES_H