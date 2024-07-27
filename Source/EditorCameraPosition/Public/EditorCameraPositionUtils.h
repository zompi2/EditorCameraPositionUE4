// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EditorCameraPositionUtils.generated.h"

UCLASS()
class EDITORCAMERAPOSITION_API UEditorCameraPositionUtils : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Editor Camera Position")
	static FVector GetEditorCameraPosition();

	UFUNCTION(BlueprintCallable, Category = "Editor Camera Position")
	static void SetEditorCameraPosition(const FVector& NewEditorCameraPosition);
};
