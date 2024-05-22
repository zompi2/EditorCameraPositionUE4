// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "EditorCameraPositionSettings.h"
#include "Runtime/Launch/Resources/Version.h"

bool UEditorCameraPositionSettings::GetIsToolBarVisible()
{
	return GetDefault<UEditorCameraPositionSettings>()->bIsToolBarVisible;
}

void UEditorCameraPositionSettings::SetIsToolBarVisible(bool bInIsVisible)
{
	UEditorCameraPositionSettings* Settings = GetMutableDefault<UEditorCameraPositionSettings>();
	Settings->bIsToolBarVisible = bInIsVisible;

#if (ENGINE_MAJOR_VERSION == 5)
	Settings->TryUpdateDefaultConfigFile();
#else
	Settings->UpdateDefaultConfigFile();
#endif
}
