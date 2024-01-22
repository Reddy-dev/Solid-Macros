// Solstice Games © 2023. All Rights Reserved.

#ifndef SOLID_SCRIPT_STRUCT_H
#define SOLID_SCRIPT_STRUCT_H

#include "CoreMinimal.h"
#include "SolidMacros/Macros.h"

// Don't use this macro directly, use DEFINE_USTRUCT instead.
#define IMPLEMENT_STRUCT_OPS(Type, PathPackage) \
	inline static UScriptStruct::TAutoCppStructOps<Type> Type##_Ops(FTopLevelAssetPath(TEXT(PathPackage), TEXT(#Type))); \

// Don't use this macro directly, use DEFINE_USTRUCT instead.
#define IMPLEMENT_STATIC_STRUCT(Type) \
	FORCEINLINE NO_DISCARD static UScriptStruct* Type::StaticStruct() \
    { \
    	return Type##Struct; \
    }

// Don't use this macro directly, use DEFINE_USTRUCT instead.
#define IMPLEMENT_SCRIPT_STRUCT(Type, Flags, ParentType) \
	namespace \
	{ \
		FORCEINLINE static UScriptStruct* Initialize##Type##Struct() \
		{ \
			UScriptStruct::ICppStructOps* StructOps = new UScriptStruct::TCppStructOps<Type>(); \
			UScriptStruct* ScriptStruct = new UScriptStruct(FObjectInitializer(), nullptr, StructOps, Flags, sizeof(Type), alignof(Type)); \
			ScriptStruct->SetCppTypeInfoStatic(StructOps->GetCppTypeInfo()); \
			ScriptStruct->StaticLink(true); \
			return ScriptStruct; \
		} \
	}

#define GET_PARENT_STRUCT(Type) \
	{ \
		IF_NOT_EXISTS(Type) \
		{ \
			return nullptr; \
		} \
		else \
		{ \
			return ParentType::StaticStruct(); \
		} \
	}

// Creates a UScriptStruct object for types that dont have the USTRUCT() macro.
#define DEFINE_USTRUCT(ModuleName, Type, Flags, ParentType) \
	static_assert(!IsStaticStruct<Type>(), "Type: " #Type " is already a static struct!"); \
	IMPLEMENT_STRUCT_OPS(Type, "/Script/" ModuleName) \
	IMPLEMENT_SCRIPT_STRUCT(Type, Flags, ParentType) \
	INLINE static UScriptStruct* Type##Struct = Initialize##Type##Struct(); \
	IMPLEMENT_STATIC_STRUCT(Type)

#endif // SOLID_SCRIPT_STRUCT_H
