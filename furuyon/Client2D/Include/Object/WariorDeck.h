
#pragma once
#include "Deck.h"
class CWariorDeck :
	public CDeck
{
public:
	CWariorDeck();
	CWariorDeck(const CWariorDeck& obj);
	virtual ~CWariorDeck();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CWariorDeck* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

