#pragma once
#include <vtkCommand.h>
#include <vtkPropPicker.h>
#include <vtkWin32RenderWindowInteractor.h>
#include <vtkRenderer.h>
#include "vtkInteractorStyle.h"

class vtkImageInteractionCallback : public vtkCommand
{
public:
	vtkImageInteractionCallback(void);
	~vtkImageInteractionCallback(void);

	static vtkImageInteractionCallback *New() 
	{
		return new vtkImageInteractionCallback; 
	}

	void SetPicker(vtkPropPicker *picker) 
	{
		this->Picker = picker; 
	}

	void SetInteractor(vtkWin32RenderWindowInteractor *interactor) 
	{
		this->Interactor = interactor; 
	}

	void SetRenderer(vtkRenderer *renderer) 
	{
		this->Renderer = renderer; 
	}

	void GetPosition(int array[2])
	{
		array[0] = position[0];
		array[1] = position[1];
	}

	bool GetState()
	{
		return state;
	}

	void SetState(bool s)
	{
		state = s;
	}

	void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *)
	{
		vtkInteractorStyle *Style = vtkInteractorStyle::SafeDownCast(
			Interactor->GetInteractorStyle());

		// Pick at the mouse location provided by the interactor
		this->Picker->Pick(Interactor->GetEventPosition()[0],
			Interactor->GetEventPosition()[1],
			0.0, Renderer);

		// Get the world coordinates of the pick
		double pos[3];
		this->Picker->GetPickPosition(pos);

		position[0] = (int)pos[0];
		position[1] = (int)pos[1];

		state = true;
		//Interactor->Render();
		//Style->OnLeftButtonDown();
	}

protected:
	int position[2];

	bool state;

private:
	// Pointer to the picker
	vtkPropPicker *Picker;

	vtkWin32RenderWindowInteractor *Interactor;

	vtkRenderer *Renderer;
};

