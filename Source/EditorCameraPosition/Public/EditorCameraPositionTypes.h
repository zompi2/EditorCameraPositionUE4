// Copyright (c) 2026 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorCameraPositionEngineVersionComparsion.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Input/SRotatorInputBox.h"
#include "EditorCameraPositionTypes.generated.h"

UENUM()
enum class EEditorCameraPositionTruncType
{
	NoTrunc,
	TwoDecimals,
	ZeroDecimals
};

DECLARE_DELEGATE(FOnCameraPosOrRotCopyPasteEvent);

#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,0,0)
	using VectorValueType = FVector::FReal;
	using VectorInputBoxType = SNumericVectorInputBox<VectorValueType>;
	using OnVectorValueChangedDelegateType = SNumericVectorInputBox<VectorValueType>::FOnNumericValueChanged;

	using RotatorValueType = FRotator::FReal;
	using RotatorInputBoxType = SNumericRotatorInputBox<RotatorValueType>;
	using OnRotatorValueChangedDelegateType = SNumericRotatorInputBox<RotatorValueType>::FOnNumericValueChanged;
#else
	using VectorValueType = float;
	using VectorInputBoxType = SVectorInputBox;
	using OnVectorValueChangedDelegateType = FOnFloatValueChanged;

	using RotatorValueType = float;
	using RotatorInputBoxType = SRotatorInputBox;
	using OnRotatorValueChangedDelegateType = FOnFloatValueChanged;
#endif