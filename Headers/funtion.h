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
	// z축을 중심으로 회전했을 때, 외적의 행렬식에 있는 부호만 사용한다
	return (left.x * right.y - left.y * right.x) < 0;
}