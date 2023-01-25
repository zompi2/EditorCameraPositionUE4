// Copyright Epic Games, Inc. All Rights Reserved.

#include "SEditorCameraPositionViewportToolBar.h"
#include "Widgets/Input/SVectorInputBox.h"

void SEditorCameraPositionViewportToolBar::Construct(const FArguments& Args)
{
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(256)
		.VAlign(VAlign_Center)
		[
			SNew(SVectorInputBox)
			.bColorAxisLabels(true)
			.AllowResponsiveLayout(true)
			.X(Args._X)
			.Y(Args._Y)
			.Z(Args._Z)
			.OnXCommitted(Args._OnXCommitted)
			.OnYCommitted(Args._OnYCommitted)
			.OnZCommitted(Args._OnZCommitted)
		]
	];
}
