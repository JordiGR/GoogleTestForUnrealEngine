#include "GUIUtilities.h"

#include <UICommandList.h>
#include <Framework/MultiBox/MultiBoxBuilder.h>
#include <AssetEditorToolkit.h>


namespace
{
	TSharedPtr<FUICommandList> CreateCommandsList(const CommandsData::CommandsDataContainer& commandsData);
}


CommandsData::CommandsData(const CommandsDataContainer& commandsData)
	: m_CommandsData(commandsData)
{
}

TSharedPtr<FUICommandList> CommandsData::GetCommandsList() const
{
	if (!m_CommandsList.IsValid())
	{
		m_CommandsList = CreateCommandsList(m_CommandsData);
	}

	return m_CommandsList;
}


void AddMenuCommands(
	IHasMenuExtensibility& module, const CommandsData& commandsData, const FName& menuName,
	const FName& neighbourMenuName, EExtensionHook::Position position)
{
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	const bool newMenu = (neighbourMenuName != FName());

	MenuExtender->AddMenuExtension(
		(newMenu) ? neighbourMenuName : menuName, position, commandsData.GetCommandsList(),
		FMenuExtensionDelegate::CreateLambda(
			[commandsData, menuName, newMenu](FMenuBuilder& builder)
			{
				if (newMenu)
				{
					builder.BeginSection(menuName);
				}

				for (auto commandData : commandsData.GetCommandsData())
				{
					builder.AddMenuEntry(commandData.first);
				}

				if (newMenu)
				{
					builder.EndSection();
				}
			}));

	module.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void AddToolbarButtons(
	IHasToolBarExtensibility& module, const CommandsData& commandsData, const FName& toolbarName,
	const FName& neighbourToolbarName, EExtensionHook::Position position)
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	const bool newToolbar = (neighbourToolbarName != FName());

	ToolbarExtender->AddToolBarExtension(
		(newToolbar) ? neighbourToolbarName : toolbarName, position, commandsData.GetCommandsList(),
		FToolBarExtensionDelegate::CreateLambda(
			[commandsData, toolbarName, newToolbar](FToolBarBuilder& builder)
			{
				if (newToolbar)
				{
					builder.BeginSection(toolbarName);
				}

				for (auto commandData : commandsData.GetCommandsData())
				{
					builder.AddToolBarButton(commandData.first);
				}

				if (newToolbar)
				{
					builder.EndSection();
				}
			}));

	module.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

namespace
{
	TSharedPtr<FUICommandList> CreateCommandsList(const CommandsData::CommandsDataContainer& commandsData)
	{
		auto commandsList = static_cast<TSharedPtr<FUICommandList>>(MakeShareable(new FUICommandList));

		for (const auto& commandData : commandsData)
		{
			commandsList->MapAction(commandData.first, FExecuteAction::CreateLambda(commandData.second),
				FCanExecuteAction());
		}

		return commandsList;
	}
}
