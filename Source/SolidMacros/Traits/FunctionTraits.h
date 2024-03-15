// Solstice Games © 2024. All Rights Reserved.

#ifndef SOLID_MACROS_FUNCTION_TRAITS_H
#define SOLID_MACROS_FUNCTION_TRAITS_H

#include "CoreMinimal.h"
#include "Macros.h"

namespace Solid
{
	template <typename Method>
	struct TFunctionInfo;

	template <typename TReturn, typename ...Ts>
	struct TFunctionInfo<TReturn(Ts...)>
	{
		using FunctionType = TReturn(Ts...);
		using ReturnType = TReturn;
		using ParameterTypes = std::tuple<Ts...>;
		static CONSTEXPR uint32 ParameterCount = sizeof...(Ts);
	}; // struct TFunctionInfo

	template <typename TReturn, typename ...Ts>
	struct TFunctionInfo<TReturn(*)(Ts...)> : TFunctionInfo<TReturn(Ts...)>
	{
	}; // struct TFunctionInfo
	
	template <typename TReturn, typename TClass, typename ...Ts>
	struct TFunctionInfo<TReturn(TClass::*)(Ts...)> : TFunctionInfo<TReturn(Ts...)>
	{
		using ClassType = TClass;
	}; // struct TFunctionInfo

	template <typename TReturn, typename TClass, typename ...Ts>
	struct TFunctionInfo<TReturn(TClass::*)(Ts...) const> : TFunctionInfo<TReturn(Ts...)>
	{
		using ClassType = TClass;
	}; // struct TFunctionInfo

	template <typename TReturn, typename TClass, typename ...Ts>
	struct TFunctionInfo<TReturn(TClass::*)(Ts...) volatile> : TFunctionInfo<TReturn(Ts...)>
	{
		using ClassType = TClass;
	}; // struct TFunctionInfo

	template <typename TReturn, typename TClass, typename ...Ts>
	struct TFunctionInfo<TReturn(TClass::*)(Ts...) const volatile> : TFunctionInfo<TReturn(Ts...)>
	{
		using ClassType = TClass;
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

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionTraits<ReturnType(ClassType::*)(Ts...) const>
	{
	}; // struct TFunctionTraits

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionTraits<ReturnType(ClassType::*)(Ts...) volatile>
	{
	}; // struct TFunctionTraits

	template <typename ReturnType, typename ClassType, typename ...Ts>
	struct TFunctionTraits<ReturnType(ClassType::*)(Ts...) const volatile>
	{
	}; // struct TFunctionTraits
	
	template <typename ReturnType, typename ...Ts>
	struct TFunctionTraits<ReturnType(*)(Ts...)>
	{
		using Ptr = ReturnType(*)(Ts...);
	}; // struct TFunctionTraits

	template <typename FunctionType>
	FORCEINLINE CONSTEXPR NO_DISCARD VoidFunctionPtr LambdaToVoidPtr(FunctionType&& InFunction)
	{
		static FunctionType Lambda_Copy = InFunction;

		return []()
		{
			Lambda_Copy();
		};
	}

	template < typename Method >
	struct TMethodInfo;

	template < typename Method, class C >
	struct TMethodInfo<Method C::*>
	  : TFunctionInfo<Method>
	{};

#if CPP_VERSION >= CPP_VERSION_20
	
	template <typename FunctionType>
	FORCEINLINE CONSTEXPR NO_DISCARD auto LambdaToPtr(FunctionType&& InFunction)
		-> typename TFunctionTraits<decltype(&FunctionType::operator())>::Ptr
	{
		static FunctionType Lambda_Copy = std::forward<FunctionType>(InFunction);

		// Corrected lambda syntax with template parameters
		return []<typename ...Args>(auto&&... InArgs) -> decltype(auto)
		{
			return Lambda_Copy(std::forward<decltype(InArgs)>(InArgs)...);
		};
	}

#endif // CPP_VERSION >= CPP_VERSION_20
	
} // namespace Solid

#endif //SOLID_MACROS_FUNCTION_TRAITS_H