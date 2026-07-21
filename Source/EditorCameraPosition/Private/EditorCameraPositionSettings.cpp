// Copyright (c) 2026 Damian Nowakowski. All rights reserved.

#pragma once

#include "EditorCameraPositionSettings.h"
#include "EditorCameraPositionEngineVersionComparsion.h"

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

#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,0,0)
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

#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,0,0)
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