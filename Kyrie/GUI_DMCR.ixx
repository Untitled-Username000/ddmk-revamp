module;
#include "../ThirdParty/ImGui/imgui.h"
#include "../ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>
export module GUI;

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



bool visibleMain = false;
bool lastVisibleMain = false;


bool visibleDMCRevamp = false;
bool lastVisibleDMCRevamp = false;


#pragma region Common

const char* buttonNames[] =
{
	"Nothing",
	"Back",
	"Left Thumb",
	"Right Thumb",
	"Start",
	"Up",
	"Right",
	"Down",
	"Left",
	"Left Shoulder",
	"Right Shoulder",
	"Left Trigger",
	"Right Trigger",
	"Y",
	"B",
	"A",
	"X",
	"Left Stick Up",
	"Left Stick Right",
	"Left Stick Down",
	"Left Stick Left",
	"Right Stick Up",
	"Right Stick Right",
	"Right Stick Down",
	"Right Stick Left",
};

constexpr byte32 buttons[] =
{
	0,
	GAMEPAD::BACK,
	GAMEPAD::LEFT_THUMB,
	GAMEPAD::RIGHT_THUMB,
	GAMEPAD::START,
	GAMEPAD::UP,
	GAMEPAD::RIGHT,
	GAMEPAD::DOWN,
	GAMEPAD::LEFT,
	GAMEPAD::LEFT_SHOULDER,
	GAMEPAD::RIGHT_SHOULDER,
	GAMEPAD::LEFT_TRIGGER,
	GAMEPAD::RIGHT_TRIGGER,
	GAMEPAD::Y,
	GAMEPAD::B,
	GAMEPAD::A,
	GAMEPAD::X,
	GAMEPAD::LEFT_STICK_UP,
	GAMEPAD::LEFT_STICK_RIGHT,
	GAMEPAD::LEFT_STICK_DOWN,
	GAMEPAD::LEFT_STICK_LEFT,
	GAMEPAD::RIGHT_STICK_UP,
	GAMEPAD::RIGHT_STICK_RIGHT,
	GAMEPAD::RIGHT_STICK_DOWN,
	GAMEPAD::RIGHT_STICK_LEFT,
};

static_assert(countof(buttons) == countof(buttonNames));











const char* floorNames[] =
{
	"Floor 1",
	"Berial",
	"Floor 2",
	"Bael",
	"Floor 3",
	"Echidna",
	"Floor 4",
	"Credo",
	"Floor 5",
	"Agnus",
	"Dante",
};

static_assert(countof(floorNames) == 11);
static_assert(countof(floorNames) == FLOOR::COUNT);




const char* playerIndexNames[] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

const char* sceneNames[] =
{
	"SCENE::MAIN",
	"SCENE::MISSION_SELECT",
	"SCENE::CUTSCENE_SELECT",
	"SCENE::MISSION_START",
	"SCENE::CUTSCENE",
	"SCENE::GAME",
	"SCENE::GAME_OVER",
	"SCENE::MISSION_RESULT",
};

const char* eventNames[] =
{
	"EVENT::MAIN",
	"EVENT::PAUSE",
	"EVENT::TELEPORT",
	"EVENT::ITEM",
	"EVENT::CUTSCENE",
};





const char* gameEnumNames[] =
{
	"GAME::NERO_DANTE",
	"GAME::VERGIL",
	"GAME::LADY_TRISH",
};



const char* gameNames[] =
{
	"Nero / Dante",
	"Vergil",
	"Trish / Lady",
};


const char* missionNames[] =
{
	"Mission Select Menu",
	"Mission 1",
	"Mission 2",
	"Mission 3",
	"Mission 4",
	"Mission 5",
	"Mission 6",
	"Mission 7",
	"Mission 8",
	"Mission 9",
	"Mission 10",
	"Mission 11",
	"Mission 12",
	"Mission 13",
	"Mission 14",
	"Mission 15",
	"Mission 16",
	"Mission 17",
	"Mission 18",
	"Mission 19",
	"Mission 20",
	"Bloody Palace",
};

constexpr uint32 missions[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	50,
};







const char* modeEnumNames[] =
{
	"MODE::HUMAN",
	"MODE::DEVIL_HUNTER",
	"MODE::SON_OF_SPARDA",
	"MODE::DANTE_MUST_DIE",
	"MODE::LEGENDARY_DARK_KNIGHT",
};









const char* modeNames[] =
{
	"Human",
	"Devil Hunter",
	"Son of Sparda",
	"Dante Must Die",
	"Legendary Dark Knight",
	"Heaven or Hell",
	"Hell and Hell",
};

constexpr uint32 modes[] =
{
	MODE::HUMAN,
	MODE::DEVIL_HUNTER,
	MODE::SON_OF_SPARDA,
	MODE::DANTE_MUST_DIE,
	MODE::LEGENDARY_DARK_KNIGHT,
	MODE::SON_OF_SPARDA,
	MODE::SON_OF_SPARDA,
};

const char* characterNames[] =
{
	"Dante",
	"Nero",
	"Vergil",
	"Trish",
	"Lady",
};


#pragma endregion





#pragma region Main






void DMCR_Main()
{
	if (!g_showMain)
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
			ImGui::SetNextWindowPos(ImVec2(0, 0));
		}

		//ImGuiIO & io = ImGui::GetIO();
		//io.FontDefault = io.Fonts->Fonts[FONT::MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT::OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT::OVERLAY_8]);
	}

	if
		(
			ImGui::Begin
			(
				DDMK_TITLE_KYRIE,
				&g_showMain
			)
			)
	{
		ImGui::Text("");





		GamepadClose
		(
			visibleMain,
			lastVisibleMain,
			CloseMain
		);





		ImGui::PushItemWidth(150);

		if
			(
				GUI_InputDefault2
				(
					"Global Scale",
					activeConfig.globalScale,
					queuedConfig.globalScale,
					defaultConfig.globalScale,
					0.1f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				)
				)
		{
			UpdateGlobalScale();
		}

		ImGui::PopItemWidth();

		ImGui::Text("");



		ImGui::Text(PATREON_TEXT);
		ImGui::Text("");

		if (GUI_Button("Open Patreon Page"))
		{
			ShellExecuteA
			(
				0,
				"open",
				PATREON_LINK,
				0,
				0,
				SW_SHOW
			);
		}
		ImGui::Text("");



		ActorSection();
		ArcadeSection();
		BarsSection();
		CameraSection();

		if constexpr (debug)
		{
			Debug();
		}

		KeyBindings();
		Overlays();
		SpeedSection();
		System();
		Teleporter();
		TrainingSection();

		ImGui::Text("");

		GUI_Checkbox2
		(
			"Show Credits",
			activeConfig.showCredits,
			queuedConfig.showCredits
		);



		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion


export void GUI_Render()
{
	::GUI::id = 0;



	Welcome();
	Main();
	CreditsWindow();



	MainOverlayWindow();

	Bars();



	HandleKeyBindings
	(
		keyBindings,
		countof(keyBindings)
	);



	{
		auto& keyBinding = characterSwitchControllerKeyBinding;

		keyBinding.Popup();
	}



	HandleSaveTimer(activeConfig.targetFrameRate);



	// static bool enable = true;
	// ImGui::ShowDemoWindow(&enable);
}

export void GUI_Init()
{
	LogFunction();

	BuildFonts();

	UpdateGlobalScale();

	GUI_UpdateStyle();

	Actor_UpdateIndices();
	Arcade_UpdateIndices();
}


