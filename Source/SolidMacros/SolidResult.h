// Solstice Games © 2023. All Rights Reserved.

#ifndef SOLIDARITY_UTILS_SOLID_RESULT_H
#define SOLIDARITY_UTILS_SOLID_RESULT_H

#include "CoreMinimal.h"
#include "Macros.h"

#include <variant>

template <typename T, typename E>
class TSolidResult
{
	using ValueType = T;
	using ErrorType = E;
	
public:
	OPTIONAL_FORCEINLINE TSolidResult() = default;
	OPTIONAL_FORCEINLINE TSolidResult(const ValueType& Value) : Value(Value) {}
	OPTIONAL_FORCEINLINE TSolidResult(ValueType&& Value) : Value(std::move(Value)) {}
	OPTIONAL_FORCEINLINE TSolidResult(const ErrorType& Error) : Value(Error) {}
	OPTIONAL_FORCEINLINE TSolidResult(ErrorType&& Error) : Value(std::move(Error)) {}
	
	OPTIONAL_FORCEINLINE NO_DISCARD bool IsOk() const
	{
		return std::holds_alternative<ValueType>(Value);
	}
	
	OPTIONAL_FORCEINLINE NO_DISCARD bool IsError() const
	{
		return std::holds_alternative<ErrorType>(Value);
	}
	
	OPTIONAL_FORCEINLINE NO_DISCARD ValueType& GetValue()
	{
		return std::get<ValueType>(Value);
	}

	OPTIONAL_FORCEINLINE NO_DISCARD const ValueType& GetValue() const
	{
		return std::get<ValueType>(Value);
	}
	
	OPTIONAL_FORCEINLINE NO_DISCARD ErrorType& GetError()
	{
		return std::get<ErrorType>(Value);
	}

	OPTIONAL_FORCEINLINE NO_DISCARD const ErrorType& GetError() const
	{
		return std::get<ErrorType>(Value);
	}

	OPTIONAL_FORCEINLINE NO_DISCARD ValueType& operator*()
	{
		return GetValue();
	}
	
	OPTIONAL_FORCEINLINE NO_DISCARD const ValueType& operator*() const
	{
		return GetValue();
	}

	OPTIONAL_FORCEINLINE NO_DISCARD ValueType* operator->()
	{
		return &GetValue();
	}

	OPTIONAL_FORCEINLINE NO_DISCARD const ValueType* operator->() const
	{
		return &GetValue();
	}

	OPTIONAL_FORCEINLINE NO_DISCARD operator bool() const
	{
		return IsOk();
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator!() const
	{
		return IsError();
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator==(const TSolidResult& Other) const
	{
		return Value == Other.Value;
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator!=(const TSolidResult& Other) const
	{
		return Value != Other.Value;
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator==(const ValueType& Other) const
	{
		return Value == Other;
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator!=(const ValueType& Other) const
	{
		return Value != Other;
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator==(const ErrorType& Other) const
	{
		return Value == Other;
	}

	OPTIONAL_FORCEINLINE NO_DISCARD bool operator!=(const ErrorType& Other) const
	{
		return Value != Other;
	}

	OPTIONAL_FORCEINLINE TSolidResult& operator=(const ValueType& Other) NOEXCEPT
	{
		Value = Other;
		return *this;
	}

	OPTIONAL_FORCEINLINE TSolidResult& operator=(ValueType&& Other) NOEXCEPT
	{
		Value = std::move(Other);
		return *this;
	}

	OPTIONAL_FORCEINLINE TSolidResult& operator=(const ErrorType& Other) NOEXCEPT
	{
		Value = Other;
		return *this;
	}

	OPTIONAL_FORCEINLINE TSolidResult& operator=(ErrorType&& Other) NOEXCEPT
	{
		Value = std::move(Other);
		return *this;
	}

private:
	std::variant<ValueType, ErrorType> Value;
}; // class TSolidResult

#endif //SOLIDARITY_UTILS_SOLID_RESULT_H