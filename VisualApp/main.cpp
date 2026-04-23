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
    // cursor
    sf::Cursor arrow(sf::Cursor::Type::Arrow);
    sf::Cursor hand(sf::Cursor::Type::Hand);
    sf::Cursor move(sf::Cursor::Type::SizeAll);
    sf::Cursor* currentCursor = &arrow;
    window.setMouseCursor(*currentCursor);
    auto setCursor = [&](sf::Cursor* next) {
        if (next != currentCursor) {
            window.setMouseCursor(*next);
            currentCursor = next;
        }
    };
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
    InputBox insertBox({ 250.f, 40.f }, { 80.f, 36.f }, font, CosmicColor::StellarYellow);
    InputBox deleteBox({ 370.f, 40.f }, { 80.f, 36.f }, font, CosmicColor::StellarYellow);
    InputBox searchBox({ 490.f, 40.f }, { 80.f, 36.f }, font, CosmicColor::StellarYellow);
    // Labels
    Label insertLabel("Insert", bolderFont, DeepColor::Green);
    Label deleteLabel("Delete", bolderFont, DeepColor::Red);
    Label searchLabel("Search", bolderFont, DeepColor::Indigo);
    Label buildLabel("Build Max Heap", bolderFont, NeonColor::Ocean, 17, {117.f, 10.f});
    Label sortLabel("Heap Sort", bolderFont, NeonColor::Lava, 18, {117.f, 64.f});
    // Position labels
    insertLabel.matchHead(insertBox.getBox().getGlobalBounds());
    deleteLabel.matchHead(deleteBox.getBox().getGlobalBounds());
    searchLabel.matchHead(searchBox.getBox().getGlobalBounds());
    // Description box
    float descX = 600.f, descY = 20.f, descW = 560.f, descH = 80.f;
    OutputBox descBox({ 600.f, 20.f }, { 560.f, 80.f }, font, { 120, 255, 180 }, "Step Description");
    // Button 
    float buttonY = 570.f;
    Button backButton({ 480.f, buttonY }, 28.f, ButtonIcon::SkipBackward);
    Button undoButton({ 540.f, buttonY }, 28.f, ButtonIcon::StepBackward);
    Button playButton({ 600.f, buttonY }, 28.f, ButtonIcon::Play);
    Button redoButton({ 660.f, buttonY }, 28.f, ButtonIcon::StepForward);
    Button skipButton({ 720.f, buttonY }, 28.f, ButtonIcon::SkipForward);
    Button buildButton({ 100.f, 18.f }, 24.f, ButtonIcon::BuildHeap);
    Button sortButton({ 100.f, 74.f }, 24.f, ButtonIcon::HeapSort);
    std::vector<Button*> buttons = { &undoButton, &redoButton, &playButton, &backButton, &skipButton, &buildButton, &sortButton };
    // assign actions
    undoButton.setAction(&controller, &HeapController::undo);
    redoButton.setAction(&controller, &HeapController::redo);
    backButton.setAction(&controller, &HeapController::resetToStart);
    skipButton.setAction(&controller, &HeapController::runToEnd);
    playButton.setAction(&controller, &HeapController::togglePaused);
    buildButton.setAction(&controller, &HeapController::buildMaxHeapVisual);
    sortButton.setAction(&controller, &HeapController::heapSortVisual);
    // Speed scale
    SpeedSlider speedSystem({ 1080.f, 123.f }, 60.f);
    Label speedText("", bolderFont, DeepColor::Red, 12, {1150.f, 119.f});
    // mouse drag
    bool dragging = false;
    sf::Vector2i lastMouse;

    // main loop
    while (window.isOpen()) {
        // ================= EVENTS =================
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            // zoom
            if (event->is<sf::Event::MouseWheelScrolled>()) {
                auto scroll = event->getIf<sf::Event::MouseWheelScrolled>();
                if (scroll->delta > 0) view.zoom(0.9f);   // zoom in
                else view.zoom(1.1f);   // zoom out
            }
            // speed slider
            speedSystem.handleEvent(*event, window);
            // mouse control
            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f pos = window.mapPixelToCoords(mouse->position);
                    bool clickedUI = false;
                    for (auto* b : buttons) {
                        if (b->isEnabled() && b->contains(pos)) {
                            b->handleClick(pos);
                            clickedUI = true;
                            break; // only one button should trigger
                        }
                    }
                    // ONLY drag if not clicking UI
                    bool inBoard = dashboard.getGlobalBounds().contains(pos) || tableBackground.getGlobalBounds().contains(pos);
                    if (!clickedUI && !inBoard && !speedSystem.contains(pos)) {
                        dragging = true;
                        lastMouse = mouse->position;
                    }
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
            if (!controller.isBusy() || (controller.isPaused() && controller.isAtOperationEnd())){
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
                bool allow = controller.canInteract();
                auto key = event->getIf<sf::Event::KeyPressed>();
                bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
                bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
                // keyboard undo, redo, pause/play
                // UNDO (Ctrl + Z) and BACKtoStart (Ctrl + Shift + Z)
                if (ctrl && key->code == sf::Keyboard::Key::Z && undoButton.isEnabled()) {
                    if (shift) backButton.trigger();
                    else undoButton.trigger();
                }
                // REDO (Ctrl + Y) and SKIPtoEnd (Ctrl + Shift + Y)
                if (ctrl && key->code == sf::Keyboard::Key::Y && redoButton.isEnabled()) {
                    if (shift) skipButton.trigger();
                    else redoButton.trigger();
                }
                // PAUSE/PLAY (Ctrl + P)
                if (ctrl && key->code == sf::Keyboard::Key::P && playButton.isEnabled()) playButton.trigger();
                // BUILD max heap (Ctrl + B) 
                if (ctrl && key->code == sf::Keyboard::Key::B && buildButton.isEnabled()) buildButton.trigger();
                // HEAPSORT (Ctrl + H)
                if (ctrl && key->code == sf::Keyboard::Key::H && sortButton.isEnabled()) sortButton.trigger();
                // INSERT
                if (key->code == sf::Keyboard::Key::Enter && insertBox.isActive() && allow) {
                    std::string txt = insertBox.getText();
                    if (!txt.empty()) {
                        int x = std::stoi(txt);
                        controller.push(x);
                        insertBox.clear();
                    }
                }
                // DELETE (pop)
                if (key->code == sf::Keyboard::Key::Enter && deleteBox.isActive() && allow) {
                    int x;
                    controller.pop(x);
                    deleteBox.clear();
                }
                // SEARCH
                if (key->code == sf::Keyboard::Key::Enter && searchBox.isActive() && allow) {
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
        // animation timeline
        float speed = speedSystem.getValue();
        float dt = clock.restart().asSeconds() * speed;
        player.update(dt, controller, window.getSize().x);
        descBox.setText(controller.getMessage());
        // show speed
        speed = std::round(speed * 100.f) / 100.f;
        speedText.setString(std::to_string(speed).substr(0, 4));
        // button 
        undoButton.setEnabled(controller.isPaused() && !controller.getHeap().empty());
        redoButton.setEnabled(controller.isPaused() && controller.isBusy());
        backButton.setEnabled(undoButton.isEnabled());
        skipButton.setEnabled(redoButton.isEnabled());
        playButton.setEnabled(controller.isBusy());
        playButton.setIcon((controller.isPaused()) ? ButtonIcon::Play : ButtonIcon::Pause);
        buildButton.setEnabled(controller.canInteract() && !controller.getHeap().empty());
        sortButton.setEnabled(controller.canInteract() && !controller.getHeap().empty());
        // cursor
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
        bool clickable = false;
        for (auto* b : buttons) {
            if (b->isEnabled() && b->contains(pos)) {
                clickable = true;
                break;
            }
        }
        if (speedSystem.contains(pos)) clickable = true;
        if (insertBox.getBox().getGlobalBounds().contains(pos) || 
            deleteBox.getBox().getGlobalBounds().contains(pos) ||
            searchBox.getBox().getGlobalBounds().contains(pos)) clickable = true;
        // edit cursor
        if (dragging) setCursor(&move);
        else if (clickable) setCursor(&hand);
        else setCursor(&arrow);
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
        // button
        for (auto* b : buttons) b->draw(window);
        // speed scaler
        speedSystem.draw(window);
        speedText.draw(window);
        // description
        descBox.draw(window);
        // input boxes
        insertBox.draw(window);
        insertLabel.draw(window);
        deleteBox.draw(window);
        deleteLabel.draw(window);
        searchBox.draw(window);
        searchLabel.draw(window);
        buildLabel.draw(window);
        sortLabel.draw(window);
        window.display();
    }
    return 0;
}