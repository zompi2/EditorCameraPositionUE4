// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorCameraPositionSettings.generated.h"

/**
 * Storing settings in DefaultEditor.ini file.
 */

UCLASS(config = Editor, defaultconfig)
class EDITORCAMERAPOSITION_API UEditorCameraPositionSettings : public UObject
{
    GENERATED_BODY()

public:

	static bool GetIsToolBarVisible();
	static void SetIsToolBarVisible(bool bInIsVisible);

private:

	UPROPERTY(config)
	bool bIsToolBarVisible = false;
};
