// main.cpp
#include <SFML/Graphics.hpp>
#include "Heap.hpp"
#include "UI.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "Heap Visualizer");
	sf::Font font;
	sf::Texture backgroundTex;
	if (!backgroundTex.loadFromFile("assets/bg.png")) return 1;
	if (!font.openFromFile("assets/font.ttf")) return 1;
	// background
	sf::Sprite background(backgroundTex);
	auto bgBounds = background.getLocalBounds();
	background.setScale(
		sf::Vector2f(
			1200.f / bgBounds.size.x,
			800.f / bgBounds.size.y
		)
	);
	background.setColor(sf::Color::White);
	// heap
	Heap heap;
	// ui box
	InputBox insertBox({ 100.f, 40.f }, { 120.f, 40.f }, font);
	InputBox deleteBox({ 400.f, 40.f }, { 120.f, 40.f }, font);
	InputBox searchBox({ 700.f, 40.f }, { 120.f, 40.f }, font);

	
	while (window.isOpen())
	{
		while (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) window.close();
			insertBox.handleEvent(*event, window);
			if (event->is<sf::Event::KeyPressed>())
			{
				auto key = event->getIf<sf::Event::KeyPressed>();
				if (key->code == sf::Keyboard::Key::Enter)
				{
					std::string txt = insertBox.getText();
					if (!txt.empty()) {
						int x = std::stoi(txt);
						heap.push(x);
						insertBox.clear();
					}
				}
			}
			

		}
		window.clear();
		window.draw(background);
		insertBox.draw(window);
		deleteBox.draw(window);
		searchBox.draw(window);

		window.display();
	}
}