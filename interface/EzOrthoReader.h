#pragma once
#include "pch.h"
#include <string>
#include <vector>
using namespace std;
using namespace EZOrthoDataStructure;
using namespace System;
class EzOrthoReader
{
public:
	EzOrthoReader()
	{
			
	}

	void LoadEzOrtho(std::string filePath)
	{
		orthoData = gcnew ProjectDataWrapper();
		orthoData->ProjectDataWrapperDeserialize(gcnew String(filePath.c_str()));
	}

	void GetCoord(int toothId,float m[16])
	{
		for (int i=0;i<16;i++)
		{
			m[i] = orthoData->toothCoordinates[toothId]->Mv[i];
		}
	}

	void GetModel(int toothId, vector<float[3]> &pts,vector<int[3]> &face)
	{
		auto model_binary = orthoData->models->tooth[toothId];
		IW_ModelStructure^ model = gcnew IW_ModelStructure();
		model->BinaryDeserialization(model_binary);

	/*	for (int i = 0; i < model->vertex->Length; i++)
		{
			float v[3];
			v[0] = model->vertex[i]->x;
			v[1] = model->vertex[i]->y;
			v[2] = model->vertex[i]->z;
			pts.push_back(v);
		}
		
		for (int i = 0; i < model->face->Length; i++)
		{
			int f[3];
			f[0] = model->face[i]->a;
			f[1] = model->face[i]->b;
			f[2] = model->face[i]->c;
			face.push_back(f);
		}*/
	}
private:
	gcroot<ProjectDataWrapper^> orthoData;

};

