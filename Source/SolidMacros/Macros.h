// Solstice Games © 2023. All Rights Reserved.

#pragma once

#ifndef SOLID_MACROS_H
#define SOLID_MACROS_H

#include <string>
#include <array>
#include <utility>

#include "CoreMinimal.h"

template <std::size_t ...Idxs>
FORCEINLINE constexpr auto substring_as_array(std::string_view str, std::index_sequence<Idxs...>)
{
	return std::array{str[Idxs]..., '\n'};
}

template <typename T>
FORCEINLINE constexpr auto type_name_array()
{
	#if defined(__clang__)
	constexpr auto prefix   = std::string_view{"[T = "};
	constexpr auto suffix   = std::string_view{"]"};
	constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
	#elif defined(__GNUC__) // defined(__clang__)
	constexpr auto prefix   = std::string_view{"with T = "};
	constexpr auto suffix   = std::string_view{"]"};
	constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
	#elif defined(_MSC_VER) // defined(__GNUC__)
	constexpr auto prefix   = std::string_view{"type_name_array<"};
	constexpr auto suffix   = std::string_view{">(void)"};
	constexpr auto function = std::string_view{__FUNCSIG__};
	#else // defined(_MSC_VER)
	# error Unsupported compiler
	#endif // defined(_MSC_VER)

	constexpr uint_fast64_t start = function.find(prefix) + prefix.size();
	constexpr uint_fast32_t end = function.rfind(suffix);

	static_assert(start < end);

	constexpr std::string_view name = function.substr(start, (end - start));
	return substring_as_array(name, std::make_index_sequence<name.size()>{});
}

template <typename T>
struct type_name_holder
{
	static inline constexpr auto value = type_name_array<T>();
}; // struct type_name_holder

template <typename T>
// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
constexpr auto type_name() -> std::string_view
{
	constexpr auto& value = type_name_holder<T>::value;
	return std::string_view{value.data(), value.size()};
}

#endif // SOLID_MACROS_H

#ifndef HAS_CPP_ATTRIBUTE
#define HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#endif // HAS_CPP_ATTRIBUTE

#ifndef EXPECTS

#if HAS_CPP_ATTRIBUTE(expects)

#define EXPECTS(x) [[expects : x]]

#else // HAS_CPP_ATTRIBUTE(expects)

#define EXPECTS(x)

#endif // HAS_CPP_ATTRIBUTE(expects)

#endif // EXPECTS

#ifndef ENSURES

#if HAS_CPP_ATTRIBUTE(ensures)

#define ENSURES(x) [[ensures : x]]

#else // HAS_CPP_ATTRIBUTE(ensures)

#define ENSURES(x)

#endif // HAS_CPP_ATTRIBUTE(ensures)

#endif // ENSURES

#ifndef ATTRIBUTE
#define ATTRIBUTE __attribute__
#endif // ATTRIBUTE

#ifndef IS_CLANG

#if defined(__clang__)

#define IS_CLANG 1

#else // defined(__clang__)

#define IS_CLANG 0

#endif // defined(__clang__)

#endif // IS_CLANG

#ifndef IS_GNU

#if defined(__GNUC__)

#define IS_GNU 1

#else // defined(__GNUC__)

#define IS_GNU 0

#endif // defined(__GNUC__)

#endif // IS_GNU

#ifndef IS_MSVC

#if defined(_MSC_VER)

#define IS_MSVC 1

#else // defined(_MSC_VER)

#define IS_MSVC 0

#endif // defined(_MSC_VER

#endif // IS_MSVC

#ifndef IS_GCC
#define IS_GCC IS_GNU
#endif // IS_GCC

#ifndef IS_UNIX
#define IS_UNIX PLATFORM_UNIX
#endif // IS_UNIX

#ifndef IS_WINDOWS
#define IS_WINDOWS PLATFORM_WINDOWS
#endif // IS_WINDOWS

#ifndef IS_LINUX
#define IS_LINUX PLATFORM_LINUX
#endif // IS_LINUX

#ifndef DECLSPEC
#define DECLSPEC __declspec
#endif // DECLSPEC

#ifndef NAKED
#define NAKED DECLSPEC(naked)
#endif // NAKED

#ifndef FORCEINLINE_CALLS
#define FORCEINLINE_CALLS [[msvc::forceinline_calls]]
#endif // FORCEINLINE_CALLS

#ifndef FORCEINLINE_ATTRIBUTE

#if IS_MSVC

#define FORCEINLINE_ATTRIBUTE [[msvc::forceinline]]

#elif IS_CLANG || IS_GNU

#define FORCEINLINE_ATTRIBUTE __attribute__((always_inline))

#else // IS_MSVC

#define FORCEINLINE_ATTRIBUTE [[gnu::always_inline]]

#endif // IS_MSVC

#endif // FORCEINLINE_ATTRIBUTE

#ifndef LIKELY_ATTRIBUTE
#define LIKELY_ATTRIBUTE [[likely]]
#endif // LIKELY_ATTRIBUTE

#ifndef LIKELY_IF
#define LIKELY_IF(x) (x) LIKELY_ATTRIBUTE
#endif // LIKELY_IF

#ifndef UNLIKELY_IF
#define UNLIKELY_IF(x) (x) UNLIKELY_ATTRIBUTE
#endif // UNLIKELY_IF

#ifndef UNLIKELY_ATTRIBUTE
#define UNLIKELY_ATTRIBUTE [[unlikely]]
#endif // UNLIKELY_ATTRIBUTE

#ifndef CPP_VERSION
#define CPP_VERSION __cplusplus
#endif // CPP_VERSION

#ifndef CPP_VERSION_98
#define CPP_VERSION_98 199711L
#endif // CPP_VERSION_98

#ifndef CPP_VERSION_11
#define CPP_VERSION_11 201103L
#endif // CPP_VERSION_11

#ifndef CPP_VERSION_14
#define CPP_VERSION_14 201402L
#endif // CPP_VERSION_14

#ifndef CPP_VERSION_17
#define CPP_VERSION_17 201703L
#endif // CPP_VERSION_17

#ifndef CPP_VERSION_20
#define CPP_VERSION_20 STRUCTCPP
#endif // CPP_VERSION_20

#ifndef CPP_VERSION_23
#define CPP_VERSION_23 202300L
#endif // CPP_VERSION_23

#ifndef INLINE
#define INLINE inline
#endif // INLINE

#ifndef OPTIONAL_FORCEINLINE
#define OPTIONAL_FORCEINLINE INLINE
#endif // OPTIONAL_FORCEINLINE

#ifdef LIKELY
#undef LIKELY
#endif // LIKELY

#ifdef UNLIKELY
#undef UNLIKELY
#endif // UNLIKELY

#ifndef LIKELY

#if IS_MSVC

#define LIKELY(x) (!!(x))

#elif IS_CLANG || IS_GNU

#define LIKELY(x) __builtin_expect(!!(x), 1)

#else // IS_MSVC

#define LIKELY(x) (!!(x))

#endif // IS_MSVC

#endif // LIKELY

#ifndef UNLIKELY

#if IS_MSVC

#define UNLIKELY(x) (!!(x))

#elif IS_CLANG || IS_GNU

#define UNLIKELY(x) __builtin_expect(!!(x), 0)

#else // IS_MSVC

#define UNLIKELY(x) (!!(x))

#endif // IS_MSVC

#endif // UNLIKELY

#ifndef SOLID_INLINE
#define SOLID_INLINE FORCEINLINE
#endif // SOLID_INLINE

#ifndef NO_DISCARD
#define NO_DISCARD [[nodiscard]]
#endif // NO_DISCARD

#ifndef NO_DISCARD_REASON
#define NO_DISCARD_REASON(x) [[nodiscard(x)]]
#endif // NO_DISCARD_REASON

#ifndef NO_UNIQUE_ADDRESS
#define NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif // NO_UNIQUE_ADDRESS

#ifndef NO_VTABLE

#if HAS_CPP_ATTRIBUTE(no_vtable)

#define NO_VTABLE [[no_vtable]]

#else // HAS_CPP_ATTRIBUTE(no_vtable)

#define NO_VTABLE DECLSPEC(novtable)

#endif // HAS_CPP_ATTRIBUTE(no_vtable)

#endif // NO_VTABLE

#ifndef NO_THROW

#if HAS_CPP_ATTRIBUTE(nothrow)

#define NO_THROW [[nothrow]]

#else // HAS_CPP_ATTRIBUTE(nothrow)

#define NO_THROW

#endif // HAS_CPP_ATTRIBUTE(nothrow)

#endif // NO_THROW

#ifndef NO_ALIAS
#define NO_ALIAS [[noalias]]
#endif // NO_ALIAS

#ifndef MAYBE_UNUSED
#define MAYBE_UNUSED [[maybe_unused]]
#endif // MAYBE_UNUSED

#ifndef DEPRECATED
#define DEPRECATED [[deprecated]]
#endif // DEPRECATED

#ifndef DEPRECATED_REASON
#define DEPRECATED_REASON(x) [[deprecated(x)]]
#endif // DEPRECATED_REASON

#ifndef NO_INLINE
#define NO_INLINE [[msvc::noinline]]
#endif // NO_INLINE

#ifndef NO_INLINE_CALLS
#define NO_INLINE_CALLS [[msvc::noinline_calls]]
#endif // NO_INLINE_CALLS

#ifndef NO_GUARD
#define NO_GUARD [[msvc::no_tls_guard]]
#endif // NO_GUARD

#ifndef NO_RETURN
#define NO_RETURN [[noreturn]]
#endif // NO_RETURN

#ifndef NO_SANITIZE
#define NO_SANITIZE(x) [[no_sanitize(x)]]
#endif // NO_SANITIZE

#ifndef NOEXCEPT
#define NOEXCEPT noexcept
#endif // NOEXCEPT

#ifndef NO_EXCEPT
#define NO_EXCEPT NOEXCEPT
#endif // NO_EXCEPT

#ifndef CONSTEXPR_IF
#define CONSTEXPR_IF(x) if constexpr (x)
#endif // CONSTEXPR_IF

#ifndef CONSTEVAL
#define CONSTEVAL consteval
#endif // CONSTEVAL

#ifndef nameof
#define nameof(x) type_name<x>()
#endif // nameof

#ifndef NAME_OF
#define NAME_OF(x) nameof(x)
#endif // NAME_OF

#ifndef FUNCTION_NAME

#if defined(__GNUC__) || defined(__clang__)
#define FUNCTION_NAME __PRETTY_FUNCTION__
#else // defined(__GNUC__) || defined(__clang__)
#define FUNCTION_NAME __FUNCTION__
#endif // defined(__GNUC__) || defined(__clang__)

#endif // FUNCTION_NAME

#ifndef FUNCTION_SIGNATURE
#define FUNCTION_SIGNATURE __FUNCSIG__
#endif // FUNCTION_SIGNATURE

#ifndef FUNCTION_SIG
#define FUNCTION_SIG FUNCTION_SIGNATURE
#endif // FUNCTION_SIG

#ifndef FUNC_SIG
#define FUNC_SIG FUNCTION_SIGNATURE
#endif // FUNC_SIG

#ifndef FUNC_SIGNATURE
#define FUNC_SIGNATURE FUNCTION_SIGNATURE
#endif // FUNC_SIGNATURE

#ifndef FUNC_NAME
#define FUNC_NAME FUNCTION_NAME
#endif // FUNC_NAME

#ifndef ASSUME

#if CPP_VERSION >= CPP_VERSION_23

#define ASSUME(x) [[assume(x)]]

#else // CPP_VERSION <= CPP_VERSION_23

#define ASSUME(x) UE_ASSUME(x)

#endif // CPP_VERSION <= CPP_VERSION_23

#endif // ASSUME

#ifndef FALLTHROUGH
#define FALLTHROUGH _FALLTHROUGH
#endif // FALLTHROUGH

#ifndef OPTIMIZE_FOR_SYNC
#define OPTIMIZE_FOR_SYNC [[optimize_for_synchronized]]
#endif // OPTIMIZE_FOR_SYNC

#ifndef CARRIES_DEPENDENCY
#define CARRIES_DEPENDENCY [[carries_dependency]]
#endif // CARRIES_DEPENDENCY

#ifndef FLATTEN
#define FLATTEN [[msvc::flatten]]
#endif // FLATTEN

#ifndef INTRINSIC
#define INTRINSIC [[msvc::intrinsic]]
#endif // INTRINSIC

#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif // FILE_NAME

#ifndef LINE_NUMBER
#define LINE_NUMBER __LINE__
#endif // LINE_NUMBER

#ifndef TIME_STAMP
#define TIME_STAMP __TIME__
#endif // TIME_STAMP

#ifndef COUNTER
#define COUNTER __COUNTER__
#endif // COUNTER

#ifndef INTELLISENSE
#define INTELLISENSE __INTELLISENSE__
#endif // INTELLISENSE

#if defined(__JETBRAINS_IDE__)

#ifndef JETBRAINS_IDE
#define JETBRAINS_IDE __JETBRAINS_IDE__
#endif // JETBRAINS_IDE

#else // (__JETBRAINS_IDE__)

#ifndef JETBRAINS_IDE
#define JETBRAINS_IDE 0
#endif // JETBRAINS_IDE

#endif // (__JETBRAINS_IDE__)

#if JETBRAINS_IDE

#ifndef FORMAT
#define FORMAT [[jetbrains::format]]
#endif // FORMAT

#elif defined(__GNUC__) // JETBRAINS_IDE

#ifndef FORMAT
#define FORMAT [[gnu::format]]
#endif // FORMAT

#elif defined(__clang__) // defined(__GNUC__)

#ifndef FORMAT
#define FORMAT [[clang::format]]
#endif // FORMAT

#else // defined(__clang__)

#ifndef FORMAT
#define FORMAT
#endif // FORMAT

#endif // JETBRAINS_IDE

#ifndef JETBRAINS_GUARD
#define JETBRAINS_GUARD [[jetbrains::guard]]
#endif // JETBRAINS_GUARD

#ifndef JETBRAINS_PASS_BY_VALUE
#define JETBRAINS_PASS_BY_VALUE [[jetbrains::pass_by_value]]
#endif // JETBRAINS_PASS_BY_VALUE

#ifndef ATTRIBUTE_LIST
#define ATTRIBUTE_LIST attribute_list
#endif // ATTRIBUTE_LIST

#ifndef REQUIRES

#if CPP_VERSION >= CPP_VERSION_20

namespace UE::Core::Private
{
	// Only needed for the UE_REQUIRES macro to work, to allow for a trailing > token after the macro
	template <bool Value>
	concept TBoolIdentityConcept = Value;
} // namespace UE::Core::Private

#define REQUIRES(...) \
	requires ((__VA_ARGS__) && UE::Core::Private::TBoolIdentityConcept<true>)

#else // CPP_VERSION >= CPP_VERSION_20

#define REQUIRES(...) ,std::enable_if_t<(__VA_ARGS__), bool> = true

#endif // CPP_VERSION >= CPP_VERSION_20

#endif // REQUIRES

#ifndef UNREACHABLE
#define UNREACHABLE ASSUME(false)
#endif // UNREACHABLE

#ifndef BINARY_LITERAL
#define BINARY_LITERAL(x) 0b##x
#endif // BINARY_LITERAL

#ifndef DEFINE_CUSTOM_LITERAL
#define DEFINE_CUSTOM_LITERAL(Name, Type, Literal) \
	constexpr Type operator"" Name(unsigned long long int Value) \
	{ \
		return static_cast<Type>(Value); \
	}
#endif // DEFINE_CUSTOM_LITERAL

#ifndef EXISTS
#define EXISTS(x) (!std::is_same_v<decltype(x), void>)
#endif // EXISTS

#ifndef NOT_EXISTS
#define NOT_EXISTS(x) (std::is_same_v<decltype(x), void>)
#endif // NOT_EXISTS

#ifndef IF_EXISTS
#define IF_EXISTS(x) if constexpr EXISTS(x)
#endif // IF_EXISTS

#ifndef IF_NOT_EXISTS
#define IF_NOT_EXISTS(x) if constexpr NOT_EXISTS(x)
#endif // IF_NOT_EXISTS

#ifndef UNDERLYING_TYPE
#define UNDERLYING_TYPE(x) std::underlying_type_t<x>
#endif // UNDERLYING_TYPE

#ifndef FUNCTION_TEXT

/**
 * @brief Takes the @String and Adds "FUNCTION_Name: ", to the beginning of the string.
 */
#define FUNCTION_TEXT(String) FUNCTION_NAME ": " String

#endif // FUNCTION_TEXT

#ifndef MSVC_WARNING_PUSH
#define MSVC_WARNING_PUSH __pragma(warning(push))
#endif // MSVC_WARNING_PUSH

#ifndef MSVC_WARNING_POP
#define MSVC_WARNING_POP __pragma(warning(pop))
#endif // MSVC_WARNING_POP

#ifndef MSVC_WARNING_DISABLE
#define MSVC_WARNING_DISABLE(x) __pragma(warning(disable : x))
#endif // MSVC_WARNING_DISABLE