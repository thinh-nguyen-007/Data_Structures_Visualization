#include "Visualizer.h"
#include "raygui.h"

Visualizer::Visualizer() {
    active = false;
    currentStep = 0;
    isPlaying = false;
    speed = 1.0f;
    timer = 0.0f;
}

void Visualizer::Init(Font codeFont, Font descFont) {
    sidepeak.SetFont(codeFont, descFont);
}

void Visualizer::SetResult(const TSPResult& res, const std::vector<std::string>& pseudoCode) {
    result = res;
    sidepeak.SetCode(pseudoCode);
    active = true;
    currentStep = 0;
    isPlaying = false;
    timer = 0.0f;
}

void Visualizer::Update() {
    if (!active || result.events.empty()) return;
    
    if (isPlaying) {
        timer += GetFrameTime();
        if (timer >= 1.0f / speed) {
            timer = 0.0f;
            if (currentStep < (int)result.events.size() - 1) {
                currentStep++;
            } else {
                isPlaying = false; // Stop at the end
            }
        }
    }
}

void Visualizer::DrawUI(int screenWidth, int screenHeight) {
    if (!active || result.events.empty()) return;
    
    const auto& event = result.events[currentStep];
    
    // Construct best path text
    std::string fullDesc = event.description;
    if (!event.bestPath.empty()) {
        fullDesc += "\nBest Path: ";
        for (size_t i = 0; i < event.bestPath.size(); i++) {
            fullDesc += std::to_string(event.bestPath[i]);
            if (i < event.bestPath.size() - 1) fullDesc += "->";
        }
        fullDesc += " (Cost: " + std::to_string(event.bestCost) + ")";
    }
    
    // Draw the sidepeak
    sidepeak.Draw(screenWidth, screenHeight, fullDesc, event.sourceCodeLine);
    
    // Draw playback controls at the bottom center
    int panelWidth = 1000;
    int panelHeight = 120;
    // Shift to the left: let's start at X = 50
    int startX = 50;
    int startY = screenHeight - panelHeight - 20;
    
    GuiPanel({(float)startX, (float)startY, (float)panelWidth, (float)panelHeight}, "Playback Controls");
    
    // Play / Pause Button
    if (GuiButton({(float)startX + 40, (float)startY + 40, 150, 60}, isPlaying ? "Pause" : "Play")) {
        isPlaying = !isPlaying;
    }
    
    // Prev / Next Buttons
    if (GuiButton({(float)startX + 210, (float)startY + 40, 100, 60}, "Prev")) {
        if (currentStep > 0) currentStep--;
        isPlaying = false;
    }
    
    if (GuiButton({(float)startX + 330, (float)startY + 40, 100, 60}, "Next")) {
        if (currentStep < (int)result.events.size() - 1) currentStep++;
        isPlaying = false;
    }
    
    // Speed Slider
    GuiLabel({(float)startX + 480, (float)startY + 55, 80, 30}, "Speed");
    GuiSlider({(float)startX + 550, (float)startY + 55, 250, 30}, "Slow", "Fast", &speed, 0.5f, 10.0f);
    
    // Close Button
    if (GuiButton({(float)startX + 830, (float)startY + 40, 120, 60}, "Stop")) {
        Stop();
    }
}

bool Visualizer::IsActive() const {
    return active;
}

void Visualizer::Stop() {
    active = false;
    isPlaying = false;
}

const VisualizationEvent* Visualizer::GetCurrentEvent() const {
    if (!active || result.events.empty()) {
        return nullptr;
    }
    return &result.events[currentStep];
}
