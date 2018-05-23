// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GoogleTestForUEToolbarStyle.h"

class FGoogleTestForUECommands : public TCommands<FGoogleTestForUECommands>
{
public:

	FGoogleTestForUECommands()
		: TCommands<FGoogleTestForUECommands>(TEXT("GoogleTestForUE"), NSLOCTEXT("Contexts", "GoogleTestForUE", "GoogleTestForUE Plugin"), NAME_None, FGoogleTestForUEToolbarStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> PluginAction;
};
