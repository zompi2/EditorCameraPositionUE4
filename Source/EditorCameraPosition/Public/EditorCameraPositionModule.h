// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "EditorCameraPositionWorldCoordsType.h"

class EDITORCAMERAPOSITION_API FEditorCameraPositionModule : public IModuleInterface
{

protected:

	void StartupModule() override;
	void ShutdownModule() override;

	void OnPostEngineInit();

	void AddViewportToolBarExtension();
	void AddViewportOptionsExtension();

	TOptional<WorldCoordsType> GetLocationX() const;
	TOptional<WorldCoordsType> GetLocationY() const;
	TOptional<WorldCoordsType> GetLocationZ() const;

	void SetLocationX(WorldCoordsType Value);
	void SetLocationY(WorldCoordsType Value);
	void SetLocationZ(WorldCoordsType Value);

	void OnCopy();
	void OnPaste();

	void SetIsToolbarVisible(bool bNewIsVisible);
	bool GetIsToolbarVisible() const;
	EVisibility GetToolbarVisibility() const;
	void ToggleToolbarVisibility();

private:

	bool Tick(float DeltaTime);
	void RefreshViewportLocation();
	TSharedRef<class SWidget> GetWidget();

	FVector CamPos;
	bool bIsToolBarVisible;

#if (ENGINE_MAJOR_VERSION == 5)
	FTSTicker::FDelegateHandle TickerHandle;
#else
	FDelegateHandle TickerHandle;
#endif

	FDelegateHandle OnPostEngineInitDelegateHandle;
};
