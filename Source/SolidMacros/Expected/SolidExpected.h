// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_EXPECTED_SOLID_EXPECTED_H
#define SOLID_EXPECTED_SOLID_EXPECTED_H

#include <variant>

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"
#include "Concepts/SolidConcepts.h"

template <typename T, typename E>
struct TSolidExpected
{
    using ValueType = T;
    using ErrorType = E;

private:
    using StorageType = std::variant<ValueType, ErrorType>;
    
public:
    FORCEINLINE CONSTEXPR explicit TSolidExpected(const ValueType& Value) NOEXCEPT
        : Storage(Value)
    {
    }

    FORCEINLINE CONSTEXPR explicit TSolidExpected(ValueType&& Value) NOEXCEPT
        : Storage(std::move(Value))
    {
    }

    FORCEINLINE CONSTEXPR explicit TSolidExpected(const ErrorType& Error) NOEXCEPT
        : Storage(Error)
    {
    }

    FORCEINLINE CONSTEXPR explicit TSolidExpected(ErrorType&& Error) NOEXCEPT
        : Storage(std::move(Error))
    {
    }

    FORCEINLINE CONSTEXPR NO_DISCARD bool HasValue() const NOEXCEPT
    {
        return std::holds_alternative<ValueType>(Storage);
    }

    FORCEINLINE CONSTEXPR NO_DISCARD bool HasError() const NOEXCEPT
    {
        return std::holds_alternative<ErrorType>(Storage);
    }

    FORCEINLINE CONSTEXPR NO_DISCARD ValueType& GetValue()
    {
        return std::get<ValueType>(Storage);
    }

    FORCEINLINE CONSTEXPR NO_DISCARD const ValueType& GetValue() const
    {
        return std::get<ValueType>(Storage);
    }

    FORCEINLINE CONSTEXPR NO_DISCARD ErrorType& GetError()
    {
        return std::get<ErrorType>(Storage);
    }

    FORCEINLINE CONSTEXPR NO_DISCARD const ErrorType& GetError() const
    {
        return std::get<ErrorType>(Storage);
    }

    template <Solid::TInvocableConcept<ErrorType> FunctionType>
    FORCEINLINE CONSTEXPR auto Then(FunctionType&& InFunction)
        -> TSolidExpected<ValueType, decltype(std::invoke(InFunction, std::declval<ErrorType>()))>
    {
        using ResultType = decltype(std::invoke(InFunction, std::declval<ErrorType>()));
        
        if (HasValue())
        {
            return TSolidExpected<ResultType, ErrorType>(std::invoke(InFunction, GetValue()));
        }
        else
        {
            return TSolidExpected<ResultType, ErrorType>(GetError());
        }
    }

    template <Solid::TInvocableConcept<ErrorType> FunctionType>
    FORCEINLINE CONSTEXPR auto Catch(FunctionType&& InFunction)
        -> TSolidExpected<ValueType, decltype(std::invoke(InFunction, std::declval<ErrorType>()))>
    {
        using ResultType = decltype(std::invoke(InFunction, std::declval<ErrorType>()));
        
        if (HasError())
        {
            return TSolidExpected<ResultType, ErrorType>(std::invoke(InFunction, GetError()));
        }
        else
        {
            return TSolidExpected<ResultType, ErrorType>(GetValue());
        }
    }

private:
    StorageType Storage;
}; // struct TSolidExpected<T, E>

#endif // SOLID_EXPECTED_SOLID_EXPECTED_H
