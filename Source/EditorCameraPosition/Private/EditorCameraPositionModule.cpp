// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionModule.h"
#include "EditorCameraPositionCommands.h"
#include "EditorCameraPositionSettings.h"
#include "EditorCameraPositionUtils.h"
#include "EditorCameraPositionTypes.h"
#include "Widgets/SEditorCameraViewportToolBar.h"

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

	if ((IsRunningCommandlet() == false) && (IsRunningGame() == false) && FSlateApplication::IsInitialized())
	{
		RefreshToolbarVisibility();
		AddViewportToolBarExtension();
		AddViewportCameraPositionOptionExtension();
		AddViewportCameraRotationOptionExtension();
	}

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
	FEditorCameraPositionCommands::Unregister();
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

void FEditorCameraPositionModule::AddViewportCameraPositionOptionExtension()
{
	TSharedPtr<FUICommandInfo> Command = FEditorCameraPositionCommands::Get().ToggleShowCameraPosWidget;
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolBar.Options");
	if (Menu)
	{
		FUIAction Action;
		Action.ExecuteAction.BindLambda([this]()
		{
			ToggleCameraPositionToolbarEnabled();
		});
		Action.GetActionCheckState.BindLambda([this]() -> ECheckBoxState
		{
			return GetIsCameraPositionToolBarEnabled() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		});
		Action.CanExecuteAction.BindLambda([this]() -> bool
		{
			return UEditorCameraPositionSettings::Get()->bEnableEditorCameraPosition;
		});
		Action.IsActionVisibleDelegate.BindLambda([this]() -> bool
		{
			return UEditorCameraPositionSettings::Get()->bEnableEditorCameraPosition;
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

void FEditorCameraPositionModule::AddViewportCameraRotationOptionExtension()
{
	TSharedPtr<FUICommandInfo> Command = FEditorCameraPositionCommands::Get().ToggleShowCameraRotWidget;
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolBar.Options");
	if (Menu)
	{
		FUIAction Action;
		Action.ExecuteAction.BindLambda([this]()
		{
			ToggleCameraRotationToolbarEnabled();
		});
		Action.GetActionCheckState.BindLambda([this]() -> ECheckBoxState
		{
			return GetIsCameraRotationToolBarEnabled() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		});
		Action.CanExecuteAction.BindLambda([this]() -> bool
		{
			return UEditorCameraPositionSettings::Get()->bEnableEditorCameraRotation;
		});
		Action.IsActionVisibleDelegate.BindLambda([this]() -> bool
		{
			return UEditorCameraPositionSettings::Get()->bEnableEditorCameraRotation;
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
	return TruncPosition(CamPos.X);
}

TOptional<VectorValueType> FEditorCameraPositionModule::GetLocationY() const
{
	return TruncPosition(CamPos.Y);
}

TOptional<VectorValueType> FEditorCameraPositionModule::GetLocationZ() const
{
	return TruncPosition(CamPos.Z);
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
	return TruncRotation(CamRot.Roll);
}

TOptional<RotatorValueType> FEditorCameraPositionModule::GetRotationPitch() const
{
	return TruncRotation(CamRot.Pitch);
}

TOptional<RotatorValueType> FEditorCameraPositionModule::GetRotationYaw() const
{
	return TruncRotation(CamRot.Yaw);
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

void FEditorCameraPositionModule::SetIsCameraPositionToolBarEnabled(bool bNewIsVisible)
{
	UEditorCameraPositionSettings::SetIsCameraPositionToolBarEnabled(bNewIsVisible);
}

bool FEditorCameraPositionModule::GetIsCameraPositionToolBarEnabled() const
{
	return bIsCamPosToolbarVisible;
}

void FEditorCameraPositionModule::ToggleCameraPositionToolbarEnabled()
{
	SetIsCameraPositionToolBarEnabled(!GetIsCameraPositionToolBarEnabled());
}

EVisibility FEditorCameraPositionModule::GetCameraPositionToolBarVisibility() const
{
	return (bIsCamPosToolbarVisible && UEditorCameraPositionSettings::Get()->bEnableEditorCameraPosition) ? EVisibility::Visible : EVisibility::Collapsed;
}

void FEditorCameraPositionModule::SetIsCameraRotationToolBarEnabled(bool bNewIsVisible)
{
	UEditorCameraPositionSettings::SetIsCameraRotationToolBarEnabled(bNewIsVisible);
}

bool FEditorCameraPositionModule::GetIsCameraRotationToolBarEnabled() const
{
	return bIsCamRotToolbarVisible;
}

void FEditorCameraPositionModule::ToggleCameraRotationToolbarEnabled()
{
	SetIsCameraRotationToolBarEnabled(!GetIsCameraRotationToolBarEnabled());
}

EVisibility FEditorCameraPositionModule::GetCameraRotationToolBarVisibility() const
{
	return (bIsCamRotToolbarVisible && UEditorCameraPositionSettings::Get()->bEnableEditorCameraRotation) ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility FEditorCameraPositionModule::GetToolbarVisibility() const
{
	return ((GetCameraPositionToolBarVisibility() == EVisibility::Visible) || (GetCameraRotationToolBarVisibility() == EVisibility::Visible)) ? EVisibility::Visible : EVisibility::Collapsed;
}

bool FEditorCameraPositionModule::Tick(float DeltaTime)
{
	RefreshToolbarVisibility();
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

void FEditorCameraPositionModule::RefreshToolbarVisibility()
{
	bIsCamPosToolbarVisible = UEditorCameraPositionSettings::GetIsCameraPositionToolBarEnabled() && UEditorCameraPositionSettings::Get()->bEnableEditorCameraPosition;
	bIsCamRotToolbarVisible = UEditorCameraPositionSettings::GetIsCameraRotationToolBarEnabled() && UEditorCameraPositionSettings::Get()->bEnableEditorCameraRotation;
}

TOptional<VectorValueType> FEditorCameraPositionModule::TruncPosition(VectorValueType InValue) const
{
	if (UEditorCameraPositionSettings::Get()->CameraPositionTrunc == EEditorCameraPositionTruncType::NoTrunc)
	{
		return InValue;
	}
	else if (UEditorCameraPositionSettings::Get()->CameraPositionTrunc == EEditorCameraPositionTruncType::TwoDecimals)
	{
		return FMath::TruncToFloat(InValue * 100) / 100;
	}
	else if (UEditorCameraPositionSettings::Get()->CameraPositionTrunc == EEditorCameraPositionTruncType::ZeroDecimals)
	{
		return FMath::TruncToFloat(InValue);
	}
	return InValue;
}

TOptional<RotatorValueType> FEditorCameraPositionModule::TruncRotation(RotatorValueType InValue) const
{
	if (UEditorCameraPositionSettings::Get()->CameraRotationTrunc == EEditorCameraPositionTruncType::NoTrunc)
	{
		return InValue;
	}
	else if (UEditorCameraPositionSettings::Get()->CameraRotationTrunc == EEditorCameraPositionTruncType::TwoDecimals)
	{
		return FMath::TruncToFloat(InValue * 100) / 100;
	}
	else if (UEditorCameraPositionSettings::Get()->CameraRotationTrunc == EEditorCameraPositionTruncType::ZeroDecimals)
	{
		return FMath::TruncToFloat(InValue);
	}
	return InValue;
}

TSharedRef<SWidget> FEditorCameraPositionModule::GetWidget()
{
	return SNew(SEditorCameraViewportToolBar)
		.Visibility_Raw(this, &FEditorCameraPositionModule::GetToolbarVisibility)
		.CameraPositionVisibility_Raw(this, &FEditorCameraPositionModule::GetCameraPositionToolBarVisibility)
		.X_Raw(this, &FEditorCameraPositionModule::GetLocationX)
		.Y_Raw(this, &FEditorCameraPositionModule::GetLocationY)
		.Z_Raw(this, &FEditorCameraPositionModule::GetLocationZ)
		.CameraRotationVisibility_Raw(this, &FEditorCameraPositionModule::GetCameraRotationToolBarVisibility)
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
