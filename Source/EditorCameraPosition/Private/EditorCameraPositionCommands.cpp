// Copyright (c) 2026 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionCommands.h"
#include "EditorCameraPositionEngineVersionComparsion.h"

#define LOCTEXT_NAMESPACE "EditorCameraPosition"

FEditorCameraPositionCommands::FEditorCameraPositionCommands()
	: TCommands<FEditorCameraPositionCommands>(
		TEXT("Editor Camera Position Tool Commands"),
		FText::FromString(TEXT("Commands to control Editor Camera Position Tool")),
		NAME_None,
#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,1,0)
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
