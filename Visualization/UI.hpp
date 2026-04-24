#pragma once
#include <SFML/Graphics.hpp>
#include "LinkedListCommand.hpp"
#include "Design.hpp"
#include <string>

// ===== INPUT BOX =====
class InputBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Text errorText;
    std::string content;
    bool active;

private:
    void updateText();

public:
    InputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, sf::Color fillColor = sf::Color::White);

    void handleInsert(const sf::Event& event, const sf::RenderWindow& window);
    void handleDelete(const sf::Event& event, const sf::RenderWindow& window);
    void handleSearch(const sf::Event& event, const sf::RenderWindow& window);

    std::string getText() const { return content; }

    bool isActive() const { return active; }
    void setActive(bool t) { active = t; }

    void updateActiveColor();
    const sf::RectangleShape& getBox() const { return box; }

    void setFillColor(sf::Color color) { box.setFillColor(color); }

    void draw(sf::RenderWindow& window);
    void clear();
};

// ===== OUTPUT BOX =====
class OutputBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Text title;

public:
    OutputBox(sf::Vector2f position, sf::Vector2f size,
              const sf::Font& font,
              sf::Color color = sf::Color::White,
              const std::string& titleStr = "");

    void setText(const std::string& str);
    void setTitle(const std::string& str) { title.setString(str); }

    void setFillColor(sf::Color color) { box.setFillColor(color); }
    void setOutlineColor(sf::Color color) { box.setOutlineColor(color); }
    void setTextColor(sf::Color color) { text.setFillColor(color); }
    void setTitleColor(sf::Color color) { title.setFillColor(color); }

    void draw(sf::RenderWindow& window);

    const sf::RectangleShape& getBox() const { return box; }
    sf::FloatRect getBounds() const { return box.getGlobalBounds(); }
};

// ===== LABEL =====
struct Label {
    sf::Text text;

    Label(const std::string& str,
          const sf::Font& font,
          sf::Color color = sf::Color::Black,
          unsigned int charSize = 16,
          sf::Vector2f position = { 0.f, 0.f });

    void setPosition(sf::Vector2f p) { text.setPosition(p); }
    void setColor(sf::Color color) { text.setFillColor(color); }
    void setString(const std::string& s) { text.setString(s); }
    void setSize(unsigned int charSize) { text.setCharacterSize(charSize); }

    void matchAbove(const sf::FloatRect& bounds, float offset = 5.f);
    void centerX(const sf::FloatRect& bounds);
    void centerY(const sf::FloatRect& bounds);
    void matchHead(const sf::FloatRect& bounds, float offset = 5.f);

    void draw(sf::RenderWindow& window) { window.draw(text); }
};