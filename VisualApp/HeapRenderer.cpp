// HeapRenderer.cpp
#include "HeapRenderer.hpp"
#include <cmath>
#include <vector>

void HeapRenderer::draw(sf::RenderWindow& window, HeapController& controller, sf::Font& font) {
    Heap& heap = controller.getHeap();
    int n = heap.getSize();
    std::vector<sf::Vector2f> pos(n);
    float width = window.getSize().x;
    // compute positions
    for (int i = 0; i < n; i++) {
        int level = std::floor(std::log2(i + 1));
        int nodes = 1 << level;
        int idx = i - (nodes - 1);
        float x = width / (nodes + 1) * (idx + 1);
        float y = 150.f + level * 80.f;
        pos[i] = { x, y };
    }
    // draw edges
    for (int i = 1; i < n; i++) {
        int p = (i - 1) / 2;
        sf::Vertex line[] = { sf::Vertex(pos[p]), sf::Vertex(pos[i]) };
        // optional styling
        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
    int a = controller.getHighlightA();
    int b = controller.getHighlightB();
    // draw nodes
    for (int i = 0; i < n; i++) {
        sf::CircleShape c(25.f);
        c.setOrigin({ 25.f, 25.f });
        c.setPosition(pos[i]);
        if (i == a || i == b) c.setFillColor(sf::Color::Red);
        else c.setFillColor(sf::Color::White);
        c.setOutlineColor(sf::Color::Black);
        c.setOutlineThickness(2.f);
        window.draw(c);
        sf::Text t(font);
        t.setString(std::to_string(heap[i]));
        t.setCharacterSize(18);
        t.setFillColor(sf::Color::Black);
        auto bounds = t.getLocalBounds();
        t.setOrigin({ bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f });
        t.setPosition(pos[i]);
        window.draw(t);
    }
}