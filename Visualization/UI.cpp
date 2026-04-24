#include "UI.hpp"
#include <iostream>

// ===== INPUT BOX =====
InputBox::InputBox(sf::Vector2f position, sf::Vector2f size,
                   const sf::Font& font, sf::Color fillColor)
{
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(fillColor);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    errorText.setFont(font);
    errorText.setCharacterSize(14);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(position.x, position.y + size.y + 5);

    active = false;
    content = "";
}

void InputBox::updateText() {
    text.setString(content);

    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.position.x, bounds.position.y);

    text.setPosition(box.getPosition().x + 5.f,
                     box.getPosition().y + (box.getSize().y - bounds.size.y) / 2.f - 2.f);
}

void InputBox::handleInsert(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::TextEntered && active) {
        if (event.text.unicode == 8) { // backspace
            if (!content.empty()) content.pop_back();
        }
        else if (event.text.unicode < 128 && std::isdigit(event.text.unicode)) {
            if (content.size() < 6)
                content += static_cast<char>(event.text.unicode);
            else
                errorText.setString("Max 6 digits");
        }
        updateText();
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        active = box.getGlobalBounds().contains(
            window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        updateActiveColor();
    }
}

void InputBox::handleDelete(const sf::Event& event, const sf::RenderWindow& window) {
    handleInsert(event, window); // same behavior
}

void InputBox::handleSearch(const sf::Event& event, const sf::RenderWindow& window) {
    handleInsert(event, window); // same behavior
}

void InputBox::updateActiveColor() {
    if (active)
        box.setOutlineColor(sf::Color::Blue);
    else
        box.setOutlineColor(sf::Color::Black);
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

// ===== OUTPUT BOX =====
OutputBox::OutputBox(sf::Vector2f position, sf::Vector2f size,
                     const sf::Font& font, sf::Color color,
                     const std::string& titleStr)
{
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(color);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);

    title.setFont(font);
    title.setCharacterSize(16);
    title.setFillColor(sf::Color::Black);
    title.setString(titleStr);
}

void OutputBox::setText(const std::string& str) {
    text.setString(str);

    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.position.x + bounds.size.x / 2.f,
                   bounds.position.y + bounds.size.y / 2.f);

    text.setPosition(
        box.getPosition().x + box.getSize().x / 2.f,
        box.getPosition().y + box.getSize().y / 2.f
    );
}

void OutputBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);

    auto b = box.getGlobalBounds();
    title.setPosition(b.position.x, b.position.y - 20);
    window.draw(title);
}

// ===== LABEL =====
Label::Label(const std::string& str, const sf::Font& font,
             sf::Color color, unsigned int charSize, sf::Vector2f position)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);
}

void Label::matchAbove(const sf::FloatRect& bounds, float offset) {
    text.setPosition(bounds.position.x, bounds.position.y - offset - text.getCharacterSize());
}

void Label::centerX(const sf::FloatRect& bounds) {
    auto b = text.getLocalBounds();
    text.setPosition(bounds.position.x + bounds.size.x / 2.f - b.size.x / 2.f, text.getPosition().y);
}

void Label::centerY(const sf::FloatRect& bounds) {
    auto b = text.getLocalBounds();
    text.setPosition(text.getPosition().x, bounds.position.y + bounds.size.y / 2.f - b.size.y / 2.f);
}

void Label::matchHead(const sf::FloatRect& bounds, float offset) {
    text.setPosition(bounds.position.x - offset - text.getLocalBounds().size.x, bounds.position.y);
}

// ===== TEXT HELPER =====
void centerText(sf::Text& text, const sf::FloatRect& bounds) {
    auto b = text.getLocalBounds();
    text.setOrigin(b.position.x + b.size.x / 2.f,
                   b.position.y + b.size.y / 2.f);
    text.setPosition(bounds.position.x + bounds.size.x / 2.f,
                     bounds.position.y + bounds.size.y / 2.f);
}