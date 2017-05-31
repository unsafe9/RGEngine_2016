#include "RGComponentBoxCollider.h"
#include "RGComponentCircleCollider.h"
#include "RGApplication.h"

namespace RGEngine
{
	namespace Components
	{
		BoxCollider::BoxCollider(GameObject *gameObject) : Collider(gameObject) {}
		BoxCollider::~BoxCollider() {}
		void BoxCollider::Reset(void)
		{
			box.SetRect(0.0f, 0.0f, 0.0f, 0.0f);
		}
		Math::Rect BoxCollider::GetBoxWithPosition(void) const
		{
			return box + GetGameObject()->position;
		}
		void BoxCollider::OnUpdate(void)
		{
			auto objects = RGApp->GetScene()->GetGameObjects();
			for (int i = 0; i < RGApp->GetScene()->GetGameObjectSize(); ++i)
			{
				if (objects[i] == GetGameObject()) continue;
				auto col_circle = objects[i]->GetComponent<CircleCollider>();
				if (col_circle && GetBoxWithPosition().Intersected(col_circle->GetCircleWithPosition()))
				{
					GetGameObject()->OnCollision(objects[i]);
				}
				auto col_box = objects[i]->GetComponent<BoxCollider>();
				if (col_box && GetBoxWithPosition().Intersected(col_box->GetBoxWithPosition()))
				{
					GetGameObject()->OnCollision(objects[i]);
				}
			}
		}
	}
}
