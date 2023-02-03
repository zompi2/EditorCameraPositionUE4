// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;

public class EditorCameraPosition : ModuleRules
{
	public EditorCameraPosition(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add("EditorCameraPosition/Private");
		PrivateIncludePaths.Add("EditorCameraPosition/Private");

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"InputCore"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Engine",
				"CoreUObject",
                "Slate",
                "SlateCore",
                "UnrealEd",
				"EditorStyle",
				"Projects",
				"LevelEditor",
				"ApplicationCore"
			}
		);
	}
}
