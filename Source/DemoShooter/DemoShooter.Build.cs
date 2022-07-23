// DemoShooter. All right reserved.

using UnrealBuildTool;

public class DemoShooter : ModuleRules
{
	public DemoShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"Niagara", 
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] {
			"DemoShooter/Public/",
			"DemoShooter/Public/Player", 
			"DemoShooter/Public/Components", 
			"DemoShooter/Public/Dev",
			"DemoShooter/Public/Weapon",
			"DemoShooter/Public/UI",
			"DemoShooter/Public/Animations",
			"DemoShooter/Public/Pickup",
			"DemoShooter/Public/Weapon/Components",
			"DemoShooter/Public/AI",
			"DemoShooter/Public/AI/Decorators"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
