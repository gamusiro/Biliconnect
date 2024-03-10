/*=========================================================================
	Date : 2022/04/04(月)	SceneInterface.h
		Author : がむしるぉ
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

