#pragma once


#include <Framework/Commands/Commands.h>
#include "GUICommandsData.h"
#include "GUIUtilities.h"


template <class TCommandHolder, class TStyle>
class GUIExtensionHolder
{
public:
	using CommandHolder = TCommandHolder;
	using Style = TStyle;

	GUIExtensionHolder(
		FName menuName, FName neighbourMenuName, EExtensionHook::Position menuPosition,
		FName toolbarName, FName neighbourToolbarName, EExtensionHook::Position toolbarPosition);
	virtual ~GUIExtensionHolder() = 0 {}
	void StartUp(IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility);
	void ShutDown(IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility);

protected:
	void AddOrReplaceCommandAction(CommandsData::CommandInfoPtr command, CommandsData::CommandCallback action);

private:
	struct ExtensionData
	{
		TSharedPtr<FExtender> extender;
		TSharedPtr<const FExtensionBase> extension;
	};

	virtual void RegisterCommandCallbacks(const CommandHolder& commandHolder) = 0;

	void RegisterCommands();
	void UnregisterCommands();
	void AddMenuAndToolbar(IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility);
	void RemoveMenuAndToolbar(IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility);
	void AddMenuCommands(
		IHasMenuExtensibility* module, ExtensionData& menuExtension, const FName& menuName,
		const FName& neighbourMenuName = FName(), EExtensionHook::Position position = EExtensionHook::After);
	void AddToolbarButtons(
		IHasToolBarExtensibility* module, ExtensionData& toolbarExtension, const FName& toolbarName,
		const FName& neighbourToolbarName = FName(), EExtensionHook::Position position = EExtensionHook::After);
	void RemoveMenuCommands(IHasMenuExtensibility* module, ExtensionData& menuExtension);
	void RemoveToolbarButtons(IHasToolBarExtensibility* module, ExtensionData& toolbarExtension);

	bool m_IsExtensionActive = false;
	IHasMenuExtensibility* m_MenuExtensibility = nullptr;
	IHasToolBarExtensibility* m_ToolbarExtensibility = nullptr;

	FName m_MenuName;
	FName m_NeighbourMenuName;
	EExtensionHook::Position m_MenuPosition;

	FName m_ToolbarName;
	FName m_NeighbourToolbarName;
	EExtensionHook::Position m_ToolbarPosition;

	CommandsData m_CommandsData;
	ExtensionData m_MenuExtender;
	ExtensionData m_ToolbarExtender;
};


template <class TCommandHolder, class TStyle>
GUIExtensionHolder<TCommandHolder, TStyle>::GUIExtensionHolder(
	FName menuName, FName neighbourMenuName, EExtensionHook::Position menuPosition,
	FName toolbarName, FName neighbourToolbarName, EExtensionHook::Position toolbarPosition) :
	m_MenuName(menuName),
	m_NeighbourMenuName(neighbourMenuName),
	m_MenuPosition(menuPosition),
	m_ToolbarName(toolbarName),
	m_NeighbourToolbarName(neighbourToolbarName),
	m_ToolbarPosition(toolbarPosition)
{}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::StartUp(
	IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility)
{
	m_MenuExtensibility = menuExtensibility;
	m_ToolbarExtensibility = toolbarExtensibility;

	RegisterCommands();
	AddMenuAndToolbar(menuExtensibility, toolbarExtensibility);

	m_IsExtensionActive = true;
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::ShutDown(
	IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility)
{
	RemoveMenuAndToolbar(menuExtensibility, toolbarExtensibility);
	UnregisterCommands();

	m_IsExtensionActive = false;
}

template <class TCommandHolder, class TStyle>
inline void GUIExtensionHolder<TCommandHolder, TStyle>::AddOrReplaceCommandAction(
	CommandsData::CommandInfoPtr command, CommandsData::CommandCallback action)
{
	m_CommandsData.AddOrReplaceCommandAction(command, action);
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::RegisterCommands()
{
	TCommandHolder::Register();

	const auto commandsHolder = TCommandHolder::Get();

	RegisterCommandCallbacks(commandsHolder);
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::UnregisterCommands()
{
	auto commandsList = m_CommandsData.GetCommandsList();

	if (commandsList.IsUnique())
	{
		TCommandHolder::Unregister();
	}
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::AddMenuAndToolbar(
	IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility)
{
	TStyle::Initialize();
	TStyle::ReloadTextures();

	AddMenuCommands(menuExtensibility, m_MenuExtender, m_MenuName, m_NeighbourMenuName, m_MenuPosition);
	AddToolbarButtons(toolbarExtensibility, m_ToolbarExtender, m_ToolbarName, m_NeighbourToolbarName, m_ToolbarPosition);
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::RemoveMenuAndToolbar(
	IHasMenuExtensibility* menuExtensibility, IHasToolBarExtensibility* toolbarExtensibility)
{
	RemoveMenuCommands(menuExtensibility, m_MenuExtender);
	RemoveToolbarButtons(toolbarExtensibility, m_ToolbarExtender);

	TStyle::Shutdown();
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::AddMenuCommands(
	IHasMenuExtensibility* menuExtensibility, ExtensionData& menuExtension, const FName& menuName,
	const FName& neighbourMenuName, EExtensionHook::Position position)
{
	if (menuExtensibility == nullptr || menuExtension.extender.IsValid())
	{
		return;
	}

	const bool newMenu = (neighbourMenuName != FName());

	menuExtension.extender = MakeShareable(new FExtender());

	menuExtension.extension = menuExtension.extender->AddMenuExtension(
		(newMenu) ? neighbourMenuName : menuName, position, m_CommandsData.GetCommandsList(),
		FMenuExtensionDelegate::CreateLambda(
			[this, menuName, newMenu](FMenuBuilder& builder)
			{
				if (!m_IsExtensionActive)
				{
					return;
				}

				if (newMenu)
				{
					builder.BeginSection(menuName);
				}

				for (auto commandData : m_CommandsData.GetCommandsData())
				{
					builder.AddMenuEntry(commandData.commandInfo);
				}

				if (newMenu)
				{
					builder.EndSection();
				}
			}));

	menuExtensibility->GetMenuExtensibilityManager()->AddExtender(menuExtension.extender);
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::AddToolbarButtons(
	IHasToolBarExtensibility* toolbarExtensibility, ExtensionData& toolbarExtension, const FName& toolbarName,
	const FName& neighbourToolbarName, EExtensionHook::Position position)
{
	if (toolbarExtensibility == nullptr || toolbarExtension.extender.IsValid())
	{
		return;
	}

	const bool newToolbar = (neighbourToolbarName != FName());

	toolbarExtension.extender = MakeShareable(new FExtender);

	toolbarExtension.extension = toolbarExtension.extender->AddToolBarExtension(
		(newToolbar) ? neighbourToolbarName : toolbarName, position, m_CommandsData.GetCommandsList(),
		FToolBarExtensionDelegate::CreateLambda(
			[this, toolbarName, newToolbar](FToolBarBuilder& builder)
			{
				if (!m_IsExtensionActive)
				{
					return;
				}

				if (newToolbar)
				{
					builder.BeginSection(toolbarName);
				}

				for (auto commandData : m_CommandsData.GetCommandsData())
				{
					builder.AddToolBarButton(commandData.commandInfo);
				}

				if (newToolbar)
				{
					builder.EndSection();
				}
			}));

	toolbarExtensibility->GetToolBarExtensibilityManager()->AddExtender(toolbarExtension.extender);
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::RemoveMenuCommands(
	IHasMenuExtensibility* module, ExtensionData& menuExtension)
{
	if (module == nullptr || !menuExtension.extender.IsValid())
	{
		return;
	}

	module->GetMenuExtensibilityManager()->RemoveExtender(menuExtension.extender);
	ensure(menuExtension.extender.IsUnique());
}

template <class TCommandHolder, class TStyle>
void GUIExtensionHolder<TCommandHolder, TStyle>::RemoveToolbarButtons(
	IHasToolBarExtensibility* module, ExtensionData& toolbarExtension)
{
	if (module == nullptr || !toolbarExtension.extender.IsValid())
	{
		return;
	}

	module->GetToolBarExtensibilityManager()->RemoveExtender(toolbarExtension.extender);
	ensure(toolbarExtension.extender.IsUnique());
}
