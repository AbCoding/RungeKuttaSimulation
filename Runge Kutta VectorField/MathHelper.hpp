#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>

struct RungeKutta {
    static constexpr float third = 1.0f / 3.0f;
    static constexpr float sixth = 1.0f / 6.0f;

    static sf::Vector2f iterateRungeKutta(sf::Vector2f state, float t, float h, std::function<sf::Vector2f(sf::Vector2f, float)> func) {
        sf::Vector2f k1 = func(state, t) * h;
        sf::Vector2f k2 = func(state + (k1 * 0.5f), t + h / 2) * h;
        sf::Vector2f k3 = func(state + (k2 * 0.5f), t + h / 2) * h;
        sf::Vector2f k4 = func(state + (k3), t + h) * h;
        return (state + k1 * sixth + k2 * third + k3 * third + k4 * sixth);
    }
};
struct MathHelper {
    static constexpr float pi = 3.14159265359f;
};
struct VectorMath {
    // Vector Math Related Stuff
    static const sf::Vector2f origin;
    

    static float GetDistance(sf::Vector2f Vec1, sf::Vector2f Vec2) {
        float x_squared = pow(Vec1.x - Vec2.x, 2);
        float y_squared = pow(Vec1.y - Vec2.y, 2);
        return sqrt(x_squared + y_squared);
    }

    static sf::Vector2f NormalizeVector(sf::Vector2f vec) {
        float distance = GetDistance(vec, origin);
        return vec * (1 / distance);
    }

};

const sf::Vector2f VectorMath::origin = sf::Vector2f(0, 0);

