module;
#include "../ThirdParty/ImGui/imgui.h"
#include "../ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>

export module GUI_DMCR;

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

bool visibleMain;
bool lastVisibleMain;
bool visibleDMCRevamp;
bool lastVisibleDMCRevamp;

#pragma region DMCRMain

void CloseDMCRevamp() {
  DebugLogFunction();
  visibleDMCRevamp = false;
}

void ToggleDMCRevamp() {
  DebugLogFunction();
  visibleDMCRevamp = !visibleDMCRevamp;
}

// The actual window
export void DMCRevamp() {
  if (!visibleDMCRevamp) {
    return;
  }

  static bool run = false;
  static bool dummyToggle = false;
  static float dummySliderA = 0.0f;
  static float dummySliderB = 50.0f;

  if (!run) {
    run = true;
    constexpr float width = 360;
    constexpr float height = 220;
    ImGui::SetNextWindowSize(ImVec2(width, height));

    if constexpr (debug) {
      ImGui::SetNextWindowPos(ImVec2(((g_renderSize.x - width) / 2), 100));
    } else {
      ImGui::SetNextWindowPos(ImVec2(620, 0));
    }
  }

  if (ImGui::Begin("DMC Revamp", &visibleDMCRevamp)) {
    GamepadClose(visibleDMCRevamp, lastVisibleDMCRevamp, CloseDMCRevamp);
    ImGui::Text("Dummy window");
    ImGui::Separator();
    ImGui::Checkbox("Dummy Toggle", &dummyToggle);
    ImGui::SliderFloat("Dummy Slider A", &dummySliderA, 0.0f, 1.0f);
    ImGui::SliderFloat("Dummy Slider B", &dummySliderB, 0.0f, 100.0f);
    ImGui::Button("Dummy Button 1");
    ImGui::SameLine();
    ImGui::Button("Dummy Button 2");
  }

  ImGui::End();
}

#pragma endregion