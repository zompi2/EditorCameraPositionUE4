// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "Editor/UnrealEd/Public/SViewportToolBar.h"
#include "EditorCameraPositionWorldCoordsType.h"

DECLARE_DELEGATE(FOnCameraPosCopyPasteEvent);

class EDITORCAMERAPOSITION_API SEditorCameraPositionViewportToolBar : public SViewportToolBar
{

public:
	SLATE_BEGIN_ARGS(SEditorCameraPositionViewportToolBar) {}
		SLATE_ATTRIBUTE(TOptional<WorldCoordsType>, X)
		SLATE_ATTRIBUTE(TOptional<WorldCoordsType>, Y)
		SLATE_ATTRIBUTE(TOptional<WorldCoordsType>, Z)
		SLATE_EVENT(OnValueChangedDelegateType, OnXChanged)
		SLATE_EVENT(OnValueChangedDelegateType, OnYChanged)
		SLATE_EVENT(OnValueChangedDelegateType, OnZChanged)
		SLATE_EVENT(FOnCameraPosCopyPasteEvent, OnCopy)
		SLATE_EVENT(FOnCameraPosCopyPasteEvent, OnPaste)
	SLATE_END_ARGS()

	FOnCameraPosCopyPasteEvent OnCopy;
	FOnCameraPosCopyPasteEvent OnPaste;

	void Construct(const FArguments& Args);

protected:
	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
	void CreateContextMenu(const FVector2D& mousePosition);
};
