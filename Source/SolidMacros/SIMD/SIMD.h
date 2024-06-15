// Solstice Games © 2024. All Rights Reserved.

// ReSharper disable CppNotAllPathsReturnValue
#ifndef SOLID_MACROS_SIMD_SIMD_H
#define SOLID_MACROS_SIMD_SIMD_H

#include <immintrin.h>
#include <type_traits>
#include <concepts>

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"
#include "SIMD_Types.h"

template <TSIMDTypeConcept T>
struct TSolidSIMDWrapper
{
    using ValueType = T;

    ValueType Value;
public:
    FORCEINLINE constexpr TSolidSIMDWrapper() = default;
    FORCEINLINE constexpr TSolidSIMDWrapper(const ValueType& InValue) : Value(InValue)
    {
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper LoadAligned(const void* Ptr)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_load_si128(static_cast<const FSimd128I*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_load_si256(static_cast<const FSimd256I*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_load_ps(static_cast<const float*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_load_ps(static_cast<const float*>(Ptr)));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper LoadUnaligned(const void* Ptr)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_loadu_si128(static_cast<const FSimd128I*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_loadu_si256(static_cast<const FSimd256I*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_loadu_ps(static_cast<const float*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_loadu_ps(static_cast<const float*>(Ptr)));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper SetZero()
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_setzero_si128());
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_setzero_si256());
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_setzero_ps());
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_setzero_ps());
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper SetOne()
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_set1_epi32(1));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_set1_epi32(1));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_set1_ps(1));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_set1_ps(1));
        }
    }

    FORCEINLINE void StoreAligned(void* Ptr) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            _mm_store_si128(static_cast<FSimd128I*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            _mm256_store_si256(static_cast<FSimd256I*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            _mm_store_ps(static_cast<float*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            _mm256_store_ps(static_cast<float*>(Ptr), Value);
        }
    }

    FORCEINLINE void StoreUnaligned(void* Ptr) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            _mm_storeu_si128(static_cast<FSimd128I*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            _mm256_storeu_si256(static_cast<FSimd256I*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            _mm_storeu_ps(static_cast<float*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            _mm256_storeu_ps(static_cast<float*>(Ptr), Value);
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator+(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_add_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_add_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_add_ps(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_add_ps(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator-(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_sub_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_sub_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_sub_ps(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_sub_ps(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator*(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_mul_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_mul_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_mul_ps(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_mul_ps(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator/(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_div_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_div_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_div_ps(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_div_ps(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator&(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_and_si128(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_and_si256(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator|(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_or_si128(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_or_si256(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator^(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_xor_si128(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_xor_si256(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator~() const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_xor_si128(Value, _mm_set1_epi32(-1)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_xor_si256(Value, _mm256_set1_epi32(-1)));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator-() const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_sub_epi32(_mm_set1_epi32(0), Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_sub_epi32(_mm256_set1_epi32(0), Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_sub_ps(_mm_set1_ps(0), Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_sub_ps(_mm256_set1_ps(0), Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator==(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_cmpeq_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_cmpeq_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_cmpeq_ps(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_cmp_ps(Value, Other.Value, _CMP_EQ_OQ));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator!=(const TSolidSIMDWrapper& Other) const
    {
        return ~(*this == Other);
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator<(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_cmplt_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_cmplt_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_cmplt_ps(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_cmp_ps(Value, Other.Value, _CMP_LT_OQ));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator<=(const TSolidSIMDWrapper& Other) const
    {
        return (*this < Other) | (*this == Other);
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator>(const TSolidSIMDWrapper& Other) const
    {
        return ~(*this <= Other);
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator>=(const TSolidSIMDWrapper& Other) const
    {
        return ~(*this < Other);
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator&&(const TSolidSIMDWrapper& Other) const
    {
        return *this & Other;
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator||(const TSolidSIMDWrapper& Other) const
    {
        return *this | Other;
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator!() const
    {
        return ~*this;
    }

    FORCEINLINE TSolidSIMDWrapper& operator+=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this + Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator-=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this - Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator*=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this * Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator/=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this / Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator&=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this & Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator|=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this | Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator^=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this ^ Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator++()
    {
        return *this += 1;
    }

    FORCEINLINE TSolidSIMDWrapper& operator--()
    {
        return *this -= 1;
    }

    FORCEINLINE TSolidSIMDWrapper operator++(int)
    {
        TSolidSIMDWrapper Temp = *this;
        ++*this;
        return Temp;
    }

    FORCEINLINE TSolidSIMDWrapper operator--(int)
    {
        TSolidSIMDWrapper Temp = *this;
        --*this;
        return Temp;
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator<<(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_sll_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_sll_epi32(Value, Other.Value));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator>>(const TSolidSIMDWrapper& Other) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_srl_epi32(Value, Other.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_srl_epi32(Value, Other.Value));
        }
    }

    FORCEINLINE TSolidSIMDWrapper& operator<<=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this << Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator>>=(const TSolidSIMDWrapper& Other)
    {
        return *this = *this >> Other;
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator<<(const int32 Other) const
    {
        return *this << TSolidSIMDWrapper(Other);
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator>>(const int32 Other) const
    {
        return *this >> TSolidSIMDWrapper(Other);
    }

    FORCEINLINE TSolidSIMDWrapper& operator<<=(const int32 Other)
    {
        return *this = *this << Other;
    }

    FORCEINLINE TSolidSIMDWrapper& operator>>=(const int32 Other)
    {
        return *this = *this >> Other;
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator[](const int32 Index) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(Value, Index));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(Value, Index));
        }
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator[](const TSolidSIMDWrapper& Index) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(Value, Index.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(Value, Index.Value));
        }
    }

    FORCEINLINE TSolidSIMDWrapper& operator[](const int32 Index)
    {
        return *this = (*this)[Index];
    }

    FORCEINLINE TSolidSIMDWrapper& operator[](const TSolidSIMDWrapper& Index)
    {
        return *this = (*this)[Index];
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator()(const int32 Index) const
    {
        return (*this)[Index];
    }

    FORCEINLINE NO_DISCARD TSolidSIMDWrapper operator()(const TSolidSIMDWrapper& Index) const
    {
        return (*this)[Index];
    }

    FORCEINLINE TSolidSIMDWrapper& operator()(const int32 Index)
    {
        return (*this)[Index];
    }

    FORCEINLINE TSolidSIMDWrapper& operator()(const TSolidSIMDWrapper& Index)
    {
        return (*this)[Index];
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Min(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_min_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_min_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_min_ps(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_min_ps(A.Value, B.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Max(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_max_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_max_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_max_ps(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_max_ps(A.Value, B.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Abs(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_abs_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_abs_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_abs_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_abs_ps(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Sqrt(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_sqrt_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_sqrt_ps(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Reciprocal(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_rcp_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_rcp_ps(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper ReciprocalSqrt(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_rsqrt_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_rsqrt_ps(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Floor(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_floor_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_floor_ps(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Ceil(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_ceil_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_ceil_ps(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Truncate(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_round_ps(A.Value, _MM_FROUND_TRUNC));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_round_ps(A.Value, _MM_FROUND_TRUNC));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Round(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_round_ps(A.Value, _MM_FROUND_CUR_DIRECTION));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_round_ps(A.Value, _MM_FROUND_CUR_DIRECTION));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper RoundToNearestInteger(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_cvtps_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_cvtps_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_round_ps(A.Value, _MM_FROUND_NINT));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_round_ps(A.Value, _MM_FROUND_NINT));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper RoundToZero(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_cvttps_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_cvttps_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_round_ps(A.Value, _MM_FROUND_TRUNC));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_round_ps(A.Value, _MM_FROUND_TRUNC));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper RoundToNegativeInfinity(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_round_ps(A.Value, _MM_FROUND_FLOOR));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_round_ps(A.Value, _MM_FROUND_FLOOR));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper RoundToPositiveInfinity(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_round_ps(A.Value, _MM_FROUND_CEIL));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_round_ps(A.Value, _MM_FROUND_CEIL));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Select(const TSolidSIMDWrapper& Mask, const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_blendv_epi8(B.Value, A.Value, Mask.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_blendv_epi8(B.Value, A.Value, Mask.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_blendv_ps(B.Value, A.Value, Mask.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_blendv_ps(B.Value, A.Value, Mask.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Select(const TSolidSIMDWrapper& Mask, const TSolidSIMDWrapper& A,
        const TSolidSIMDWrapper& B, const TSolidSIMDWrapper& C)
    {
        return Select(Mask, A, Select(~Mask, B, C));
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Select(const TSolidSIMDWrapper& Mask, const TSolidSIMDWrapper& A,
        const TSolidSIMDWrapper& B, const TSolidSIMDWrapper& C, const TSolidSIMDWrapper& D)
    {
        return Select(Mask, A, Select(~Mask, B, C, D));
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalAdd(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
              return TSolidSIMDWrapper(_mm_hadd_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
           return TSolidSIMDWrapper(_mm256_hadd_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
              return TSolidSIMDWrapper(_mm_hadd_ps(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
           return TSolidSIMDWrapper(_mm256_hadd_ps(A.Value, B.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalSubtract(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
              return TSolidSIMDWrapper(_mm_hsub_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
           return TSolidSIMDWrapper(_mm256_hsub_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
              return TSolidSIMDWrapper(_mm_hsub_ps(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
           return TSolidSIMDWrapper(_mm256_hsub_ps(A.Value, B.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalAddSubtract(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalAdd(A, B) - HorizontalSubtract(A, B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalSubtractAdd(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalSubtract(A, B) + HorizontalAdd(A, B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper UnpackLow(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_unpacklo_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_unpacklo_epi32(A.Value, B.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper UnpackHigh(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_unpackhi_epi32(A.Value, B.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_unpackhi_epi32(A.Value, B.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Shuffle(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B, const int32 Control)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(_mm_unpacklo_epi32(A.Value, B.Value), Control));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(_mm256_unpacklo_epi32(A.Value, B.Value), Control));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Permute(const TSolidSIMDWrapper& A, const int32 Control)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(A.Value, Control));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(A.Value, Control));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Permute(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& Control)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(A.Value, Control.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(A.Value, Control.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Permute(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B,
        const int32 Control)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(_mm_unpacklo_epi32(A.Value, B.Value), Control));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(_mm256_unpacklo_epi32(A.Value, B.Value), Control));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Permute(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B,
     const TSolidSIMDWrapper& Control)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_shuffle_epi32(_mm_unpacklo_epi32(A.Value, B.Value), Control.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_shuffle_epi32(_mm256_unpacklo_epi32(A.Value, B.Value), Control.Value));
        }
    }
    
    FORCEINLINE NO_DISCARD static float HorizontalSum(const TSolidSIMDWrapper<FSimd128>& A)
    {
        FSimd128 Shuffle = _mm_movehdup_ps(A.Value);  // duplicate high elements
        FSimd128 Sums = _mm_add_ps(A.Value, Shuffle);
        Shuffle = _mm_movehl_ps(Shuffle, Sums); // high half -> low half
        Sums = _mm_add_ss(Sums, Shuffle);
        return _mm_cvtss_f32(Sums);
    }

    template <typename InValueType>
    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper<InValueType> Convert(const TSolidSIMDWrapper<InValueType>& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper<InValueType>(_mm_cvtepi32_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper<InValueType>(_mm256_cvtepi32_ps(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper<InValueType>(_mm_cvtps_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper<InValueType>(_mm256_cvtps_epi32(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Min(const TSolidSIMDWrapper& A,
        const TSolidSIMDWrapper& B, const TSolidSIMDWrapper& C)
    {
        return Min(Min(A, B), C);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Max(const TSolidSIMDWrapper& A,
        const TSolidSIMDWrapper& B, const TSolidSIMDWrapper& C)
    {
        return Max(Max(A, B), C);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Min(const TSolidSIMDWrapper& A,
        const TSolidSIMDWrapper& B, const TSolidSIMDWrapper& C, const TSolidSIMDWrapper& D)
    {
        return Min(Min(A, B), Min(C, D));
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Max(const TSolidSIMDWrapper& A,
        const TSolidSIMDWrapper& B, const TSolidSIMDWrapper& C, const TSolidSIMDWrapper& D)
    {
        return Max(Max(A, B), Max(C, D));
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Sum(const TSolidSIMDWrapper& A)
    {
        return HorizontalAdd(A, A);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Product(const TSolidSIMDWrapper& A)
    {
        return HorizontalMultiply(A, A);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalMultiply(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalAdd(A * B, A * B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalMultiplySubtract(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalSubtract(HorizontalMultiply(A, B), A * B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalMultiplyAdd(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalAdd(HorizontalMultiply(A, B), A * B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalMultiplySubtractAdd(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalAdd(HorizontalMultiplySubtract(A, B), A * B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalMultiplyAddSubtract(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalSubtract(HorizontalMultiplyAdd(A, B), A * B);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper HorizontalMultiplySubtractAddSubtract(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return HorizontalSubtract(HorizontalMultiplyAddSubtract(A, B), A * B);
    }
    
    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper SetAll(const int32 Value)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_set1_epi32(Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_set1_epi32(Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper SetAll(const float Value)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_set1_ps(Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_set1_ps(Value));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Set(const float X, const float Y, const float Z, const float W)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_set_ps(W, Z, Y, X));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_set_ps(W, Z, Y, X, W, Z, Y, X));
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper MaskedLoad(const float* Ptr, const TSolidSIMDWrapper& Mask)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_maskload_ps(Ptr, Mask.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_maskload_ps(Ptr, Mask.Value));
        }
    }

    FORCEINLINE void MaskedStore(float* Ptr, const TSolidSIMDWrapper& Mask) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            _mm_maskstore_ps(Ptr, Mask.Value, Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            _mm256_maskstore_ps(Ptr, Mask.Value, Value);
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper MaskedLoad(const int32* Ptr, const TSolidSIMDWrapper& Mask)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_maskload_epi32(Ptr, Mask.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_maskload_epi32(Ptr, Mask.Value));
        }
    }

    FORCEINLINE void MaskedStore(int32* Ptr, const TSolidSIMDWrapper& Mask) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            _mm_maskstore_epi32(Ptr, Mask.Value, Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            _mm256_maskstore_epi32(Ptr, Mask.Value, Value);
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load(const float* Ptr)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            return TSolidSIMDWrapper(_mm_load_ps(Ptr));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            return TSolidSIMDWrapper(_mm256_load_ps(Ptr));
        }
    }

    FORCEINLINE void Store(float* Ptr) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128>)
        {
            _mm_store_ps(Ptr, Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256>)
        {
            _mm256_store_ps(Ptr, Value);
        }
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load(const int32* Ptr)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_load_si128(reinterpret_cast<const FSimd128I*>(Ptr)));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_load_si256(reinterpret_cast<const FSimd256I*>(Ptr)));
        }
    }

    FORCEINLINE void Store(int32* Ptr) const
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            _mm_store_si128(reinterpret_cast<FSimd128I*>(Ptr), Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            _mm256_store_si256(reinterpret_cast<FSimd256I*>(Ptr), Value);
        }
    }

    // Broadcast Functions
    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper BroadcastX(const TSolidSIMDWrapper& A)
    {
        return Permute(A, 0);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper BroadcastY(const TSolidSIMDWrapper& A)
    {
        return Permute(A, 1);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper BroadcastZ(const TSolidSIMDWrapper& A)
    {
        return Permute(A, 2);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper BroadcastW(const TSolidSIMDWrapper& A)
    {
        return Permute(A, 3);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const float Value)
    {
        return SetAll(Value);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const int32 Value)
    {
        return SetAll(Value);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const TSolidSIMDWrapper& A, const int32 Index)
    {
        return Permute(A, Index);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& Index)
    {
        return Permute(A, Index);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const float X, const float Y, const float Z, const float W)
    {
        return Set(X, Y, Z, W);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const int32 X, const int32 Y, const int32 Z, const int32 W)
    {
        return Set(X, Y, Z, W);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Broadcast(const TSolidSIMDWrapper& X, const TSolidSIMDWrapper& Y,
        const TSolidSIMDWrapper& Z, const TSolidSIMDWrapper& W)
    {
        return Set(X, Y, Z, W);
    }

    // Load Functions
    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load1(const float* Ptr)
    {
        return Load(Ptr);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load1(const int32* Ptr)
    {
        return Load(Ptr);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load2(const float* Ptr)
    {
        return Set(Ptr[0], Ptr[1], 0.0f, 0.0f);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load2(const int32* Ptr)
    {
        return Set(Ptr[0], Ptr[1], 0, 0);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load3(const float* Ptr)
    {
        return Set(Ptr[0], Ptr[1], Ptr[2], 0.0f);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load3(const int32* Ptr)
    {
        return Set(Ptr[0], Ptr[1], Ptr[2], 0);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load4(const float* Ptr)
    {
        return Load(Ptr);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Load4(const int32* Ptr)
    {
        return Load(Ptr);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const int32* Indices)
    {
        return Set(Ptr[Indices[0]], Ptr[Indices[1]], Ptr[Indices[2]], Ptr[Indices[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const int32* Indices)
    {
        return Set(Ptr[Indices[0]], Ptr[Indices[1]], Ptr[Indices[2]], Ptr[Indices[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices)
    {
        return Set(Ptr[Indices[0]], Ptr[Indices[1]], Ptr[Indices[2]], Ptr[Indices[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices)
    {
        return Set(Ptr[Indices[0]], Ptr[Indices[1]], Ptr[Indices[2]], Ptr[Indices[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale)
    {
        return Set(Ptr[Indices[0] * Scale], Ptr[Indices[1] * Scale], Ptr[Indices[2] * Scale], Ptr[Indices[3] * Scale]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale)
    {
        return Set(Ptr[Indices[0] * Scale], Ptr[Indices[1] * Scale], Ptr[Indices[2] * Scale], Ptr[Indices[3] * Scale]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale)
    {
        return Set(Ptr[Indices[0] * Scale[0]], Ptr[Indices[1] * Scale[1]], Ptr[Indices[2] * Scale[2]], Ptr[Indices[3] * Scale[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale)
    {
        return Set(Ptr[Indices[0] * Scale[0]], Ptr[Indices[1] * Scale[1]], Ptr[Indices[2] * Scale[2]], Ptr[Indices[3] * Scale[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const int32 Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset], Ptr[Indices[1] * Scale + Offset], Ptr[Indices[2] * Scale + Offset], Ptr[Indices[3] * Scale + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const int32 Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset], Ptr[Indices[1] * Scale + Offset], Ptr[Indices[2] * Scale + Offset], Ptr[Indices[3] * Scale + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const TSolidSIMDWrapper& Offset)
    {
        return Set(Ptr[Indices[0] * Scale[0] + Offset[0]], Ptr[Indices[1] * Scale[1] + Offset[1]], Ptr[Indices[2] * Scale[2] + Offset[2]], Ptr[Indices[3] * Scale[3] + Offset[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const TSolidSIMDWrapper& Offset)
    {
        return Set(Ptr[Indices[0] * Scale[0] + Offset[0]], Ptr[Indices[1] * Scale[1] + Offset[1]], Ptr[Indices[2] * Scale[2] + Offset[2]], Ptr[Indices[3] * Scale[3] + Offset[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const TSolidSIMDWrapper& Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset[0]], Ptr[Indices[1] * Scale + Offset[1]], Ptr[Indices[2] * Scale + Offset[2]], Ptr[Indices[3] * Scale + Offset[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const TSolidSIMDWrapper& Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset[0]], Ptr[Indices[1] * Scale + Offset[1]], Ptr[Indices[2] * Scale + Offset[2]], Ptr[Indices[3] * Scale + Offset[3]]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const int32 Offset)
    {
        return Set(Ptr[Indices[0] * Scale[0] + Offset], Ptr[Indices[1] * Scale[1] + Offset], Ptr[Indices[2] * Scale[2] + Offset], Ptr[Indices[3] * Scale[3] + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const int32 Offset)
    {
        return Set(Ptr[Indices[0] * Scale[0] + Offset], Ptr[Indices[1] * Scale[1] + Offset], Ptr[Indices[2] * Scale[2] + Offset], Ptr[Indices[3] * Scale[3] + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const float Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset], Ptr[Indices[1] * Scale + Offset], Ptr[Indices[2] * Scale + Offset], Ptr[Indices[3] * Scale + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const float Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset], Ptr[Indices[1] * Scale + Offset], Ptr[Indices[2] * Scale + Offset], Ptr[Indices[3] * Scale + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const float* Ptr, const TSolidSIMDWrapper& Indices, const float Scale, const int32 Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset], Ptr[Indices[1] * Scale + Offset], Ptr[Indices[2] * Scale + Offset], Ptr[Indices[3] * Scale + Offset]);
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper Gather(const int32* Ptr, const TSolidSIMDWrapper& Indices, const float Scale, const int32 Offset)
    {
        return Set(Ptr[Indices[0] * Scale + Offset], Ptr[Indices[1] * Scale + Offset], Ptr[Indices[2] * Scale + Offset], Ptr[Indices[3] * Scale + Offset]);
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices) const
    {
        Ptr[Indices[0]] = (*this)[0];
        Ptr[Indices[1]] = (*this)[1];
        Ptr[Indices[2]] = (*this)[2];
        Ptr[Indices[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices) const
    {
        Ptr[Indices[0]] = (*this)[0];
        Ptr[Indices[1]] = (*this)[1];
        Ptr[Indices[2]] = (*this)[2];
        Ptr[Indices[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale) const
    {
        Ptr[Indices[0] * Scale] = (*this)[0];
        Ptr[Indices[1] * Scale] = (*this)[1];
        Ptr[Indices[2] * Scale] = (*this)[2];
        Ptr[Indices[3] * Scale] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale) const
    {
        Ptr[Indices[0] * Scale] = (*this)[0];
        Ptr[Indices[1] * Scale] = (*this)[1];
        Ptr[Indices[2] * Scale] = (*this)[2];
        Ptr[Indices[3] * Scale] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale) const
    {
        Ptr[Indices[0] * Scale[0]] = (*this)[0];
        Ptr[Indices[1] * Scale[1]] = (*this)[1];
        Ptr[Indices[2] * Scale[2]] = (*this)[2];
        Ptr[Indices[3] * Scale[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale) const
    {
        Ptr[Indices[0] * Scale[0]] = (*this)[0];
        Ptr[Indices[1] * Scale[1]] = (*this)[1];
        Ptr[Indices[2] * Scale[2]] = (*this)[2];
        Ptr[Indices[3] * Scale[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const int32 Offset) const
    {
        Ptr[Indices[0] * Scale + Offset] = (*this)[0];
        Ptr[Indices[1] * Scale + Offset] = (*this)[1];
        Ptr[Indices[2] * Scale + Offset] = (*this)[2];
        Ptr[Indices[3] * Scale + Offset] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const int32 Offset) const
    {
        Ptr[Indices[0] * Scale + Offset] = (*this)[0];
        Ptr[Indices[1] * Scale + Offset] = (*this)[1];
        Ptr[Indices[2] * Scale + Offset] = (*this)[2];
        Ptr[Indices[3] * Scale + Offset] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const TSolidSIMDWrapper& Offset) const
    {
        Ptr[Indices[0] * Scale[0] + Offset[0]] = (*this)[0];
        Ptr[Indices[1] * Scale[1] + Offset[1]] = (*this)[1];
        Ptr[Indices[2] * Scale[2] + Offset[2]] = (*this)[2];
        Ptr[Indices[3] * Scale[3] + Offset[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const TSolidSIMDWrapper& Offset) const
    {
        Ptr[Indices[0] * Scale[0] + Offset[0]] = (*this)[0];
        Ptr[Indices[1] * Scale[1] + Offset[1]] = (*this)[1];
        Ptr[Indices[2] * Scale[2] + Offset[2]] = (*this)[2];
        Ptr[Indices[3] * Scale[3] + Offset[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const TSolidSIMDWrapper& Offset) const
    {
        Ptr[Indices[0] * Scale + Offset[0]] = (*this)[0];
        Ptr[Indices[1] * Scale + Offset[1]] = (*this)[1];
        Ptr[Indices[2] * Scale + Offset[2]] = (*this)[2];
        Ptr[Indices[3] * Scale + Offset[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const int32 Scale, const TSolidSIMDWrapper& Offset) const
    {
        Ptr[Indices[0] * Scale + Offset[0]] = (*this)[0];
        Ptr[Indices[1] * Scale + Offset[1]] = (*this)[1];
        Ptr[Indices[2] * Scale + Offset[2]] = (*this)[2];
        Ptr[Indices[3] * Scale + Offset[3]] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const int32 Offset) const
    {
        Ptr[Indices[0] * Scale[0] + Offset] = (*this)[0];
        Ptr[Indices[1] * Scale[1] + Offset] = (*this)[1];
        Ptr[Indices[2] * Scale[2] + Offset] = (*this)[2];
        Ptr[Indices[3] * Scale[3] + Offset] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const TSolidSIMDWrapper& Scale, const int32 Offset) const
    {
        Ptr[Indices[0] * Scale[0] + Offset] = (*this)[0];
        Ptr[Indices[1] * Scale[1] + Offset] = (*this)[1];
        Ptr[Indices[2] * Scale[2] + Offset] = (*this)[2];
        Ptr[Indices[3] * Scale[3] + Offset] = (*this)[3];
    }

    FORCEINLINE void Scatter(float* Ptr, const TSolidSIMDWrapper& Indices, const float Scale, const int32 Offset) const
    {
        Ptr[Indices[0] * Scale + Offset] = (*this)[0];
        Ptr[Indices[1] * Scale + Offset] = (*this)[1];
        Ptr[Indices[2] * Scale + Offset] = (*this)[2];
        Ptr[Indices[3] * Scale + Offset] = (*this)[3];
    }

    FORCEINLINE void Scatter(int32* Ptr, const TSolidSIMDWrapper& Indices, const float Scale, const int32 Offset) const
    {
        Ptr[Indices[0] * Scale + Offset] = (*this)[0];
        Ptr[Indices[1] * Scale + Offset] = (*this)[1];
        Ptr[Indices[2] * Scale + Offset] = (*this)[2];
        Ptr[Indices[3] * Scale + Offset] = (*this)[3];
    }

    FORCEINLINE NO_DISCARD static TSolidSIMDWrapper PopCount(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return TSolidSIMDWrapper(_mm_popcnt_epi32(A.Value));
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return TSolidSIMDWrapper(_mm256_popcnt_epi32(A.Value));
        }
    }

    FORCEINLINE NO_DISCARD static int32 CountLeadingZeros(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return _mm_clz_epi32(A.Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return _mm256_clz_epi32(A.Value);
        }
    }

    FORCEINLINE NO_DISCARD static int32 CountTrailingZeros(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return _mm_ctz_epi32(A.Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return _mm256_ctz_epi32(A.Value);
        }
    }

    FORCEINLINE NO_DISCARD static int32 CountLeadingSignBits(const TSolidSIMDWrapper& A)
    {
        if constexpr (std::is_same_v<ValueType, FSimd128I>)
        {
            return _mm_cmsb_epi32(A.Value);
        }
        else if constexpr (std::is_same_v<ValueType, FSimd256I>)
        {
            return _mm256_cmsb_epi32(A.Value);
        }
    }

    FORCEINLINE NO_DISCARD static int32 PopCount(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return PopCount(A) + PopCount(B);
    }

    FORCEINLINE NO_DISCARD static int32 CountLeadingZeros(const TSolidSIMDWrapper& A, const TSolidSIMDWrapper& B)
    {
        return CountLeadingZeros(A) + CountLeadingZeros(B);
    }
    
}; // struct TSolidSIMDWrapper

#endif // SOLID_MACROS_SIMD_SIMD_H