#pragma once

#include "Engine_Defines.h"

/* ��� Ŭ�������� �θ� �Ǵ� SuperŬ������ */
/* ���۷��� ī��Ʈ�� �ο��ϰ� ����, ���� or ������ ��Ȱ�� �ο��Ѵ�. */

/* abstract  : �߻�Ŭ���� */

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	/* AddRef : ���۷���ī��Ʈ�� ������Ű��. */
	/* unsigned long : ������Ű�� �� �����ǰ�. */
	_ulong AddRef();

	/* Release : ���۷���ī��Ʈ�� ���ҽ�Ű��. or �����Ѵ�.  */
	/* unsigned long : ���ҽ�Ű�� �����ǰ�. */
	_ulong Release();

private:
	_ulong		m_dwRefCnt = { 0 };

public:	
	virtual void Free() = 0;
};

END

