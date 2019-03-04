
# GoogleTestForUnrealEngine
Google Test runner plugin for Unreal Engine

# Installation
To integrate this plugin into your Unreal project, follow these steps:

* Clone this repository into the `<your project>\Plugins\GoogleTestForUnreal` folder.
* Create and add at least one new module, of *Type* = **"Developer"**, in your project to write the tests into. This is necessary since this module should only be included in development builds.
	`File MyProject.uproject`:
	```
	"Modules": [
		...
		{
			"Name": "MyProjectTests",
			"Type": "Developer",
			"LoadingPhase": "Default"
		}
	]
	```

* In your tests module \<your tests module\>.Build.cs file
	* Add dependencies to the modules **Core**, **CoreUObject**, **GoogleTestForUnreal** and to your project's module(s) to test:
	* Set Googletest to link as a shared library
	`File MyProjectTests.Build.cs`:
	```
	using UnrealBuildTool;

	public class MyProjectTests : ModuleRules
	{
		public MyProjectTests(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(new string[]{"Core", "CoreUObject"});
			PrivateDependencyModuleNames.AddRange(new string[]{"GoogleTestForUnreal", "MyProject"});
			
			PrivateDefinitions.Add("GTEST_LINKED_AS_SHARED_LIBRARY=1");
		}
	}
	```

* Add a dummy UCLASS to your tests module, in order to make it hot-reloadable.
	`File MakeMyProjectTestsHotReloadable.h`:
	
	```
	#pragma once

	#include "CoreMinimal.h"
	#include "MakeMyProjectTestsHotReloadable.generated.h"

	UCLASS(Const, NotPlaceable, Transient)
	class UMakeMyProjectTestsHotReloadable : public UObject
	{
		GENERATED_BODY()
	};

	```


That's it! You can start writing Googletest tests in your Unreal project.
Happy TDDing!
