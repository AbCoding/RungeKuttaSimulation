#include <SFML/Graphics.hpp>
#include "MathHelper.hpp"
#include <iostream>
#include <functional>
#include <random>
class Particle {
    sf::Vector2f pos;
    sf::Vector2f vel;
    float t;
    sf::CircleShape object;
   
    float width;
    float height;
public:
    Particle(sf::Vector2f position, float tim,float width,float height) {
        pos = position;
        t = tim;
        object.setRadius(4);
        object.setPosition(pos);
        this->width = width;
        this->height = height;
        
    }

    static sf::Vector2f VectorField(sf::Vector2f position, float tim) {
        float x = position.x / 20;
        float y = position.y / 20;
        float XVal = sin(x-y)+cos(x*y*tim);
        float YVal = 4*XVal+sin(y+x);
        return sf::Vector2f(XVal, YVal);
    }

    void UpdatePos(float dt) {
        auto func = [](sf::Vector2f position, float tim) {
            return Particle::VectorField(position, tim);
        };
        pos = RungeKutta::iterateRungeKutta(pos, t, dt, func);
    }

    void TickPhysics(float dt) {
        posToCord();
        UpdatePos(dt);
        CordToPos();
        t += dt;
        
    }
    void posToCord() {
        pos.x -= width/2;
        pos.y -= height/2;
        
    }
    void CordToPos() {
            pos.x += width / 2;
            pos.y += height / 2;
    }
    void render(sf::RenderWindow& window) {
        object.setPosition(pos);
        window.draw(object);
    }
    float getTime() {
        return t;
    }
    sf::Vector2f getPos() {
        return pos;
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "My Program");
    window.setFramerateLimit(60);

    const int numParticles = 10000;
    std::vector<Particle> particles;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posXDist(0, window.getSize().x);
    std::uniform_real_distribution<float> posYDist(0, window.getSize().y);

    for (int i = 0; i < numParticles; ++i) {
        sf::Vector2f position(posXDist(gen), posYDist(gen));
        particles.emplace_back(position, 0,1600,1000);
    }

    float dt = 0.5;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear();

        for (auto& particle : particles) {
            particle.TickPhysics(dt);
            particle.render(window);
            
        }

        window.display();
    }

    return 0;
}