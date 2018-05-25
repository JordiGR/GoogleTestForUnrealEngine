// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GoogleTestForUECommands.h"

#define LOCTEXT_NAMESPACE "FGoogleTestForUEModule"

void FGoogleTestForUECommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Run Google Test", "Run Google Test for all tests found in the project",
		EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
