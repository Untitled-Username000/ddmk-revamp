module;
#include "../ThirdParty/ImGui/imgui.h"
#include "../ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>


import Core;
import Core_GUI;
import Core_ImGui;

#include "../Core/Macros.h"

import Windows;
import XI;

using namespace Windows;

import GlobalBase;
import GUIBase;

import Actor;
import Arcade;
import Camera;
import Config;
import Global;
import Graphics;
import Input;
import Steam;
import Training;
import Vars;
import Window;

#define debug false



extern bool visibleMain;
extern bool lastVisibleMain;

extern bool visibleDMCRevamp;
extern bool lastVisibleDMCRevamp;




#pragma region DMCMain


void CloseDMCRevamp()
{
	DebugLogFunction();
	visibleDMCRevamp = false;
}

void ToggleDMCRevamp()
{
	DebugLogFunction();
	visibleDMCRevamp = !visibleDMCRevamp;
}



// The actual window
void DMCRevamp()
{
	// FIX: Use visibleDMCRevamp instead of g_showMain
	if (!visibleDMCRevamp)
	{
		return;
	}

	static bool run = false;

	if (!run)
	{
		run = true;

		constexpr float width = 600;
		constexpr float height = 650;

		ImGui::SetNextWindowSize(ImVec2(width, height));

		if constexpr (debug)
		{
			ImGui::SetNextWindowPos
			(
				ImVec2
				(
					((g_renderSize.x - width) / 2),
					100
				)
			);
		}
		else
		{
			// Position next to main window
			ImGui::SetNextWindowPos(ImVec2(620, 0));
		}
	}

	// FIX: Use different window title and visibility variable
	if (ImGui::Begin("DMC Revamp", &visibleDMCRevamp))
	{
		ImGui::Text("");

		// CRITICAL: Add GamepadClose for controller support
		GamepadClose
		(
			visibleDMCRevamp,
			lastVisibleDMCRevamp,
			CloseDMCRevamp
		);

		ImGui::PushItemWidth(150);

		// Your DMC Revamp content here
		ImGui::Text("DMC Revamp Settings");
		ImGui::Text("");

		// Example: Add collapsing headers for different sections
		if (ImGui::CollapsingHeader("Gameplay Tweaks"))
		{
			ImGui::Text("");

			// Add your gameplay settings
			// Example:
			// GUI_Checkbox2("Enable Feature", activeConfig.feature, queuedConfig.feature);

			ImGui::Text("");
		}

		if (ImGui::CollapsingHeader("Move Modifications"))
		{
			ImGui::Text("");

			// Add your move mods here

			ImGui::Text("");
		}

		if (ImGui::CollapsingHeader("Advanced Settings"))
		{
			ImGui::Text("");

			// Add advanced settings

			ImGui::Text("");
		}

		ImGui::PopItemWidth();
		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion



