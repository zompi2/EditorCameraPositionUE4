// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionModule.h"
#include "EditorCameraPositionCommands.h"
#include "EditorCameraPositionSettings.h"
#include "SEditorCameraPositionViewportToolBar.h"

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

TOptional<WorldCoordsType> FEditorCameraPositionModule::GetLocationX() const
{
	return FMath::TruncToFloat(CamPos.X);
}

TOptional<WorldCoordsType> FEditorCameraPositionModule::GetLocationY() const
{
	return FMath::TruncToFloat(CamPos.Y);
}

TOptional<WorldCoordsType> FEditorCameraPositionModule::GetLocationZ() const
{
	return FMath::TruncToFloat(CamPos.Z);
}

void FEditorCameraPositionModule::SetLocationX(WorldCoordsType Value)
{
	CamPos.X = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::SetLocationY(WorldCoordsType Value)
{
	CamPos.Y = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::SetLocationZ(WorldCoordsType Value)
{
	CamPos.Z = Value;
	RefreshViewportLocation();
}

void FEditorCameraPositionModule::OnCopy()
{
	const FString CopyStr = FString::Printf(TEXT("(%s)"), *CamPos.ToString());
	if (CopyStr.IsEmpty() == false)
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
	if (GCurrentLevelEditingViewportClient)
	{
		const FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();
		CamPos = ViewTransform.GetLocation();
	}
	return true;
}

void FEditorCameraPositionModule::RefreshViewportLocation()
{
	if (GCurrentLevelEditingViewportClient)
	{
		FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();

		UCameraComponent* CamComp = GCurrentLevelEditingViewportClient->GetCameraComponentForView();
		AActor* CamOwner = CamComp ? CamComp->GetOwner() : nullptr;
		if (CamOwner)
		{
			const FVector NewOwnerPos = CamPos - (ViewTransform.GetLocation() - CamOwner->GetActorLocation());
			ViewTransform.SetLocation(CamPos);
			CamOwner->SetActorLocation(NewOwnerPos);
		}
		else
		{
			ViewTransform.SetLocation(CamPos);
		}
	}
}

TSharedRef<SWidget> FEditorCameraPositionModule::GetWidget()
{
	return SNew(SEditorCameraPositionViewportToolBar)
		.Visibility_Raw(this, &FEditorCameraPositionModule::GetToolbarVisibility)
		.X_Raw(this, &FEditorCameraPositionModule::GetLocationX)
		.Y_Raw(this, &FEditorCameraPositionModule::GetLocationY)
		.Z_Raw(this, &FEditorCameraPositionModule::GetLocationZ)
		.OnXChanged_Raw(this, &FEditorCameraPositionModule::SetLocationX)
		.OnYChanged_Raw(this, &FEditorCameraPositionModule::SetLocationY)
		.OnZChanged_Raw(this, &FEditorCameraPositionModule::SetLocationZ)
		.OnCopy_Raw(this, &FEditorCameraPositionModule::OnCopy)
		.OnPaste_Raw(this, &FEditorCameraPositionModule::OnPaste);
}
