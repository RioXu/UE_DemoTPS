// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPSTutorial : ModuleRules
{
	public TPSTutorial(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				"ALSV4_CPP/Public"
			}
		);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "ALSV4_CPP", "HeadMountedDisplay" });
	}
}
