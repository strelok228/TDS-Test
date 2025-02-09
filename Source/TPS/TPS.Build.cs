// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class TPS : ModuleRules
{
	public TPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "TPS" });

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "TPS"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "TPS"));

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysicsCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
