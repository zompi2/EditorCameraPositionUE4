// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "SEditorCopyPasteBoxWidget.h"

FReply SEditorCopyPasteBoxWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		CreateContextMenu(MouseEvent.GetScreenSpacePosition());
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void SEditorCopyPasteBoxWidget::CreateContextMenu(const FVector2D& MousePosition)
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
