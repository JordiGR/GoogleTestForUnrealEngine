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


#define LOCTEXT_NAMESPACE "FGoogleTestForUnrealModule"


namespace
{
	class FGoogleTestForUnrealCommands : public TCommands<FGoogleTestForUnrealCommands>
	{
	public:
		FGoogleTestForUnrealCommands()
			: TCommands<FGoogleTestForUnrealCommands>(
				TEXT("GoogleTestForUnreal"), NSLOCTEXT("Contexts", "GoogleTestForUnreal", "GoogleTestForUnreal Plugin"), NAME_None,
				FGoogleTestForUnrealStyle::GetStyleSetName())
		{}

		// TCommands<> interface
		void RegisterCommands() override
		{
			UI_COMMAND(RunGoogleTest, "Run Google Test", "Run Google Test for all tests found in the project",
				EUserInterfaceActionType::Button, FInputGesture());
		}

		TSharedPtr<FUICommandInfo> GetCommandInfo() const { return RunGoogleTest; }

	private:
		TSharedPtr<FUICommandInfo> RunGoogleTest;
	};

	const FName kGoogleTestForUnrealToolbarTabName("GoogleTestForUnrealToolbar");
	const FName kGoogleTestForUnrealMenuName("GoogleTestForUnrealMenu");

	void RunGoogleTests();
}


void FGoogleTestForUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin
	// file per-module
	InitialiseGoogleTest();

	FGoogleTestForUnrealStyle::Initialize();
	FGoogleTestForUnrealStyle::ReloadTextures();

	FGoogleTestForUnrealCommands::Register();

	auto commandInfo = FGoogleTestForUnrealCommands::Get().GetCommandInfo();
	auto command = CreateCommand(commandInfo, []() { RunGoogleTests(); });
	auto& levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	AddMenuCommand(levelEditorModule, command, commandInfo, kGoogleTestForUnrealMenuName, "WindowLayout");
	AddToolbarButton(levelEditorModule, command, commandInfo, kGoogleTestForUnrealToolbarTabName, "Game");
}

void FGoogleTestForUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this function before unloading the module.

	FGoogleTestForUnrealStyle::Shutdown();

	FGoogleTestForUnrealCommands::Unregister();
}

void FGoogleTestForUnrealModule::InitialiseGoogleTest()
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

void FGoogleTestForUnrealModule::RedirectGoogleTestOutput()
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
	
IMPLEMENT_MODULE(FGoogleTestForUnrealModule, GoogleTestForUnreal)


namespace
{
	void RunGoogleTests()
	{
		::testing::UnitTest::GetInstance()->RemoveDuplicateTests();

		RUN_ALL_TESTS();
	}
}
