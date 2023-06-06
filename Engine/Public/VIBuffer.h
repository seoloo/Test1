#pragma once

#include "Component.h"

/* Vertex + Index ����(Buffer) �� ������.*/
/* �������� ��(�׸�, ť��, ���� ����) ���� �θ� �Ǵ� ũ������. */
BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render();

protected:
	/* ������ �迭�� ������ �޸� ������ ��ǥ�ϴ� �İ�ü */
	LPDIRECT3DVERTEXBUFFER9				m_pVB = { nullptr };
	LPDIRECT3DINDEXBUFFER9				m_pIB = { nullptr };

protected:
	_uint								m_iStride = { 0 }; /* ���� �ϳ��� byteũ�� */
	_uint								m_iNumVertices = { 0 };
	_ulong								m_dwFVF = { 0 }; /* ������ �� ������ ��������־�! */
	D3DPRIMITIVETYPE					m_PrimitiveType;
	_uint								m_iNumPrimitive = { 0 };

protected:
	_uint								m_iIndexStride = { 0 }; /* �ε��� ��ĭ�� ũ�� (2 or 4 Byte)*/
	_uint								m_iNumIndices = { 0 };
	D3DFORMAT							m_eIndexFormat;

protected:
	HRESULT Create_VertexBuffer();
	HRESULT Create_IndexBuffer();

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END