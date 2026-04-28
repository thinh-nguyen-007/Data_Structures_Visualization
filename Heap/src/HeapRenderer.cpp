// HeapRenderer.cpp
#include "HeapRenderer.hpp"
#include <cmath>
#include <vector>
#include "Design.hpp"

void HeapRenderer::draw(sf::RenderWindow& window, HeapController& controller, AnimationPlayer& anim, const sf::Font& font) {
    float R = 25.f;
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
        sf::Vector2f start = pos[p];
        sf::Vector2f end = pos[i];
        sf::Vector2f diff = end - start;
        float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (length != 0.f) {
            sf::Vector2f unit = diff / length;
            start += unit * R;
            end -= unit * R;
        }
        sf::Vertex line[] = {
            sf::Vertex(start, DeepColor::Purple),
            sf::Vertex(end, DeepColor::Purple) };
        drawArrow(window, line, DeepColor::Purple);
    }
    int a = controller.getHighlightA();
    int b = controller.getHighlightB();
    // draw binary tree nodes
    for (int i = 0; i < n; i++) {
        sf::CircleShape c(R);
        c.setOrigin({ R, R });
        c.setPosition(pos[i]);
        if (i == a || i == b) c.setFillColor(PastelColor::Red);
        else c.setFillColor(CosmicColor::LightPurpleTan);
        c.setOutlineColor(DeepColor::Cyan);
        c.setOutlineThickness(3.f);
        window.draw(c);
        sf::Text t(font);
        t.setString(std::to_string(heap[i]));
        t.setCharacterSize(18);
        t.setFillColor(sf::Color::Black);
        auto bounds = t.getLocalBounds();
        t.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
        t.setPosition(pos[i]);
        window.draw(t);
    }
    // stars effect
    const auto& stars = anim.getStars();
    for (const auto& s : stars) {
        auto star = createStar(10.f, 5.f);
        sf::Vector2f finalPos = s.basePos + sf::Vector2f(s.offsetX, s.offsetY);
        star.setPosition(finalPos);
        float alpha = std::min(255.f, s.lifetime * 255.f + 128.f);
        sf::Color color = s.color;
        color.a = static_cast<std::uint8_t>(alpha);
        star.setFillColor(color);
        star.setRotation(sf::degrees(360.f * (1.f - s.lifetime)));
        window.draw(star);
    }
}
void HeapRenderer::drawTable(sf::RenderWindow& window, HeapController& controller, const sf::Font& font) {
    Heap& heap = controller.getHeap();
    int n = heap.getSize();
    if (n == 0) return;
    // base config
    float baseCellW = 60.f;
    float baseCellH = 60.f;
    float baseValueFont = 18.f;
    float baseIndexFont = 14.f;
    float startY = 620.f;
    // scaling
    float availableWidth = window.getSize().x - 40.f; // margin
    float neededWidth = n * baseCellW;
    float scale = 1.f;
    if (neededWidth > availableWidth) {
        scale = availableWidth / neededWidth;
    }
    // prevent becoming too tiny
    scale = std::max(scale, 0.4f);
    // apply scale
    float cellW = baseCellW * scale;
    float cellH = baseCellH * scale;
    unsigned int valueFontSize = static_cast<unsigned int>(baseValueFont * scale);
    unsigned int indexFontSize = static_cast<unsigned int>(baseIndexFont * scale);
    // center table
    float totalWidth = n * cellW;
    float startX = (window.getSize().x - totalWidth) / 2.f;
    int a = controller.getHighlightA();
    int b = controller.getHighlightB();
    // draw
    for (int i = 0; i < n; i++) {
        float x = startX + i * cellW;
        float y = startY;
        // cell
        sf::RectangleShape cell({ cellW, cellH });
        cell.setPosition({ x, y });
        if (i == a || i == b) cell.setFillColor(PastelColor::Red); // highlighted
        else cell.setFillColor(CosmicColor::LightPurpleTan);
        cell.setOutlineColor(DeepColor::Cyan);
        cell.setOutlineThickness(2.f * scale);
        window.draw(cell);
        // value text
        sf::Text valueText(font);
        valueText.setString(std::to_string(heap[i]));
        valueText.setCharacterSize(valueFontSize);
        valueText.setFillColor(sf::Color::Black);
        auto bounds = valueText.getLocalBounds();
        valueText.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
        valueText.setPosition({ x + cellW / 2.f, y + cellH / 2.f });
        window.draw(valueText);
        // index footer
        sf::Text indexText(font);
        indexText.setString(std::to_string(i));
        indexText.setCharacterSize(indexFontSize);
        indexText.setFillColor(DeepColor::Purple);
        auto ib = indexText.getLocalBounds();
        indexText.setOrigin({ ib.position.x + ib.size.x / 2.f, ib.position.y + ib.size.y / 2.f });
        indexText.setPosition({ x + cellW / 2.f, y + cellH + 12.f * scale });
        window.draw(indexText);
    }
}