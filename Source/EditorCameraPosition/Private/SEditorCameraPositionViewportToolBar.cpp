// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "SEditorCameraPositionViewportToolBar.h"

void SEditorCameraPositionViewportToolBar::Construct(const FArguments& Args)
{
	OnCopy = Args._OnCopy;
	OnPaste = Args._OnPaste;

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(256)
		.HeightOverride(0)
		.VAlign(VAlign_Top)
		[
			SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
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
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(VectorInputBoxType)
				]
		]
	];
}

FReply SEditorCameraPositionViewportToolBar::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		CreateContextMenu(MouseEvent.GetScreenSpacePosition());
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void SEditorCameraPositionViewportToolBar::CreateContextMenu(const FVector2D& MousePosition)
{
	FUIAction CopyAction = FUIAction(FExecuteAction::CreateLambda([this]()
	{
		OnCopy.ExecuteIfBound();
	}));

	FUIAction PasteAction = FUIAction(FExecuteAction::CreateLambda([this]()
	{
		OnPaste.ExecuteIfBound();
	}));

	FMenuBuilder MenuBuilder(true, nullptr);

	MenuBuilder.AddMenuEntry(
		NSLOCTEXT("PropertyView", "CopyProperty", "Copy"),
		NSLOCTEXT("PropertyView", "CopyProperty_ToolTip", "Copy this property value"),
		FSlateIcon(FCoreStyle::Get().GetStyleSetName(), "GenericCommands.Copy"),
		CopyAction);

	MenuBuilder.AddMenuEntry(
		NSLOCTEXT("PropertyView", "PasteProperty", "Paste"),
		NSLOCTEXT("PropertyView", "PasteProperty_ToolTip", "Paste the copied value here"),
		FSlateIcon(FCoreStyle::Get().GetStyleSetName(), "GenericCommands.Paste"),
		PasteAction);

	FSlateApplication::Get().PushMenu(
		SharedThis(this),
		FWidgetPath(),
		MenuBuilder.MakeWidget(),
		MousePosition,
		FPopupTransitionEffect(FPopupTransitionEffect::ContextMenu));
}
