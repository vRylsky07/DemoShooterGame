// DemoShooter. All right reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DemoShooterTarget : TargetRules
{
	public DemoShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DemoShooter" } );
	}
}
