#pragma once

template <typename T>
static void Safe_Delete(T& Pointer)
{
	if(NULL != Pointer)
	{
		delete Pointer;
		Pointer = NULL;
	}
}

template <typename T>
static  void Safe_Delete_Array(T& Pointer)
{
	if(NULL != Pointer)
	{
		delete [] Pointer;
		Pointer = NULL;
	}
}

class DeleteMap
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if(Temp.second)
		{
			delete Temp.second;
			Temp.second =NULL;
		}
	}
};

class DeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if(Temp)
		{
			delete Temp;
			Temp =NULL;
		}
	}
};

static bool IsCw( const D3DXVECTOR3& left, const D3DXVECTOR3& right )
{
	// z���� �߽����� ȸ������ ��, ������ ��ĽĿ� �ִ� ��ȣ�� ����Ѵ�
	return (left.x * right.y - left.y * right.x) < 0;
}