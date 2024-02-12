// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SolidMacros : ModuleRules
{
	public SolidMacros(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				ModuleDirectory,
				ModuleDirectory + "/Logs",
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"PropertyPath"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
