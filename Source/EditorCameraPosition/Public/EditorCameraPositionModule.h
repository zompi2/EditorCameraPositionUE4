// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Localization Editor module, which handles Editor object and DockTab creation.
 */

class EDITORCAMERAPOSITION_API FEditorCameraPositionModule : public IModuleInterface
{

public:

	// IModuleInterface implementation
	void StartupModule() override;
	void ShutdownModule() override;

	TOptional<float> GetLocationX() const;
	TOptional<float> GetLocationY() const;
	TOptional<float> GetLocationZ() const;

	void SetLocationX(float Value, ETextCommit::Type CommitType);
	void SetLocationY(float Value, ETextCommit::Type CommitType);
	void SetLocationZ(float Value, ETextCommit::Type CommitType);

	bool Tick(float DeltaTime);
	class UWorld* GetWorld();

protected:

	/**
	 * Run some initializations after the Engine has been initialized.
	 */
	void OnPostEngineInit();

private:

	TSharedRef<class SWidget> GetWidget();
	TSharedPtr<SWidget> Test;
	FVector CamPos;
	FDelegateHandle TickerHandle;
	FDelegateHandle OnPostEngineInitDelegateHandle;
};
