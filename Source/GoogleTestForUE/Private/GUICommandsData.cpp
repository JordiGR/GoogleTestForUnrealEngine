#include "GUICommandsData.h"

#include <UICommandList.h>


bool operator==(const CommandsData::CommandData& left, const CommandsData::CommandData& right)
{
	return left.commandInfo.Get() == right.commandInfo.Get();
}

namespace
{
	TSharedPtr<FUICommandList> CreateCommandsList(const CommandsData::CommandsDataContainer& commandsData);
}


void CommandsData::AddOrReplaceCommandAction(CommandInfoPtr command, CommandCallback action)
{
	CommandData newCommandData{command, action};

	auto foundIter = std::find(std::begin(m_CommandsData), std::end(m_CommandsData), newCommandData);

	if (foundIter == std::end(m_CommandsData))
	{
		m_CommandsData.emplace_back(newCommandData);
	}
	else
	{
		(*foundIter) = newCommandData;
	}
}

TSharedPtr<FUICommandList> CommandsData::GetCommandsList() const
{
	if (!m_CommandsList.IsValid())
	{
		m_CommandsList = CreateCommandsList(m_CommandsData);
	}

	return m_CommandsList;
}


namespace
{
	TSharedPtr<FUICommandList> CreateCommandsList(const CommandsData::CommandsDataContainer& commandsData)
	{
		auto commandsList = static_cast<TSharedPtr<FUICommandList>>(MakeShareable(new FUICommandList));

		for (const auto& commandData : commandsData)
		{
			commandsList->MapAction(commandData.commandInfo, FExecuteAction::CreateLambda(commandData.action),
				FCanExecuteAction());
		}

		return commandsList;
	}
}
