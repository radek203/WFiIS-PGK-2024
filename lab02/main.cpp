#include "SFML/Graphics.hpp"
#include "custom_font.h"
#include <numeric>
#include <cmath>
#include <iostream>
#include <memory>

std::shared_ptr<sf::Font> font;
float brightness = 1.0f;
std::string str = "";
float clickedAlfa = 0.0f;
float clickedBeta = 0.0f;
int clickedRhomb = 0;

class suwak : public sf::Drawable {
public:
    mutable sf::Vector2f leftTop;
    mutable sf::Vector2f rightTop;
    mutable sf::Vector2f rightBottom;
    mutable sf::Vector2f leftBottom;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void suwak::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    sf::RectangleShape rectangleBorder;

    rectangleBorder.setSize(sf::Vector2f(80, target.getSize().y - 160));
    rectangleBorder.setFillColor(sf::Color::Transparent);
    rectangleBorder.setOutlineColor(sf::Color(128,128,128));
    rectangleBorder.setOutlineThickness(2.0f);
    rectangleBorder.setPosition(sf::Vector2f(target.getSize().x - 120, 20));
    target.draw(rectangleBorder);

    leftTop = sf::Vector2f(target.getSize().x - 120, 20);
    rightTop = sf::Vector2f(target.getSize().x - 40, 20);
    rightBottom = sf::Vector2f(target.getSize().x - 40, target.getSize().y - 140);
    leftBottom = sf::Vector2f(target.getSize().x - 120, target.getSize().y - 140);

    sf::Vertex rectangle[] = {
            sf::Vertex(leftTop, sf::Color::Black),
            sf::Vertex(rightTop, sf::Color::Black),
            sf::Vertex(rightBottom, sf::Color::White),
            sf::Vertex(leftBottom, sf::Color::White),
            sf::Vertex(leftTop, sf::Color::White)
    };

    target.draw(rectangle, 5, sf::Quads, states);

    double offset = (target.getSize().y - 160) * (1-brightness);

    sf::VertexArray triangle(sf::Triangles, 3);

    triangle[0].position = sf::Vector2f(leftBottom.x - 20, leftBottom.y - 10 - offset);
    triangle[1].position = sf::Vector2f(leftBottom.x - 20, leftBottom.y + 10 - offset);
    triangle[2].position = sf::Vector2f(leftBottom.x , leftBottom.y - offset);

    triangle[0].color = sf::Color::Black;
    triangle[1].color = sf::Color::Black;
    triangle[2].color = sf::Color::Black;

    target.draw(triangle, states);

    triangle[0].position = sf::Vector2f(rightBottom.x + 20, rightBottom.y - 10 - offset);
    triangle[1].position = sf::Vector2f(rightBottom.x + 20, rightBottom.y + 10 - offset);
    triangle[2].position = sf::Vector2f(rightBottom.x , rightBottom.y - offset);

    triangle[0].color = sf::Color::Black;
    triangle[1].color = sf::Color::Black;
    triangle[2].color = sf::Color::Black;

    target.draw(triangle, states);
}

suwak suuuwak;

class hexagon : public sf::Drawable {
public:
    sf::Vector2f left_top, right_bottom, center;
    sf::Vector2f p[6]; // Kolejność punktów opisana w pliku PDF do laboratorium.
public:
    void Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom);
    void Draw_Border(sf::RenderTarget& target, sf::RenderStates states, sf::String name, sf::Color fill) const;
    bool rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const;
private:
    float d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const;
};

//Trochę matematyki jeszcze nikomu nie zaszkodziło. Więc dwie kolejne metody to czysta matematyka.
float hexagon::d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const {
    float A = p0.y - p1.y;
    float B = p1.x - p0.x;
    float C = p0.x * (p1.y - p0.y) - p0.y * (p1.x - p0.x);

    return 2 * ((A * p.x + B * p.y + C) / sqrt(A * A + B * B)) / sqrt(3.0f);
}

bool hexagon::rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const {
    float L = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    sf::Vector2f p3(0.5f * (p0.x - p1.x) + 0.5f * sqrt(3.0f) * (p1.y - p0.y) + p0.x, 0.5f * sqrt(3.0f) * (p0.x - p1.x) - 0.5f * (p1.y - p0.y) + p0.y);

    beta = -d_coefficient(p0, p1, p) / L;
    alpha = d_coefficient(p0, p3, p) / L;

    if ((alpha > 1.0f) || (beta > 1.0f) || (alpha < 0.0f) || (beta < 0.0f)) return false; else return true;
}

void hexagon::Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom) {
    left_top = _left_top;
    right_bottom = _right_bottom;
    float a = ((right_bottom.y - left_top.y) / 2.0f + 0.5f) - 20.0f;
    center = left_top + sf::Vector2f((right_bottom.x - left_top.x) / 2.0f + 0.5f, (right_bottom.y - left_top.y) / 2.0f + 0.5f + 10);

    p[0] = center - sf::Vector2f( 0.0f, a);
    p[1] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[2] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
    p[3] = center + sf::Vector2f(0.0f, a);
    p[4] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[5] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
}

void hexagon::Draw_Border(sf::RenderTarget& target, sf::RenderStates states, sf::String name, sf::Color fill) const {
    sf::RectangleShape rectangle;

    rectangle.setSize(sf::Vector2f(right_bottom.x - left_top.x - 20, right_bottom.y - left_top.y - 20));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color(128,128,128));
    rectangle.setOutlineThickness(2.0f);
    rectangle.setPosition(sf::Vector2f(left_top.x + 10, left_top.y + 20));
    target.draw(rectangle);

    sf::ConvexShape convex;
    convex.setPointCount(6);
    for (int i = 0; i < 6; i++) {
        convex.setPoint(i, p[i]);
    }
    convex.setFillColor(fill);
    convex.setOutlineColor(sf::Color::Black);
    convex.setOutlineThickness(2);
    target.draw(convex);

    sf::Text text;
    text.setString(name);
    text.setFont(*font);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color(111, 111, 111));

    text.setPosition(sf::Vector2f(left_top.x + 13, left_top.y + 21));
    target.draw(text);
}

class hexagon_RGB : public hexagon {
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void hexagon_RGB::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Text text;

    text.setFont(*font);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color(111, 111, 111));
    text.setString("R");
    text.setPosition(p[0].x - 34, p[0].y - 14);
    target.draw(text);

    text.setString("G");
    text.setPosition(p[2].x - 18, p[2].y - 14);
    target.draw(text);

    text.setString("B");
    text.setPosition(p[4].x + 8, p[4].y - 14);
    target.draw(text);

	sf::Vertex rectangle[] = {
        sf::Vertex(p[2], sf::Color(0, 255*brightness, 0)),
        sf::Vertex(p[3], sf::Color(0, 255*brightness, 255*brightness)),
        sf::Vertex(center, sf::Color(255*brightness, 255*brightness, 255*brightness)),
        sf::Vertex(p[1], sf::Color(255*brightness, 255*brightness, 0))
    };

    sf::Vertex rectangle2[] = {
        sf::Vertex(p[4], sf::Color(0, 0, 255*brightness)),
        sf::Vertex(p[5], sf::Color(255*brightness, 0, 255*brightness)),
        sf::Vertex(center, sf::Color(255*brightness, 255*brightness, 255*brightness)),
        sf::Vertex(p[3], sf::Color(0, 255*brightness, 255*brightness))
    };

    sf::Vertex rectangle3[] = {
        sf::Vertex(p[0], sf::Color(255*brightness, 0, 0)),
        sf::Vertex(p[1], sf::Color(255*brightness, 255*brightness, 0)),
        sf::Vertex(center, sf::Color(255*brightness, 255*brightness, 255*brightness)),
        sf::Vertex(p[5], sf::Color(255*brightness, 0, 255*brightness))
    };

    target.draw(rectangle, 4, sf::Quads, states);
    target.draw(rectangle2, 4, sf::Quads, states);
    target.draw(rectangle3, 4, sf::Quads, states);

    Draw_Border(target, states, "RGB", sf::Color::Transparent);
}

sf::Color RGB_to_CMY(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) {
    return sf::Color((1 - (r / 255)) * 255, (1 - (g / 255))*255, (1 - (b / 255))*255, 255*brightness);
}

class hexagon_CMY : public hexagon {
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void hexagon_CMY::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Text text;

    text.setFont(*font);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color(111, 111, 111));
    text.setString("C");
    text.setPosition(p[0].x - 34, p[0].y - 14);
    target.draw(text);

    text.setString("M");
    text.setPosition(p[2].x - 18, p[2].y - 14);
    target.draw(text);

    text.setString("Y");
    text.setPosition(p[4].x + 8, p[4].y - 14);
    target.draw(text);

	sf::Vertex rectangle[] = {
		sf::Vertex(p[2], RGB_to_CMY(0, 255, 0)),
		sf::Vertex(p[3], RGB_to_CMY(0, 255, 255)),
		sf::Vertex(center, RGB_to_CMY(255, 255, 255)),
		sf::Vertex(p[1], RGB_to_CMY(255, 255, 0))
	};

	sf::Vertex rectangle2[] = {
		sf::Vertex(p[4], RGB_to_CMY(0, 0, 255)),
		sf::Vertex(p[5], RGB_to_CMY(255, 0, 255)),
		sf::Vertex(center, RGB_to_CMY(255, 255, 255)),
		sf::Vertex(p[3], RGB_to_CMY(0, 255, 255))
	};

	sf::Vertex rectangle3[] = {
		sf::Vertex(p[0], RGB_to_CMY(255, 0, 0)),
		sf::Vertex(p[1], RGB_to_CMY(255, 255, 0)),
		sf::Vertex(center, RGB_to_CMY(255, 255, 255)),
		sf::Vertex(p[5], RGB_to_CMY(255, 0, 255))
	};

	target.draw(rectangle, 4, sf::Quads, states);
	target.draw(rectangle2, 4, sf::Quads, states);
	target.draw(rectangle3, 4, sf::Quads, states);

    Draw_Border(target, states, "CMY", sf::Color::Transparent);
}

double Hue_2_RGB(double v1, double v2, double vH ) {
    if ( vH < 0 ) vH += 1;
    if ( vH > 1 ) vH -= 1;
    if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
    if ( ( 2 * vH ) < 1 ) return ( v2 );
    if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0 / 3.0 ) - vH ) * 6 );
    return ( v1 );
 }

sf::Color HSL_TO_RGB(float h, float s, float l) {
    if ( s == 0 ) {
        return sf::Color(l * 255, l * 255, l * 255);
    }
    double var_2;
    double var_1;
    if ( l < 0.5 ) {
        var_2 = l * ( 1 + s );
    }
    else {
        var_2 = ( l + s ) - ( s * l );
    }

    var_1 = 2 * l - var_2;

    return sf::Color(255 * Hue_2_RGB( var_1, var_2, h + ( 1.0 / 3.0 ) ), 255 * Hue_2_RGB( var_1, var_2, h ), 255 * Hue_2_RGB( var_1, var_2, h - ( 1.0 / 3.0 ) ));
}

class hexagon_HSL : public hexagon {
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void hexagon_HSL::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Draw_Border(target, states, "HSL", sf::Color::Black);

    sf::Text text;

    text.setFont(*font);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color(111, 111, 111));
    text.setString("H");
    text.setPosition(p[0].x - 34, p[0].y - 14);
    target.draw(text);

    text.setString("S");
    text.setPosition(p[2].x - 18, p[2].y - 14);
    target.draw(text);

    text.setString("L");
    text.setPosition(p[4].x + 8, p[4].y - 14);
    target.draw(text);

    sf::VertexArray point(sf::Points, (p[5].x - p[1].x) * (p[3].y - p[0].y));
    int x, y;
    float alpha = 0;
    float beta = 0;
    sf::Vector2f z;
    int i = 0;
    for (x = p[1].x; x < p[5].x; x++) {
        for (y = p[0].y; y < center.y; y++) {
            z = sf::Vector2f(x, y);
            if (rhombus(p[0], p[1], z, alpha, beta)) {
                point[i].position = z;

                point[i].color = HSL_TO_RGB(1, alpha, beta * brightness);

                i++;
            }
        }
    }
    for (x = p[1].x; x < center.x; x++) {
        for (y = p[1].y; y < p[3].y; y++) {
            z = sf::Vector2f(x, y);
            if (rhombus(p[2], p[3], z, alpha, beta)) {
                point[i].position = z;

                point[i].color = HSL_TO_RGB(beta, 1, alpha * brightness);

                i++;
            }
        }
    }
    for (x = center.x; x < p[5].x; x++) {
        for (y = p[5].y; y < p[3].y; y++) {
            z = sf::Vector2f(x, y);
            if (rhombus(p[4], p[5], z, alpha, beta)) {
                point[i].position = z;

                point[i].color = HSL_TO_RGB(alpha, beta, brightness);

                i++;
            }
        }
    }
    target.draw(point);
}

sf::Color HSB_TO_RGB(float h,float s,float v) {
	if (s == 0) {
		return sf::Color(v * 255, v * 255, v * 255);
	}
	float varh = h * 6;
	if (varh == 6) {
		varh = 0;
	}
	int var_i = static_cast<int>(varh);
	float var1 = v * (1 - s);
	float var2 = v * (1 - s * (varh - var_i));
	float var3 = v * (1 - s * (1 - (varh - var_i)));
	float var_r, var_g, var_b;
	if (var_i == 0) {
		var_r = v;
		var_g = var3;
		var_b = var1;
	}
	else if (var_i == 1) {
		var_r = var2;
		var_g = v;
		var_b = var1;
	}
	else if (var_i == 2) {
		var_r = var1;
		var_g = v;
		var_b = var3;
	}
	else if (var_i == 3) {
		var_r = var1;
		var_g = var2;
		var_b = v;
	}
	else if (var_i == 4) {
		var_r = var3;
		var_g = var1;
		var_b = v;
	}
	else {
		var_r = v;
		var_g = var1;
		var_b = var2;
	}
	return sf::Color(var_r * 255, var_g * 255, var_b * 255);
}

class hexagon_HSB : public hexagon {
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void hexagon_HSB::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Draw_Border(target, states, "HSB", sf::Color::Black);

    sf::Text text;

    text.setFont(*font);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color(111, 111, 111));
    text.setString("H");
    text.setPosition(p[0].x - 34, p[0].y - 14);
    target.draw(text);

    text.setString("S");
    text.setPosition(p[2].x - 18, p[2].y - 14);
    target.draw(text);

    text.setString("B");
    text.setPosition(p[4].x + 8, p[4].y - 14);
    target.draw(text);

    sf::VertexArray point(sf::Points, (p[5].x - p[1].x) * (p[3].y - p[0].y));
    int x, y;
    float alpha = 0;
    float beta = 0;
    sf::Vector2f z;
    int i = 0;
    for (x = p[1].x; x < p[5].x; x++) {
        for (y = p[0].y; y < center.y; y++) {
            z = sf::Vector2f(x, y);
            if (rhombus(p[0], p[1], z, alpha, beta)) {
                point[i].position = z;

                point[i].color = HSB_TO_RGB(1, alpha, beta * brightness);

                i++;
            }
        }
    }
    for (x = p[1].x; x < center.x; x++) {
        for (y = p[1].y; y < p[3].y; y++) {
            z = sf::Vector2f(x, y);
            if (rhombus(p[2], p[3], z, alpha, beta)) {
                point[i].position = z;

                point[i].color = HSB_TO_RGB(beta, 1, alpha * brightness);

                i++;
            }
        }
    }
    for (x = center.x; x < p[5].x; x++) {
        for (y = p[5].y; y < p[3].y; y++) {
            z = sf::Vector2f(x, y);
            if (rhombus(p[4], p[5], z, alpha, beta)) {
                point[i].position = z;

                point[i].color = HSB_TO_RGB(alpha, beta, brightness);

                i++;
            }
        }
    }
    target.draw(point);
}

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8.0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, settings);

	hexagon_RGB h_RGB;
	hexagon_CMY h_CMY;
	hexagon_HSL h_HSL;
	hexagon_HSB h_HSB;

	sf::Clock frame_clock, around_half_secound_clock;
	sf::Int64 mean_frames_time = 0;
	std::vector<sf::Int64> frame_times;
	sf::Text text;

	font = std::make_shared<sf::Font>();
	font->loadFromMemory(&(ShareTechMono_Regular_ttf[0]), ShareTechMono_Regular_ttf.size());
	text.setFont(*font);
	text.setCharacterSize(21);
	text.setFillColor(sf::Color::Black);

	//Nie mogę uniknąć tych "magic numbers" bo bym zdradził w ten sposób co ma być w sf::Event::Resize. A tego byśmy nie chcieli - prawda? :-D
	text.setPosition(window.getSize().x - 120, window.getSize().y - 60);
	h_RGB.Set_Borders(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(300.0f,294.0f));
	h_CMY.Set_Borders(sf::Vector2f(300.0f, 0.0f), sf::Vector2f(600.0f, 294.0f));
	h_HSL.Set_Borders(sf::Vector2f(0.0f, 294.0f), sf::Vector2f(300.0f, 588.0f));
	h_HSB.Set_Borders(sf::Vector2f(300.0f, 294.0f), sf::Vector2f(600.0f, 588.0f));

	sf::Text textClicked;

	textClicked.setFont(*font);
	textClicked.setCharacterSize(16);
	textClicked.setFillColor(sf::Color(111, 111, 111));
	textClicked.setString(str);
	textClicked.setPosition(20, 0);

	around_half_secound_clock.restart();

	while (window.isOpen()) {
		sf::Event event;
		window.clear(sf::Color::White);

		frame_clock.restart(); // Start pomiaru czasu.

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::Resized) {
				float width = static_cast<float>(event.size.width);
				float height = static_cast<float>(event.size.height);
				if (width < 800 || height < 600) {
					window.setSize(sf::Vector2u(800, 600));
					window.setView(sf::View(sf::FloatRect(0, 0, 800, 600)));
				} else {
					window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				}
				double border_size = std::min(event.size.width / 2 - 100 - 10, event.size.height / 2 - 10);
				h_RGB.Set_Borders(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(border_size, border_size));
				h_CMY.Set_Borders(sf::Vector2f(border_size, 0.0f), sf::Vector2f(border_size*2, border_size));
				h_HSL.Set_Borders(sf::Vector2f(0.0f, border_size), sf::Vector2f(border_size, border_size*2));
				h_HSB.Set_Borders(sf::Vector2f(border_size, border_size), sf::Vector2f(border_size*2, border_size*2));
				text.setPosition(window.getSize().x - 110, window.getSize().y - 80);
			}
			if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if (suuuwak.leftTop.x <= event.mouseMove.x && event.mouseMove.x <= suuuwak.rightBottom.x && suuuwak.leftTop.y <= event.mouseMove.y && event.mouseMove.y <= suuuwak.rightBottom.y) {
					brightness = 1 - (window.getSize().y - 160 - (event.mouseMove.y - suuuwak.leftTop.y)) / (window.getSize().y - 160);
					if (!str.empty()) {
						if (clickedRhomb == 1) {
							str = "RGB: (" + std::to_string(255*brightness) + "," + std::to_string(255 * clickedAlfa * brightness) + "," + std::to_string(255 * clickedBeta * brightness) + ")";
						} else if (clickedRhomb == 2) {
							str = "RGB: (" + std::to_string(255* clickedBeta * brightness) + "," + std::to_string(255 * brightness) + "," + std::to_string(255 * clickedAlfa * brightness) + ")";
						} else if (clickedRhomb == 3) {
							str = "RGB: (" + std::to_string(255* clickedAlfa * brightness) + "," + std::to_string(255 * clickedBeta * brightness) + "," + std::to_string(255 * brightness) + ")";
						}
						textClicked.setString(str);
						window.draw(textClicked);
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					sf::Vector2<int> pos = sf::Mouse::getPosition(window);
					if (h_RGB.left_top.x <= pos.x && h_RGB.right_bottom.x >= pos.x && h_RGB.left_top.y <= pos.y && h_RGB.right_bottom.y >= pos.y) {
						float alpha = 0;
						float beta = 0;
						sf::Vector2f z = sf::Vector2f(pos.x, pos.y);
						if (h_RGB.rhombus(h_RGB.p[0], h_RGB.p[1], z, alpha, beta)) {
							clickedRhomb = 1;
							clickedAlfa = alpha;
							clickedBeta = beta;
							str = "RGB: (" + std::to_string(255*brightness) + "," + std::to_string(255 * alpha * brightness) + "," + std::to_string(255 * beta * brightness) + ")";
						} else if (h_RGB.rhombus(h_RGB.p[2], h_RGB.p[3], z, alpha, beta)) {
							clickedRhomb = 2;
							clickedAlfa = alpha;
							clickedBeta = beta;
							str = "RGB: (" + std::to_string(255* beta * brightness) + "," + std::to_string(255 * brightness) + "," + std::to_string(255 * alpha * brightness) + ")";
						} else if (h_RGB.rhombus(h_RGB.p[4], h_RGB.p[5], z, alpha, beta)) {
							clickedRhomb = 3;
							clickedAlfa = alpha;
							clickedBeta = beta;
							str = "RGB: (" + std::to_string(255* alpha * brightness) + "," + std::to_string(255 * beta * brightness) + "," + std::to_string(255 * brightness) + ")";
						}
					}
					textClicked.setString(str);
				}
			}
		}

		window.draw(h_RGB);
		window.draw(h_CMY);
		window.draw(h_HSL);
		window.draw(h_HSB);
		window.draw(suuuwak);

		window.draw(textClicked);

		text.setString(std::to_string(mean_frames_time)+ "us");
		window.draw(text);

		// Pomiar czasu uśrednimy w okresie około 1/2 sekundy.
		frame_times.push_back(frame_clock.getElapsedTime().asMicroseconds());
		if (around_half_secound_clock.getElapsedTime().asSeconds() >= 0.5f && !frame_times.empty()) {
			mean_frames_time = (sf::Int64)((float)std::reduce(frame_times.begin(), frame_times.end()) / (float)frame_times.size());
			frame_times.clear();
			around_half_secound_clock.restart();
		}

		frame_clock.restart(); // Stop pomiaru czasu.
		window.display();
	}

	font.reset();

	return 0;
}