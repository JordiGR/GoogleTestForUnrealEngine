// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;


public class GoogleTestForUnreal : ModuleRules
{
	public GoogleTestForUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]{Path.Combine(ModuleDirectory, "Public")});
		PrivateIncludePaths.AddRange(new string[]{Path.Combine(ModuleDirectory, "Private")});

		PublicDependencyModuleNames.AddRange(new string[]{"Core"});
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject", "Engine", "Slate", "SlateCore", "UnrealEd", "PropertyEditor", "LevelEditor", "Projects"
			});

		DynamicallyLoadedModuleNames.AddRange(new string[]{});

		SetUpGoogleTest(Target);
	}

	private void SetUpGoogleTest(ReadOnlyTargetRules Target)
	{
		var googleTestMainPath = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "googletest");
		var googleTestPath = Path.Combine(googleTestMainPath, "googletest");
		var googleMockPath = Path.Combine(googleTestMainPath, "googlemock");

		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(googleTestPath, "include"),
				Path.Combine(googleMockPath, "include")
			});
		PrivateIncludePaths.AddRange(new string[]{googleTestPath, googleMockPath});

		PrivateDefinitions.Add("GTEST_CREATE_SHARED_LIBRARY=1");
    }
}
