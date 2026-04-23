// Design.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>
// COLOR TABLE
namespace CosmicColor {
    inline const sf::Color StellarYellow = sf::Color(255, 240, 120);
    inline const sf::Color LightPurpleTan = sf::Color(220, 200, 210);
    inline const sf::Color AuroraGreen = sf::Color(120, 255, 180);
    inline const sf::Color AuroraPurple = sf::Color(180, 120, 255);
    inline const sf::Color AuroraTeal = sf::Color(100, 255, 220);
}
namespace PastelColor {
    inline const sf::Color Red = sf::Color(255, 160, 160);
    inline const sf::Color Orange = sf::Color(255, 200, 150);
    inline const sf::Color Yellow = sf::Color(255, 240, 170);
    inline const sf::Color Green = sf::Color(170, 255, 170);
    inline const sf::Color Cyan = sf::Color(170, 240, 255);
    inline const sf::Color Blue = sf::Color(170, 200, 255);
    inline const sf::Color Purple = sf::Color(210, 170, 255);
    inline const sf::Color Pink = sf::Color(255, 180, 220);
    inline const sf::Color CyanLime = sf::Color(180, 255, 200); // custom vibe
    inline sf::Color random() {
        static const std::vector<sf::Color> palette = { Red, Orange, Yellow, Green, Cyan, Blue, Purple, Pink, CyanLime };
        return palette[rand() % palette.size()];
    }
}
namespace StarColor {
    inline const sf::Color Gold = sf::Color(255, 235, 160);
    inline const sf::Color Peach = sf::Color(255, 200, 170);
    inline const sf::Color Pink = sf::Color(255, 180, 220);
    inline const sf::Color Lavender = sf::Color(210, 190, 255);
    inline const sf::Color Mint = sf::Color(180, 255, 220);
    inline const sf::Color Cyan = sf::Color(170, 240, 255);
    inline const sf::Color LimeAccent = sf::Color(200, 255, 170); // rare accent
    inline sf::Color random() {
        static const std::vector<sf::Color> palette = { Gold, Peach, Pink, Lavender, Mint, Cyan, LimeAccent };
        return palette[rand() % palette.size()];
    }
}
namespace DeepColor {
    inline const sf::Color Red = sf::Color(120, 30, 40);
    inline const sf::Color Orange = sf::Color(140, 70, 30);
    inline const sf::Color Gold = sf::Color(150, 120, 40);
    inline const sf::Color Green = sf::Color(30, 120, 70);
    inline const sf::Color Teal = sf::Color(30, 120, 110);
    inline const sf::Color Cyan = sf::Color(40, 110, 140);
    inline const sf::Color Indigo = sf::Color(70, 60, 140);
    inline const sf::Color Purple = sf::Color(90, 40, 130);
    inline sf::Color random() {
        static const std::vector<sf::Color> palette = { Red, Orange, Gold, Green, Teal, Cyan, Indigo, Purple };
        return palette[rand() % palette.size()];
    }
}
namespace NeonColor {
    inline const sf::Color Green = sf::Color(57, 255, 20);
    inline const sf::Color Blue = sf::Color(77, 77, 255);
    inline const sf::Color Pink = sf::Color(255, 20, 147);
    inline const sf::Color Cyan = sf::Color(0, 255, 255);
    inline const sf::Color Orange = sf::Color(255, 95, 31);
    inline const sf::Color Purple = sf::Color(180, 0, 255);
    inline const sf::Color Lava = sf::Color(255, 30, 0);    // glowing lava red
    inline const sf::Color Ocean = sf::Color(0, 120, 255);   // brighter, electric blue
    inline const sf::Color Radioactive = sf::Color(102, 255, 0);   // radioactive green
    inline sf::Color transparency(sf::Color target, uint8_t a) {
        sf::Color color = target;
        color.a = a;
        return color;
    }
}
// create star
inline sf::ConvexShape createStar(float outer = 4.f, float inner = 2.f) {
    sf::ConvexShape star;
    star.setPointCount(10);
    for (int i = 0; i < 10; i++) {
        float angle = i * 3.14159f / 5.f - 3.14159f / 2.f;
        float r = (i % 2 == 0) ? outer : inner;
        star.setPoint(i, { std::cos(angle) * r, std::sin(angle) * r });
    }
    star.setOrigin({ 0.f, 0.f }); // optional
    return star;
}
// draw arow
inline void drawArrow(sf::RenderWindow& window, sf::Vertex line[2], sf::Color color) {
    auto& start = line[0].position;
    auto& end = line[1].position;
    // calculate head
    float angle = std::atan2(end.y - start.y, end.x - start.x);
    float headLength = 15.f;
    float headAngle = 0.5f; // Radians
    sf::Vector2f p1(end.x - headLength * std::cos(angle - headAngle),
        end.y - headLength * std::sin(angle - headAngle));
    sf::Vector2f p2(end.x - headLength * std::cos(angle + headAngle),
        end.y - headLength * std::sin(angle + headAngle));
    // shape
    sf::ConvexShape arrowhead;
    arrowhead.setPointCount(3);
    arrowhead.setPoint(0, end);
    arrowhead.setPoint(1, p1);
    arrowhead.setPoint(2, p2);
    arrowhead.setFillColor(color);

    // 4. Draw
    window.draw(line, 2, sf::PrimitiveType::Lines);
    window.draw(arrowhead);
}
// create Equilateral Triangle
inline sf::ConvexShape createEquilateralTriangle(sf::Vector2f center, float side, float rotationDeg, sf::Color color)
{
    sf::ConvexShape tri;
    tri.setPointCount(3);
    float R = side / std::sqrt(3.f); // circumradius
    float baseAngle = rotationDeg * 3.14159265f / 180.f;
    for (int i = 0; i < 3; i++) {
        float angle = baseAngle + i * 2.f * 3.14159265f / 3.f;
        float x = center.x + R * std::cos(angle);
        float y = center.y + R * std::sin(angle);
        tri.setPoint(i, { x, y });
    }
    tri.setFillColor(color);
    return tri;
}
