// Elie Wiese-Namir © 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

#include <gsl/pointers>
#include <type_traits>

class FArchive;

/**
 * TSolidNonNullPtr is a non-nullable, non-owning, raw/naked/unsafe pointer.
 * Copied from: @TNonNullPtr<ObjectType>
 */
template<typename ObjectType>
class TSolidNonNullPtr
{
	using FUnrealNonNullPtr = TNonNullPtr<ObjectType>;
public:

	/**
	 * Hack that can be used under extraordinary circumstances
	 */
	FORCEINLINE TSolidNonNullPtr(EDefaultConstructNonNullPtr)
		: Object(nullptr)
	{	
	}

	/**
	 * nullptr constructor - not allowed.
	 */
	FORCEINLINE TSolidNonNullPtr(TYPE_OF_NULLPTR)
	{
		// Essentially static_assert(false), but this way prevents GCC/Clang from crying wolf by merely inspecting the function body
		static_assert(sizeof(ObjectType) == 0, "Tried to initialize TSolidNonNullPtr with a null pointer!");
	}

	/**
	 * Constructs a non-null pointer from the provided pointer. Must not be nullptr.
	 */
	FORCEINLINE TSolidNonNullPtr(ObjectType* InObject)
		: Object(InObject)
	{
		solid_checkf(InObject, TEXT("Tried to initialize TSolidNonNullPtr with a null pointer!"));
	}

	/**
	 * Converts from gsl::not_null
	 */
	template <typename OtherType, typename = std::enable_if_t<std::is_convertible<OtherType, ObjectType*>::value>>
	FORCEINLINE TSolidNonNullPtr(const gsl::not_null<OtherType>& Other)
		: Object(Other.get())
	{
	}

	/**
	 * Constructs a non-null pointer from another non-null pointer
	 */
	template <
		typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)
	>
	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<OtherObjectType>& Other)
		: Object(Other.Get())
	{
	}
	/**
	 * Assignment operator taking a nullptr - not allowed.
	 */
	FORCEINLINE TSolidNonNullPtr& operator=(TYPE_OF_NULLPTR)
	{
		// Essentially static_assert(false), but this way prevents GCC/Clang from crying wolf by merely inspecting the function body
		static_assert(sizeof(ObjectType) == 0, "Tried to assign a null pointer to a TSolidNonNullPtr!");
		return *this;
	}

	/**
	 * Assignment operator taking a pointer
	 */
	FORCEINLINE TSolidNonNullPtr& operator=(ObjectType* InObject)
	{
		solid_checkf(InObject, TEXT("Tried to assign a null pointer to a TSolidNonNullPtr!"));
		Object = InObject;
		return *this;
	}

	/**
	 * Assignment operator taking another TSolidNonNullPtr
	 */
	template <
		typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)
	>
	FORCEINLINE TSolidNonNullPtr& operator=(const TSolidNonNullPtr<OtherObjectType>& Other)
	{
		Object = Other.Get();
		return *this;
	}

	/**
	 * Assignment operator taking a gsl::not_null
	 */
	template <typename OtherType, typename = std::enable_if_t<std::is_convertible<OtherType, ObjectType*>::value>>
	FORCEINLINE TSolidNonNullPtr& operator=(const gsl::not_null<OtherType>& Other)
	{
		Object = Other.Get();
		return *this;
	}

	/**
	 * Comparison, will also handle default constructed state
	 */
	FORCEINLINE bool operator==(const TSolidNonNullPtr& Other) const
	{
		return Object == Other.Object;
	}
#if !PLATFORM_COMPILER_HAS_GENERATED_COMPARISON_OPERATORS
	FORCEINLINE bool operator!=(const TSolidNonNullPtr& Other) const
	{
		return Object != Other.Object;
	}
#endif

	/**
	 * Comparison with a raw pointer
	 */
	template <
		typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))
	>
	FORCEINLINE bool operator==(OtherObjectType* Other) const
	{
		return Object == Other;
	}
	template <
		typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))
	>
	FORCEINLINE friend bool operator==(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs == Rhs.Object;
	}
#if !PLATFORM_COMPILER_HAS_GENERATED_COMPARISON_OPERATORS
	template <
		typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))
	>
	FORCEINLINE bool operator!=(OtherObjectType* Other) const
	{
		return Object != Other;
	}
	template <
		typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))
	>
	FORCEINLINE friend bool operator!=(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs != Rhs.Object;
	}
#endif

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE operator ObjectType*() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return Object;
	}

	FORCEINLINE operator FUnrealNonNullPtr() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return FUnrealNonNullPtr(Object);
	}
	
	/**
	 * Converts to a gsl::not_null
	 */
	FORCEINLINE operator gsl::not_null<ObjectType*>() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return gsl::make_not_null<ObjectType*>(Object);
	}

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE ObjectType* Get() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return Object;
	}

	/**
	 * Dereference operator returns a reference to the object this pointer points to
	 */
	FORCEINLINE ObjectType& operator*() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return *Object;
	}

	/**
	 * Arrow operator returns a pointer to this pointer's object
	 */
	FORCEINLINE ObjectType* operator->() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return Object;
	}

	/*
	 * WARNING: Hack that can be used under extraordinary circumstances. Pointers here 
	 * should always be valid but might be in the EDefaultConstructNonNullPtr state 
	 * during initialization.
	 */
	FORCEINLINE bool IsInitialized() const
	{
		return Object != nullptr;
	}
	
	/**
	 * Use IsInitialized if needed
	 */
	explicit operator bool() const = delete;

	////////////////////////////////////////////////////
	// Start - intrusive TOptional<TSolidNonNullPtr> state //
	////////////////////////////////////////////////////
	constexpr static bool bHasIntrusiveUnsetOptionalState = true;
	using IntrusiveUnsetOptionalStateType = TSolidNonNullPtr;
	FORCEINLINE explicit TSolidNonNullPtr(FIntrusiveUnsetOptionalState)
		: Object(nullptr)
	{
	}
	FORCEINLINE bool operator==(FIntrusiveUnsetOptionalState) const
	{
		return Object == nullptr;
	}
	//////////////////////////////////////////////////
	// End - intrusive TOptional<TSolidNonNullPtr> state //
	//////////////////////////////////////////////////

private:

	/** The object we're holding a reference to. */
	ObjectType* Object;
};

/** Convenience function to turn an `TOptional<TSolidNonNullPtr<T>>` back into a nullable T* */
template<typename ObjectType>
inline ObjectType* GetRawPointerOrNull(const TOptional<TSolidNonNullPtr<ObjectType>>& Optional)
{
	return Optional.IsSet() ? Optional->Get() : nullptr;
}

template<typename ObjectType>
class TSolidNonNullPtr<TObjectPtr<ObjectType>>
{
public:
	
	FORCEINLINE TSolidNonNullPtr(EDefaultConstructNonNullPtr)
		: Object(nullptr)
	{	
	}	

	/**
	 * nullptr constructor - not allowed.
	 */
	FORCEINLINE TSolidNonNullPtr(TYPE_OF_NULLPTR)
	{
		// Essentially static_assert(false), but this way prevents GCC/Clang from crying wolf by merely inspecting the function body
		static_assert(sizeof(ObjectType) == 0, "Tried to initialize TSolidNonNullPtr with a null pointer!");
	}

	/**
	 * Constructs a non-null pointer from the provided pointer. Must not be nullptr.
	 */
	FORCEINLINE TSolidNonNullPtr(TObjectPtr<ObjectType> InObject)
		: Object(InObject)
	{
		solid_checkf(InObject, TEXT("Tried to initialize TSolidNonNullPtr with a null pointer!"));
	}

	/**
	 * Constructs a non-null pointer from another non-null pointer
	 */
	template <
		typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)
	>
	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<OtherObjectType>& Other)
		: Object(Other.Object)
	{
	}

	/**
	 * Assignment operator taking a nullptr - not allowed.
	 */
	FORCEINLINE TSolidNonNullPtr& operator=(TYPE_OF_NULLPTR)
	{
		// Essentially static_assert(false), but this way prevents GCC/Clang from crying wolf by merely inspecting the function body
		static_assert(sizeof(ObjectType) == 0, "Tried to assign a null pointer to a TSolidNonNullPtr!");
		return *this;
	}

	/**
	 * Assignment operator taking a pointer
	 */
	FORCEINLINE TSolidNonNullPtr& operator=(ObjectType* InObject)
	{
		solid_checkf(InObject, TEXT("Tried to assign a null pointer to a TSolidNonNullPtr!"));
		Object = InObject;
		return *this;
	}

	/**
	 * Assignment operator taking another TSolidNonNullPtr
	 */
	template <
		typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)
	>
	FORCEINLINE TSolidNonNullPtr& operator=(const TSolidNonNullPtr<OtherObjectType>& Other)
	{
		Object = Other.Object;
		return *this;
	}

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE operator ObjectType*() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return Object;
	}

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE ObjectType* Get() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return Object;
	}

	/**
	 * Dereference operator returns a reference to the object this pointer points to
	 */
	FORCEINLINE ObjectType& operator*() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return *Object;
	}

	/**
	 * Arrow operator returns a pointer to this pointer's object
	 */
	FORCEINLINE ObjectType* operator->() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));
		return Object;
	}

	FORCEINLINE const TObjectPtr<ObjectType>& GetRef() const
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));		
		return Object;
	}
	
	FORCEINLINE TObjectPtr<ObjectType>& GetRef() 
	{
		solid_checkf(Object, TEXT("Tried to access null pointer!"));		
		return Object;
	}

	FORCEINLINE bool IsInitialized() const
	{
		return Object != nullptr;
	}

	/**
	 * Use IsInitialized if needed
	 */
	explicit operator bool() const = delete;

private:

	/** The object we're holding a reference to. */
	TObjectPtr<ObjectType> Object;
};

#if UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_4
#include "Templates/EnableIf.h"
#include "Templates/PointerIsConvertibleFromTo.h"
#endif
