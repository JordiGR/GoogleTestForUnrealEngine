#pragma once


class IHasMenuExtensibility;
class IHasToolBarExtensibility;


using ExtensionData = std::pair<TSharedPtr<FExtender>, TSharedPtr<const FExtensionBase>>;

template <class TBase, class TDerived>
inline TBase* GetSafeCastToBase(TDerived* object)
{
	return (std::is_base_of<TBase, TDerived>::value) ? static_cast<TBase*>(object) : nullptr;
}

template <class TBase, class TDerived>
inline const TBase* GetSafeCastToBase(const TDerived* object)
{
	return GetSafeCastToBase(const_cast<TDerived>(object));
}

template <class TModule>
inline IHasMenuExtensibility* GetModuleMenuExtensibility(TModule* module)
{
	return GetSafeCastToBase<IHasMenuExtensibility, TModule>(module);
}

template <class TModule>
inline const IHasMenuExtensibility* GetModuleMenuExtensibility(const TModule* module)
{
	return GetModuleMenuExtensibility(const_cast<TModule*>(module));
}

template <class TModule>
inline IHasToolBarExtensibility* GetModuleToolbarExtensibility(TModule* module)
{
	return GetSafeCastToBase<IHasToolBarExtensibility, TModule>(module);
}

template <class TModule>
const IHasToolBarExtensibility* GetModuleToolbarExtensibility(const TModule* module)
{
	return GetModuleToolbarExtensibility(const_cast<TModule*>(module));
}
