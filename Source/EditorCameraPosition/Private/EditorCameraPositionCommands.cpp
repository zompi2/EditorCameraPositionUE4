// Copyright (c) 2023 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionCommands.h"

#define LOCTEXT_NAMESPACE "EditorCameraPosition"

FEditorCameraPositionCommands::FEditorCameraPositionCommands()
: TCommands<FEditorCameraPositionCommands>(TEXT("Editor Camera Position Tool Commands"), FText::FromString(TEXT("Commands to control Editor Camera Position Tool")), NAME_None, FAppStyle::GetAppStyleSetName())
{}

void FEditorCameraPositionCommands::RegisterCommands()
{
	UI_COMMAND(ToggleShowCameraPosWidget, "Toggle Camera Position", "Toggles if to show the camera position get/set toolbar in viewport.", EUserInterfaceActionType::ToggleButton, FInputChord());
}

#undef LOCTEXT_NAMESPACE