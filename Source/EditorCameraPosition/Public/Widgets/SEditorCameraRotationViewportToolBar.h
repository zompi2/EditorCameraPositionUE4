// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "SEditorCopyPasteBoxWidget.h"

class EDITORCAMERAPOSITION_API SEditorCameraRotationViewportToolBar : public SEditorCopyPasteBoxWidget
{

public:
	SLATE_BEGIN_ARGS(SEditorCameraRotationViewportToolBar) {}
		SLATE_ATTRIBUTE(TOptional<RotatorValueType>, Roll)
		SLATE_ATTRIBUTE(TOptional<RotatorValueType>, Pitch)
		SLATE_ATTRIBUTE(TOptional<RotatorValueType>, Yaw)
		SLATE_EVENT(OnRotatorValueChangedDelegateType, OnRollChanged)
		SLATE_EVENT(OnRotatorValueChangedDelegateType, OnPitchChanged)
		SLATE_EVENT(OnRotatorValueChangedDelegateType, OnYawChanged)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnCopy)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnPaste)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
};
