// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionModule.h"
#include "EditorCameraPositionCommands.h"
#include "EditorCameraPositionSettings.h"
#include "EditorCameraPositionUtils.h"
#include "SEditorCameraPositionViewportToolBar.h"
#include "SEditorCameraViewportToolBar.h"

#include "Editor.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "Containers/Ticker.h"
#include "HAL/PlatformApplicationMisc.h"
#include "ToolMenus.h"

IMPLEMENT_MODULE(FEditorCameraPositionModule, EditorCameraPosition)

void FEditorCameraPositionModule::StartupModule()
{
	FEditorCameraPositionCommands::Register();
	OnPostEngineInitDelegateHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEditorCameraPositionModule::OnPostEngineInit);

#if (ENGINE_MAJOR_VERSION == 5)
	TickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FEditorCameraPositionModule::Tick), 0.0f);
#else
	TickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FEditorCameraPositionModule::Tick), 0.0f);
#endif
}

void FEditorCameraPositionModule::ShutdownModule()
{
#if (ENGINE_MAJOR_VERSION == 5)
	FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
#else
	FTicker::GetCoreTicker().RemoveTicker(TickerHandle);
#endif
	FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitDelegateHandle);
	FEditorCameraPositionCommands::Unregister();
}

void FEditorCameraPositionModule::OnPostEngineInit()
{
	if ((IsRunningCommandlet() == false) && (IsRunningGame() == false) && FSlateApplication::IsInitialized())
	{
		bIsToolBarVisible = UEditorCameraPositionSettings::GetIsToolBarVisible();

		AddViewportToolBarExtension();
		AddViewportOptionsExtension();
	}
}

void FEditorCameraPositionModule::AddViewportToolBarExtension()
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

void FEditorCameraPositionModule::AddViewportOptionsExtension()
{
	TSharedPtr<FUICommandInfo> Command = FEditorCameraPositionCommands::Get().ToggleShowCameraPosWidget;
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolBar.Options");
	if (Menu)
	{
		FUIAction Action;
		Action.ExecuteAction.BindLambda([this]()
		{
			ToggleToolbarVisibility();
		});
		Action.GetActionCheckState.BindLambda([this]() -> ECheckBoxState
		{
			return GetIsToolbarVisible() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		});
		Action.CanExecuteAction.BindLambda([this]() -> bool
		{
			return true;
		});

		FToolMenuSection& Section = Menu->FindOrAddSection("LevelViewportViewportOptions2");
		Section.AddMenuEntry(Command);

		if (FLevelEditorModule* LevelEditor = FModuleManager::LoadModulePtr<FLevelEditorModule>(TEXT("LevelEditor")))
		{
			TSharedRef<FUICommandList> GlobalLevelEditorActions = LevelEditor->GetGlobalLevelEditorActions();
			GlobalLevelEditorActions->MapAction(Command, Action);
		}
	}
}

TOptional<VectorValueType> FEditorCameraPositionModule::GetLocationX() const
{
	return FMath::TruncToFloat(CamPos.X);
}

TOptional<VectorValueType> FEditorCameraPositionModule::GetLocationY() const
{
	return FMath::TruncToFloat(CamPos.Y);
}

TOptional<VectorValueType> FEditorCameraPositionModule::GetLocationZ() const
{
	return FMath::TruncToFloat(CamPos.Z);
}

void FEditorCameraPositionModule::SetLocationX(VectorValueType Value)
{
	CamPos.X = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::SetLocationY(VectorValueType Value)
{
	CamPos.Y = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::SetLocationZ(VectorValueType Value)
{
	CamPos.Z = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::OnLocationCopy()
{
	const FString CopyStr = FString::Printf(TEXT("(%s)"), *CamPos.ToString());
	if (CopyStr.IsEmpty() == false)
	{
		FPlatformApplicationMisc::ClipboardCopy(*CopyStr);
	}
}

void FEditorCameraPositionModule::OnLocationPaste()
{
	FString PastedText;
	FPlatformApplicationMisc::ClipboardPaste(PastedText);
	if (CamPos.InitFromString(PastedText))
	{
		RefreshViewportLocation();
	}
}

TOptional<RotatorValueType> FEditorCameraPositionModule::GetRotationRoll() const
{
	return FMath::TruncToFloat(CamRot.Roll);
}

TOptional<RotatorValueType> FEditorCameraPositionModule::GetRotationPitch() const
{
	return FMath::TruncToFloat(CamRot.Pitch);
}

TOptional<RotatorValueType> FEditorCameraPositionModule::GetRotationYaw() const
{
	return FMath::TruncToFloat(CamRot.Yaw);
}

void FEditorCameraPositionModule::SetRotationRoll(RotatorValueType Value)
{
	CamRot.Roll = Value;
	RefreshViewportRotation();
}

void FEditorCameraPositionModule::SetRotationPitch(RotatorValueType Value)
{
	CamRot.Pitch = Value;
	RefreshViewportRotation();
}

void FEditorCameraPositionModule::SetRotationYaw(RotatorValueType Value)
{
	CamRot.Yaw = Value;
	RefreshViewportRotation();
}

void FEditorCameraPositionModule::OnRotationCopy()
{
	const FString CopyStr = FString::Printf(TEXT("(%s)"), *CamRot.ToString());
	if (CopyStr.IsEmpty() == false)
	{
		FPlatformApplicationMisc::ClipboardCopy(*CopyStr);
	}
}

void FEditorCameraPositionModule::OnRotationPaste()
{
	FString PastedText;
	FPlatformApplicationMisc::ClipboardPaste(PastedText);
	if (CamRot.InitFromString(PastedText))
	{
		RefreshViewportRotation();
	}
}

void FEditorCameraPositionModule::SetIsToolbarVisible(bool bNewIsVisible)
{
	bIsToolBarVisible = bNewIsVisible;
	UEditorCameraPositionSettings::SetIsToolBarVisible(bIsToolBarVisible);
}

bool FEditorCameraPositionModule::GetIsToolbarVisible() const
{
	return bIsToolBarVisible;
}

EVisibility FEditorCameraPositionModule::GetToolbarVisibility() const
{
	return bIsToolBarVisible ? EVisibility::Visible : EVisibility::Collapsed;
}

void FEditorCameraPositionModule::ToggleToolbarVisibility()
{
	SetIsToolbarVisible(!GetIsToolbarVisible());
}

bool FEditorCameraPositionModule::Tick(float DeltaTime)
{
	CamPos = UEditorCameraPositionUtils::GetEditorCameraPosition();
	CamRot = UEditorCameraPositionUtils::GetEditorCameraRotation();
	return true;
}

void FEditorCameraPositionModule::RefreshViewportLocation()
{
	UEditorCameraPositionUtils::SetEditorCameraPosition(CamPos);
}

void FEditorCameraPositionModule::RefreshViewportRotation()
{
	UEditorCameraPositionUtils::SetEditorCameraRotation(CamRot);
}

TSharedRef<SWidget> FEditorCameraPositionModule::GetWidget()
{
	return SNew(SEditorCameraViewportToolBar)
		.Visibility_Raw(this, &FEditorCameraPositionModule::GetToolbarVisibility)
		.X_Raw(this, &FEditorCameraPositionModule::GetLocationX)
		.Y_Raw(this, &FEditorCameraPositionModule::GetLocationY)
		.Z_Raw(this, &FEditorCameraPositionModule::GetLocationZ)
		.Roll_Raw(this, &FEditorCameraPositionModule::GetRotationRoll)
		.Pitch_Raw(this, &FEditorCameraPositionModule::GetRotationPitch)
		.Yaw_Raw(this, &FEditorCameraPositionModule::GetRotationYaw)
		.OnXChanged_Raw(this, &FEditorCameraPositionModule::SetLocationX)
		.OnYChanged_Raw(this, &FEditorCameraPositionModule::SetLocationY)
		.OnZChanged_Raw(this, &FEditorCameraPositionModule::SetLocationZ)
		.OnRollChanged_Raw(this, &FEditorCameraPositionModule::SetRotationRoll)
		.OnPitchChanged_Raw(this, &FEditorCameraPositionModule::SetRotationPitch)
		.OnYawChanged_Raw(this, &FEditorCameraPositionModule::SetRotationYaw)
		.OnLocationCopy_Raw(this, &FEditorCameraPositionModule::OnLocationCopy)
		.OnLocationPaste_Raw(this, &FEditorCameraPositionModule::OnLocationPaste)
		.OnRotationCopy_Raw(this, &FEditorCameraPositionModule::OnRotationCopy)
		.OnRotationPaste_Raw(this, &FEditorCameraPositionModule::OnRotationPaste);
}
