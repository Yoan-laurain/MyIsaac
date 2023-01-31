#include "Transform.h"

Transform::Transform(){}
Transform::~Transform(){}

void Transform::init()
{
	this->position = sf::Vector2f(0, 0);
	this->scale = sf::Vector2f(1, 1);
	this->rotation = 0;
	this->transform = sf::Transform();
}

void Transform::update() {}

void Transform::destroy() {}

sf::Vector2f Transform::getPosition() const
{
	return sf::Vector2f();
}

void Transform::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->transform.translate(position);
}

sf::Vector2f Transform::getScale() const
{
	return scale;
}

void Transform::setScale(sf::Vector2f scale)
{
	this->scale = scale;
	this->transform.scale(scale);
}

float Transform::getRotation() const
{
	return rotation;
}

void Transform::setRotation(float rotation)
{
	this->rotation = rotation;
	this->transform.rotate(rotation);
}
