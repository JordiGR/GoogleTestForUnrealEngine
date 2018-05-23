// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "ModuleManager.h"


class FToolBarBuilder;
class FMenuBuilder;


class FGoogleTestForUEModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginButtonClicked();

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
