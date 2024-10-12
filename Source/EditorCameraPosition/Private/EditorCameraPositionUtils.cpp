// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "EditorCameraPositionUtils.h"
#include "Editor.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"

FVector UEditorCameraPositionUtils::GetEditorCameraPosition()
{
	if (GCurrentLevelEditingViewportClient)
	{
		const FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();
		return ViewTransform.GetLocation();
	}
	return FVector::ZeroVector;
}

void UEditorCameraPositionUtils::SetEditorCameraPosition(const FVector& NewEditorCameraPosition)
{
	if (GCurrentLevelEditingViewportClient)
	{
		FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();

		UCameraComponent* CamComp = GCurrentLevelEditingViewportClient->GetCameraComponentForView();
		AActor* CamOwner = CamComp ? CamComp->GetOwner() : nullptr;
		if (CamOwner)
		{
			const FVector NewOwnerPos = NewEditorCameraPosition - (ViewTransform.GetLocation() - CamOwner->GetActorLocation());
			ViewTransform.SetLocation(NewEditorCameraPosition);
			CamOwner->SetActorLocation(NewOwnerPos);
		}
		else
		{
			ViewTransform.SetLocation(NewEditorCameraPosition);
		}
	}
}

FRotator UEditorCameraPositionUtils::GetEditorCameraRotation()
{
	if (GCurrentLevelEditingViewportClient)
	{
		const FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();
		return ViewTransform.GetRotation();
	}
	return FRotator::ZeroRotator;
}

void UEditorCameraPositionUtils::SetEditorCameraRotation(const FRotator& NewEditorCameraRotation)
{
	if (GCurrentLevelEditingViewportClient)
	{
		FViewportCameraTransform& ViewTransform = GCurrentLevelEditingViewportClient->GetViewTransform();

		UCameraComponent* CamComp = GCurrentLevelEditingViewportClient->GetCameraComponentForView();
		AActor* CamOwner = CamComp ? CamComp->GetOwner() : nullptr;
		if (CamOwner)
		{
			const FRotator NewOwnerRot = NewEditorCameraRotation - (ViewTransform.GetRotation() - CamOwner->GetActorRotation());
			ViewTransform.SetRotation(NewEditorCameraRotation);
			CamOwner->SetActorRotation(NewOwnerRot);
		}
		else
		{
			ViewTransform.SetRotation(NewEditorCameraRotation);
		}
	}
}