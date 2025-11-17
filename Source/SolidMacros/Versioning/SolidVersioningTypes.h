// Elie Wiese-Namir © 2025. All Rights Reserved.

#pragma once


#include <functional>

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "SolidMacros/Macros.h"
#include "Types/SolidNotNull.h"
#include "Standard/robin_hood.h"

#define UE_API SOLIDMACROS_API

#define START_SOLID_ASSET_VERSION(Name) \
	struct F##Name##CustomVersion \
	{ \
		static const FGuid GUID; \
		\
		enum Type \
		{ \
			/** Before any version changes were made */ \
			BeforeCustomVersionWasAdded = 0,

#define DEFINE_SOLID_ASSET_VERSION(VersionName) \
			VersionName,

#define END_SOLID_ASSET_VERSION() \
			\
			/* -----<new versions can be added above this line>----- */ \
			VersionPlusOne, \
			LatestVersion = VersionPlusOne - 1 \
		}; \
	};

#define GET_SOLID_ASSET_VERSION_VALUE(ObjectType, VersionName) \
	F##ObjectType##CustomVersion::VersionName

#define IMPLEMENT_SOLID_ASSET_VERSION(Name, GuidA, GuidB, GuidC, GuidD, FriendlyName) \
	const FGuid F##Name##CustomVersion::GUID(GuidA, GuidB, GuidC, GuidD);             \
	static FCustomVersionRegistration GRegister_##Name##CustomVersion(                 \
		F##Name##CustomVersion::GUID,                                                 \
		F##Name##CustomVersion::LatestVersion,                                        \
		TEXT(FriendlyName)                                                            \
	)

#define DECLARE_SOLID_VERSION_TYPE_TRAITS(Name) \
	template<> \
	struct TStructOpsTypeTraits<Name> : public TStructOpsTypeTraitsBase2<Name> \
	{ \
		enum \
		{ \
			WithIdentical = true, \
			WithStructuredSerializer = true, \
		}; \
	};

// @TODO: compile this out in non-editor builds?

namespace Solid
{
	class UE_API FAssetMigrationRegistry
	{
	public:
		using FStepFunctionType = std::function<void(const TSolidNotNull<UObject*>)>;

		struct FAssetMigrationStep
		{
			int32 ToVersion;
			FStepFunctionType StepFunction;
		}; // struct FAssetMigrationStep

		static FAssetMigrationRegistry& Get()
		{
			static FAssetMigrationRegistry GAssetMigrationRegistry;
			
			return GAssetMigrationRegistry;
		}

		void Register(const TSolidNotNull<const UClass*> ForClass, const int32 ToVersion, FStepFunctionType Func)
		{
			TArray<FAssetMigrationStep>& Array = Steps.FindOrAdd(ForClass);
			Array.Add({ .ToVersion = ToVersion, .StepFunction = MoveTemp(Func) });
			
			Array.Sort([](const FAssetMigrationStep& Left, const FAssetMigrationStep& Right)
			{
				return Left.ToVersion < Right.ToVersion;
			});
		}

		bool Migrate(const TSolidNotNull<UObject*> Object, const int32 FromVersion, const int32 ToVersion) const  // NOLINT(modernize-use-nodiscard)
		{
			bool bChanged = false;
			
			if (const TArray<FAssetMigrationStep>* Array = Steps.Find(Object->GetClass()))
			{
				for (const FAssetMigrationStep& Step : *Array)
				{
					if (Step.ToVersion > FromVersion && Step.ToVersion <= ToVersion)
					{
						Step.StepFunction(Object);
						bChanged = true;
					}
				}
			}
			
			return bChanged;
		}

	private:
		TMap<const UClass*, TArray<FAssetMigrationStep>> Steps;
		
	}; // class FAssetMigrationRegistry

	NO_DISCARD static bool FPropertyMatchesCDO(const TSolidNotNull<const UObject*> Object, const TSolidNotNull<const FProperty*> Property);
	NO_DISCARD static bool PropertyMatchesCDO(const TSolidNotNull<const UObject*> Object, const FName PropertyName);
	
} // namespace Solid

#if WITH_EDITOR

#define REGISTER_ASSET_MIGRATION_STEP(ClassType, ToVersion, FunctionBody) \
	namespace \
	{ \
		struct FAutoRegister##ClassType##ToVersion \
		{ \
			FAutoRegister##ClassType##ToVersion() \
			{ \
				Solid::FAssetMigrationRegistry::Get().Register(ClassType::StaticClass(), GET_SOLID_ASSET_VERSION_VALUE(ClassType, ToVersion), \
					[](const TSolidNotNull<UObject*> InAssetObject) \
					{ \
						const TSolidNotNull<ClassType*> Self = CastChecked<ClassType>(InAssetObject); \
						const TSolidNotNull<ClassType*> Archetype = CastChecked<ClassType>(Self->GetArchetype()); \
						 \
						FunctionBody \
					}); \
			} \
		}; \
		static FAutoRegister##ClassType##ToVersion AutoRegister##ClassType##ToVersionInstance; \
	}

#ifndef IMPLEMENT_ASSET_MIGRATION_POST_LOAD

#define IMPLEMENT_ASSET_MIGRATION_POST_LOAD(ObjectType) \
		do \
		{ \
			if (HasAnyFlags(RF_ClassDefaultObject)) \
			{ \
				break; \
			} \
			 \
			const int32 FromVersion = GetLinkerCustomVersion(F##ObjectType##CustomVersion::GUID); \
			const int32 ToVersion = F##ObjectType##CustomVersion::LatestVersion; \
			 \
			if (Solid::FAssetMigrationRegistry::Get().Migrate(TSolidNotNull<UObject*>(this), FromVersion, ToVersion)) \
			{ \
				MarkPackageDirty(); \
			} \
		} while (0)
		
#endif // IMPLEMENT_ASSET_MIGRATION_POST_LOAD

#else // !WITH_EDITOR

#define REGISTER_ASSET_MIGRATION_STEP(ClassType, ToVersion, FunctionBody) UE_EMPTY
#define IMPLEMENT_ASSET_MIGRATION_POST_LOAD(ObjectType) UE_EMPTY

#endif // WITH_EDITOR

#ifndef INTERNAL_SOLID_VERSION_MAJOR_SHIFT
#define INTERNAL_SOLID_VERSION_MAJOR_SHIFT 48
#endif // INTERNAL_SOLID_VERSION_MAJOR_SHIFT

#ifndef INTERNAL_SOLID_VERSION_MINOR_SHIFT
#define INTERNAL_SOLID_VERSION_MINOR_SHIFT 32
#endif // INTERNAL_SOLID_VERSION_MINOR_SHIFT

#ifndef INTERNAL_SOLID_VERSION_PATCH_SHIFT
#define INTERNAL_SOLID_VERSION_PATCH_SHIFT 16
#endif // INTERNAL_SOLID_VERSION_PATCH_SHIFT

#ifndef INTERNAL_SOLID_VERSION_BUILD_SHIFT
#define INTERNAL_SOLID_VERSION_BUILD_SHIFT 0
#endif // INTERNAL_SOLID_VERSION_BUILD_SHIFT

#ifndef SOLID_PACK_VERSION
#define SOLID_PACK_VERSION(Major, Minor, Patch, Build) \
	(((Major) << INTERNAL_SOLID_VERSION_MAJOR_SHIFT) | \
	 ((Minor) << INTERNAL_SOLID_VERSION_MINOR_SHIFT) | \
	 ((Patch) << INTERNAL_SOLID_VERSION_PATCH_SHIFT) | \
	 ((Build) << INTERNAL_SOLID_VERSION_BUILD_SHIFT))
#endif // SOLID_PACK_VERSION

#ifndef SOLID_UNPACK_VERSION
#define SOLID_UNPACK_VERSION(Major, Minor, Patch, Build, PackedVersion) \
	do { \
		Major = (uint16)(((PackedVersion) >> INTERNAL_SOLID_VERSION_MAJOR_SHIFT) & 0xFFFF); \
		Minor = (uint16)(((PackedVersion) >> INTERNAL_SOLID_VERSION_MINOR_SHIFT) & 0xFFFF); \
		Patch = (uint16)(((PackedVersion) >> INTERNAL_SOLID_VERSION_PATCH_SHIFT) & 0xFFFF); \
		Build = (uint16)(((PackedVersion) >> INTERNAL_SOLID_VERSION_BUILD_SHIFT) & 0xFFFF); \
	} while (0) // we want to force the semicolon at the end of the macro usage
#endif // SOLID_UNPACK_VERSION

#ifndef SOLID_GET_VERSION_MAJOR
#define SOLID_GET_VERSION_MAJOR(PackedVersion) \
	((((PackedVersion) >> INTERNAL_SOLID_VERSION_MAJOR_SHIFT) & 0xFFFF))
#endif // SOLID_GET_VERSION_MAJOR

#ifndef SOLID_GET_VERSION_MINOR
#define SOLID_GET_VERSION_MINOR(PackedVersion) \
	((((PackedVersion) >> INTERNAL_SOLID_VERSION_MINOR_SHIFT) & 0xFFFF))
#endif // SOLID_GET_VERSION_MINOR

#ifndef SOLID_GET_VERSION_PATCH
#define SOLID_GET_VERSION_PATCH(PackedVersion) \
	((((PackedVersion) >> INTERNAL_SOLID_VERSION_PATCH_SHIFT) & 0xFFFF))
#endif // SOLID_GET_VERSION_PATCH

#ifndef SOLID_GET_VERSION_BUILD
#define SOLID_GET_VERSION_BUILD(PackedVersion) \
	((uint16)(((PackedVersion) >> INTERNAL_SOLID_VERSION_BUILD_SHIFT) & 0xFFFF))
#endif // SOLID_GET_VERSION_BUILD

// usable in static_assert and #if
#ifndef SOLID_REQUIRE_VERSION_MIN_PACKED
#define SOLID_REQUIRE_VERSION_MIN_PACKED(PackedCurrentVersion, PackedExpectedVersion) \
	SOLID_REQUIRE_VERSION_MIN( \
		PackedCurrentVersion, \
		SOLID_GET_VERSION_MAJOR(PackedExpectedVersion), \
		SOLID_GET_VERSION_MINOR(PackedExpectedVersion), \
		SOLID_GET_VERSION_PATCH(PackedExpectedVersion), \
		SOLID_GET_VERSION_BUILD(PackedExpectedVersion) \
	)
#endif // SOLID_REQUIRE_VERSION_MIN_PACKED

// usable in static_assert and #if
#ifndef SOLID_REQUIRE_VERSION_MIN
#define SOLID_REQUIRE_VERSION_MIN(PackedCurrentVersion, ReqMajor, ReqMinor, ReqPatch, ReqBuild) \
	( \
		(SOLID_GET_VERSION_MAJOR(PackedCurrentVersion) >  (ReqMajor)) || \
		(SOLID_GET_VERSION_MAJOR(PackedCurrentVersion) == (ReqMajor) && \
		(SOLID_GET_VERSION_MINOR(PackedCurrentVersion) >  (ReqMinor) || \
		(SOLID_GET_VERSION_MINOR(PackedCurrentVersion) == (ReqMinor) && \
		(SOLID_GET_VERSION_PATCH(PackedCurrentVersion) >  (ReqPatch) || \
		(SOLID_GET_VERSION_PATCH(PackedCurrentVersion) == (ReqPatch) && \
		(SOLID_GET_VERSION_BUILD(PackedCurrentVersion) >= (ReqBuild))))))) \
	)
#endif // SOLID_REQUIRE_VERSION_MIN

#ifndef SOLID_REQUIRE_VERSION_MAX
#define SOLID_REQUIRE_VERSION_MAX(PackedCurrentVersion, MaxMajor, MaxMinor, MaxPatch, MaxBuild) \
	( \
		(SOLID_GET_VERSION_MAJOR(PackedCurrentVersion) <  (MaxMajor)) || \
		(SOLID_GET_VERSION_MAJOR(PackedCurrentVersion) == (MaxMajor) && \
		(SOLID_GET_VERSION_MINOR(PackedCurrentVersion) <  (MaxMinor) || \
		(SOLID_GET_VERSION_MINOR(PackedCurrentVersion) == (MaxMinor) && \
		(SOLID_GET_VERSION_PATCH(PackedCurrentVersion) <  (MaxPatch) || \
		(SOLID_GET_VERSION_PATCH(PackedCurrentVersion) == (MaxPatch) && \
		(SOLID_GET_VERSION_BUILD(PackedCurrentVersion) <= (MaxBuild))))))) \
	)
#endif // SOLID_REQUIRE_VERSION_MAX

// usable in static_assert and #if
#ifndef SOLID_REQUIRE_VERSION_MAX_PACKED
#define SOLID_REQUIRE_VERSION_MAX_PACKED(PackedCurrentVersion, PackedExpectedVersion) \
	SOLID_REQUIRE_VERSION_MAX( \
		PackedCurrentVersion, \
		SOLID_GET_VERSION_MAJOR(PackedExpectedVersion), \
		SOLID_GET_VERSION_MINOR(PackedExpectedVersion), \
		SOLID_GET_VERSION_PATCH(PackedExpectedVersion), \
		SOLID_GET_VERSION_BUILD(PackedExpectedVersion) \
	)
#endif // SOLID_REQUIRE_VERSION_MAX_PACKED


#undef UE_API // SOLIDVERSIONING_API