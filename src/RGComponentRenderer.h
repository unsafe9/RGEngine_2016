#ifndef _RGCOMPONENTRENDERER_H_
#define _RGCOMPONENTRENDERER_H_

#include "RGComponent.h"

namespace RGEngine
{
	namespace Components
	{
		class Renderer : public Component
		{
		public:
			Renderer(GameObject *gameObject) : Component(gameObject) {}
			~Renderer() override {}

		public:
			virtual void Reset(void) override {}
			virtual std::type_index GetID(void) override = 0 { return typeid(Renderer); }
			virtual std::type_index GetFamilyID(void) override = 0 { return typeid(Renderer); }

			static std::type_index GetStaticID(void) { return typeid(Renderer); }
			static std::type_index GetStaticFamilyID(void) { return typeid(Renderer); }

		public:
			virtual void OnCreate(void) override {}
			virtual void OnDestroy(void) override {}
			virtual void OnUpdate(void) override {}
			virtual void OnRender(void) override {}

		};
	}
}

#endif // _RGCOMPONENTRENDERER_H_