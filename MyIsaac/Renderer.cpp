#include "Renderer.h"
#include "IEntity.h"

Renderer::Renderer(IEntity& entity)
{
    m_entity = &entity;
}

Renderer::~Renderer(){}

void Renderer::init()
{
    for (auto& drawable : m_drawables)
        drawable->init();
}

void Renderer::update()
{
    for (auto& drawable : m_drawables)
        drawable->update();
}

void Renderer::destroy()
{
    for (auto& drawable : m_drawables)
        drawable->destroy();
}

void Renderer::draw(sf::RenderWindow& window)
{
    for (IDrawable* drawable : m_drawables)
        window.draw( drawable->get_drawable() );
}

void Renderer::add_drawable(IDrawable& drawable)
{
    m_drawables.push_back(&drawable);
}

void Renderer::get_comp()
{
    m_transform = *m_entity->GetComponent<Transform>();
}
