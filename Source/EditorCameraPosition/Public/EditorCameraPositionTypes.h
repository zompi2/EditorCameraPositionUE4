// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"
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

#if (ENGINE_MAJOR_VERSION == 5)
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