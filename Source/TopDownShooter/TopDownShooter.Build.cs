// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownShooter : ModuleRules
{
	public TopDownShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "HeadMountedDisplay", 
	        "NavigationSystem", 
	        "AIModule", 
	        "Niagara", 
	        "EnhancedInput",
	        "UMG"
        });
        
        PrivateDependencyModuleNames.AddRange(new string[]
        {
	        "Slate",
        });
	
        PublicIncludePaths.AddRange(new string[]
        {
	        "TopDownShooter/Public/Core",
	        "TopDownShooter/Public/Interfaces",
	        "TopDownShooter/Public/Components",
	        "TopDownShooter/Public/Weapons",
	        "TopDownShooter/Public/Data",
        });
    }
}
