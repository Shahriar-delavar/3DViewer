#pragma once
#include "vtkinteractorstyleimage.h"
#include <vtkObjectFactory.h>

class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
	myVtkInteractorStyleImage(void);
	~myVtkInteractorStyleImage(void);
	static myVtkInteractorStyleImage* New();
	vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

protected:
	int _slice;
	int _minSlice;
	int _maxSlice;

public:
	void SetMaxAndMinSlice(int minSlice, int maxSlice)
	{
		_maxSlice = maxSlice;
		_minSlice = minSlice;

		// ����l�[�ݪ�������m�b����
		_slice = (maxSlice + minSlice)*0.4;
	}

	int SetSlice()
	{
		return _slice;
	}

protected:

	// ����u�����ƥ�
	void MoveSliceForward()
	{
		if(_slice < _maxSlice)
		{
			_slice += 1;
			SetSlice();
		}
	}

	void MoveSliceBackward()
	{
		if(_slice > _minSlice)
		{
			_slice -= 1;
			SetSlice();
		}
	}

	virtual void OnMouseWheelForward()
	{
		MoveSliceForward();
	}


	virtual void OnMouseWheelBackward()
	{
		if(_slice > _minSlice)
		{
			MoveSliceBackward();
		}
	}
};

