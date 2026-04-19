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
	InputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font,
        sf::Color fillColor = sf::Color::White);
	void handleInsert(const sf::Event& event, const sf::RenderWindow& window);
    void handleDelete(const sf::Event& event, const sf::RenderWindow& window, int top);
	std::string getText() const;
	void draw(sf::RenderWindow& window);
	void clear();
	bool isActive() const;
    const sf::RectangleShape& getBox() const;
    void setFillColor(sf::Color color);
};
class OutputBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Text title;
public:
    OutputBox(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, sf::Color color = sf::Color::White, const std::string& titleStr = "");
    void setText(const std::string& str);
    void setTitle(const std::string& title);
    // color and draw
    void setFillColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setTitleColor(sf::Color color);
    void draw(sf::RenderWindow& window);
    // get data
    const sf::RectangleShape& getBox() const;
    sf::FloatRect getBounds() const;
};
struct Label {
    sf::Text text;
    // constructor 
    Label(const std::string& str, const sf::Font& font, sf::Color color = sf::Color::Black,
        unsigned int charSize = 16, sf::Vector2f position = { 0.f, 0.f });
    // edit
    void setPosition(sf::Vector2f p);
    void setColor(sf::Color color);
    void setString(const std::string& s);
    // match with a box
    void matchAbove(const sf::FloatRect& bounds, float offset = 5.f);
    void centerX(const sf::FloatRect& bounds);
    void centerY(const sf::FloatRect& bounds);
    void matchHead(const sf::FloatRect& bounds, float offset = 5.f);
    // draw
    void draw(sf::RenderWindow& window);
};

// Text helpers
void centerText(sf::Text& text, const sf::FloatRect& bounds);