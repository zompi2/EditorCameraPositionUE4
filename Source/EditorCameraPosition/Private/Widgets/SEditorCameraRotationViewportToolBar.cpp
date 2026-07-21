// Copyright (c) 2026 Damian Nowakowski. All rights reserved.

#include "Widgets/SEditorCameraRotationViewportToolBar.h"
#include "EditorCameraPositionEngineVersionComparsion.h"

void SEditorCameraRotationViewportToolBar::Construct(const FArguments& Args)
{
	OnCopy = Args._OnCopy;
	OnPaste = Args._OnPaste;

	ChildSlot
	[
		SNew(RotatorInputBoxType)
			.bColorAxisLabels(true)
#if (ENGINE_MAJOR_VERSION == 4)
			.AllowResponsiveLayout(true)
#endif
			.AllowSpin(true)
#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,4,0)
			.SpinDelta(1.f)
#endif
			.Roll(Args._Roll)
			.Pitch(Args._Pitch)
			.Yaw(Args._Yaw)
			.OnRollChanged(Args._OnRollChanged)
			.OnPitchChanged(Args._OnPitchChanged)
			.OnYawChanged(Args._OnYawChanged)
	];
}
