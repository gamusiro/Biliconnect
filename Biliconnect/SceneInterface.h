/*=========================================================================
	Date : 2022/04/04(��)	SceneInterface.h
		Author : ���ނ��邧
		Update : 
=========================================================================*/
#pragma once
#ifndef SCENEINTERFACE_H_
#define SCENEINTERFACE_H_

class SceneInterface
{
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif // !SCENEINTERFACE_H_

