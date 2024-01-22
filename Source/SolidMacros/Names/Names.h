// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_NAMES_NAMES_H
#define SOLID_MACROS_NAMES_NAMES_H

#include "CoreMinimal.h"

#define DECLARE_SOLID_NAME(Name, Literal) \
    struct F##Name \
    { \
        FORCEINLINE CONSTEXPR NO_DISCARD static FName Name() \
        { \
            static CONSTEXPR FName StaticName = FName(Literal); \
            return StaticName; \
        } \
    };

#endif //SOLID_MACROS_NAMES_NAMES_H