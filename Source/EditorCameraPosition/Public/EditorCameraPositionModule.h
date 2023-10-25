// Copyright (c) 2023 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class EDITORCAMERAPOSITION_API FEditorCameraPositionModule : public IModuleInterface
{

protected:

	void StartupModule() override;
	void ShutdownModule() override;

	void OnPostEngineInit();

	void AddViewportToolBarExtension();
	void AddViewportOptionsExtension();

	TOptional<float> GetLocationX() const;
	TOptional<float> GetLocationY() const;
	TOptional<float> GetLocationZ() const;

	void SetLocationX(float Value);
	void SetLocationY(float Value);
	void SetLocationZ(float Value);

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

	FTSTicker::FDelegateHandle TickerHandle;
	FDelegateHandle OnPostEngineInitDelegateHandle;
};
