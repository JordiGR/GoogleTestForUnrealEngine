// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <ModuleManager.h>
#include "GUIExtensionHolder.h"
#include "GoogleTestForUEStyle.h"


namespace testing
{
	class TestEventListener;
}


class FGoogleTestForUEModule : public IModuleInterface
{
public:
	FGoogleTestForUEModule();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	class FGoogleTestForUECommands : public TCommands<FGoogleTestForUECommands>
	{
	public:
		FGoogleTestForUECommands();

		// TCommands<> interface
		void RegisterCommands() override;

		//TSharedPtr<FUICommandInfo> GetListCommandInfo() const { return ListGoogleTest; }
		TSharedPtr<FUICommandInfo> GetRunCommandInfo() const { return RunGoogleTest; }

	private:
		//TSharedPtr<FUICommandInfo> ListGoogleTest;
		TSharedPtr<FUICommandInfo> RunGoogleTest;
	};

	class GoogleTestForUEExtensionHolder : public GUIExtensionHolder<FGoogleTestForUECommands, FGoogleTestForUEStyle>
	{
	public:
		using Base = GUIExtensionHolder<FGoogleTestForUECommands, FGoogleTestForUEStyle>;

		GoogleTestForUEExtensionHolder(
			FGoogleTestForUEModule& parentModule,
			FName menuName, FName neighbourMenuName, EExtensionHook::Position menuPosition,
			FName toolbarName, FName neighbourToolbarName, EExtensionHook::Position toolbarPosition);

	private:
		void RegisterCommandCallbacks(const CommandHolder& commandHolder) override;

		FGoogleTestForUEModule& m_ParentModule;
	};

	void InitialiseGoogleTest();
	void RedirectGoogleTestOutput();
	//int ListGoogleTests();
	int RunGoogleTests();

	::testing::TestEventListener* m_GoogleTestEventListener = nullptr;
	GoogleTestForUEExtensionHolder m_GuiExtension;
};
