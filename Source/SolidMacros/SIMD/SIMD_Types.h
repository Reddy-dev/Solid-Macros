﻿// Solstice Games © 2024. All Rights Reserved.

// ReSharper disable CppInconsistentNaming
#ifndef SOLID_MACROS_SIMD_SIMD_TYPES_H
#define SOLID_MACROS_SIMD_SIMD_TYPES_H

#include "CoreMinimal.h"

using FSimd128 = __m128;
using FSimd256 = __m256;
using FSimd128I = __m128i;
using FSimd256I = __m256i;
    
template <typename T>
concept TSIMDTypeConcept = std::is_same_v<T, FSimd128I> || std::is_same_v<T, FSimd256I>
|| std::is_same_v<T, FSimd128> || std::is_same_v<T, FSimd256>;

template <typename T>
concept TSIMD128TypeConcept = std::is_same_v<T, FSimd128I> || std::is_same_v<T, FSimd128>;

template <typename T>
concept TSIMD256TypeConcept = std::is_same_v<T, FSimd256I> || std::is_same_v<T, FSimd256>;

template <typename T>
concept TSIMD128ITypeConcept = std::is_same_v<T, FSimd128I>;

template <typename T>
concept TSIMD256ITypeConcept = std::is_same_v<T, FSimd256I>;

#endif //SOLID_MACROS_SIMD_SIMD_TYPES_H
