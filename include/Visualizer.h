#pragma once
#include "Algorithms.h"
#include "Graph.h"
#include "Sidepeak.h"
#include "raylib.h"
#include <vector>
#include <string>

class Visualizer {
public:
    Visualizer();
    
    void Init();
    
    // Feed the algorithm result into the visualizer
    void SetResult(const TSPResult& res, const std::vector<std::string>& pseudoCode);
    
    void Update();
    void DrawUI(int screenWidth, int screenHeight);
    
    const VisualizationEvent* GetCurrentEvent() const;
    
    bool IsActive() const;
    void Stop();

private:
    TSPResult result;
    bool active;
    
    // Playback state
    int currentStep;
    bool isPlaying;
    float speed; // events per second
    float timer;
    
    Sidepeak sidepeak;
};
