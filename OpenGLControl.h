#pragma once
#include "afxwin.h"
#include <GLEW\glew.h>
#include <glut.h>

#define SIZE_RESIZE 5

class OpenGLControl : public CWnd
{
public:
	//Timer
	UINT_PTR _Timer;

	float _fLastX;
	float _fLastY;
	float _fRotX;
	float _fRotY;
	float _fZoom;
	float _fPosX;
	float _fPosY;
	bool _isMaximized;

	float space;
	float step;

public:
	OpenGLControl();
	virtual ~OpenGLControl();

	void oglCreate(CRect rect, CWnd *parent);
	void oglInitialize(void);
	void oglDrawCube(void);
	void oglDrawSphere(void);
	void LightShine(void);

private:
	CWnd *hWnd;
	HDC hdc;
	HGLRC hrc;
	int _pixelFormat;
	CRect _rect;
	CRect _oldWindow;
	CRect _originalRect;

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTranslate(CDC *pDC);	//manually added
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//If you declare any member after DECLARE_MESSAGE_MAP,
	//you must specify a new access type (public, private, or protected) for them.
	DECLARE_MESSAGE_MAP()
};

