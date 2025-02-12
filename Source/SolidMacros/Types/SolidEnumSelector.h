// Elie Wiese-Namir © 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SolidEnumSelector.generated.h"

USTRUCT(BlueprintType)
struct SOLIDMACROS_API FSolidEnumSelector
{
	GENERATED_BODY()

public:
	FSolidEnumSelector() = default;

	FORCEINLINE FSolidEnumSelector(UEnum* InClass, int64 InValue)
		: Class(InClass), Value(InValue)
	{
	}
	
	UPROPERTY(DisplayName="Enum Class")
	TObjectPtr<UEnum> Class;

	UPROPERTY(DisplayName="Enum Value")
	int64 Value = 0;

	FText GetDisplayName() const;
	FString GetCultureInvariantDisplayName() const;
	
}; // struct FSolidEnumSelector
