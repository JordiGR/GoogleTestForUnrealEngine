#pragma once


#include <functional>
#include <vector>
#include <SharedPointer.h>


class FUICommandInfo;
class FUICommandList;


class CommandsData
{
public:
	using CommandInfoPtr = TSharedPtr<FUICommandInfo>;
	using CommandCallback = std::function<void()>;

	struct CommandData
	{
		CommandInfoPtr commandInfo;
		CommandCallback action;
	};

	using CommandsDataContainer = std::vector<CommandData>;

	void AddOrReplaceCommandAction(CommandInfoPtr command, CommandCallback action);
	TSharedPtr<FUICommandList> GetCommandsList() const;
	CommandsDataContainer GetCommandsData() const { return m_CommandsData; }

private:
	mutable TSharedPtr<FUICommandList> m_CommandsList;
	CommandsDataContainer m_CommandsData;
};

bool operator==(const CommandsData::CommandData& left, const CommandsData::CommandData& right);
