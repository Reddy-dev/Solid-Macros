// Solstice Games © 2023. All Rights Reserved.

#pragma once

#ifndef EXPECTS
#define EXPECTS(x) [[expects : x]]
#endif // EXPECTS

#ifndef ENSURES
#define ENSURES(x) [[ensures : x]]
#endif // ENSURES

#ifndef ATTRIBUTE
#define ATTRIBUTE __attribute__
#endif // ATTRIBUTE

#ifndef CONSTEXPR
#define CONSTEXPR constexpr
#endif // CONSTEXPR

#ifndef FORCEINLINE_CALLS
#define [[msvc::forceinline_calls]]
#endif // FORCEINLINE_CALLS

#ifndef likely
#define likely(x) [[likely]]
#endif // likely

#ifndef unlikely
#define unlikely(x) [[unlikely]]
#endif // unlikely

#ifndef CPP_VERSION
#define CPP_VERSION __cplusplus
#endif // CPP_VERSION

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
#define CPP_VERSION_20 202002L
#endif // CPP_VERSION_20

// only for 
#if CPP_VERSION >= CPP_VERSION_20 && !((defined(__clang__) || defined(__GNUC__) ) && (PLATFORM_UNIX))

#ifdef LIKELY
#undef LIKELY
#endif // LIKELY

#ifdef UNLIKELY
#undef UNLIKELY
#endif // UNLIKELY

#ifndef LIKELY
#define LIKELY(x) \
	( \
		([](bool Value) [[likely]] -> bool { return Value; })(x) \
	)
#endif // LIKELY

#ifndef UNLIKELY
#define UNLIKELY(x) \
	( \
		([](bool Value) [[unlikely]] -> bool { return Value; })(x) \
	)
#endif // UNLIKELY

#endif // CPP_VERSION >= CPP_VERSION_20 && !((defined(__clang__) || defined(__GNUC__) ) && (PLATFORM_UNIX))

#ifndef INLINE
#define INLINE inline
#endif // INLINE

#ifndef OPTIONAL_FORCEINLINE
#define OPTIONAL_FORCEINLINE INLINE
#endif // OPTIONAL_FORCEINLINE

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
#define NO_VTABLE [[no_vtable]]
#endif // NO_VTABLE

#ifndef NO_THROW
#define NO_THROW [[nothrow]]
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

#ifndef CONSTEXPR
#define CONSTEXPR constexpr
#endif // CONSTEXPR

#ifndef nameof
#define nameof(x) typeid(x).name()
#endif // nameof

#ifndef NAME_OF
#define NAME_OF(x) nameof(x)
#endif // NAME_OF

#ifndef FUNCTION_NAME

#if defined(__GNUC__) || defined(__clang__)
#define FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define FUNCTION_NAME __FUNCTION__
#endif // defined(__GNUC__) || defined(__clang__)

#endif // FUNCTION_NAME

#ifndef FUNCTION_SIGNATURE
#define FUNCTION_SIGNATURE __FUNCSIG__
#endif // FUNCTION_SIGNATURE

#ifndef ASSUME
#define ASSUME(x) [[assume(x)]]
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

#ifndef (__JETBRAINS_IDE__)

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

#ifndef DEFINE_ATTRIBUTE

#if CPP_VERSION >= CPP_VERSION_20

#elif CPP_VERSION >= CPP_VERSION_17 // CPP_VERSION >= CPP_VERSION_20

#else // CPP_VERSION >= CPP_VERSION_17

#endif // CPP_VERSION >= CPP_VERSION_20

#endif // DEFINE_ATTRIBUTE

/*	namespace
	{
// Only needed for the UE_REQUIRES macro to work, to allow for a trailing > token after the macro
template <bool B>
concept BoolIdentityConcept = B;
}

#define UE_REQUIRES(...) > requires (!!(__VA_ARGS__)) && UE::Core::Private::BoolIdentityConcept<true*/

#ifndef REQUIRES

#if CPP_VERSION >= CPP_VERSION_20

namespace UE::Core::Private
{
	// Only needed for the UE_REQUIRES macro to work, to allow for a trailing > token after the macro
	template <bool Value>
	concept TBoolIdentityConcept = Value;
}; // namespace UE::Core::Private

#define REQUIRES(...) \
	requires ((__VA_ARGS__) && UE::Core::Private::TBoolIdentityConcept<true>)

#else // CPP_VERSION >= CPP_VERSION_20

#define REQUIRES(...) ,std::enable_if_t<(__VA_ARGS__), bool> = true

#endif // CPP_VERSION >= CPP_VERSION_20

#endif // REQUIRES


