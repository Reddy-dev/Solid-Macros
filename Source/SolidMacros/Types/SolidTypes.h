// Solstice Games © 2024. All Rights Reserved.

// ReSharper disable CppFunctionIsNotImplemented

#ifndef SOLID_TYPES_H
#define SOLID_TYPES_H

#include <string_view>

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

namespace Solid::Meta
{
    template <typename...>
    struct TTypeGroup
    {
    private:
        static inline uint32 NextId = 0;
    public:
        template <typename ...Type>
        static inline const uint32 Id = NextId++;
        
    }; // struct TTypeGroup

    template <>
    struct TTypeGroup<void>;

    struct FTypeInfo final
    {
    private:
        FORCEINLINE constexpr static NO_DISCARD uint64 FindFirstOf(const char* Data, const uint64 Length,
            const char Search, const uint64 SearchStartPosition = 0)
        {
            for (uint64 Index = SearchStartPosition; Index < Length; ++Index)
            {
                if (Data[Index] == Search)
                {
                    return Index;
                }
            }
            
            return static_cast<uint64>(-1);
        }

        FORCEINLINE constexpr static NO_DISCARD uint64 FindLastOf(const char* Data, const uint64 Length,
            const char Search, const uint64 SearchStartPosition = static_cast<uint64>(-1))
        {
            for (uint64 Index = Length - 1; Index >= SearchStartPosition; --Index)
            {
                if (Data[Index] == Search)
                {
                    return Index;
                }
            }
            
            return static_cast<uint64>(-1);
        }

    public:
        template <typename T>
        FORCEINLINE constexpr NO_DISCARD uint32 Id()
        {
            return TTypeGroup<T>::template Id<T>;
        }
        
    }; // struct FTypeTraits

    MSVC_WARNING_PUSH

    MSVC_WARNING_DISABLE(4702)

    namespace detail
    {
        // Check if type T is constructible via T{Args...}
        struct any_type
        {
            template <typename T>
            constexpr operator T(); // non explicit
        }; // struct any_type

        template <typename T, typename... TArgs>
        decltype(void(T{std::declval<TArgs>()...}), std::true_type{}) is_braces_constructible(int);

        template <typename, typename...>
        std::false_type is_braces_constructible(...);

        template <typename T, typename... TArgs>
        using is_braces_constructible_t = decltype(detail::is_braces_constructible<T, TArgs...>(0));
        
    } // namespace detail

    template <typename StructType, uint64 ...Indices, typename Tuple>
    FORCEINLINE NO_DISCARD StructType TupleToStruct(const Tuple& InTuple, std::index_sequence<Indices...>)
    {
        return { std::get<Indices>(std::forward<Tuple>(InTuple))... };
    }

    template <typename StructType, typename Tuple>
    FORCEINLINE NO_DISCARD StructType TupleToStruct(const Tuple& InTuple)
    {
        using TupleType = std::remove_reference_t<Tuple>;
        return TupleToStruct<StructType>(std::make_index_sequence<std::tuple_size_v<TupleType>>(),
            std::forward<Tuple>(InTuple));
    }

    /*
     * C++'s PRE-PROCESSOR SUCKS
     **/

    static constexpr uint32 STRUCT_TO_TUPLE_MAX_TYPES_BITS = 4;
    static constexpr uint32 STRUCT_TO_TUPLE_MAX_TYPES = (1 << STRUCT_TO_TUPLE_MAX_TYPES_BITS) - 1;

    #define SOLID_CONCAT(a, b) SOLID_CONCAT_IMPL(a, b)
    #define SOLID_CONCAT_IMPL(a, b) a##b

    #define SOLID_REPEAT_1(x) SOLID_CONCAT(x,1)
    #define SOLID_REPEAT_2(x) SOLID_REPEAT_1(x), SOLID_CONCAT(x,2)
    #define SOLID_REPEAT_3(x) SOLID_REPEAT_2(x), SOLID_CONCAT(x,3)
    #define SOLID_REPEAT_4(x) SOLID_REPEAT_3(x), SOLID_CONCAT(x,4)
    #define SOLID_REPEAT_5(x) SOLID_REPEAT_4(x), SOLID_CONCAT(x,5)
    #define SOLID_REPEAT_6(x) SOLID_REPEAT_5(x), SOLID_CONCAT(x,6)
    #define SOLID_REPEAT_7(x) SOLID_REPEAT_6(x), SOLID_CONCAT(x,7)
    #define SOLID_REPEAT_8(x) SOLID_REPEAT_7(x), SOLID_CONCAT(x,8)
    #define SOLID_REPEAT_9(x) SOLID_REPEAT_8(x), SOLID_CONCAT(x,9)
    #define SOLID_REPEAT_10(x) SOLID_REPEAT_9(x), SOLID_CONCAT(x,10)
    #define SOLID_REPEAT_11(x) SOLID_REPEAT_10(x), SOLID_CONCAT(x,11)
    #define SOLID_REPEAT_12(x) SOLID_REPEAT_11(x), SOLID_CONCAT(x,12)
    #define SOLID_REPEAT_13(x) SOLID_REPEAT_12(x), SOLID_CONCAT(x,13)
    #define SOLID_REPEAT_14(x) SOLID_REPEAT_13(x), SOLID_CONCAT(x,14)
    #define SOLID_REPEAT_15(x) SOLID_REPEAT_14(x), SOLID_CONCAT(x,15)
    #define SOLID_REPEAT_16(x) SOLID_REPEAT_15(x), SOLID_CONCAT(x,16)
    #define SOLID_REPEAT_17(x) SOLID_REPEAT_16(x), SOLID_CONCAT(x,17)
    #define SOLID_REPEAT_18(x) SOLID_REPEAT_17(x), SOLID_CONCAT(x,18)
    #define SOLID_REPEAT_19(x) SOLID_REPEAT_18(x), SOLID_CONCAT(x,19)
    #define SOLID_REPEAT_20(x) SOLID_REPEAT_19(x), SOLID_CONCAT(x,20)
    

    #define SOLID_REPEAT(x, N) SOLID_CONCAT(SOLID_REPEAT_, N)(x)

    #define SOLID_REPEAT_NO_NUM_1(x) x
    #define SOLID_REPEAT_NO_NUM_2(x) x, x
    #define SOLID_REPEAT_NO_NUM_3(x) x, x, x
    #define SOLID_REPEAT_NO_NUM_4(x) x, x, x, x
    #define SOLID_REPEAT_NO_NUM_5(x) x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_6(x) x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_7(x) x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_8(x) x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_9(x) x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_10(x) x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_11(x) x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_12(x) x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_13(x) x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_14(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_15(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_16(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_17(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_18(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_19(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x
    #define SOLID_REPEAT_NO_NUM_20(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x

    #define SOLID_REPEAT_NO_NUM(x, N) SOLID_CONCAT(SOLID_REPEAT_NO_NUM_, N)(x)

    #define IS_BRACES_CONSTRUCTIBLE_N(TYPE, N) \
        detail::is_braces_constructible_t<TYPE, SOLID_REPEAT_NO_NUM(detail::any_type, N)>{}

    #define STRUCT_MEMBERS_CASE(Num) \
        auto&& [SOLID_REPEAT(p, Num)] = std::forward<T>(InStruct); \

    #define STRUCT_TO_TUPLE_CASE(Num) \
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, Num)) { \
            auto&& [SOLID_REPEAT(p, Num)] = std::forward<T>(InStruct); \
            return std::make_tuple(SOLID_REPEAT(p, Num)); \
        }

    #define FOR_EACH_MEMBER_CASE(Num) \
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, Num)) \
        { \
            STRUCT_MEMBERS_CASE(Num) \
            return InFunction(SOLID_REPEAT(p, Num)); \
        }

    template <typename T>
    FORCEINLINE auto StructToTuple(T&& InStruct)
    {
        using Type = std::decay_t<std::remove_pointer_t<T>>;

        if constexpr (std::is_empty_v<Type>)
        {
            return std::make_tuple();
        }
        
        STRUCT_TO_TUPLE_CASE(15)
        STRUCT_TO_TUPLE_CASE(14)
        STRUCT_TO_TUPLE_CASE(13)
        STRUCT_TO_TUPLE_CASE(12)
        STRUCT_TO_TUPLE_CASE(11)
        STRUCT_TO_TUPLE_CASE(10)
        STRUCT_TO_TUPLE_CASE(9)
        STRUCT_TO_TUPLE_CASE(8)
        STRUCT_TO_TUPLE_CASE(7)
        STRUCT_TO_TUPLE_CASE(6)
        STRUCT_TO_TUPLE_CASE(5)
        STRUCT_TO_TUPLE_CASE(4)
        STRUCT_TO_TUPLE_CASE(3)
        STRUCT_TO_TUPLE_CASE(2)
        STRUCT_TO_TUPLE_CASE(1)
        
        constexpr std::string_view TypeName = nameof(Type);
        checkf(false, TEXT("Unsupported Number of Members in Struct: %s"), TypeName.data());
    }

    template <typename T>
    FORCEINLINE auto StructMemberCount()
    {
        using Type = std::decay_t<std::remove_pointer_t<T>>;

        if constexpr (std::is_empty_v<Type>)
        {
            return 0;
        }
        
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 15))
        {
            return 15;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 14))
        {
            return 14;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 13))
        {
            return 13;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 12))
        {
            return 12;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 11))
        {
            return 11;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 10))
        {
            return 10;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 9))
        {
            return 9;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 8))
        {
            return 8;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 7))
        {
            return 7;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 6))
        {
            return 6;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 5))
        {
            return 5;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 4))
        {
            return 4;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 3))
        {
            return 3;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 2))
        {
            return 2;
        }
        if constexpr (IS_BRACES_CONSTRUCTIBLE_N(Type, 1))
        {
            return 1;
        }

        constexpr std::string_view TypeName = nameof(Type);
        checkf(false, TEXT("Unsupported Number of Members in Struct: %s"), TypeName.data());
    }

    template <typename T, typename FunctionType>
    FORCEINLINE auto ForEachMember(T&& InStruct, FunctionType&& InFunction)
    {
        using Type = std::decay_t<std::remove_pointer_t<T>>;

        if constexpr (std::is_empty_v<Type>)
        {
            InFunction();
        }
        
        FOR_EACH_MEMBER_CASE(15)
        FOR_EACH_MEMBER_CASE(14)
        FOR_EACH_MEMBER_CASE(13)
        FOR_EACH_MEMBER_CASE(12)
        FOR_EACH_MEMBER_CASE(11)
        FOR_EACH_MEMBER_CASE(10)
        FOR_EACH_MEMBER_CASE(9)
        FOR_EACH_MEMBER_CASE(8)
        FOR_EACH_MEMBER_CASE(7)
        FOR_EACH_MEMBER_CASE(6)
        FOR_EACH_MEMBER_CASE(5)
        FOR_EACH_MEMBER_CASE(4)
        FOR_EACH_MEMBER_CASE(3)
        FOR_EACH_MEMBER_CASE(2)
        FOR_EACH_MEMBER_CASE(1)

        constexpr std::string_view TypeName = nameof(Type);
        checkf(false, TEXT("Unsupported Number of Members in Struct: %s"), TypeName.data());
    }
    
    MSVC_WARNING_POP // 4702
    
} // namespace Solid::Meta

#endif // SOLID_TYPES_H
