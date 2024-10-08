// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "SEditorCameraRotationViewportToolBar.h"

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
			.SpinDelta(1)
			.Roll(Args._Roll)
			.Pitch(Args._Pitch)
			.Yaw(Args._Yaw)
			.OnRollChanged(Args._OnRollChanged)
			.OnPitchChanged(Args._OnPitchChanged)
			.OnYawChanged(Args._OnYawChanged)
	];
}
