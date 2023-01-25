// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionModule.h"
#include "SEditorCameraPositionViewportToolBar.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"
#include "Containers/Ticker.h"

IMPLEMENT_MODULE(FEditorCameraPositionModule, EditorCameraPosition)

void FEditorCameraPositionModule::StartupModule()
{
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorCameraPositionModule::OnPostEngineInit);
	TickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FEditorCameraPositionModule::Tick), 0.0f);
}

void FEditorCameraPositionModule::ShutdownModule()
{
	FTicker::GetCoreTicker().RemoveTicker(TickerHandle);
	FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitDelegateHandle);
}

void FEditorCameraPositionModule::OnPostEngineInit()
{
	if ((IsRunningCommandlet() == false) && (IsRunningGame() == false) && FSlateApplication::IsInitialized())
	{
		if (FLevelEditorModule* LevelEditor = FModuleManager::LoadModulePtr<FLevelEditorModule>(TEXT("LevelEditor")))
		{
			TSharedPtr<FUICommandList> Commands = MakeShareable(new FUICommandList());
			TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
			ToolbarExtender->AddToolBarExtension(
				"CameraSpeed", 
				EExtensionHook::After, 
				Commands,
				FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& ToolbarBuilder)
				{
					ToolbarBuilder.AddSeparator();
					ToolbarBuilder.BeginSection("CameraPosition");
					ToolbarBuilder.AddWidget(GetWidget());
					ToolbarBuilder.EndSection();
				})
			);
			LevelEditor->GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
		}
	}
}

TSharedRef<SWidget> FEditorCameraPositionModule::GetWidget()
{
	return SNew(SEditorCameraPositionViewportToolBar)
		.X_Raw(this, &FEditorCameraPositionModule::GetLocationX)
		.Y_Raw(this, &FEditorCameraPositionModule::GetLocationY)
		.Z_Raw(this, &FEditorCameraPositionModule::GetLocationZ)
		.OnXCommitted_Raw(this, &FEditorCameraPositionModule::SetLocationX)
		.OnYCommitted_Raw(this, &FEditorCameraPositionModule::SetLocationY)
		.OnZCommitted_Raw(this, &FEditorCameraPositionModule::SetLocationZ);

}

TOptional<float> FEditorCameraPositionModule::GetLocationX() const
{
	return CamPos.X;
}

TOptional<float> FEditorCameraPositionModule::GetLocationY() const
{
	return CamPos.Y;
}

TOptional<float> FEditorCameraPositionModule::GetLocationZ() const
{
	return CamPos.Z;
}

void FEditorCameraPositionModule::SetLocationX(float Value, ETextCommit::Type CommitType)
{
	CamPos.X = Value;
}

void FEditorCameraPositionModule::SetLocationY(float Value, ETextCommit::Type CommitType)
{
	CamPos.Y = Value;
}

void FEditorCameraPositionModule::SetLocationZ(float Value, ETextCommit::Type CommitType)
{
	CamPos.Z = Value;
}

bool FEditorCameraPositionModule::Tick(float DeltaTime)
{
	if (UWorld* World = GetWorld()) 
	{
		const TArray<FVector>& LastFramesLoc = World->ViewLocationsRenderedLastFrame;
		if (LastFramesLoc.Num() > 0)
		{
			CamPos.X = FMath::RoundToFloat(LastFramesLoc[0].X);
			CamPos.Y = FMath::RoundToFloat(LastFramesLoc[0].Y);
			CamPos.Z = FMath::RoundToFloat(LastFramesLoc[0].Z);
		}
	}
	return true;
}

UWorld* FEditorCameraPositionModule::GetWorld()
{
	return GEditor ? GEditor->GetEditorWorldContext(false).World() : nullptr;
}
