// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "Widgets/Layout/SBox.h"
#include "EditorCameraPositionWorldCoordsType.h"

class EDITORCAMERAPOSITION_API SEditorCopyPasteBoxWidget : public SBox
{

public:

	FOnCameraPosOrRotCopyPasteEvent OnCopy;
	FOnCameraPosOrRotCopyPasteEvent OnPaste;

protected:
	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
	void CreateContextMenu(const FVector2D& mousePosition);
};
