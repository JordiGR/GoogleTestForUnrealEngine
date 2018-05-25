#include "GUIUtilities.h"

#include <UICommandList.h>
#include <Framework/MultiBox/MultiBoxBuilder.h>
#include <AssetEditorToolkit.h>


TSharedPtr<FUICommandList> CreateCommand(TSharedPtr<FUICommandInfo> commandInfo, std::function<void()> callback)
{
	TSharedPtr<FUICommandList> command = MakeShareable(new FUICommandList);

	command->MapAction(commandInfo, FExecuteAction::CreateLambda(callback), FCanExecuteAction());

	return command;
}

void AddMenuCommand(
	IHasMenuExtensibility& module,
	TSharedPtr<FUICommandList> commands, TSharedPtr<FUICommandInfo> commandInfo, const FName& menuName,
	const FName& neighbourMenuName, EExtensionHook::Position position)
{
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

	MenuExtender->AddMenuExtension(
		neighbourMenuName, position, commands,
		FMenuExtensionDelegate::CreateLambda(
			[commandInfo, menuName](FMenuBuilder& builder)
			{
				builder.BeginSection(menuName);
				builder.AddMenuEntry(commandInfo);
				builder.EndSection();
			}));

	module.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void AddToolbarButton(
	IHasToolBarExtensibility& module,
	TSharedPtr<FUICommandList> commands, TSharedPtr<FUICommandInfo> commandInfo, const FName& toolbarName,
	const FName& neighbourToolbarName, EExtensionHook::Position position)
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension(
		neighbourToolbarName, position, commands,
		FToolBarExtensionDelegate::CreateLambda(
			[commandInfo, toolbarName](FToolBarBuilder& builder)
			{
				builder.BeginSection(toolbarName);
				builder.AddToolBarButton(commandInfo);
				builder.EndSection();
			}));

	module.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}
