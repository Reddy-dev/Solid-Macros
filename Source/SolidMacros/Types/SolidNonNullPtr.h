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
template <typename ObjectType>
class TSolidNonNullPtr
{
	using FUnrealNonNullPtr = TNonNullPtr<ObjectType>;

	#ifndef PLATFORM_COMPILER_IWYU
	// TObjectPtr should only be used on types T that are EITHER:
	// - incomplete (ie: forward declared and we have not seen their definition yet)
	// - complete and derived from UObject
	// This means that the following are invalid and must fail to compile:
	// - TObjectPtr<int>
	// - TObjectPtr<IInterface>
	static_assert(std::disjunction<std::bool_constant<sizeof(ObjectPtr_Private::ResolveTypeIsComplete<ObjectType>(1)) != 2>,
		std::is_base_of<UObject, ObjectType>>::value, "TObjectPtr<T> can only be used with types derived from UObject");
	#endif
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
		solid_checkf(IsValid(InObject),
			TEXT("Tried to initialize TSolidNonNullPtr with a null pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TObjectPtr<ObjectType> InObject)
		: Object(InObject.Get())
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to initialize TSolidNonNullPtr with an invalid pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TWeakObjectPtr<ObjectType> InObject)
		: Object(InObject.Get())
	{
		solid_checkf(InObject.IsValid(),
			TEXT("Tried to initialize TSolidNonNullPtr with an invalid pointer!"));
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
	template <typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)>
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
		solid_checkf(IsValid(InObject),
			TEXT("Tried to assign a null pointer to a TSolidNonNullPtr!"));
		Object = InObject;
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TObjectPtr<ObjectType> InObject)
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject.Get();
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TWeakObjectPtr<ObjectType> InObject)
	{
		solid_checkf(InObject.IsValid(),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject.Get();
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
	
	FORCEINLINE bool operator!=(const TSolidNonNullPtr& Other) const
	{
		return Object != Other.Object;
	}

	/**
	 * Comparison with a raw pointer
	 */
	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))>
	FORCEINLINE bool operator==(OtherObjectType* Other) const
	{
		return Object == Other;
	}
	
	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))>
	FORCEINLINE friend bool operator==(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs == Rhs.Object;
	}
	
	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))>
	FORCEINLINE bool operator!=(OtherObjectType* Other) const
	{
		return Object != Other;
	}
	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))>
	FORCEINLINE friend bool operator!=(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs != Rhs.Object;
	}

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE operator ObjectType*() const
	{
		solid_checkf(IsValid((UObject*)Object), TEXT("Tried to access null pointer!"));
		return Object;
	}

	FORCEINLINE operator TObjectPtr<ObjectType>() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return TObjectPtr<ObjectType>(Object);
	}

	FORCEINLINE operator TWeakObjectPtr<ObjectType>() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return TWeakObjectPtr<ObjectType>(Object);
	}

	FORCEINLINE operator FUnrealNonNullPtr() const
	{
		solid_checkf(IsValid(Object), TEXT("Tried to access null pointer!"));
		return FUnrealNonNullPtr(Object);
	}
	
	/**
	 * Converts to a gsl::not_null
	 */
	FORCEINLINE operator gsl::not_null<ObjectType*>() const
	{
		solid_checkf(IsValid(Object), TEXT("Tried to access null pointer!"));
		return gsl::make_not_null<ObjectType*>(Object);
	}

	/**
	 * Returns the internal pointer
	 */
	NO_DISCARD FORCEINLINE ObjectType* Get() const
	{
		solid_checkf(IsValid(Object), TEXT("Tried to access null pointer!"));
		return Object;
	}

	/**
	 * Dereference operator returns a reference to the object this pointer points to
	 */
	FORCEINLINE ObjectType& operator*() const
	{
		solid_checkf(IsValid(Object), TEXT("Tried to access null pointer!"));
		return *Object;
	}

	/**
	 * Arrow operator returns a pointer to this pointer's object
	 */
	FORCEINLINE ObjectType* operator->() const
	{
		solid_checkf(IsValid(Object), TEXT("Tried to access null pointer!"));
		return Object;
	}

	/*
	 * WARNING: Hack that can be used under extraordinary circumstances. Pointers here 
	 * should always be valid but might be in the EDefaultConstructNonNullPtr state 
	 * during initialization.
	 */
	NO_DISCARD FORCEINLINE bool IsInitialized() const
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

template <typename ObjectType>
class TSolidNonNullPtr<TObjectPtr<ObjectType>>
{
	using FUnrealNonNullPtr = TNonNullPtr<TObjectPtr<ObjectType>>;
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
		static_assert(sizeof(ObjectType) == 0, "Tried to initialize TSolidNonNullPtr with a null pointer!");
	}

	FORCEINLINE TSolidNonNullPtr(ObjectType* InObject)
		: Object(InObject)
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to initialize TSolidNonNullPtr with a null pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TObjectPtr<ObjectType> InObject)
		: Object(InObject.Get())
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to initialize TSolidNonNullPtr with an invalid pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TWeakObjectPtr<ObjectType> InObject)
		: Object(InObject.Get())
	{
		solid_checkf(InObject.IsValid(),
			TEXT("Tried to initialize TSolidNonNullPtr with an invalid pointer!"));
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
	template <typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)>
	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<OtherObjectType>& Other)
		: Object(Other.Get())
	{
	}

	template <typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, TObjectPtr<ObjectType>>) >
	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<TObjectPtr<OtherObjectType>>& Other)
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
		solid_checkf(IsValid(InObject),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject;
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TObjectPtr<ObjectType> InObject)
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject.Get();
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TWeakObjectPtr<ObjectType> InObject)
	{
		solid_checkf(InObject.IsValid(),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject.Get();
		return *this;
	}

	/**
	 * Assignment operator taking another TSolidNonNullPtr
	 */
	template <
		typename OtherObjectType
		UE_REQUIRES(std::is_convertible_v<OtherObjectType*, ObjectType*>)>
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

	FORCEINLINE bool operator!=(const TSolidNonNullPtr& Other) const
	{
		return Object != Other.Object;
	}

	/**
	 * Comparison with a raw pointer
	 */
	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))>
	FORCEINLINE bool operator==(OtherObjectType* Other) const
	{
		return Object == Other;
	}

	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))>
	FORCEINLINE friend bool operator==(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs == Rhs.Object;
	}

	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))>
	FORCEINLINE bool operator!=(OtherObjectType* Other) const
	{
		return Object != Other;
	}

	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))>
	FORCEINLINE friend bool operator!=(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs != Rhs.Object;
	}

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE operator ObjectType*() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return Object;
	}

	FORCEINLINE operator TObjectPtr<ObjectType>() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return TObjectPtr<ObjectType>(Object);
	}

	FORCEINLINE operator TWeakObjectPtr<ObjectType>() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return TWeakObjectPtr<ObjectType>(Object);
	}

	FORCEINLINE operator FUnrealNonNullPtr() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return FUnrealNonNullPtr(Object);
	}

	/**
	 * Converts to a gsl::not_null
	 */
	FORCEINLINE operator gsl::not_null<ObjectType*>() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return gsl::make_not_null<ObjectType*>(Object);
	}
	
	/**
	 * Returns the internal pointer
	 */
	NO_DISCARD FORCEINLINE ObjectType* Get() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return Object;
	}
	
	/**
	 * Dereference operator returns a reference to the object this pointer points to
	 */
	FORCEINLINE ObjectType& operator*() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return *Object;
	}
	
	/**
	 * Arrow operator returns a pointer to this pointer's object
	 */
	FORCEINLINE ObjectType* operator->() const
	{
		solid_checkf(IsValid(Object),
			TEXT("Tried to access invalid pointer!"));
		return Object;
	}

	/*
	 * WARNING: Hack that can be used under extraordinary circumstances. Pointers here 
	 * should always be valid but might be in the EDefaultConstructNonNullPtr state 
	 * during initialization.
	 */
	NO_DISCARD FORCEINLINE bool IsInitialized() const
	{
		return Object != nullptr;
	}

	/**
	 * Use IsInitialized if needed
	 */
	explicit operator bool() const = delete;

	////////////////////////////////////////////////////
	/// Start - intrusive TOptional<TSolidNonNullPtr> state //
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
	TObjectPtr<ObjectType> Object;
};

template <typename ObjectType>
class TSolidNonNullPtr<TWeakObjectPtr<ObjectType>>
{
	using FUnrealNonNullPtr = TNonNullPtr<TWeakObjectPtr<ObjectType>>;
	
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
		static_assert(sizeof(ObjectType) == 0, "Tried to initialize TSolidNonNullPtr with a null pointer!");
	}

	FORCEINLINE TSolidNonNullPtr(ObjectType* InObject)
		: Object(InObject)
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to initialize TSolidNonNullPtr with a null pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TObjectPtr<ObjectType> InObject)
		: Object(InObject.Get())
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to initialize TSolidNonNullPtr with an invalid pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TWeakObjectPtr<ObjectType> InObject)
		: Object(InObject.Get())
	{
		solid_checkf(InObject.IsValid(),
			TEXT("Tried to initialize TSolidNonNullPtr with an invalid pointer!"));
	}

	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<TWeakObjectPtr<ObjectType>>& Other)
		: Object(Other)
	{
	}

	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<TObjectPtr<ObjectType>>& Other)
		: Object(Other.Get())
	{
	}

	FORCEINLINE TSolidNonNullPtr(const TSolidNonNullPtr<ObjectType>& Other)
		: Object(Other.Get())
	{
	}

	template <typename OtherType, typename = std::enable_if_t<std::is_convertible<OtherType, ObjectType*>::value>>
	FORCEINLINE TSolidNonNullPtr(const gsl::not_null<OtherType>& Other)
		: Object(Other.get())
	{
	}

	FORCEINLINE TSolidNonNullPtr& operator=(TYPE_OF_NULLPTR)
	{
		static_assert(sizeof(ObjectType) == 0, "Tried to assign a null pointer to a TSolidNonNullPtr!");
		
		return *this;
	}
	
	FORCEINLINE TSolidNonNullPtr& operator=(ObjectType* InObject)
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject;
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TObjectPtr<ObjectType> InObject)
	{
		solid_checkf(IsValid(InObject),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject.Get();
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TWeakObjectPtr<ObjectType> InObject)
	{
		solid_checkf(InObject.IsValid(),
			TEXT("Tried to assign an invalid pointer to a TSolidNonNullPtr!"));
		Object = InObject.Get();
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TSolidNonNullPtr<TWeakObjectPtr<ObjectType>>& Other)
	{
		Object = Other.Object;
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TSolidNonNullPtr<TObjectPtr<ObjectType>>& Other)
	{
		Object = Other.Get();
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const TSolidNonNullPtr<ObjectType>& Other)
	{
		Object = Other.Get();
		return *this;
	}

	FORCEINLINE TSolidNonNullPtr& operator=(const gsl::not_null<ObjectType*>& Other)
	{
		Object = Other.get();
		return *this;
	}

	/**
	 * Comparison, will also handle default constructed state
	 */
	FORCEINLINE bool operator==(const TSolidNonNullPtr& Other) const
	{
		return Object == Other.Object;
	}

	FORCEINLINE bool operator!=(const TSolidNonNullPtr& Other) const
	{
		return Object != Other.Object;
	}

	/**
	 * Comparison with a raw pointer
	 */
	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))>
	FORCEINLINE bool operator==(OtherObjectType* Other) const
	{
		return Object == Other;
	}

	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))>
	FORCEINLINE friend bool operator==(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs == Rhs.Object;
	}

	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<ObjectType*>() == std::declval<OtherObjectType*>()))>
	FORCEINLINE bool operator!=(OtherObjectType* Other) const
	{
		return Object != Other;
	}

	template <typename OtherObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(std::declval<OtherObjectType*>() == std::declval<ObjectType*>()))>
	FORCEINLINE friend bool operator!=(OtherObjectType* Lhs, const TSolidNonNullPtr& Rhs)
	{
		return Lhs != Rhs.Object;
	}

	/**
	 * Returns the internal pointer
	 */
	FORCEINLINE operator ObjectType*() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return Object.Get();
	}

	FORCEINLINE operator TObjectPtr<ObjectType>() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return TObjectPtr<ObjectType>(Object.Get());
	}

	FORCEINLINE operator TWeakObjectPtr<ObjectType>() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return TWeakObjectPtr<ObjectType>(Object);
	}

	FORCEINLINE operator FUnrealNonNullPtr() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return FUnrealNonNullPtr(Object.Get);
	}

	FORCEINLINE operator gsl::not_null<ObjectType*>() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		
		return gsl::make_not_null<ObjectType*>(Object.Get());
	}

	FORCEINLINE ObjectType* Get() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return Object.Get();
	}
	
	/**
	 * Dereference operator returns a reference to the object this pointer points to
	 */
	FORCEINLINE ObjectType& operator*() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return *Object;
	}

	/**
	 * Arrow operator returns a pointer to this pointer's object
	 */
	FORCEINLINE ObjectType* operator->() const
	{
		solid_checkf(Object.IsValid(),
			TEXT("Tried to access invalid pointer!"));
		return Object.Get();
	}

	/*
	 * WARNING: Hack that can be used under extraordinary circumstances. Pointers here 
	 * should always be valid but might be in the EDefaultConstructNonNullPtr state 
	 * during initialization.
	 */
	NO_DISCARD FORCEINLINE bool IsInitialized() const
	{
		return Object.IsValid();
	}

	explicit operator bool() const = delete;
	
	////////////////////////////////////////////////////
	/// Start - intrusive TOptional<TSolidNonNullPtr> state //
	////////////////////////////////////////////////////
	constexpr static bool bHasIntrusiveUnsetOptionalState = true;
	using IntrusiveUnsetOptionalStateType = TSolidNonNullPtr;

	FORCEINLINE explicit TSolidNonNullPtr(FIntrusiveUnsetOptionalState)
		: Object(nullptr)
	{
	}
	FORCEINLINE bool operator==(FIntrusiveUnsetOptionalState) const
	{
		return !Object.IsValid();
	}
	//////////////////////////////////////////////////
	// End - intrusive TOptional<TSolidNonNullPtr> state //
	//////////////////////////////////////////////////
	

private:
	TWeakObjectPtr<ObjectType> Object;
};

/** Convenience function to turn an `TOptional<TSolidNonNullPtr<T>>` back into a nullable T* */
template<typename ObjectType>
inline ObjectType* GetRawPointerOrNull(const TOptional<TSolidNonNullPtr<ObjectType>>& Optional)
{
	return Optional.IsSet() ? Optional->Get() : nullptr;
}

#if UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_4
#include "Templates/EnableIf.h"
#include "Templates/PointerIsConvertibleFromTo.h"
#endif
