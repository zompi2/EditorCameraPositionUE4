// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "EditorCameraPositionSettings.h"
#include "Runtime/Launch/Resources/Version.h"

const UEditorCameraPositionSettings* UEditorCameraPositionSettings::Get()
{
	return GetDefault<UEditorCameraPositionSettings>();
}

bool UEditorCameraPositionSettings::GetIsCameraPositionToolBarEnabled()
{
	return Get()->bIsCameraPositionToolBarEnabled;
}

void UEditorCameraPositionSettings::SetIsCameraPositionToolBarEnabled(bool bInIsVisible)
{
	UEditorCameraPositionSettings* Settings = GetMutableDefault<UEditorCameraPositionSettings>();
	Settings->bIsCameraPositionToolBarEnabled = bInIsVisible;

#if (ENGINE_MAJOR_VERSION == 5)
	Settings->TryUpdateDefaultConfigFile();
#else
	Settings->UpdateDefaultConfigFile();
#endif
}

bool UEditorCameraPositionSettings::GetIsCameraRotationToolBarEnabled()
{
	return Get()->bIsCameraRotationToolBarEnabled;
}

void UEditorCameraPositionSettings::SetIsCameraRotationToolBarEnabled(bool bInIsVisible)
{
	UEditorCameraPositionSettings* Settings = GetMutableDefault<UEditorCameraPositionSettings>();
	Settings->bIsCameraRotationToolBarEnabled = bInIsVisible;

#if (ENGINE_MAJOR_VERSION == 5)
	Settings->TryUpdateDefaultConfigFile();
#else
	Settings->UpdateDefaultConfigFile();
#endif
}

FName UEditorCameraPositionSettings::GetContainerName() const
{
	return FName("Editor");
}

FName UEditorCameraPositionSettings::GetCategoryName() const
{
	return FName("Plugins");
}
FName UEditorCameraPositionSettings::GetSectionName() const 
{
	return FName("EditorCameraPosition"); 
}

FText UEditorCameraPositionSettings::GetSectionText() const
{
	return INVTEXT("Editor Camera Position");
}

FText UEditorCameraPositionSettings::GetSectionDescription() const
{
	return INVTEXT("Configure the Editor Camera Position Plugin");
}