#pragma once

#include "Component.h"

/* Vertex + Index 공간(Buffer) 을 가진다.*/
/* 여러가지 모델(네모, 큐브, 지형 등등등) 들의 부목가 되는 크래스다. */
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
	/* 정점을 배열로 선언한 메모리 공간을 대표하는 컴객체 */
	LPDIRECT3DVERTEXBUFFER9				m_pVB = { nullptr };
	LPDIRECT3DINDEXBUFFER9				m_pIB = { nullptr };

protected:
	_uint								m_iStride = { 0 }; /* 정점 하나의 byte크기 */
	_uint								m_iNumVertices = { 0 };
	_ulong								m_dwFVF = { 0 }; /* 정점이 어떤어떤 정보로 만들어져있어! */
	D3DPRIMITIVETYPE					m_PrimitiveType;
	_uint								m_iNumPrimitive = { 0 };

protected:
	_uint								m_iIndexStride = { 0 }; /* 인덱스 한칸의 크기 (2 or 4 Byte)*/
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