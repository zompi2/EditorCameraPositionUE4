// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "Editor/UnrealEd/Public/SViewportToolBar.h"
#include "EditorCameraPositionWorldCoordsType.h"

class EDITORCAMERAPOSITION_API SEditorCameraViewportToolBar : public SViewportToolBar
{

public:
	SLATE_BEGIN_ARGS(SEditorCameraViewportToolBar) {}
		SLATE_ATTRIBUTE(TOptional<VectorValueType>, X)
		SLATE_ATTRIBUTE(TOptional<VectorValueType>, Y)
		SLATE_ATTRIBUTE(TOptional<VectorValueType>, Z)
		SLATE_ATTRIBUTE(TOptional<RotatorValueType>, Roll)
		SLATE_ATTRIBUTE(TOptional<RotatorValueType>, Pitch)
		SLATE_ATTRIBUTE(TOptional<RotatorValueType>, Yaw)
		SLATE_EVENT(OnVectorValueChangedDelegateType, OnXChanged)
		SLATE_EVENT(OnVectorValueChangedDelegateType, OnYChanged)
		SLATE_EVENT(OnVectorValueChangedDelegateType, OnZChanged)
		SLATE_EVENT(OnRotatorValueChangedDelegateType, OnRollChanged)
		SLATE_EVENT(OnRotatorValueChangedDelegateType, OnPitchChanged)
		SLATE_EVENT(OnRotatorValueChangedDelegateType, OnYawChanged)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnLocationCopy)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnLocationPaste)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnRotationCopy)
		SLATE_EVENT(FOnCameraPosOrRotCopyPasteEvent, OnRotationPaste)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
};
