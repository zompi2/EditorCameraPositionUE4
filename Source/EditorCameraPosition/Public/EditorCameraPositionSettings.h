// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EditorCameraPositionTypes.h"
#include "EditorCameraPositionSettings.generated.h"

/**
 * Storing settings in DefaultEditor.ini file.
 */

UCLASS(config = Editor, defaultconfig)
class EDITORCAMERAPOSITION_API UEditorCameraPositionSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:

	static const UEditorCameraPositionSettings* Get();

	static bool GetIsCameraPositionToolBarEnabled();
	static void SetIsCameraPositionToolBarEnabled(bool bInIsVisible);

	static bool GetIsCameraRotationToolBarEnabled();
	static void SetIsCameraRotationToolBarEnabled(bool bInIsVisible);

	// UDeveloperSettings implementation
	FName GetContainerName() const override;
	FName GetCategoryName() const override;
	FName GetSectionName() const override;
	FText GetSectionText() const override;
	FText GetSectionDescription() const override;
	// UDeveloperSettings implementation

	UPROPERTY(config, EditAnywhere, Category = "Editor Camera Position")
	bool bEnableEditorCameraPosition = true;

	UPROPERTY(config, EditAnywhere, Category = "Editor Camera Position")
	bool bEnableEditorCameraRotation = true;

	UPROPERTY(config, EditAnywhere, Category = "Editor Camera Position")
	EEditorCameraPositionTruncType CameraPositionTrunc = EEditorCameraPositionTruncType::TwoDecimals;

	UPROPERTY(config, EditAnywhere, Category = "Editor Camera Position")
	EEditorCameraPositionTruncType CameraRotationTrunc = EEditorCameraPositionTruncType::TwoDecimals;

private:

	UPROPERTY(config)
	bool bIsCameraPositionToolBarEnabled = false;

	UPROPERTY(config)
	bool bIsCameraRotationToolBarEnabled = false;
};
