#include "StdAfx.h"
#include "vtkImageInteractionCallback.h"


vtkImageInteractionCallback::vtkImageInteractionCallback(void)
{
	this->Picker = 0;
	this->Interactor = vtkWin32RenderWindowInteractor::New();
	this->Renderer = vtkRenderer::New();

	position[0] = 0;
	position[1] = 0;

	state = false;
}

vtkImageInteractionCallback::~vtkImageInteractionCallback(void)
{
	this->Picker = 0;
	//this->Interactor->Delete();
	//this->Renderer->Delete();

	position[0] = 0;
	position[1] = 0;

	state = false;
}