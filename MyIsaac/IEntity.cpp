#include "IEntity.h"

void IEntity::init()
{
	for (IComponent* comp : listComponents)
		comp->init();
}

void IEntity::update()
{
	for (IComponent* comp : listComponents)
		comp->update();
}

void IEntity::destroy()
{
	for (IComponent* comp : listComponents)
		comp->destroy();
}