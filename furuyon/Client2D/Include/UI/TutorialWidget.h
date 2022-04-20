
#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Button.h"
#include "UI/Image.h"
#include "../Object/TutorialObj.h"
class CTutorialWidget :
	public CWidgetWindow
{
	friend class CViewport;

public:
	CTutorialWidget();
	CTutorialWidget(const CTutorialWidget& widget);
	virtual ~CTutorialWidget();

private:
	class CButton* m_MirrorMenuButton;
	class CButton* m_StageMenuButton;


	class CTutorialObj* m_TutorialObj;
public:
	void SetTutorialObj(class CTutorialObj* obj)
	{
		m_TutorialObj = obj;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CTutorialWidget* Clone();

private:
	void StartClick();
	void ExitClick();
	void StageExitClick();
	void Nothing();
	void SetSelectButton();
};


