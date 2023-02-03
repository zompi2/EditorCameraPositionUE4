// Copyright (c) 2023 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class EDITORCAMERAPOSITION_API FEditorCameraPositionModule : public IModuleInterface
{

public:

	// IModuleInterface implementation
	void StartupModule() override;
	void ShutdownModule() override;

	TOptional<float> GetLocationX() const;
	TOptional<float> GetLocationY() const;
	TOptional<float> GetLocationZ() const;

	void SetLocationX(float Value);
	void SetLocationY(float Value);
	void SetLocationZ(float Value);

	void OnCopy();
	void OnPaste();

protected:

	/**
	 * Run some initializations after the Engine has been initialized.
	 */
	void OnPostEngineInit();

	void AddViewportToolBarExtension(class FLevelEditorModule* LevelEditor);
	void AddViewportOptionsExtension(class FLevelEditorModule* LevelEditor);

	void SetIsToolbarVisible(bool bNewIsVisible);
	bool GetIsToolbarVisible() const;
	EVisibility GetToolbarVisibility() const;

	void ToggleToolbarVisibility();

private:

	bool Tick(float DeltaTime);
	void RefreshViewportLocation();
	TSharedRef<class SWidget> GetWidget();

	FVector CamPos;

	FDelegateHandle TickerHandle;
	FDelegateHandle OnPostEngineInitDelegateHandle;
};
