// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "ModuleManager.h"


class FToolBarBuilder;
class FMenuBuilder;

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

	::testing::TestEventListener* m_GoogleTestEventListener = nullptr;
};
