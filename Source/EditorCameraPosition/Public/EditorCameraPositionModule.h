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

	TOptional<VectorValueType> GetLocationX() const;
	TOptional<VectorValueType> GetLocationY() const;
	TOptional<VectorValueType> GetLocationZ() const;

	void SetLocationX(VectorValueType Value);
	void SetLocationY(VectorValueType Value);
	void SetLocationZ(VectorValueType Value);

	void OnLocationCopy();
	void OnLocationPaste();

	TOptional<RotatorValueType> GetRotationRoll() const;
	TOptional<RotatorValueType> GetRotationPitch() const;
	TOptional<RotatorValueType> GetRotationYaw() const;

	void SetRotationRoll(RotatorValueType Value);
	void SetRotationPitch(RotatorValueType Value);
	void SetRotationYaw(RotatorValueType Value);

	void OnRotationCopy();
	void OnRotationPaste();

	void SetIsToolbarVisible(bool bNewIsVisible);
	bool GetIsToolbarVisible() const;
	EVisibility GetToolbarVisibility() const;
	void ToggleToolbarVisibility();

private:

	bool Tick(float DeltaTime);
	void RefreshViewportLocation();
	void RefreshViewportRotation();
	TSharedRef<class SWidget> GetWidget();

	FVector CamPos;
	FRotator CamRot;
	bool bIsToolBarVisible;

#if (ENGINE_MAJOR_VERSION == 5)
	FTSTicker::FDelegateHandle TickerHandle;
#else
	FDelegateHandle TickerHandle;
#endif

	FDelegateHandle OnPostEngineInitDelegateHandle;
};
