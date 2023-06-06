#include "..\Public\VIBuffer.h"

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_iStride(rhs.m_iStride)
	, m_iNumVertices(rhs.m_iNumVertices)
	, m_dwFVF(rhs.m_dwFVF)
	, m_PrimitiveType(rhs.m_PrimitiveType)
	, m_iNumPrimitive(rhs.m_iNumPrimitive)
	, m_iIndexStride(rhs.m_iIndexStride)
	, m_iNumIndices(rhs.m_iNumIndices)
	, m_eIndexFormat(rhs.m_eIndexFormat)
	
{	
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	/* � �ҽ�(�ڿ�, ������) �� �̿��ؼ� �׸����K ? */
	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, m_iStride);
	m_pGraphic_Device->SetFVF(m_dwFVF);	
	m_pGraphic_Device->SetIndices(m_pIB);
	
	m_pGraphic_Device->DrawIndexedPrimitive(m_PrimitiveType, 0, 0, m_iNumVertices, 0, m_iNumPrimitive);
	
	return S_OK;
}



HRESULT CVIBuffer::Create_VertexBuffer()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	/* ����(Vertex) �迭�� �Ҵ��Ѵ�. */
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iStride * m_iNumVertices, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;	

	return S_OK;
}

HRESULT CVIBuffer::Create_IndexBuffer()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	/* �ε���(������ Index) �迭�� �Ҵ��Ѵ�. */
	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iIndexStride * m_iNumIndices, 0, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	return S_OK;

	
}

void CVIBuffer::Free()
{
	__super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

}
