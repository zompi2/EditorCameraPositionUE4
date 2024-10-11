// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorCameraPositionTypes.generated.h"

UENUM()
enum class EEditorCameraPositionTruncType
{
	NoTrunc,
	TwoDecimals,
	ZeroDecimals
};
