// main.cpp
#include <SFML/Graphics.hpp>
#include "Design.hpp"
#include "HeapController.hpp"
#include "HeapRenderer.hpp"
#include "AnimationPlayer.hpp"
#include "UI.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "Heap Visualizer");
    sf::View view = window.getDefaultView();
    window.setFramerateLimit(60);
    // assets
    sf::Font font, bolderFont;
    sf::Texture backgroundTex;
    if (!backgroundTex.loadFromFile("assets/bg_trees.png")) return 1;
    if (!font.openFromFile("assets/Roboto.ttf")) return 1;
    if (!bolderFont.openFromFile("assets/RobotoExtraBold.ttf")) return 1;
    // background
    sf::Sprite background(backgroundTex);
    auto bgBounds = background.getLocalBounds();
    background.setScale({ 1200.f / bgBounds.size.x, 800.f / bgBounds.size.y });
    background.setColor(sf::Color::White);
    // core system
    HeapController controller;
    HeapRenderer renderer;
    AnimationPlayer player;
    // timing
    sf::Clock clock;
    // UI
    // Dashboard
    sf::RectangleShape dashboard({ 1200.f, 106.f });
    dashboard.setFillColor({ 176, 226, 255 }); // light sky blue
    dashboard.setOutlineThickness(8.f);
    dashboard.setOutlineColor({ 135, 206, 235 }); // sky blue
    sf::RectangleShape tableBackground({ 1200.f, 200.f });
    tableBackground.setFillColor(PastelColor::Yellow);
    tableBackground.setPosition({ 0.f, 600.f });
    // Input Box
    InputBox insertBox({ 100.f, 40.f }, { 80.f, 36.f }, font, CosmicColor::StellarYellow);
    InputBox deleteBox({ 270.f, 40.f }, { 80.f, 36.f }, font, CosmicColor::StellarYellow);
    InputBox searchBox({ 440.f, 40.f }, { 80.f, 36.f }, font, CosmicColor::StellarYellow);
    // Labels
    Label insertLabel("Insert", bolderFont, DeepColor::Green);
    Label deleteLabel("Delete", bolderFont, DeepColor::Red);
    Label searchLabel("Search", bolderFont, DeepColor::Indigo);
    // Position labels
    insertLabel.matchHead(insertBox.getBox().getGlobalBounds());
    deleteLabel.matchHead(deleteBox.getBox().getGlobalBounds());
    searchLabel.matchHead(searchBox.getBox().getGlobalBounds());
    // Description box
    float descX = 600.f, descY = 20.f, descW = 560.f, descH = 80.f;
    OutputBox descBox({ 600.f, 20.f }, { 560.f, 80.f }, font, { 120, 255, 180 }, "Step Description");
    // mouse drag
    bool dragging = false;
    sf::Vector2i lastMouse;

    // main loop
    while (window.isOpen()) {
        // ================= EVENTS =================
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            // mouse control
            if (event->is<sf::Event::MouseWheelScrolled>()) {
                auto scroll = event->getIf<sf::Event::MouseWheelScrolled>();
                if (scroll->delta > 0) view.zoom(0.9f);   // zoom in
                else view.zoom(1.1f);   // zoom out
            }
            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left) {
                    dragging = true;
                    lastMouse = mouse->position;
                }
            }
            if (event->is<sf::Event::MouseButtonReleased>()) dragging = false;
            if (event->is<sf::Event::MouseMoved>() && dragging) {
                auto move = event->getIf<sf::Event::MouseMoved>();
                sf::Vector2i delta = lastMouse - move->position;
                sf::Vector2f worldDelta = window.mapPixelToCoords(lastMouse) -
                    window.mapPixelToCoords(move->position);
                view.move(worldDelta);
                lastMouse = move->position;
            }
            // keyboard input
            if (!controller.isBusy()){
                insertBox.setFillColor(CosmicColor::StellarYellow);
                deleteBox.setFillColor(CosmicColor::StellarYellow);
                searchBox.setFillColor(CosmicColor::StellarYellow);
                insertBox.handleInsert(*event, window);
                int t = -1;
                if (!controller.getHeap().empty()) t = controller.getHeap().top();
                deleteBox.handleDelete(*event, window, t);
                searchBox.handleInsert(*event, window);
            }
            else {
                insertBox.setFillColor(DeepColor::Gold);
                deleteBox.setFillColor(DeepColor::Gold);
                searchBox.setFillColor(DeepColor::Gold);
            }
            if (event->is<sf::Event::KeyPressed>()) {
                if (controller.isBusy()) continue;
                auto key = event->getIf<sf::Event::KeyPressed>();
                bool ctrl =
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
                // UNDO (Ctrl + Z)
                if (ctrl && key->code == sf::Keyboard::Key::Z) controller.undo();
                // REDO (Ctrl + Y)
                if (ctrl && key->code == sf::Keyboard::Key::Y) controller.redo();
                // INSERT
                if (key->code == sf::Keyboard::Key::Enter && insertBox.isActive()) {
                    std::string txt = insertBox.getText();
                    if (!txt.empty()) {
                        int x = std::stoi(txt);
                        controller.push(x);
                        insertBox.clear();
                    }
                }
                // DELETE (pop)
                if (key->code == sf::Keyboard::Key::Enter && deleteBox.isActive()) {
                    int x;
                    controller.pop(x);
                    deleteBox.clear();
                }
                // SEARCH
                if (key->code == sf::Keyboard::Key::Enter && searchBox.isActive()) {
                    std::string txt = searchBox.getText();
                    if (!txt.empty()) {
                        int x = std::stoi(txt);
                        controller.searchVisual(x);
                        searchBox.clear();
                    }
                }
            }
        }
        // ================= UPDATE =================
        float speed = 3.6f;
        float dt = clock.restart().asSeconds() * speed;
        player.update(dt, controller, window.getSize().x);
        descBox.setText(controller.getMessage());
        // ================= RENDER =================
        window.clear();
        window.draw(background);
        // Heap's binary tree
        window.setView(view);
        renderer.draw(window, controller, player, font);
        // Fixed UI
        window.setView(window.getDefaultView());
        window.draw(dashboard);
        // Heap's table
        window.draw(tableBackground);
        renderer.drawTable(window, controller, font);
        // Header fixed UI
        descBox.draw(window);
        insertBox.draw(window);
        insertLabel.draw(window);
        deleteBox.draw(window);
        deleteLabel.draw(window);
        searchBox.draw(window);
        searchLabel.draw(window);
        window.display();
    }
    return 0;
}