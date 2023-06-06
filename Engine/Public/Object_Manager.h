#pragma once

/* 1. ������ü���� �����Ѵ�. */
/* 2. ��������� ��ü�� �����ϴ� �۾��� �Ѵ�. �����Ͽ� ������ ��ü�� ���� ��������� ���ؿ����� �����ϳ� */
/* 3. ������ ��ü���� ƽ�� ����Ʈ ƽ�� ȣ���Ѵ�. */
/* 4. ��ü���� ������ ȣ���Ѵ�.(x) */

#include "Base.h"

BEGIN(Engine)

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Reserve_Manager(_uint iNumLevels);
	HRESULT Add_Prototype(const wstring& strPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg);

	void Tick(_float fTimeDelta);
	void Late_Tick(_float fTimeDelta);

	void Clear(_uint iLevelIndex);


private: /* ��ü���� ������ �����Ѵ�. */
	map<wstring, class CGameObject*>		m_Prototypes;

private:
	_uint									m_iNumLevels = { 0 };
	map<wstring, class CLayer*>*			m_pLayers = { nullptr };
	typedef map<wstring, class CLayer*>		LAYERS;

private:
	class CGameObject* Find_Prototype(const wstring& strPrototypeTag);
	class CLayer* Find_Layer(_uint iLevelIndex, const wstring& strLayerTag);

public:
	virtual void Free() override;
};

END