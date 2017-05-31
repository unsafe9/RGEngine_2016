#ifndef _RGCOMPONENTBOXCOLLIDER_H_
#define _RGCOMPONENTBOXCOLLIDER_H_

#include "RGComponentCollider.h"
#include "RGMath.h"

namespace RGEngine
{
	namespace Components
	{
		class BoxCollider : public Collider
		{
		public:
			Math::Rect box; // ¿ùµå ÁÂÇ¥¿¡¼­ transformÀÇ ÁÂÇ¥(¿ÞÂÊ À§) ±âÁØ
			Math::Rect GetBoxWithPosition(void) const;

		public:
			BoxCollider(GameObject *gameObject);
			~BoxCollider() override;

		public:
			void Reset(void) override;
			std::type_index GetID(void) override { return typeid(BoxCollider); }
			std::type_index GetFamilyID(void) override { return typeid(Collider); }

			static std::type_index GetStaticID(void) { return typeid(BoxCollider); }
			static std::type_index GetStaticFamilyID(void) { return typeid(Collider); }

		public:
			void OnUpdate(void) override;

		};
	}
}

#endif // _RGCOMPONENTBOXCOLLIDER_H_