// UI.hpp
#include <SFML/Graphics.hpp>
#include <string>
class InputBox {
private:
	sf::RectangleShape box;
	sf::Text text;
	sf::Text errorText; // limit characters
	std::string content;
	bool active;
private:
	void updateText();
public:
	InputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font);
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
	std::string getText() const;
	void draw(sf::RenderWindow& window);
	void clear();
};