#include "RGComponentCircleCollider.h"
#include "RGComponentBoxCollider.h"
#include "RGApplication.h"

namespace RGEngine
{
	namespace Components
	{
		CircleCollider::CircleCollider(GameObject *gameObject) : Collider(gameObject) {}
		CircleCollider::~CircleCollider() {}
		void CircleCollider::Reset(void)
		{
			circle.SetCircle(0.0f, 0.0f, 0.0f);
		}
		Math::Circle CircleCollider::GetCircleWithPosition(void) const
		{
			return Math::Circle(circle.center + GetGameObject()->position, circle.radius);
		}
		void CircleCollider::OnUpdate(void)
		{
			auto objects = RGApp->GetScene()->GetGameObjects();
			for (int i = 0; i < RGApp->GetScene()->GetGameObjectSize(); ++i)
			{
				if (objects[i] == GetGameObject()) continue;
				auto col_circle = objects[i]->GetComponent<CircleCollider>();
				if (col_circle && GetCircleWithPosition().Intersected(col_circle->GetCircleWithPosition()))
				{
					GetGameObject()->OnCollision(objects[i]);
				}
				auto col_box = objects[i]->GetComponent<BoxCollider>();
				if (col_box && GetCircleWithPosition().Intersected(col_box->GetBoxWithPosition()))
				{
					GetGameObject()->OnCollision(objects[i]);
				}
			}
		}
	}
}
