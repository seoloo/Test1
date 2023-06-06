#include "stdafx.h"
#include "..\Public\BackGround.h"

#include "GameInstance.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	
}

CBackGround::CBackGround(const CBackGround & rhs)
	: CGameObject(rhs)
{

}

HRESULT CBackGround::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	/* 백그라운드가 사용하기위한 컴포넌트들을 추가하낟. */
	if (FAILED(Add_Components()))
		return E_FAIL;

	m_fSizeX = g_iWinSizeX;
	m_fSizeY = g_iWinSizeY;
	m_fX = g_iWinSizeX * 0.5f;
	m_fY = g_iWinSizeY * 0.5f;

	_float4x4		Scaling, Translation;

	m_WorldMatrix = *D3DXMatrixScaling(&Scaling, m_fSizeX, m_fSizeY, 1.f) * 
		*D3DXMatrixTranslation(&Translation, m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f);

	m_ViewMatrix = *D3DXMatrixIdentity(&m_ViewMatrix);
	

	/* 뷰 스페이스에서 뷰 볼륨을 설정하고. 해당 뷰 볼륨에 있는 모든 점들을 
	투영스페이스로 그대로 찍어낸다. */
	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0.0f, 1.f);

	return S_OK;
}

void CBackGround::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CBackGround::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);	
}


HRESULT CBackGround::Render()
{
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	// _float4x4		WorldMatrix, ViewMatrix, ProjMatrix;

	/*D3DXMatrixIdentity(&WorldMatrix);
	D3DXMatrixIdentity(&ViewMatrix);*/
	// D3DXMatrixLookAtLH(&ViewMatrix, &_float3(5.f, 0.f, -5.f), 
	//	&_float3(0.f, 0.f, 0.f), 
	//	&_float3(0.f, 1.f, 0.f));
	//D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.0f),
	//	(_float)g_iWinSizeX / g_iWinSizeY,
	//	0.2f,
	//	300.f);

	/* 장치에 행렬을 바인딩한다. */
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	/* 장치에 텍스쳐를 바인딩한다. */
	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(0)))
		return E_FAIL;	

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CBackGround::Add_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"),
		TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_LOGO, TEXT("Prototype_Component_Texture_BackGround"),
		TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround*	pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Created : CBackGround");
	}

	return pInstance;
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CBackGround*	pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed to Cloned : CBackGround");
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);	
}
