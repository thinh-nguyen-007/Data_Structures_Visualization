#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <string>

#include "../LinkedListCommand/LinkedListCommand.hpp"
#include "LinkedListRenderer.hpp"
#include "Animation.hpp"
#include "UI.hpp"

// ===== helper: parse multiple numbers =====
std::vector<int> parseInput(const std::string& s) {
    std::stringstream ss(s);
    std::vector<int> res;
    int x;
    while (ss >> x) res.push_back(x);
    return res;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Linked List Visualizer PRO");
    window.setFramerateLimit(60);

    // ===== FONT =====
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    // ===== CORE =====
    LinkedListController controller;
    LinkedListRenderer renderer;
    Animation animation;

    // ===== UI =====
    InputBox input({ 50, 40 }, { 250, 45 }, font);
    OutputBox output({ 320, 40 }, { 350, 45 }, font, sf::Color::White, "Message");

    // ===== BUTTONS =====
    Button btnPlay({ 60, 120 }, 22, ButtonIcon::Play);
    Button btnStepF({ 120, 120 }, 22, ButtonIcon::StepForward);
    Button btnStepB({ 180, 120 }, 22, ButtonIcon::StepBackward);
    Button btnSkipF({ 240, 120 }, 22, ButtonIcon::SkipForward);
    Button btnSkipB({ 300, 120 }, 22, ButtonIcon::SkipBackward);

    Button btnInsert({ 380, 120 }, 22, ButtonIcon::Insert);
    Button btnDelete({ 440, 120 }, 22, ButtonIcon::Delete);
    Button btnSearch({ 500, 120 }, 22, ButtonIcon::Search);

    // ===== BIND ACTION =====
    btnPlay.setAction(&controller, &LinkedListController::togglePaused);
    btnStepF.setAction(&controller, &LinkedListController::nextStep);
    btnStepB.setAction(&controller, &LinkedListController::undo);
    btnSkipF.setAction(&controller, &LinkedListController::runToEnd);
    btnSkipB.setAction(&controller, &LinkedListController::resetToStart);
}