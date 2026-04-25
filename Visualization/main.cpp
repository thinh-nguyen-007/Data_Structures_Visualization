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

    Button btnSave({ 580, 120 }, 22, ButtonIcon::Save);
    Button btnLoad({ 640, 120 }, 22, ButtonIcon::Load);

    // ===== BIND ACTION =====
    btnPlay.setAction(&controller, &LinkedListController::togglePaused);
    btnStepF.setAction(&controller, &LinkedListController::nextStep);
    btnStepB.setAction(&controller, &LinkedListController::undo);
    btnSkipF.setAction(&controller, &LinkedListController::runToEnd);
    btnSkipB.setAction(&controller, &LinkedListController::resetToStart);

    // ===== SPEED =====
    SpeedSlider slider({ 50, 180 }, 250);

    sf::Clock clock;

    // ===== LOOP =====
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // ===== INPUT =====
            input.handleInsert(event, window);

            // ===== BUTTON CLICK =====
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                btnPlay.handleClick(mouse);
                btnStepF.handleClick(mouse);
                btnStepB.handleClick(mouse);
                btnSkipF.handleClick(mouse);
                btnSkipB.handleClick(mouse);

                btnInsert.handleClick(mouse);
                btnDelete.handleClick(mouse);
                btnSearch.handleClick(mouse);

                btnSave.handleClick(mouse);
                btnLoad.handleClick(mouse);

                // ===== INSERT MULTIPLE =====
                if (btnInsert.contains(mouse)) {
                    std::vector<int> vals = parseInput(input.getText());
                    for (int x : vals) controller.push(x);
                    input.clear();
                }

                // ===== DELETE =====
                if (btnDelete.contains(mouse)) {
                    int x;
                    controller.pop(x);
                }

                // ===== SEARCH =====
                if (btnSearch.contains(mouse)) {
                    std::vector<int> vals = parseInput(input.getText());
                    if (!vals.empty())
                        controller.searchVisual(vals[0]);
                }

                // ===== SAVE =====
                if (btnSave.contains(mouse)) {
                    controller.saveToFile("data.txt");
                }

                // ===== LOAD =====
                if (btnLoad.contains(mouse)) {
                    controller.loadFromFile("data.txt");
                }
            }

            // ===== SPEED =====
            slider.handleEvent(event, window);
        }

        float dt = clock.restart().asSeconds();

        // ===== UPDATE =====
        animation.setDelay(1.f / slider.getValue());
        animation.update(dt, controller, window.getSize().x);

        // ===== RENDER =====
        window.clear(sf::Color(30, 30, 45));

        renderer.draw(window, controller, animation, font);
        renderer.drawTable(window, controller, font);

        input.draw(window);

        output.setText(controller.getMessage());
        output.draw(window);

        btnPlay.draw(window);
        btnStepF.draw(window);
        btnStepB.draw(window);
        btnSkipF.draw(window);
        btnSkipB.draw(window);

        btnInsert.draw(window);
        btnDelete.draw(window);
        btnSearch.draw(window);

        btnSave.draw(window);
        btnLoad.draw(window);

        slider.draw(window);

        window.display();
    }

    return 0;
}