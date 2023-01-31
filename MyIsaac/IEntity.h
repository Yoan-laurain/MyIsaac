#pragma once
#include <vector>
#include <IComponent.h>

class IEntity
{
	public:
		
		void init();
		void update();
		void destroy();

		template <typename T>
		void AddComponent(T* component);
		
		template <typename T>
		T* GetComponent();
	

	private : 
		std::vector<IComponent*> listComponents;
};

template<typename T>
inline void IEntity::AddComponent(T* component)
{
	listComponents.push_back(component);
}

template<typename T>
T* IEntity::GetComponent()
{
	for (auto* comp : listComponents)
		if (comp == dynamic_cast<T*>(comp))
			return dynamic_cast<T*>(comp);
	
	return nullptr;
}
