#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>

// ===== COLOR =====
namespace LLColor {
    inline const sf::Color Node = sf::Color(170, 200, 255);
    inline const sf::Color Highlight = sf::Color(255, 240, 120);
    inline const sf::Color Insert = sf::Color(120, 255, 180);
    inline const sf::Color Remove = sf::Color(255, 120, 120);
}

// ===== PARTICLE COLOR =====
namespace StarColor {
    inline const sf::Color Yellow = sf::Color(255, 235, 160);
    inline const sf::Color Pink = sf::Color(255, 180, 220);
    inline const sf::Color Cyan = sf::Color(170, 240, 255);
    inline const sf::Color Mint = sf::Color(180, 255, 220);

    inline sf::Color random() {
        static const std::vector<sf::Color> palette = {
            Yellow, Pink, Cyan, Mint
        };
        return palette[rand() % palette.size()];
    }
}

namespace DeepColor {
    inline const sf::Color Red = sf::Color(120, 30, 40);
    inline const sf::Color Purple = sf::Color(90, 40, 130);
    inline const sf::Color Blue = sf::Color(40, 110, 140);

    inline sf::Color random() {
        static const std::vector<sf::Color> palette = {
            Red, Purple, Blue
        };
        return palette[rand() % palette.size()];
    }
}

// ===== STAR (particle effect) =====
inline sf::ConvexShape createStar(float outer = 4.f, float inner = 2.f) {
    sf::ConvexShape star;
    star.setPointCount(10);

    for (int i = 0; i < 10; i++) {
        float angle = i * 3.14159f / 5.f - 3.14159f / 2.f;
        float r = (i % 2 == 0) ? outer : inner;
        star.setPoint(i, { std::cos(angle) * r, std::sin(angle) * r });
    }

    return star;
}

// ===== ARROW (NEXT POINTER) =====
inline void drawArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, sf::Color color) {

    sf::Vertex line[] = {
        sf::Vertex{start, color},
        sf::Vertex{end, color}
    };

    float angle = std::atan2(end.y - start.y, end.x - start.x);
    float headLength = 12.f;
    float headAngle = 0.5f;

    sf::Vector2f p1(
        end.x - headLength * std::cos(angle - headAngle),
        end.y - headLength * std::sin(angle - headAngle)
    );

    sf::Vector2f p2(
        end.x - headLength * std::cos(angle + headAngle),
        end.y - headLength * std::sin(angle + headAngle)
    );

    sf::ConvexShape arrowhead;
    arrowhead.setPointCount(3);
    arrowhead.setPoint(0, end);
    arrowhead.setPoint(1, p1);
    arrowhead.setPoint(2, p2);
    arrowhead.setFillColor(color);

    window.draw(line, 2, sf::PrimitiveType::Lines);
    window.draw(arrowhead);
}

// ===== Design Play Button =====
inline sf::ConvexShape createEquilateralTriangle(
    sf::Vector2f center,
    float size,
    float rotationDeg,
    sf::Color color)
{
    sf::ConvexShape tri;
    tri.setPointCount(3);

    float R = size; // bán kính

    float base = rotationDeg * 3.14159265f / 180.f;

    for (int i = 0; i < 3; i++) {
        float angle = base + i * 2.f * 3.14159265f / 3.f;

        float x = center.x + R * std::cos(angle);
        float y = center.y + R * std::sin(angle);

        tri.setPoint(i, { x, y });
    }

    tri.setFillColor(color);

    return tri;
}