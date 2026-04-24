#include "LinkedListRenderer.hpp"
#include "Design.hpp"
#include <vector>

void LinkedListRenderer::draw(sf::RenderWindow& window,
                              LinkedListCommand& controller,
                              Animation& anim,
                              const sf::Font& font)
{
    float R = 25.f;
    float spacing = 90.f;

    LinkedList& list = controller.getList();
    int n = list.getSize();

    float width = window.getSize().x;
    float startX = width / 2.f - (n - 1) * spacing / 2.f;
    float y = 300.f;

    std::vector<sf::Vector2f> pos(n);

    // ===== compute positions =====
    for (int i = 0; i < n; i++) {
        pos[i] = { startX + i * spacing, y };
    }

    // ===== draw arrows (next pointer) =====
    for (int i = 0; i < n - 1; i++) {
        sf::Vector2f start = pos[i];
        sf::Vector2f end = pos[i + 1];

        start.x += R;
        end.x -= R;

        drawArrow(window, start, end, sf::Color::Black);
    }

    int h = controller.getHighlightIndex();

    // ===== draw nodes =====
    for (int i = 0; i < n; i++) {
        sf::CircleShape c(R);
        c.setOrigin({ R, R });
        c.setPosition(pos[i]);

        if (i == h)
            c.setFillColor(LLColor::Highlight);
        else
            c.setFillColor(LLColor::Node);

        c.setOutlineColor(sf::Color::Black);
        c.setOutlineThickness(3.f);

        window.draw(c);

        // ===== value =====
        sf::Text t(font);
        t.setString(std::to_string(list.get(i)));
        t.setCharacterSize(18);
        t.setFillColor(sf::Color::Black);

        auto bounds = t.getLocalBounds();
        t.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        });

        t.setPosition(pos[i]);
        window.draw(t);
    }

    // ===== draw particles =====
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

    // ===== draw message =====
    sf::Text msg(font);
    msg.setString(controller.getMessage());
    msg.setCharacterSize(20);
    msg.setFillColor(sf::Color::White);

    msg.setPosition({ 20.f, 20.f });

    window.draw(msg);
}

// ===== optional table view =====
void LinkedListRenderer::drawTable(sf::RenderWindow& window,
                                   LinkedListCommand& controller,
                                   const sf::Font& font)
{
    LinkedList& list = controller.getList();
    int n = list.getSize();

    if (n == 0) return;

    float cellW = 60.f;
    float cellH = 60.f;

    float startY = 600.f;
    float startX = (window.getSize().x - n * cellW) / 2.f;

    int h = controller.getHighlightIndex();

    for (int i = 0; i < n; i++) {
        float x = startX + i * cellW;
        float y = startY;

        // ===== cell =====
        sf::RectangleShape cell({ cellW, cellH });
        cell.setPosition({ x, y });

        if (i == h)
            cell.setFillColor(LLColor::Highlight);
        else
            cell.setFillColor(LLColor::Node);

        cell.setOutlineColor(sf::Color::Black);
        cell.setOutlineThickness(2.f);

        window.draw(cell);

        // ===== value =====
        sf::Text valueText(font);
        valueText.setString(std::to_string(list.get(i)));
        valueText.setCharacterSize(18);
        valueText.setFillColor(sf::Color::Black);

        auto vb = valueText.getLocalBounds();
        valueText.setOrigin({
            vb.position.x + vb.size.x / 2.f,
            vb.position.y + vb.size.y / 2.f
        });

        valueText.setPosition({
            x + cellW / 2.f,
            y + cellH / 2.f
        });

        window.draw(valueText);

        // ===== index =====
        sf::Text indexText(font);
        indexText.setString(std::to_string(i));
        indexText.setCharacterSize(14);
        indexText.setFillColor(sf::Color::White);

        auto ib = indexText.getLocalBounds();
        indexText.setOrigin({
            ib.position.x + ib.size.x / 2.f,
            ib.position.y + ib.size.y / 2.f
        });

        indexText.setPosition({
            x + cellW / 2.f,
            y + cellH + 12.f
        });

        window.draw(indexText);
    }
}