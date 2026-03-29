// UI.cpp
#include "UI.hpp"
#include "Design.hpp"

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
InputBox::InputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, 
	sf::Color fill)
	: text(font), errorText(font)
{
	// box
	box.setPosition(position);
	box.setSize(size);
	box.setFillColor(fill);
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
		if (active) {
			box.setOutlineColor(NeonColor::transparency(NeonColor::Lava, 140));
			box.setOutlineThickness(5.f);
		}
		else {
			box.setOutlineColor(sf::Color::Black);
			box.setOutlineThickness(2.f);
		}
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
		box.setOutlineColor(NeonColor::transparency(NeonColor::Orange, 180));
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
const sf::RectangleShape& InputBox::getBox() const {
	return box;
}
// OutputBox
OutputBox::OutputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, 
	sf::Color fill, const std::string& titleStr) : text(font), title(font) {
	// box
	box.setPosition(position);
	box.setSize(size);
	box.setFillColor(fill);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(1.f);
	// title
	title.setString(titleStr);
	title.setCharacterSize(14);
	title.setFillColor(sf::Color::Black);
	title.setPosition({ position.x + 8.f, position.y + 4.f });
	// text
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Black);
}
void OutputBox::setText(const std::string& str) {
	text.setString(str);
	auto bounds = box.getGlobalBounds();
	auto tb = text.getLocalBounds();
	float x = bounds.position.x + 10.f;
	float y = bounds.position.y + (bounds.size.y - tb.size.y) / 2.f	- tb.position.y;
	text.setPosition({ x, y });
}
void OutputBox::setTitle(const std::string& str) {
	title.setString(str);
}
void OutputBox::setFillColor(sf::Color color) {
	box.setFillColor(color);
}
void OutputBox::setOutlineColor(sf::Color color) {
	box.setOutlineColor(color);
}
void OutputBox::setTextColor(sf::Color color) {
	text.setFillColor(color);
}
void OutputBox::setTitleColor(sf::Color color) {
	title.setFillColor(color);
}
void OutputBox::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
	window.draw(title);
}
const sf::RectangleShape& OutputBox::getBox() const {
	return box;
}
sf::FloatRect OutputBox::getBounds() const {
	return box.getGlobalBounds();
}
// Label
Label::Label(const std::string& str, const sf::Font& font, sf::Color color, unsigned int charSize,
	sf::Vector2f position) : text(font) {
	text.setString(str);
	text.setPosition(position);
	text.setCharacterSize(charSize);
	text.setFillColor(color);
}
// Edit label
void Label::setPosition(sf::Vector2f p) {
	text.setPosition(p);
}
void Label::setColor(sf::Color color) {
	text.setFillColor(color);
}
void Label::setString(const std::string& s) {
	text.setString(s);
}
// match with a box
void Label::matchAbove(const sf::FloatRect& bounds, float offset) {
	text.setPosition({ bounds.position.x, bounds.position.y - text.getCharacterSize() - offset });
}
void Label::centerX(const sf::FloatRect& bounds) {
	sf::FloatRect textBounds = text.getLocalBounds();
	float x = bounds.position.x + (bounds.size.x - textBounds.size.x) / 2.f;
	text.setPosition({ x, text.getPosition().y });
}
void Label::centerY(const sf::FloatRect& bounds) {
	sf::FloatRect textBounds = text.getLocalBounds();
	float y = bounds.position.y + (bounds.size.y - textBounds.size.y) / 2.f - textBounds.position.y;
	text.setPosition({ text.getPosition().x, y });
}
void Label::matchHead(const sf::FloatRect& bounds, float offset) {
	matchAbove(bounds, offset);
	centerX(bounds);
}
// draw label
void Label::draw(sf::RenderWindow& window) {
	window.draw(text);
}
// Text helpers
void centerText(sf::Text& text, const sf::FloatRect& bounds) {
	sf::FloatRect textBounds = text.getLocalBounds();

	float x = bounds.position.x + (bounds.size.x - textBounds.size.x) / 2.f;
	float y = bounds.position.y + (bounds.size.y - textBounds.size.y) / 2.f
		- textBounds.position.y;

	text.setPosition({ x, y });
}