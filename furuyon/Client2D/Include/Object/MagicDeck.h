#pragma once
#include "Deck.h"
class CMagicDeck :
    public CDeck
{
public:
	CMagicDeck();
	CMagicDeck(const CMagicDeck& obj);
	virtual ~CMagicDeck();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMagicDeck* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

