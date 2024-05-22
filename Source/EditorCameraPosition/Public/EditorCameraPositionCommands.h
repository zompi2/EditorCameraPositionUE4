// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class EDITORCAMERAPOSITION_API FEditorCameraPositionCommands : public TCommands<FEditorCameraPositionCommands>
{
public:

	FEditorCameraPositionCommands();
	void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> ToggleShowCameraPosWidget;
};
