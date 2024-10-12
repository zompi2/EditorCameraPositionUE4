// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "SEditorCameraPositionViewportToolBar.h"

void SEditorCameraPositionViewportToolBar::Construct(const FArguments& Args)
{
	OnCopy = Args._OnCopy;
	OnPaste = Args._OnPaste;

	ChildSlot
	[
		SNew(VectorInputBoxType)
			.bColorAxisLabels(true)
#if (ENGINE_MAJOR_VERSION == 4)
			.AllowResponsiveLayout(true)
#endif
			.AllowSpin(true)
			.SpinDelta(1)
			.X(Args._X)
			.Y(Args._Y)
			.Z(Args._Z)
			.OnXChanged(Args._OnXChanged)
			.OnYChanged(Args._OnYChanged)
			.OnZChanged(Args._OnZChanged)
	];
}
