#pragma once

#include "Editor/UnrealEd/Public/SViewportToolBar.h"

class EDITORCAMERAPOSITION_API SEditorCameraPositionViewportToolBar : public SViewportToolBar
{
public:
	SLATE_BEGIN_ARGS(SEditorCameraPositionViewportToolBar) {}
		SLATE_ATTRIBUTE(TOptional<float>, X)
		SLATE_ATTRIBUTE(TOptional<float>, Y)
		SLATE_ATTRIBUTE(TOptional<float>, Z)
		SLATE_EVENT(FOnFloatValueCommitted, OnXCommitted)
		SLATE_EVENT(FOnFloatValueCommitted, OnYCommitted)
		SLATE_EVENT(FOnFloatValueCommitted, OnZCommitted)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
};