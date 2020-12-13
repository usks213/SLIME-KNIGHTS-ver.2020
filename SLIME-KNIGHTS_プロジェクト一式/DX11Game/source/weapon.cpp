//==================================================================
//								weapon.h
//	武器	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/14	ウェポンのクラス
//
//===================================================================


//====== インクルード部 ======
#include "weapon.h"

#include "objectMgr.h"
#include "animation.h"
#include "animator.h"
#include "rigidbody.h"
#include "collision.h"

#include "effect.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"
#endif // _WIN64

//===== マクロ定義 =====
#define OFFSET_X (20)
#define OFFSET_Y (12)


//===== 静的メンバ =====
CTexture CWeapon::sm_texture[WEAPON::MAX_WEAPON_TYPE];


//===== 名前空間 =====


//========================================
//
//	コンストラクタ
//
//========================================
CWeapon::CWeapon()
{
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 192, 192 });
	m_transform.SetAngle(45);

	// スプライトデータ
	m_sprite.SetColor(Float4{ 1.f, 1.f, 1.f, 1.0f });

	// レイヤー
	m_enLayer = LAYER::WEAPON;

	// 座標更新データ
	m_pParentTrans = nullptr;
	m_nMoveFrame = 0;
	m_nMoveCnt = 0;
	m_bRight = false;
	
	// オフセット
	m_fOffSetX = OFFSET_X;
	m_fOffSetY = OFFSET_Y;

	// タイプ
	m_eWeaponType = WEAPON::SWORD;
}


//========================================
//
//	デストラクタ
//
//========================================
CWeapon::~CWeapon()
{
	m_pAnimator->Destroy();
}


//========================================
//
//	初期化
//
//========================================
void CWeapon::Init()
{
	// テクスチャ
	//sm_texture.LoadTexture(FILE_PATH"player/weapon_base.tga");
	sm_texture[WEAPON::SWORD].LoadTexture(FILE_PATH"weapon/weapon_sword.tga");
	sm_texture[WEAPON::LANCE].LoadTexture(FILE_PATH"weapon/weapon_lance.tga");
	sm_texture[WEAPON::BOW].LoadTexture(FILE_PATH"weapon/weapon_bow.tga");
	sm_texture[WEAPON::STICK].LoadTexture(FILE_PATH"weapon/weapon_stick.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CWeapon::Uninit()
{
	// テクスチャの解放
	for (int i = 0; i < WEAPON::MAX_WEAPON_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
}

//========================================
//
//	更新処理
//
//========================================
void CWeapon::Update()
{
	// 座標更新
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.y += m_fOffSetY;

	m_transform.SetPos(pos);
}

//========================================
//
//	更新処理
//
//========================================
void CWeapon::LateUpdate()
{
	// 座標更新
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.y += m_fOffSetY;

	// 右か左か
	if (m_bRight)
	{
		pos.x += m_fOffSetX;
		// 角度更新
		if (m_nMoveCnt > 0)
		{
			float addAng = 90.0f / m_nMoveFrame;
			if (m_bDown)
			{
				float angle = m_transform.GetAngle() + addAng;
				m_transform.SetAngle(angle);
			}
			else
			{
				float angle = m_transform.GetAngle() - addAng;
				m_transform.SetAngle(angle);
			}

			m_nMoveCnt--;
		}
	}
	else
	{
		pos.x -= m_fOffSetX;
		// 角度更新
		if (m_nMoveCnt > 0)
		{
			float addAng = 90.0f / m_nMoveFrame;
			if (m_bDown)
			{
				float angle = m_transform.GetAngle() - addAng;
				m_transform.SetAngle(angle);
			}
			else
			{
				float angle = m_transform.GetAngle() + addAng;
				m_transform.SetAngle(angle);
			}

			m_nMoveCnt--;
		}
	}
	m_transform.SetPos(pos);


}

//========================================
//
//	描画処理
//
//========================================
void CWeapon::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	m_sprite.Draw(&m_transform, &sm_texture[m_eWeaponType]);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	生成
//
//========================================
CWeapon* CWeapon::Create(CTransform *pParent, WEAPON::EWEAPON_TYPE eType)
{
	CWeapon *pWeapon = CObjectManager::CreateObject<CWeapon>();

	pWeapon->m_pParentTrans = pParent;
	pWeapon->m_eWeaponType = eType;

	return pWeapon;
}

//========================================
//
//	消去
//
//========================================
void CWeapon::Destroy()
{
	CObjectManager::DestroyObject(this);

}


//========================================
//
//	当たり判定
//
//========================================
void CWeapon::OnAnimator(CAnimator *pAnim)
{
	CAnimation *pAn = pAnim->GetCurrentAnimation();
	if (pAn == nullptr) return;

	if (pAn->GetName() == "a")
	{

	}
}


//========================================
//
//	剣のモーションスタート
//
//========================================
void CWeapon::StartMove(int nFrame, bool bRight, bool bDown)
{
	m_nMoveFrame = m_nMoveCnt = nFrame;
	m_bRight = bRight;
	m_bDown = bDown;

	if (m_bRight)
	{
		if (m_bDown)
		{
			m_transform.SetAngle(180);
		}
		else
		{
			m_transform.SetAngle(270);
		}
	}
	else
	{
		if (m_bDown)
		{
			m_transform.SetAngle(90);
		}
		else
		{
			m_transform.SetAngle(0);
		}
	}
}


void CWeapon::SetPos(bool bRight, bool bDown)
{
	m_bRight = bRight;
	m_bDown = bDown;

	if (m_nMoveCnt > 0) return;

	if (m_bRight)
	{
		if (m_bDown)
		{
			m_transform.SetAngle(180);
		}
		else
		{
			m_transform.SetAngle(270);
		}
	}
	else
	{
		if (m_bDown)
		{
			m_transform.SetAngle(90);
		}
		else
		{
			m_transform.SetAngle(0);
		}
	}

	/*if (m_bRight)
	{
		if (m_bDown)
		{
			m_transform.SetAngle(-45);
		}
		else
		{
			m_transform.SetAngle(45);
		}
	}
	else
	{
		if (m_bDown)
		{
			m_transform.SetAngle(225);
		}
		else
		{
			m_transform.SetAngle(135);
		}
	}*/
}


void CWeapon::SetTargetAngle(Float3 targetPos)
{
	Float3 myPos = m_pParentTrans->GetPos();

	Float3 vec = targetPos;
	vec.x -= myPos.x;
	vec.y -= myPos.y;
	vec.z = 0;

	vec = Normalize(vec);



	Float3 right = Float3{ 1.0f, 0.0f, 0.0f };
	float rad = acosf(Dot(right, vec));
	float angle = rad / 3.1415f * 180.0f;
	float cross = Cross2D(right, vec);

	// ０～１８０
	if (cross >= 0)
	{
		m_transform.SetAngle(-(angle + 90.0f + 45.0f));
	}
	// １８０～３６０
	else
	{
		m_transform.SetAngle(angle - 90 - 45.0f);
	}

}
