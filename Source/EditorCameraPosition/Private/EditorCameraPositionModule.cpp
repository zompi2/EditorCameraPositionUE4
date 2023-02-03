// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionModule.h"
#include "SEditorCameraPositionViewportToolBar.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"
#include "Containers/Ticker.h"
#include "Editor.h"
#include "LevelEditorViewport.h"
#include "HAL/PlatformApplicationMisc.h"

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
		.OnXChanged_Raw(this, &FEditorCameraPositionModule::SetLocationX)
		.OnYChanged_Raw(this, &FEditorCameraPositionModule::SetLocationY)
		.OnZChanged_Raw(this, &FEditorCameraPositionModule::SetLocationZ)
		.OnCopy_Raw(this, &FEditorCameraPositionModule::OnCopy)
		.OnPaste_Raw(this, &FEditorCameraPositionModule::OnPaste);

}

void FEditorCameraPositionModule::RefreshViewportLocation()
{
	if (GCurrentLevelEditingViewportClient)
	{
		FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();
		ViewTransform.SetLocation(CamPos);
	}
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

void FEditorCameraPositionModule::SetLocationX(float Value)
{
	CamPos.X = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::SetLocationY(float Value)
{
	CamPos.Y = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::SetLocationZ(float Value)
{
	CamPos.Z = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::OnCopy()
{
	const FString CopyStr = FString::Printf(TEXT("(X=%f,Y=%f,Z=%f)"), CamPos.X, CamPos.Y, CamPos.Z);
	if (!CopyStr.IsEmpty())
	{
		FPlatformApplicationMisc::ClipboardCopy(*CopyStr);
	}
}

void FEditorCameraPositionModule::OnPaste()
{
	FString PastedText;
	FPlatformApplicationMisc::ClipboardPaste(PastedText);
	if (CamPos.InitFromString(PastedText))
	{
		RefreshViewportLocation();
	}
}

bool FEditorCameraPositionModule::Tick(float DeltaTime)
{
	if (GCurrentLevelEditingViewportClient)
	{
		FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();
		CamPos = ViewTransform.GetLocation();
	}
	return true;
}
