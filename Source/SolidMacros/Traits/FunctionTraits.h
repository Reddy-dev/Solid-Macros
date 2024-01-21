// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_FUNCTION_TRAITS_H
#define SOLID_MACROS_FUNCTION_TRAITS_H

#include "CoreMinimal.h"
#include "Macros.h"

namespace Solid
{
	template <typename Method>
	struct TFunctionInfo;

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(Ts...)>
	{
		using FunctionType = ReturnType(Ts...);
		using ReturnType = ReturnType;
		using ParameterTypes = std::tuple<Ts...>;
		static CONSTEXPR uint32 ParameterCount = sizeof...(Ts);
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(*)(Ts...)> : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo
	
	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionInfo<ReturnType(ClassType::*)(Ts...)> : TFunctionInfo<ReturnType(Ts...)>
	{
		using ClassType = ClassType;
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionInfo<ReturnType(ClassType::*)(Ts...) const> : TFunctionInfo<ReturnType(Ts...)>
	{
		using ClassType = ClassType;
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionInfo<ReturnType(ClassType::*)(Ts...) volatile> : TFunctionInfo<ReturnType(Ts...)>
	{
		using ClassType = ClassType;
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionInfo<ReturnType(ClassType::*)(Ts...) const volatile> : TFunctionInfo<ReturnType(Ts...)>
	{
		using ClassType = ClassType;
	}; // struct TFunctionInfo

	template <typename T>
	struct TFunctionInfo : TFunctionInfo<decltype(&T::operator())>
	{
	}; // struct TFunctionInfo

	template <typename T>
	struct TFunctionInfo<T&> : TFunctionInfo<T>
	{
	}; // struct TFunctionInfo

	template <typename T>
	struct TFunctionInfo<const T&> : TFunctionInfo<T>
	{
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(Ts...) &>
	  : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(Ts...) const &>
	  : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(Ts...) &&>
	  : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(Ts...) const &&>
	  : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo
	
	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(&)(Ts...)>
	  : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo

	template <typename ReturnType, typename ...Ts>
	struct TFunctionInfo<ReturnType(* const)(Ts...)>
	  : TFunctionInfo<ReturnType(Ts...)>
	{
	}; // struct TFunctionInfo

	template <typename FunctionType>
	struct TFunctionTraits;

	using VoidFunctionPtr = void(*)();

	template <typename ReturnType, typename ...Ts>
	struct TFunctionTraits<ReturnType(Ts...)>
	{
		using Ptr = ReturnType(*)(Ts...);
	}; // struct TFunctionTraits

	template <typename ReturnType, typename ...Ts>
	struct TFunctionTraits<ReturnType(*const)(Ts...)>
	{
	}; // struct TFunctionTraits

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionTraits<ReturnType(ClassType::*)(Ts...)>
	{
	}; // struct TFunctionTraits

	template <typename FunctionType>
	FORCEINLINE CONSTEXPR NO_DISCARD VoidFunctionPtr LambdaToVoidPtr(FunctionType&& InFunction)
	{
		static FunctionType Lambda_Copy = InFunction;

		return [] FORCEINLINE_ATTRIBUTE -> void
		{
			Lambda_Copy();
		};
	}

#if CPP_VERSION >= CPP_VERSION_20
	
	template <typename FunctionType>
	FORCEINLINE CONSTEXPR NO_DISCARD typename TFunctionTraits<decltype(&FunctionType::operator())>::Ptr LambdaToPtr(FunctionType&& InFunction)
	{
		static FunctionType Lambda_Copy = InFunction;

		return []<typename ...Args>(Args ...InArgs) FORCEINLINE_ATTRIBUTE -> decltype(auto)
		{
			return Lambda_Copy(InArgs...);
		};
	}

#endif // CPP_VERSION >= CPP_VERSION_20
	
} // namespace Solid

#endif //SOLID_MACROS_FUNCTION_TRAITS_H