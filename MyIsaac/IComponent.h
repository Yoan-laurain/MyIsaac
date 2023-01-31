#pragma once
class IComponent
{
	public:

		IComponent() {}
		virtual ~IComponent() {}

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void destroy() = 0;
};

