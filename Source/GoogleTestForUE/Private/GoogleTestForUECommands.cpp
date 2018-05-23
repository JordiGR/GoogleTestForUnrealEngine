// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GoogleTestForUECommands.h"

#define LOCTEXT_NAMESPACE "FEditorToolbarModule"

void FGoogleTestForUECommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Google Test", "Run Google Test", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
