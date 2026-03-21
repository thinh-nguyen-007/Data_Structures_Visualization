// main.cpp
#include <SFML/Graphics.hpp>
#include "HeapController.hpp"
#include "HeapRenderer.hpp"
#include "AnimationPlayer.hpp"
#include "UI.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "Heap Visualizer");
    window.setFramerateLimit(60);
    // assets
    sf::Font font;
    sf::Texture backgroundTex;
    if (!backgroundTex.loadFromFile("assets/bg.png")) return 1;
    if (!font.openFromFile("assets/font.ttf")) return 1;
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
    InputBox insertBox({ 100.f, 40.f }, { 120.f, 40.f }, font);
    InputBox deleteBox({ 400.f, 40.f }, { 120.f, 40.f }, font);
    InputBox searchBox({ 700.f, 40.f }, { 120.f, 40.f }, font);
    while (window.isOpen()) {
        // ================= EVENTS =================
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            insertBox.handleEvent(*event, window);
            deleteBox.handleEvent(*event, window);
            searchBox.handleEvent(*event, window);
            // keyboard input
            if (event->is<sf::Event::KeyPressed>()) {
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
            }
        }
        // ================= UPDATE =================
        float maxSpeed = 3.6f;
        float speed = 1.0f + std::log(controller.getHeap().getSize() + 1);
        if (speed > maxSpeed) speed = maxSpeed;
        float dt = clock.restart().asSeconds() * speed;
        player.update(dt, controller);
        // ================= RENDER =================
        window.clear();
        window.draw(background);
        renderer.draw(window, controller, font);
        insertBox.draw(window);
        deleteBox.draw(window);
        searchBox.draw(window);
        window.display();
    }
    return 0;
}