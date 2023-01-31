#pragma once
#include <SFML/Graphics/Transform.hpp>

#include "IComponent.h"
#include <SFML/System/Vector2.hpp>

class Transform : public IComponent
{
	public:
		Transform();
		~Transform();

		void init() override;
		void update() override;
		void destroy() override;

		sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f position);
		
		sf::Vector2f getScale() const;
		void setScale(sf::Vector2f scale);
		
		float getRotation() const;
		void setRotation(float rotation);

	private:
		sf::Vector2f position;
		sf::Vector2f scale;
		float rotation;
		sf::Transform transform;
	
};