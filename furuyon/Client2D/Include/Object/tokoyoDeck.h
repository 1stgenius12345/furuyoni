#pragma once
#include "Deck.h"
class CtokoyoDeck :
	public CDeck
{
public:
	CtokoyoDeck();
	CtokoyoDeck(const CtokoyoDeck& obj);
	virtual ~CtokoyoDeck();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CtokoyoDeck* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

