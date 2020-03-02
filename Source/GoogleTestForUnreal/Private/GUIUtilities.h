#pragma once


#include <functional>
#include <Framework/Multibox/MultiBoxExtender.h>


class IHasMenuExtensibility;
class IHasToolBarExtensibility;
class FUICommandInfo;
class FUICommandList;


TSharedPtr<FUICommandList> CreateCommand(TSharedPtr<FUICommandInfo> commandInfo, std::function<void()> callback);
void AddMenuCommand(
	IHasMenuExtensibility& module,
	TSharedPtr<FUICommandList> commands, TSharedPtr<FUICommandInfo> commandInfo, const FName& menuName,
	const FName& neighbourMenuName, EExtensionHook::Position position = EExtensionHook::After);
void AddToolbarButton(
	IHasToolBarExtensibility& module,
	TSharedPtr<FUICommandList> commands, TSharedPtr<FUICommandInfo> commandInfo, const FName& toolbarName,
	const FName& neighbourToolbarName, EExtensionHook::Position position = EExtensionHook::After);
