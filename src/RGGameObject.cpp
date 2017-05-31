#include "RGGameObject.h"
#include "RGScene.h"
#include "RGComponent.h"
#include "RGApplication.h"

namespace RGEngine
{
	GameObject::GameObject(void) : m_enabled(true), m_destroyed(false)
	{
		matrix.Identity();
		position = center = rotationCenter = scalingCenter = Math::Vector(0.0f, 0.0f);
		scale.SetVector(1.0f, 1.0f);
		rotate = scalingRotation = 0.0f;
	}

	GameObject::~GameObject()
	{
		for (auto &i : m_components)
		{
			(i.second)->OnDestroy();
			delete i.second;
		}
		m_components.clear();
	}

	void GameObject::SetEnabled(bool flag)
	{
		if (m_enabled != flag)
		{
			m_enabled = flag;
			m_enabled ? OnEnabled() : OnDisabled();
		}
	}

	bool GameObject::GetEnabled(void) const
	{
		return m_enabled;
	}

	void GameObject::Update(void)
	{
		for (auto &i : m_components)
		{
			if ((i.second)->GetEnabled())
			{
				(i.second)->OnUpdate();
			}
		}
	}

	void GameObject::Render(void)
	{
		D3DXMatrixTransformation2D(
			(LPD3DXMATRIX)&matrix,					// 연산 결과 행렬
			(LPD3DXVECTOR2)&scalingCenter,			// 스케일 중심점 지정, NULL(=0, 0), 0, 0 이미지 왼쪽 상단
			scalingRotation,						// 확대 회전 요소를 지정, pScaling 의 x, y의 확대비율이 다른 경우에  영향
			(LPD3DXVECTOR2)&scale,				// 확대율을 지정, NULL 은 스케일 하지 않음
			(LPD3DXVECTOR2)&rotationCenter,			// 회전 중심점 NULL(=0, 0)
			rotate,								// 회전 각도(Radian 단위), 우회전 기준
			(LPD3DXVECTOR2)&(position - center));	// 평행이동 NULL(=0, 0)
		if (parent)
		{
			matrix *= parent->matrix;
		}
		RGGraphic->GetSprite()->SetTransform((LPD3DXMATRIX)&matrix);

		for (auto &i : m_components)
		{
			if ((i.second)->GetEnabled())
			{
				(i.second)->OnRender();
			}
		}
	}
	void GameObject::Destroy(void)
	{
		m_destroyed = true;
	}
}