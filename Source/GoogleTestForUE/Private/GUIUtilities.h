#pragma once


#include <functional>
#include <vector>
#include <MultiBoxExtender.h>


class IHasMenuExtensibility;
class IHasToolBarExtensibility;
class FUICommandInfo;
class FUICommandList;


class CommandsData
{
public:
	using CommandData = std::pair<TSharedPtr<FUICommandInfo>, std::function<void()>>;
	using CommandsDataContainer = std::vector<CommandData>;

	explicit CommandsData(const CommandsDataContainer& commandsData);
	TSharedPtr<FUICommandList> GetCommandsList() const;
	CommandsDataContainer GetCommandsData() const { return m_CommandsData;  }

private:
	mutable TSharedPtr<FUICommandList> m_CommandsList;
	CommandsDataContainer m_CommandsData;
};


void AddMenuCommands(
	IHasMenuExtensibility& module, const CommandsData& commandsData, const FName& menuName,
	const FName& neighbourMenuName = FName(), EExtensionHook::Position position = EExtensionHook::After);
void AddToolbarButtons(
	IHasToolBarExtensibility& module, const CommandsData& commandsData, const FName& toolbarName,
	const FName& neighbourToolbarName = FName(), EExtensionHook::Position position = EExtensionHook::After);
