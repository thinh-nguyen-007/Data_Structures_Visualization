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

// ===== TEXT HELPER =====
void centerText(sf::Text& text, const sf::FloatRect& bounds);

// ===== BUTTON =====
enum class ButtonIcon {
    Play,
    Pause,
    StepForward,
    StepBackward,
    SkipForward,
    SkipBackward,
    Insert,
    Delete,
    Search,
    Save,
    Load
};

class Button {
private:
    sf::Vector2f center;
    float size;
    ButtonIcon icon;

    bool enabled = true;
    bool selected = false;

    LinkedListCommand* controller = nullptr;
    void (LinkedListCommand::* action)() = nullptr;

public:
    Button(sf::Vector2f center, float size, ButtonIcon icon)
        : center(center), size(size), icon(icon) {}

    void setAction(LinkedListCommand* ctrl, void (LinkedListCommand::* func)()) {
        controller = ctrl;
        action = func;
    }

    void setEnabled(bool e) { enabled = e; }
    bool isEnabled() const { return enabled; }

    void setSelected(bool s) { selected = s; }
    bool isSelected() const { return selected; }

    void setIcon(ButtonIcon newIcon) { icon = newIcon; }

    void draw(sf::RenderWindow& window);

    void trigger() {
        if (controller && action) {
            (controller->*action)();
        }

        if (controller && controller->isBusy()) {
            if (icon == ButtonIcon::Play) icon = ButtonIcon::Pause;
            else if (icon == ButtonIcon::Pause) icon = ButtonIcon::Play;
        }
    }

    void handleClick(sf::Vector2f mousePos) {
        if (enabled && contains(mousePos)) {
            trigger();
        }
    }

    bool contains(sf::Vector2f p) const {
        return (p.x >= center.x - size && p.x <= center.x + size &&
                p.y >= center.y - size && p.y <= center.y + size);
    }
};

// ===== SPEED SLIDER =====
class SpeedSlider {
    sf::RectangleShape bar;
    sf::CircleShape knob;

    float min = 0.75f;
    float max = 7.5f;
    float value = 1.f;

    bool dragging = false;

    float t = 0.f;
    float grabOffsetX = 0.f;

public:
    SpeedSlider(sf::Vector2f pos, float width);

    void updateKnob();
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    float getValue() const { return value; }

    void draw(sf::RenderWindow& window) {
        window.draw(bar);
        window.draw(knob);
    }

    bool contains(sf::Vector2f pos) const {
        return knob.getGlobalBounds().contains(pos) ||
               bar.getGlobalBounds().contains(pos);
    }
};