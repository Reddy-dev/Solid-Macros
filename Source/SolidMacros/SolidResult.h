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

private:
	std::variant<ValueType, ErrorType> Value;
}; // class TSolidResult

#endif //SOLIDARITY_UTILS_SOLID_RESULT_H