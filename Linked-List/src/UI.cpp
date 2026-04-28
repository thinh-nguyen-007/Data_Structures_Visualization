#include "UI.hpp"
#include <iostream>
#include <cctype>

// ================= INPUT BOX =================
InputBox::InputBox(sf::Vector2f position, sf::Vector2f size,
                   const sf::Font& font, sf::Color fillColor)
    : text(font), errorText(font)
{
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(fillColor);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);

    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    errorText.setCharacterSize(14);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition({ position.x, position.y + size.y + 5 });

    active = false;
    content = "";
}

void InputBox::updateText() {
    text.setString(content);

    auto bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x,
        bounds.position.y
    });

    text.setPosition({
        box.getPosition().x + 5.f,
        box.getPosition().y + (box.getSize().y - bounds.size.y) / 2.f - 2.f
    });
}

void InputBox::handleInsert(const sf::Event& event, const sf::RenderWindow& window) {

    // ===== TEXT INPUT =====
    if (const auto* txt = event.getIf<sf::Event::TextEntered>()) {
        if (active) {
            if (txt->unicode == 8) {
                if (!content.empty()) content.pop_back();
            }
            else if (txt->unicode < 128 && std::isdigit(txt->unicode)) {
                if (content.size() < 6)
                    content += static_cast<char>(txt->unicode);
                else
                    errorText.setString("Max 6 digits");
            }
            updateText();
        }
    }

    // ===== MOUSE CLICK =====
    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        active = box.getGlobalBounds().contains(pos);
        updateActiveColor();
    }
}

void InputBox::handleDelete(const sf::Event& event, const sf::RenderWindow& window) {
    handleInsert(event, window);
}

void InputBox::handleSearch(const sf::Event& event, const sf::RenderWindow& window) {
    handleInsert(event, window);
}

void InputBox::updateActiveColor() {
    box.setOutlineColor(active ? sf::Color::Blue : sf::Color::Black);
}

void InputBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    window.draw(errorText);
}

void InputBox::clear() {
    content.clear();
    updateText();
}

// ================= OUTPUT BOX =================
OutputBox::OutputBox(sf::Vector2f position, sf::Vector2f size,
                     const sf::Font& font, sf::Color color,
                     const std::string& titleStr)
    : text(font), title(font)
{
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(color);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);

    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    title.setCharacterSize(16);
    title.setFillColor(sf::Color::Black);
    title.setString(titleStr);
}

void OutputBox::setText(const std::string& str) {
    text.setString(str);

    auto bounds = text.getLocalBounds();

    text.setOrigin(
        sf::Vector2f(
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        )
    );

    text.setPosition(
        sf::Vector2f(
            box.getPosition().x + box.getSize().x / 2.f,
            box.getPosition().y + box.getSize().y / 2.f
        )
    );
}

void OutputBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);

    auto b = box.getGlobalBounds();
    title.setPosition({ b.position.x, b.position.y - 20 });

    window.draw(title);
}

// ================= LABEL =================
Label::Label(const std::string& str, const sf::Font& font,
             sf::Color color, unsigned int charSize, sf::Vector2f position)
    : text(font)
{
    text.setString(str);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);
}

void Label::matchAbove(const sf::FloatRect& bounds, float offset) {
    text.setPosition({
        bounds.position.x,
        bounds.position.y - offset - text.getCharacterSize()
    });
}

void Label::centerX(const sf::FloatRect& bounds) {
    auto b = text.getLocalBounds();
    text.setPosition({
        bounds.position.x + bounds.size.x / 2.f - b.size.x / 2.f,
        text.getPosition().y
    });
}

void Label::centerY(const sf::FloatRect& bounds) {
    auto b = text.getLocalBounds();
    text.setPosition({
        text.getPosition().x,
        bounds.position.y + bounds.size.y / 2.f - b.size.y / 2.f
    });
}

void Label::matchHead(const sf::FloatRect& bounds, float offset) {
    text.setPosition({
        bounds.position.x - offset - text.getLocalBounds().size.x,
        bounds.position.y
    });
}

// ================= TEXT HELPER =================
void centerText(sf::Text& text, const sf::FloatRect& bounds) {
    auto b = text.getLocalBounds();

    text.setOrigin({
        b.position.x + b.size.x / 2.f,
        b.position.y + b.size.y / 2.f
    });

    text.setPosition({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
}

// ================= BUTTON =================
void Button::draw(sf::RenderWindow& window) {
    // ===== Circle =====
    sf::CircleShape shape(size);
    shape.setOrigin({ size, size });
    shape.setPosition(center);

    if (!enabled)
        shape.setFillColor(sf::Color(150,150,150));
    else if (selected)
        shape.setFillColor(sf::Color(200,255,200));
    else
        shape.setFillColor(sf::Color(220,220,220));

    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2.f);

    window.draw(shape);

    // ===== Common setup =====
    float iconSize = size * 0.5f;
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Black);

    // ===== Icon =====
    switch (icon) {

    case ButtonIcon::Play:
        window.draw(createEquilateralTriangle(center, iconSize, 90.f, sf::Color::Black));
        break;

    case ButtonIcon::Pause:
        rect.setSize({4.f, iconSize});
        rect.setOrigin({2.f, iconSize / 2});
        rect.setPosition({center.x - 4.f, center.y});
        window.draw(rect);

        rect.setPosition({center.x + 4.f, center.y});
        window.draw(rect);
        break;

    case ButtonIcon::StepForward:
        window.draw(createEquilateralTriangle({center.x - 4.f, center.y}, iconSize * 0.8f, 90.f, sf::Color::Black));

        rect.setSize({3.f, iconSize});
        rect.setOrigin({1.5f, iconSize / 2});
        rect.setPosition({center.x + iconSize * 0.6f, center.y});
        window.draw(rect);
        break;

    case ButtonIcon::StepBackward:
        window.draw(createEquilateralTriangle({center.x + 4.f, center.y}, iconSize * 0.8f, -90.f, sf::Color::Black));

        rect.setSize({3.f, iconSize});
        rect.setOrigin({1.5f, iconSize / 2});
        rect.setPosition({center.x - iconSize * 0.6f, center.y});
        window.draw(rect);
        break;
    case ButtonIcon::SkipForward:
    {
        float s = iconSize * 0.8f;

        window.draw(createEquilateralTriangle(
            {center.x - s * 0.4f, center.y},
            s,
            90.f,
            sf::Color::Black
        ));

        window.draw(createEquilateralTriangle(
            {center.x + s * 0.4f, center.y},
            s,
            90.f,
            sf::Color::Black
        ));
    }
    break;

    case ButtonIcon::SkipBackward:
    {
        float s = iconSize * 0.8f;

        window.draw(createEquilateralTriangle(
            {center.x + s * 0.4f, center.y},
            s,
            -90.f,
            sf::Color::Black
        ));

        window.draw(createEquilateralTriangle(
            {center.x - s * 0.4f, center.y},
            s,
            -90.f,
            sf::Color::Black
        ));
    }
    break;

    case ButtonIcon::Insert:
        rect.setSize({iconSize, 4.f});
        rect.setOrigin({iconSize / 2, 2.f});
        rect.setPosition(center);
        window.draw(rect);

        rect.setSize({4.f, iconSize});
        rect.setOrigin({2.f, iconSize / 2});
        rect.setPosition(center);
        window.draw(rect);
        break;

    case ButtonIcon::Delete:
        rect.setSize({iconSize, 4.f});
        rect.setOrigin({iconSize / 2, 2.f});
        rect.setPosition(center);
        window.draw(rect);
        break;

    case ButtonIcon::Search:
    {
        sf::CircleShape c(iconSize * 0.6f);
        c.setOrigin({iconSize * 0.6f, iconSize * 0.6f});
        c.setPosition({center.x - 3.f, center.y - 3.f});
        c.setFillColor(sf::Color::Transparent);
        c.setOutlineColor(sf::Color::Black);
        c.setOutlineThickness(2.f);
        window.draw(c);

        rect.setSize({iconSize * 0.6f, 3.f});
        rect.setOrigin({0.f, 1.5f});
        rect.setPosition({center.x + 2.f, center.y + 2.f});
        rect.setRotation(sf::degrees(45));
        window.draw(rect);
    }
        break;

    case ButtonIcon::Save:
    {
        sf::RectangleShape box({iconSize, iconSize});
        box.setOrigin({iconSize / 2, iconSize / 2});
        box.setPosition(center);
        box.setFillColor(sf::Color::Black);
        window.draw(box);
    }
        break;

    case ButtonIcon::Load:
    {
        sf::RectangleShape base({iconSize, iconSize / 2});
        base.setOrigin({iconSize / 2, iconSize / 4});
        base.setPosition({center.x, center.y + iconSize / 4});
        base.setFillColor(sf::Color::Black);
        window.draw(base);

        window.draw(createEquilateralTriangle(
            {center.x, center.y - iconSize / 4},
            iconSize * 0.5f,
            0.f,
            sf::Color::Black
        ));
    }
        break;

    default:
        break;
    }
}

// ================= SLIDER =================
SpeedSlider::SpeedSlider(sf::Vector2f pos, float width) {
    bar.setPosition(pos);
    bar.setSize({width, 4.f});
    bar.setFillColor(sf::Color::Black);

    knob.setRadius(8.f);
    knob.setOrigin({8.f,8.f});
    knob.setFillColor(sf::Color::Red);

    updateKnob();
}

void SpeedSlider::updateKnob() {
    float x = bar.getPosition().x + t * bar.getSize().x;
    float y = bar.getPosition().y + bar.getSize().y / 2.f;

    knob.setPosition({x,y});
    value = min + t*(max-min);
}

void SpeedSlider::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {

    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event.is<sf::Event::MouseButtonPressed>()) {
        if (knob.getGlobalBounds().contains(mouse)) {
            dragging = true;
            grabOffsetX = knob.getPosition().x - mouse.x;
        }
    }

    if (event.is<sf::Event::MouseButtonReleased>()) {
        dragging = false;
    }

    if (event.is<sf::Event::MouseMoved>() && dragging) {
        float x = mouse.x + grabOffsetX;

        float left = bar.getPosition().x;
        float right = left + bar.getSize().x;

        x = std::max(left, std::min(x, right));
        t = (x - left) / bar.getSize().x;

        updateKnob();
    }
}