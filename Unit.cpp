//
// Created by Сергей Апарин on 20.10.2018.
//

#include "Unit.h"
#include <iostream>

Unit::Unit(sf::RenderWindow &window, Player *player, std::string file, float w, float h, sf::Vector2f pos, float sp) :
        GameObject(window, player, file, w, h, pos)
{
    speed = sp;
    isMove = false;
    isAlive = true;
    isSelect = false;
    distance = 0;
}

void Unit::control(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {//если нажата клавиша мыши
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
        sf::Vector2f cursor_pos = window.mapPixelToCoords(pixelPos);
        if (event.key.code == sf::Mouse::Left) {//а именно левая
            if (sprite.getGlobalBounds().contains(cursor_pos.x,
                                                  cursor_pos.y))//и при этом координата курсора попадает в спрайт
            {
                sprite.setColor(
                        sf::Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
                isSelect = true;
            }
        }
    }
    if (isSelect)
    {
        if (event.type == sf::Event::MouseButtonPressed) {//если нажата клавиша мыши
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
            sf::Vector2f cursor_pos = window.mapPixelToCoords(pixelPos);
            if (event.key.code == sf::Mouse::Right) {//а именно правая
                isMove = true;//то начинаем движение
                isSelect = false;//объект уже не выбран
                sprite.setColor(sf::Color::White);//возвращаем обычный цвет спрайту
                tempX = cursor_pos.x;//забираем координату нажатия курсора Х
                tempY = cursor_pos.y;//и Y
            }
        }
    }
}

void Unit::update(double time)
{
    if (isMove) {
        distance = sqrt((pow((tempX - coordinates.x), 2) + pow((tempY - coordinates.y),
                                                               2)));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора
        if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта

            coordinates.x +=
                    0.1 * time * (tempX - coordinates.x) / distance;//идем по иксу с помощью вектора нормали
            coordinates.y += 0.1 * time * (tempY - coordinates.y) / distance;//идем по игреку так же
        } else {
            isMove = false;
        }
        sprite.setPosition(coordinates);
    }
}