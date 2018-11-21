// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;


public class GoogleTestForUE : ModuleRules
{
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string GoogleTestPath
	{
		get { return Path.Combine(ModulePath, "../../ThirdParty/googletest/"); }
	}

	public GoogleTestForUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {"GoogleTestForUE/Public"});
		PrivateIncludePaths.AddRange(new string[] {"GoogleTestForUE/Private"});
		PublicDependencyModuleNames.AddRange(new string[] {"Core"});
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject", "Engine", "Slate", "SlateCore", "UnrealEd", "PropertyEditor", "LevelEditor", "Projects"
			});
		DynamicallyLoadedModuleNames.AddRange(new string[] {});

		SetUpGoogleTest(Target);
	}

	private void SetUpGoogleTest(ReadOnlyTargetRules Target)
	{
		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(GoogleTestPath, "googletest/include"),
				Path.Combine(GoogleTestPath, "googlemock/include")
			});
		PrivateIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(GoogleTestPath, "googletest"),
                Path.Combine(GoogleTestPath, "googlemock")
            });

		PrivateDefinitions.Add("GTEST_CREATE_SHARED_LIBRARY=1");
    }
}
