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

extern bool visibleMain;
extern bool lastVisibleMain;

extern bool visibleDMCRevamp;
extern bool lastVisibleDMCRevamp;

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
  // FIX: Use visibleDMCRevamp instead of g_showMain
    if (!visibleDMCRevamp) {
        return;
    }

    static bool run = false;

    if (!run) {
        run = true;

    constexpr float width = 600;
    constexpr float height = 650;

    ImGui::SetNextWindowSize(ImVec2(width, height));

    if constexpr (debug) {
        ImGui::SetNextWindowPos(ImVec2(((g_renderSize.x - width) / 2), 100));
    } else {
      // Position next to main window
        ImGui::SetNextWindowPos(ImVec2(620, 0));
    }
}

  // FIX: Use different window title and visibility variable
    if (ImGui::Begin("DMC Revamp", &visibleDMCRevamp)) {
    ImGui::Text("");

    // CRITICAL: Add GamepadClose for controller support
    GamepadClose(visibleDMCRevamp, lastVisibleDMCRevamp, CloseDMCRevamp);

    ImGui::PushItemWidth(150);

    ImGui::Text("DMC Revamp Settings");
    ImGui::Separator();
    ImGui::Text("");

    static bool enablePracticeMode = false;
    static bool infiniteGauge = false;
    static int selectedStyle = 0;
    static float enemySpeedScale = 1.0f;
    static int maxEnemyCount = 3;
    static char presetName[64] = "Default";

    const char *styles[]{"Balanced", "Aggressive", "Defensive", "Arcade"};
    constexpr int styleCount = IM_ARRAYSIZE(styles);
    if (selectedStyle < 0) {
        selectedStyle = 0;
    } else if (selectedStyle >= styleCount) {
        selectedStyle = styleCount - 1;
    }

    if (ImGui::CollapsingHeader("Gameplay Tweaks",
                                ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Checkbox("Enable Practice Mode", &enablePracticeMode);
    ImGui::Checkbox("Infinite Gauge", &infiniteGauge);
    ImGui::SliderFloat("Enemy Speed Scale", &enemySpeedScale, 0.25f, 2.0f,"%.2fx");
    ImGui::SliderInt("Max Enemy Count", &maxEnemyCount, 1, 10);
    ImGui::Text("");
    }

    if (ImGui::CollapsingHeader("Move Modifications",
                                ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Combo("Combat Style", &selectedStyle, styles, styleCount);
    ImGui::InputText("Preset Name", presetName, IM_ARRAYSIZE(presetName));

    if (ImGui::Button("Apply Preset")) {
        ImGui::OpenPopup("Preset Applied");
    }

        if (ImGui::BeginPopupModal("Preset Applied", nullptr,
                                ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Preset '%s' applied.", presetName);
        ImGui::Text("");
        if (ImGui::Button("OK", ImVec2(120, 0))) {
        ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

        ImGui::Text("");
    }

    if (ImGui::CollapsingHeader("Advanced Settings")) {
        ImGui::Text("Window visible: %s", visibleDMCRevamp ? "Yes" : "No");
        ImGui::Text("Current style: %s", styles[selectedStyle]);
        ImGui::Text("Use this section for debug or expert options.");
        ImGui::Text("");
    }

    ImGui::PopItemWidth();
    ImGui::Text("");
    }

    ImGui::End();
}

#pragma endregion
