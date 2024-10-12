// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "SEditorCopyPasteBoxWidget.h"

class EDITORCAMERAPOSITION_API SEditorCameraPositionViewportToolBar : public SEditorCopyPasteBoxWidget
{

public:
	SLATE_BEGIN_ARGS(SEditorCameraPositionViewportToolBar) {}
		SLATE_ATTRIBUTE(TOptional<VectorValueType>, X)
		SLATE_ATTRIBUTE(TOptional<VectorValueType>, Y)
		SLATE_ATTRIBUTE(TOptional<VectorValueType>, Z)
		SLATE_EVENT(OnVectorValueChangedDelegateType, OnXChanged)
		SLATE_EVENT(OnVectorValueChangedDelegateType, OnYChanged)
		SLATE_EVENT(OnVectorValueChangedDelegateType, OnZChanged)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnCopy)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnPaste)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
};
