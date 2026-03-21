// UI.cpp
#include "UI.hpp"

// InputBox
void InputBox::updateText() {
	float padding = 6.f; 
	float boxWidth = box.getSize().x - padding * 2.f;
	float boxHeight = box.getSize().y;
	// Text size scale with box height
	unsigned int charSize = static_cast<unsigned int>(boxHeight * 0.6f);
	text.setCharacterSize(charSize);
	sf::FloatRect bounds = text.getLocalBounds();
	// Shrink if text too long
	while (bounds.size.x > boxWidth && charSize > 10)
	{
		charSize--;
		text.setCharacterSize(charSize);
		bounds = text.getLocalBounds();
	}
	// Horizontal padding
	float x = box.getPosition().x + padding;
	// Vertical centering
	float y = box.getPosition().y +	(boxHeight - bounds.size.y) / 2.f - bounds.position.y;
	text.setPosition({ x, y });
}
InputBox::InputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font)
	: text(font), errorText(font)
{
	// box
	box.setPosition(position);
	box.setSize(size);
	box.setFillColor(sf::Color::White);
	box.setOutlineThickness(2.f);
	box.setOutlineColor(sf::Color::Black);
	// text
	text.setFont(font);
	unsigned int charSize = static_cast<unsigned int> (size.y * 0.6f);
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::Black);
	content = "";
	text.setString(content);
	active = false;
	// error text
	errorText.setFont(font);
	errorText.setCharacterSize(charSize - 5);
	errorText.setFillColor(sf::Color::Red);
	errorText.setString("");
	errorText.setPosition({ box.getPosition().x + 4.f,
		box.getPosition().y + box.getSize().y + 2.f
		});
	updateText();
}
void InputBox::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	if (event.is<sf::Event::MouseButtonPressed>()) 
	{
		auto mouse = event.getIf<sf::Event::MouseButtonPressed>();
		sf::Vector2f pos = window.mapPixelToCoords(mouse->position);
		active = box.getGlobalBounds().contains(pos);
		if (active) box.setOutlineColor(sf::Color::Blue);
		else box.setOutlineColor(sf::Color::Black);
	}
	if (!active) return; 
	if (event.is<sf::Event::TextEntered>())
	{
		auto txt = event.getIf<sf::Event::TextEntered>();
		char c = static_cast<char>(txt->unicode);
		if (c >= '0' && c <= '9') {
			if (content.size() < 9) {
				content += c;
				errorText.setString("");
			}
			else {
				errorText.setString("Limit 9 digits!");
			}
		}
		if (txt->unicode == 8 && !content.empty()) {
			content.pop_back(); // backspace
			errorText.setString("");
		}
		box.setOutlineColor(sf::Color::Blue);
		text.setString(content);
		updateText();
	}
}
std::string InputBox::getText() const {
	return content;
}
void InputBox::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
	window.draw(errorText);
}
void InputBox::clear() {
	content.clear();
	text.setString(content);
	updateText();
}
bool InputBox::isActive() const {
	return active;
}