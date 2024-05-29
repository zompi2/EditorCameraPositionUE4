// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"
#include "Widgets/Input/SVectorInputBox.h"

using WorldCoordsType = decltype(FVector::X);

#if (ENGINE_MAJOR_VERSION == 5)
	using VectorInputBoxType = SNumericVectorInputBox<WorldCoordsType>;
	using OnValueChangedDelegateType = SNumericVectorInputBox<WorldCoordsType>::FOnNumericValueChanged;
#else
	using VectorInputBoxType = SVectorInputBox;
	using OnValueChangedDelegateType = FOnFloatValueChanged;
#endif