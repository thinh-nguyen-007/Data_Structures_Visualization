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
void InputBox::updateActiveColor() {
	if (isActive()) {
		box.setOutlineColor(NeonColor::transparency(NeonColor::Lava, 140));
		box.setOutlineThickness(5.f);
	}
	else {
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(2.f);
	}
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
	errorText.setPosition({ box.getPosition().x + 1.f,
		box.getPosition().y + box.getSize().y + 2.f
		});
	updateText();
}
void InputBox::handleInsert(const sf::Event& event, const sf::RenderWindow& window) {
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
			text.setString("");
			content.clear();
		}
	}
	if (!active) {
		errorText.setString("");
		return;
	}
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
void InputBox::handleDelete(const sf::Event& event, const sf::RenderWindow& window, int top) {
	if (event.is<sf::Event::MouseButtonPressed>())
	{
		auto mouse = event.getIf<sf::Event::MouseButtonPressed>();
		sf::Vector2f pos = window.mapPixelToCoords(mouse->position);
		active = box.getGlobalBounds().contains(pos);
		if (active) {
			box.setOutlineColor(NeonColor::transparency(NeonColor::Lava, 140));
			box.setOutlineThickness(5.f);
			if (top > 0) text.setString("Top: " + std::to_string(top));
			else text.setString("Top: null");
			updateText();
		}
		else {
			box.setOutlineColor(sf::Color::Black);
			box.setOutlineThickness(2.f);
			text.setString("");
		}
	}
	if (!active) {
		errorText.setString("");
		return;
	}
	if (event.is<sf::Event::TextEntered>())
	{
		if (top >= 0) {
			errorText.setString("Enter to pop");
			errorText.setFillColor(CosmicColor::AuroraGreen);
		}
		else {
			text.setString("Nothing");
			errorText.setString("No element to pop!");
			errorText.setFillColor(sf::Color::Red);
		}
		updateText();
	}
}
void InputBox::handleFile(const sf::Event& event, const sf::RenderWindow& window) {
	if (!active) {
		errorText.setString("");
		return;
	}
	// text input
	if (event.is<sf::Event::TextEntered>()) {
		auto txt = event.getIf<sf::Event::TextEntered>();
		// ignore non-ASCII 
		if (txt->unicode > 127) return;
		char c = static_cast<char>(txt->unicode);
		// Backspace
		if (txt->unicode == 8) {
			if (!content.empty()) content.pop_back();
			errorText.setString("");
		}
		// Allowed characters
		else if (std::isalnum(c) || c == '_' || c == '-') {
			if (content.size() < 40) {
				content += c;
				errorText.setString("");
			}
			else {
				errorText.setString("Max 40 chars!");
			}
		}
		// Ignore Enter (handled in main)
		else if (txt->unicode == 13) {
			return;
		}
		// Invalid character
		else {
			errorText.setString("Invalid char!");
		}
		text.setString(content);
		updateText();
	}
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
// OutputBox
OutputBox::OutputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, 
	sf::Color fill, const std::string& titleStr) : text(font), title(font) {
	// box
	box.setPosition(position);
	box.setSize(size);
	box.setFillColor(fill);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);
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
void OutputBox::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
	window.draw(title);
}
// Label
Label::Label(const std::string& str, const sf::Font& font, sf::Color color, unsigned int charSize,
	sf::Vector2f position) : text(font) {
	text.setString(str);
	text.setPosition(position);
	text.setCharacterSize(charSize);
	text.setFillColor(color);
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
// Text helpers
void centerText(sf::Text& text, const sf::FloatRect& bounds) {
	sf::FloatRect textBounds = text.getLocalBounds();
	float x = bounds.position.x + (bounds.size.x - textBounds.size.x) / 2.f;
	float y = bounds.position.y + (bounds.size.y - textBounds.size.y) / 2.f - textBounds.position.y;
	text.setPosition({ x, y });
}
// Button
void Button::draw(sf::RenderWindow& window) {
	switch (icon) {
	case ButtonIcon::Play: {
		sf::Color color = (enabled) ? sf::Color::Green : DeepColor::Green;
		auto tri = createEquilateralTriangle(center, size, 0.f, color);
		window.draw(tri);
		break;
	}
	case ButtonIcon::StepBackward: {
		sf::Color color = enabled ? DeepColor::Indigo : PastelColor::Blue;
		auto tri = createEquilateralTriangle(center, size, 180.f, color);
		window.draw(tri);
		break;
	}
	case ButtonIcon::Pause: {
		float w = size / 4.f;
		float h = size;
		sf::RectangleShape left({ w, h });
		sf::RectangleShape right({ w, h });
		left.setPosition({ center.x - w * 1.5f, center.y - h / 2.f });
		right.setPosition({ center.x + w * 0.5f, center.y - h / 2.f });
		left.setFillColor(sf::Color::Red);
		right.setFillColor(sf::Color::Red);
		window.draw(left);
		window.draw(right);
		break;
	}
	case ButtonIcon::StepForward: {
		sf::Color color = enabled ? DeepColor::Indigo : PastelColor::Blue;
		auto tri = createEquilateralTriangle(center, size, 0.f, color);
		window.draw(tri);
		break;
	}
	case ButtonIcon::SkipForward: {
		sf::Color color = enabled ? DeepColor::Purple : PastelColor::Purple;
		float offset = size * 0.35f;
		// two triangles
		auto left = createEquilateralTriangle(center - sf::Vector2f(offset, 0.f), size, 0.f, color);
		auto right = createEquilateralTriangle(center + sf::Vector2f(offset, 0.f), size, 0.f, color);
		window.draw(left);
		window.draw(right);
		// slim vertical bar (right side)
		float barWidth = size * 0.12f;
		float barHeight = size;
		sf::RectangleShape bar({ barWidth, barHeight });
		bar.setFillColor(color);
		bar.setPosition({ center.x + offset + size * 0.5f, center.y - barHeight / 2.f });
		window.draw(bar);
		break;
	}
	case ButtonIcon::SkipBackward: {
		sf::Color color = enabled ? DeepColor::Purple : PastelColor::Purple;
		float offset = size * 0.35f;
		// two triangles
		auto left = createEquilateralTriangle(center - sf::Vector2f(offset, 0.f), size, 180.f, color);
		auto right = createEquilateralTriangle(center + sf::Vector2f(offset, 0.f), size, 180.f, color);
		window.draw(left);
		window.draw(right);
		// slim vertical bar (left side)
		float barWidth = size * 0.12f;
		float barHeight = size;
		sf::RectangleShape bar({ barWidth, barHeight });
		bar.setFillColor(color);
		bar.setPosition({ center.x - offset - size * 0.5f - barWidth,center.y - barHeight / 2.f });
		window.draw(bar);
		break;
	}
	case ButtonIcon::BuildHeap: {
		auto bars = createBarColumns(center, size, { 0.5f, 0.9f, 0.65f }, { DeepColor::Green, DeepColor::Indigo, DeepColor::Red });
		for (auto& b : bars) window.draw(b);
		break;
	}
	case ButtonIcon::HeapSort: {
		auto bars = createBarColumns(center, size, { 0.4f, 0.7f, 1.0f }, { DeepColor::Red, DeepColor::Orange, DeepColor::Green });
		for (auto& b : bars) window.draw(b);
		break;
	}
	case ButtonIcon::Save: {
		sf::Color color = (enabled && selected) ? PastelColor::Green : DeepColor::Green;
		float h = size;
		float w = size * 0.2f;
		// vertical shaft
		sf::RectangleShape shaft({ w, h * 0.5f });
		shaft.setFillColor(color);
		shaft.setPosition({ center.x - w / 2.f, center.y - h * 0.65f });
		// arrow head (triangle)
		auto tri = createEquilateralTriangle({ center.x, center.y + h * 0.f }, size * 0.6f, 90.f, color);
		// base bar
		sf::RectangleShape base({ size * 1.2f, size * 0.12f });
		base.setFillColor(color);
		base.setPosition({ center.x - size * 0.6f, center.y + h * 0.35f });
		window.draw(shaft);
		window.draw(tri);
		window.draw(base);
		break;
	}
	case ButtonIcon::Load: {
		sf::Color color = (enabled && selected) ? PastelColor::Orange : DeepColor::Orange;
		float h = size;
		float w = size * 0.2f;
		// vertical shaft
		sf::RectangleShape shaft({ w, h * 0.5f });
		shaft.setFillColor(color);
		shaft.setPosition({ center.x - w / 2.f, center.y - h * 0.25f });
		// arrow head (triangle)
		auto tri = createEquilateralTriangle({ center.x, center.y - h * 0.35f }, size * 0.6f, 270.f, color);
		// base bar
		sf::RectangleShape base({ size * 1.2f, size * 0.12f });
		base.setFillColor(color);
		base.setPosition({ center.x - size * 0.6f, center.y + h * 0.35f });
		window.draw(shaft);
		window.draw(tri);
		window.draw(base);
		break;
	}
	}
}
// Speed scaling system
SpeedSlider::SpeedSlider(sf::Vector2f pos, float width) {
	bar.setPosition(pos);
	bar.setSize({ width, 6.f });
	bar.setFillColor(sf::Color::Black);
	knob.setRadius(8.f);
	knob.setOrigin({ 8.f, 8.f });
	knob.setFillColor(sf::Color::Red);
	t = std::log(value / min) / std::log(max / min);
	updateKnob();
}
void SpeedSlider::updateKnob() {
	float x = bar.getPosition().x + t * bar.getSize().x;
	float y = bar.getPosition().y + bar.getSize().y / 2.f;
	knob.setPosition({ x, y });
}
void SpeedSlider::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	auto uiView = window.getDefaultView();
	if (event.is<sf::Event::MouseButtonPressed>()) {
		auto m = event.getIf<sf::Event::MouseButtonPressed>();
		sf::Vector2f pos = window.mapPixelToCoords(m->position, uiView);
		if (knob.getGlobalBounds().contains(pos)) {
			dragging = true;
			grabOffsetX = pos.x - knob.getPosition().x;
		}
		else if (bar.getGlobalBounds().contains(pos)) {
			// click anywhere on bar → jump
			float left = bar.getPosition().x;
			float width = bar.getSize().x;
			t = (pos.x - left) / width;
			t = std::clamp(t, 0.f, 1.f);
			value = min * std::pow(max / min, t);
			updateKnob();
		}
	}
	if (event.is<sf::Event::MouseButtonReleased>()) {
		dragging = false;
	}
	if (event.is<sf::Event::MouseMoved>() && dragging) {
		auto m = event.getIf<sf::Event::MouseMoved>();
		sf::Vector2f pos = window.mapPixelToCoords(m->position, uiView);
		float x = pos.x - grabOffsetX;
		float left = bar.getPosition().x;
		float right = left + bar.getSize().x;
		x = std::clamp(x, left, right);
		float width = bar.getSize().x;
		t = (x - left) / width;
		value = min * std::pow(max / min, t);
		updateKnob();
	}
}