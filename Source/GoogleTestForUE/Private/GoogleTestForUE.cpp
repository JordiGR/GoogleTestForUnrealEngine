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

#include <SharedPointer.h>
#include <UICommandList.h>
#include <LevelEditor.h>	//jjj
#include <Framework/MultiBox/MultiBoxBuilder.h>
#include "GoogleTestForUEToolbarStyle.h"
#include "GoogleTestForUECommands.h"
#include "LogStream.h"


namespace
{
	const FName GoogleTestForUEToolbarTabName("GoogleTestForUEToolbar");

	void InitialiseGoogleTest();
	void AddMenuCommand(
		TSharedPtr<class FUICommandList> commands, IHasMenuExtensibility& module,
		TSharedPtr<FUICommandInfo> commandInfo, const FName& menuName, EExtensionHook::Position position);
	void AddToolbarButton(
		TSharedPtr<class FUICommandList> commands, IHasToolBarExtensibility& module,
		TSharedPtr<FUICommandInfo> commandInfo, const FName& toolbarName, EExtensionHook::Position position);
	/*jjj	void AddMenuExtension(FMenuBuilder& Builder);
	void AddToolbarExtension(FToolBarBuilder& Builder);
	*/
}


#define LOCTEXT_NAMESPACE "FGoogleTestForUEModule"


void FGoogleTestForUEModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	InitialiseGoogleTest();

	FGoogleTestForUEToolbarStyle::Initialize();
	FGoogleTestForUEToolbarStyle::ReloadTextures();

	FGoogleTestForUECommands::Register();

	auto commandInfo = FGoogleTestForUECommands::Get().PluginAction;

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		commandInfo,
		FExecuteAction::CreateRaw(this, &FGoogleTestForUEModule::PluginButtonClicked),
		FCanExecuteAction());

	auto& levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	AddMenuCommand(PluginCommands, levelEditorModule, commandInfo, "WindowLayout", EExtensionHook::After);
	AddToolbarButton(PluginCommands, levelEditorModule, commandInfo, "Game", EExtensionHook::After);
}

void FGoogleTestForUEModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FGoogleTestForUEToolbarStyle::Shutdown();

	FGoogleTestForUECommands::Unregister();
}

void FGoogleTestForUEModule::PluginButtonClicked()
{
	LogStream stream;

	auto previousStream = std::cout.rdbuf(&stream);

	printf("********** PrintF redirected\n");
	std::cout << "********** cout redirected" << std::endl;

	RUN_ALL_TESTS();

	std::cout << std::endl;
	std::cout.rdbuf(previousStream);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGoogleTestForUEModule, GoogleTestForUE)


namespace
{
	void InitialiseGoogleTest()
	{
		using StringPtr = char*;
		auto argc = 1;
		StringPtr* argv = new StringPtr[argc];
		char* emptyString = "";

		argv[0] = emptyString;

		::testing::InitGoogleTest(&argc, argv);

		delete[] argv;
	}

	void AddMenuCommand(
		TSharedPtr<class FUICommandList> commands, IHasMenuExtensibility& module,
		TSharedPtr<FUICommandInfo> commandInfo, const FName& menuName, EExtensionHook::Position position)
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

		MenuExtender->AddMenuExtension(
			menuName, position, commands,
			//jjj	FMenuExtensionDelegate::CreateRaw(this, &FGoogleTestForUEModule::AddMenuExtension));
			FMenuExtensionDelegate::CreateLambda(
				[commandInfo](FMenuBuilder& builder)
				{
					builder.AddMenuEntry(commandInfo);
				}));

		module.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	void AddToolbarButton(
		TSharedPtr<class FUICommandList> commands, IHasToolBarExtensibility& module,
		TSharedPtr<FUICommandInfo> commandInfo, const FName& toolbarName, EExtensionHook::Position position)
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension(
			toolbarName, position, commands,
			//jjj	FToolBarExtensionDelegate::CreateRaw(this, &FGoogleTestForUEModule::AddToolbarExtension));
			FToolBarExtensionDelegate::CreateLambda(
				[commandInfo](FToolBarBuilder& builder)
				{
					builder.AddToolBarButton(commandInfo);
				}));

		module.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	/*jjj	void AddMenuExtension(FMenuBuilder& Builder)
	{
		Builder.AddMenuEntry(FGoogleTestForUECommands::Get().PluginAction);
	}

	void AddToolbarExtension(FToolBarBuilder& Builder)
	{
		Builder.AddToolBarButton(FGoogleTestForUECommands::Get().PluginAction);
	}
	*/
}
