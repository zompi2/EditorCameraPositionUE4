// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "Editor/UnrealEd/Public/SViewportToolBar.h"

DECLARE_DELEGATE(FOnCameraPosCopyPasteEvent);

class EDITORCAMERAPOSITION_API SEditorCameraPositionViewportToolBar : public SViewportToolBar
{

public:
	SLATE_BEGIN_ARGS(SEditorCameraPositionViewportToolBar) {}
		SLATE_ATTRIBUTE(TOptional<float>, X)
		SLATE_ATTRIBUTE(TOptional<float>, Y)
		SLATE_ATTRIBUTE(TOptional<float>, Z)
		SLATE_EVENT(FOnFloatValueChanged, OnXChanged)
		SLATE_EVENT(FOnFloatValueChanged, OnYChanged)
		SLATE_EVENT(FOnFloatValueChanged, OnZChanged)
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
