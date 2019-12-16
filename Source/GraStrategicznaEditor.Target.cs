// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GraStrategicznaEditorTarget : TargetRules
{
	public GraStrategicznaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GraStrategiczna" } );

		DefaultBuildSettings = BuildSettingsVersion.V2;
	}
}
