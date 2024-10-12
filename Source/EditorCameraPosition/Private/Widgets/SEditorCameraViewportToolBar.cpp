// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "Widgets/SEditorCameraViewportToolBar.h"
#include "Widgets/SEditorCameraPositionViewportToolBar.h"
#include "Widgets/SEditorCameraRotationViewportToolBar.h"

void SEditorCameraViewportToolBar::Construct(const FArguments& Args)
{
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(256)
		.HeightOverride(0)
		.VAlign(VAlign_Top)
#if (ENGINE_MAJOR_VERSION == 4)
		.Padding(FMargin(0.f, -24.f, 0.f, 0.f))
#endif
		[
			SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SEditorCameraPositionViewportToolBar)
						.Visibility(Args._CameraPositionVisibility)
						.X(Args._X)
						.Y(Args._Y)
						.Z(Args._Z)
						.OnXChanged(Args._OnXChanged)
						.OnYChanged(Args._OnYChanged)
						.OnZChanged(Args._OnZChanged)
						.OnCopy(Args._OnLocationCopy)
						.OnPaste(Args._OnLocationPaste)
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SEditorCameraRotationViewportToolBar)
						.Visibility(Args._CameraRotationVisibility)
						.Roll(Args._Roll)
						.Pitch(Args._Pitch)
						.Yaw(Args._Yaw)
						.OnRollChanged(Args._OnRollChanged)
						.OnPitchChanged(Args._OnPitchChanged)
						.OnYawChanged(Args._OnYawChanged)
						.OnCopy(Args._OnRotationCopy)
						.OnPaste(Args._OnRotationPaste)
				]
		]
	];
}
