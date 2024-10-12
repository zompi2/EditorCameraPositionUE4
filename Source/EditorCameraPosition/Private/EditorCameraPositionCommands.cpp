// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionCommands.h"

#define LOCTEXT_NAMESPACE "EditorCameraPosition"

FEditorCameraPositionCommands::FEditorCameraPositionCommands()
	: TCommands<FEditorCameraPositionCommands>(
		TEXT("Editor Camera Position Tool Commands"),
		FText::FromString(TEXT("Commands to control Editor Camera Position Tool")),
		NAME_None,
#if ((ENGINE_MAJOR_VERSION == 5) && (ENGINE_MINOR_VERSION >= 1))
		FAppStyle::GetAppStyleSetName()
#else
		FEditorStyle::GetStyleSetName()
#endif
	)
{}

void FEditorCameraPositionCommands::RegisterCommands()
{
	UI_COMMAND(ToggleShowCameraPosWidget, "Toggle Camera Position", "Toggles if to show the camera position get/set toolbar in viewport.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::C));
	UI_COMMAND(ToggleShowCameraRotWidget, "Toggle Camera Rotation", "Toggles if to show the camera rotation get/set toolbar in viewport.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::X));
}

#undef LOCTEXT_NAMESPACE
