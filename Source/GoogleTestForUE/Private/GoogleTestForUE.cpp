// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GoogleTestForUE.h"

#include <memory>

#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable:4668)

	//#undef TEXT
#endif

#include <gtest/gtest.h>

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

#include <CoreMinimal.h>
#include <Framework/Commands/Commands.h>
#include <LevelEditor.h>
#include "GUIUtilities.h"
#include "GoogleTestForUEStyle.h"
#include "GoogleTestOutputLogRedirector.h"


#define LOCTEXT_NAMESPACE "FGoogleTestForUEModule"


namespace
{
	class FGoogleTestForUECommands : public TCommands<FGoogleTestForUECommands>
	{
	public:
		FGoogleTestForUECommands()
			: TCommands<FGoogleTestForUECommands>(
				TEXT("GoogleTestForUE"), NSLOCTEXT("Contexts", "GoogleTestForUE", "GoogleTestForUE Plugin"), NAME_None,
				FGoogleTestForUEStyle::GetStyleSetName())
		{}

		// TCommands<> interface
		void RegisterCommands() override
		{
			UI_COMMAND(PluginAction, "Run Google Test", "Run Google Test for all tests found in the project",
				EUserInterfaceActionType::Button, FInputGesture());
		}

		TSharedPtr<FUICommandInfo> GetCommandInfo() const { return PluginAction; }

	private:
		TSharedPtr<FUICommandInfo> PluginAction;
	};

	const FName kGoogleTestForUEToolbarTabName("GoogleTestForUEToolbar");
	const FName kGoogleTestForUEMenuName("GoogleTestForUEMenu");

	void RunGoogleTests();
}


void FGoogleTestForUEModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin
	// file per-module
	InitialiseGoogleTest();

	FGoogleTestForUEStyle::Initialize();
	FGoogleTestForUEStyle::ReloadTextures();

	FGoogleTestForUECommands::Register();

	auto commandInfo = FGoogleTestForUECommands::Get().GetCommandInfo();
	auto command = CreateCommand(commandInfo, []() { RunGoogleTests(); });
	auto& levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	AddMenuCommand(levelEditorModule, command, commandInfo, kGoogleTestForUEMenuName, "WindowLayout");
	AddToolbarButton(levelEditorModule, command, commandInfo, kGoogleTestForUEToolbarTabName, "Game");
}

void FGoogleTestForUEModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this function before unloading the module.

	FGoogleTestForUEStyle::Shutdown();

	FGoogleTestForUECommands::Unregister();
}

void FGoogleTestForUEModule::InitialiseGoogleTest()
{
	using StringPtr = char*;
	auto argc = 1;
	StringPtr* argv = new StringPtr[argc];
	char* emptyString = "";

	argv[0] = emptyString;

	::testing::InitGoogleTest(&argc, argv);

	delete[] argv;

	RedirectGoogleTestOutput();
}

void FGoogleTestForUEModule::RedirectGoogleTestOutput()
{
	if (m_GoogleTestEventListener == nullptr)
	{
		m_GoogleTestEventListener = new GoogleTestOutputLogRedirector;
		auto& listeners = ::testing::UnitTest::GetInstance()->listeners();

		delete listeners.Release(listeners.default_result_printer());
		listeners.Append(m_GoogleTestEventListener);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGoogleTestForUEModule, GoogleTestForUE)


namespace
{
	void RunGoogleTests()
	{
		RUN_ALL_TESTS();
	}
}
