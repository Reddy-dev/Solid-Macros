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
	SOLID_INLINE TSolidResult() = default;
	SOLID_INLINE TSolidResult(const ValueType& Value) : Value(Value) {}
	SOLID_INLINE TSolidResult(ValueType&& Value) : Value(std::move(Value)) {}
	SOLID_INLINE TSolidResult(const ErrorType& Error) : Value(Error) {}
	SOLID_INLINE TSolidResult(ErrorType&& Error) : Value(std::move(Error)) {}
	
	SOLID_INLINE NO_DISCARD bool IsOk() const
	{
		return std::holds_alternative<ValueType>(Value);
	}
	
	SOLID_INLINE NO_DISCARD bool IsError() const
	{
		return std::holds_alternative<ErrorType>(Value);
	}
	
	SOLID_INLINE NO_DISCARD ValueType& GetValue()
	{
		return std::get<ValueType>(Value);
	}

	SOLID_INLINE NO_DISCARD const ValueType& GetValue() const
	{
		return std::get<ValueType>(Value);
	}
	
	SOLID_INLINE NO_DISCARD ErrorType& GetError()
	{
		return std::get<ErrorType>(Value);
	}

	SOLID_INLINE NO_DISCARD const ErrorType& GetError() const
	{
		return std::get<ErrorType>(Value);
	}

	SOLID_INLINE NO_DISCARD ValueType& operator*()
	{
		return GetValue();
	}
	
	SOLID_INLINE NO_DISCARD const ValueType& operator*() const
	{
		return GetValue();
	}

	SOLID_INLINE NO_DISCARD ValueType* operator->()
	{
		return &GetValue();
	}

	SOLID_INLINE NO_DISCARD const ValueType* operator->() const
	{
		return &GetValue();
	}

	SOLID_INLINE NO_DISCARD operator bool() const
	{
		return IsOk();
	}

	SOLID_INLINE NO_DISCARD bool operator!() const
	{
		return IsError();
	}

	SOLID_INLINE NO_DISCARD bool operator==(const TSolidResult& Other) const
	{
		return Value == Other.Value;
	}

	SOLID_INLINE NO_DISCARD bool operator!=(const TSolidResult& Other) const
	{
		return Value != Other.Value;
	}

	SOLID_INLINE NO_DISCARD bool operator==(const ValueType& Other) const
	{
		return Value == Other;
	}

	SOLID_INLINE NO_DISCARD bool operator!=(const ValueType& Other) const
	{
		return Value != Other;
	}

	SOLID_INLINE NO_DISCARD bool operator==(const ErrorType& Other) const
	{
		return Value == Other;
	}

	SOLID_INLINE NO_DISCARD bool operator!=(const ErrorType& Other) const
	{
		return Value != Other;
	}

	SOLID_INLINE TSolidResult& operator=(const ValueType& Other) NOEXCEPT
	{
		Value = Other;
		return *this;
	}

	SOLID_INLINE TSolidResult& operator=(ValueType&& Other) NOEXCEPT
	{
		Value = std::move(Other);
		return *this;
	}

	SOLID_INLINE TSolidResult& operator=(const ErrorType& Other) NOEXCEPT
	{
		Value = Other;
		return *this;
	}

	SOLID_INLINE TSolidResult& operator=(ErrorType&& Other) NOEXCEPT
	{
		Value = std::move(Other);
		return *this;
	}

private:
	std::variant<ValueType, ErrorType> Value;
}; // class TSolidResult

#endif //SOLIDARITY_UTILS_SOLID_RESULT_H