#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SFML/Graphics.hpp>

class Window
{
public:
    Window(const std::string& windowName);

    void Update();

    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
    void EndDraw();

    sf::Vector2u GetCenter() const;
    sf::FloatRect GetViewSpace() const;

    bool IsOpen() const;

private:
    sf::RenderWindow window;
};

#endif /* _WINDOW_H_ */
