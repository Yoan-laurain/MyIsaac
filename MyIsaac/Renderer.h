#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IComponent.h"
#include "IDrawable.h"
#include "IEntity.h"
#include "Transform.h"

class Renderer: public IComponent
{
	public:
		Renderer( IEntity& entity );
		~Renderer() override;

		void init() override;
		void update() override;
		void destroy() override;

		void draw(sf::RenderWindow& window);
		void add_drawable(IDrawable& drawable);

		void get_comp();

	private :

		Transform m_transform;
		std::vector<IDrawable*> m_drawables;
		IEntity* m_entity;
};
