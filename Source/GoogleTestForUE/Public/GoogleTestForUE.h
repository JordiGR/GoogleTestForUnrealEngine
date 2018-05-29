// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include <memory>
#include "CoreMinimal.h"
#include "ModuleManager.h"


class CommandsData;

namespace testing
{
	class TestEventListener;
}


class FGoogleTestForUEModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void InitialiseGoogleTest();
	void RedirectGoogleTestOutput();
	int RunGoogleTests();

	::testing::TestEventListener* m_GoogleTestEventListener = nullptr;
	std::unique_ptr<CommandsData> m_CommandsData;
};
