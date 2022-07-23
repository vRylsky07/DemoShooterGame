// DemoShooter. All right reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DemoShooterEditorTarget : TargetRules
{
	public DemoShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DemoShooter" } );
	}
}
