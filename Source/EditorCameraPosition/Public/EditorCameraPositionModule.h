// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "EditorCameraPositionTypes.h"

class EDITORCAMERAPOSITION_API FEditorCameraPositionModule : public IModuleInterface
{

protected:

	void StartupModule() override;
	void ShutdownModule() override;

	void AddViewportToolBarExtension();
	void AddViewportCameraPositionOptionExtension();
	void AddViewportCameraRotationOptionExtension();

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

	void SetIsCameraPositionToolBarEnabled(bool bNewIsVisible);
	bool GetIsCameraPositionToolBarEnabled() const;
	void ToggleCameraPositionToolbarEnabled();
	EVisibility GetCameraPositionToolBarVisibility() const;

	void SetIsCameraRotationToolBarEnabled(bool bNewIsVisible);
	bool GetIsCameraRotationToolBarEnabled() const;
	void ToggleCameraRotationToolbarEnabled();
	EVisibility GetCameraRotationToolBarVisibility() const;

	EVisibility GetToolbarVisibility() const;

private:

	bool Tick(float DeltaTime);
	void RefreshViewportLocation();
	void RefreshViewportRotation();
	void RefreshToolbarVisibility();
	TOptional<VectorValueType> TruncPosition(VectorValueType InValue) const;
	TOptional<RotatorValueType> TruncRotation(RotatorValueType InValue) const;
	TSharedRef<class SWidget> GetWidget();

	FVector CamPos;
	FRotator CamRot;
	bool bIsCamPosToolbarVisible = true;
	bool bIsCamRotToolbarVisible = true;

#if (ENGINE_MAJOR_VERSION == 5)
	FTSTicker::FDelegateHandle TickerHandle;
#else
	FDelegateHandle TickerHandle;
#endif
};
