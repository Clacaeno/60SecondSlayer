#include "Engine.hpp"
#include "Graphics.hpp"
#include "UI.hpp"
#include "Transform.hpp"
#include "Controller.hpp"
#include "Physics.hpp"
#include "Time.hpp"
#include "Log.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "GameState.hpp"
#include "Debug.hpp"
#include <iostream>
#include <cmath>

using Aspen::Engine::Engine;
using Aspen::GameState::GameState;
using Aspen::GameState::GameStateManager;
using Aspen::Graphics::Graphics;
using Aspen::Object::Object;

void ChangeScene(Aspen::Graphics::UI::Button *button, std::string scene, GameStateManager *gsm)
{
  gsm->SetCurrentState(scene);
}
    int roundNum = 1;
    int mKilled = 0;
    int mHp = 5;
    int mMaxHP = 5;
    int mSpeed = 1;
    int mAttack = 3;
    int mDefense = 2;
    int Score = 0; 

    int eHp = 7;
    int eMaxHP = 7;
    int eSpeed = 2;
    int eAttack = 3;
    int eDefense = 0;

    int pHp = 20;
    int pMaxHP = 20;
    int pSpeed = 4;
    int pAttack = 5;
    int pDefense = 2;
    int pRestoration = 2;
    int Gold = 0;


    float charPosX = 543.0f;
    float charPosY = 1684.0f;

    float enPosX = 2948.0f;
    float enPosY = 1618.0f;

    float bgPosX = 490.0f;
    float bgPosY = 360.0f;

    float timerX = 474.0f;
    float timerY = 42.0f;

    float timer = 60.00;

class BackGround : public Object
{
    Aspen::Graphics::Animation *BG;
    Aspen::Graphics::UI::Text *timertext;
    public:
    BackGround(Object *parent = nullptr, std::string name = "BG") : Object(parent, name)
    {
    BG = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/BG.png", 980, 720 , 1, nullptr, "BG"));
    BG->GetTransform()->SetPosition(bgPosX,bgPosY);
    BG->GetTransform()->SetScale(1,1);
    timertext = new Aspen::Graphics::UI::Text("Hello", "default", 90);
    timertext->GetTransform()->SetPosition(timerX, timerY);
    AddChild(BG);
    AddChild(timertext);
    }

    void SetTimerText(std::string str)
    {
      timertext->SetText(str);
    }
    void OnUpdate()
    {
      timer -= Aspen::Engine::Engine::Get()->FindChildOfType<Aspen::Time::Time>()->DeltaTime();
      timertext->SetText(std::to_string(int(std::ceil(timer))));
      if (timer <= 0)
      {
        Aspen::Engine::Engine::Get()->End();
      }
    }
};
class Player : public Object
{
  Aspen::Graphics::Animation *RogueIdle;
  Aspen::Graphics::Animation *RogueStab;

    public:
    Player(Object *parent = nullptr, std::string name = "Player") : Object(parent, name)
    {
    RogueIdle = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Rogue.png", 960, 768 , 1, nullptr, "RogueIdle"));
    RogueStab = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/RogueStab.png", 960, 768 , 6, nullptr, "RogueStab"));
    RogueStab->GetTransform()->SetScale(0.3 , 0.3);
    RogueIdle->GetTransform()->SetScale(0.3 , 0.3);
    RogueIdle->GetTransform()->SetPosition(charPosX,charPosY);
    RogueStab->GetTransform()->SetPosition(charPosX,charPosY);
    AddChild(RogueStab);
    AddChild(RogueIdle);
    RogueStab->Deactivate();
    }

    void OnUpdate()
    {
      
    RogueStab->Deactivate();
    RogueIdle->Activate();
    if(Aspen::Input::KeyPressed(SDLK_a))
    {
      RogueIdle->Deactivate();
      RogueStab->Activate();
      mHp -= (pAttack - mDefense);
      pHp -= (mAttack - pDefense);
    }
    }
};
class Slop : public Object
{
  Aspen::Graphics::Animation *SlopBounce;
  Aspen::Graphics::Animation *SlopHurt;

    public:
    Slop(Object *parent = nullptr, std::string name = "Slop") : Object(parent, name)
    {
    SlopBounce = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Slop1.png", 1024, 1024 , 5, nullptr, "SlopBounce"));
    SlopHurt = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Slop2.png", 1024, 1024 , 2, nullptr, "SlopHurt"));
    SlopBounce->GetTransform()->SetScale(0.3 , 0.3);
    SlopHurt->GetTransform()->SetScale(0.3 , 0.3);
    SlopBounce->GetTransform()->SetPosition(2948, 1618);
    SlopHurt->GetTransform()->SetPosition(2948, 1618);
    AddChild(SlopHurt);
    AddChild(SlopBounce);
    SlopBounce->Activate();
    SlopHurt->Deactivate();
    }


  void OnUpdate()
  {
    SlopBounce->Activate();
    SlopHurt->Deactivate();
    if(Aspen::Input::KeyPressed(SDLK_a))
    {
      SlopBounce->Deactivate();
      SlopHurt->Activate();
    }

  }
};

class StoreOwner : public Object
{
  Aspen::Graphics::Sprite *sprite;
  Aspen::Graphics::Animation *Shopkeep;

    public:
    StoreOwner(Object *parent = nullptr, std::string name = "Store Owner") : Object(parent, name)
    {
    Shopkeep = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/ShopKeeper.png", 64, 64, 16, nullptr, "SlopBounce"));
    sprite = new Aspen::Graphics::Sprite("./resources/Rogue.png", nullptr, "RogueIdle");
    //Shopkeep->GetTransform()->SetPosition(shopX, shopY);
    AddChild(sprite);
    AddChild(Shopkeep);
    }

    
    void OnUpdate()
    {
    if(Aspen::Input::KeyPressed(SDLK_a) && Gold >= 2)
    {
      pAttack++;
      Gold -= 3;
      Score += 35;
    }
    if(Aspen::Input::KeyPressed(SDLK_s) && Gold >= 1)
    {
      pDefense++;
      Gold -= 1;
      Score += 35;
      
    }
    if(Aspen::Input::KeyPressed(SDLK_d) && Gold >= 3)
    {
      pRestoration++;
      Gold -= 2;
      Score += 35;
    }

    
    }
};

class MainMenu : public GameState
{   
    double time;
    
  Aspen::Graphics::UI::Text *title;
  Aspen::Graphics::UI::Text *title2;
  Aspen::Graphics::Animation *sprite; 
  BackGround *bg;


  public:
  MainMenu(Object *parent = nullptr, std::string name = "Mainmenu") : GameState(parent, name)
  {
    bg = new BackGround();
    AddChild(bg);
    CreateChild<Player>();
    CreateChild<Slop>();


    title = new Aspen::Graphics::UI::Text("WWWWWWWW", "default", 64, this, "Title");
    title2 = new Aspen::Graphics::UI::Text("WWWWWWWW", "default", 64, this, "Title");
    title->GetTransform()->SetPosition(127,339);
    title2->GetTransform()->SetPosition(846,438);
    AddChild(title);
    AddChild(title2);
  }

  void OnUpdate()
  {
    title->SetText(std::to_string(pHp) + " / " + std::to_string(pMaxHP));
    title2->SetText(std::to_string(mHp) + " / " + std::to_string(mMaxHP));

    if (pHp < 1)
    {
      Aspen::Engine::Engine::Get()->FindChildOfType<Aspen::GameState::GameStateManager>()->SetCurrentState("Shop");
    }
    else if (mHp < 1)
    {
      mKilled++;
      if (mKilled == 5 * roundNum)
      {
        Gold += 20;
        Score += 100;
        Aspen::Engine::Engine::Get()->FindChildOfType<Aspen::GameState::GameStateManager>()->SetCurrentState("Shop");
      }
    }
  }

};
class Shop : public GameState
{   
    double time;
  Aspen::Graphics::UI::Text *AtkBuy;
  Aspen::Graphics::UI::Text *DefBuy;
  Aspen::Graphics::UI::Text *HpBuy;
  Aspen::Graphics::Animation *sprite; 


  public:
  Shop(Object *parent = nullptr, std::string name = "Shop") : GameState(parent, name)
  {
    CreateChild<StoreOwner>();
    AtkBuy = new Aspen::Graphics::UI::Text("+1 Attack! (A)", "default", 64, this, "atkbuy");
    DefBuy = new Aspen::Graphics::UI::Text("+1 Defense! (S)", "default", 64, this, "atkbuy");
    HpBuy = new Aspen::Graphics::UI::Text("+5 Health! (D)", "default", 64, this, "atkbuy");
    AtkBuy->GetTransform()->SetPosition(100, 100);
    DefBuy->GetTransform()->SetPosition(100, 100);
    HpBuy->GetTransform()->SetPosition(100, 100);
  }

  void OnUpdate()
  {

  }

};
class Score1 : public GameState
{   
    
  Aspen::Graphics::UI::Text *title;

  public:
  Score1(Object *parent = nullptr, std::string name = "Score1") : GameState(parent, name)
  {
    title = new Aspen::Graphics::UI::Text("WWWWWWWW", "default", 64, this, "Title");
    title->GetTransform()->SetPosition(127,339);
    AddChild(title);
    title->SetText(std::to_string(Score));
  }
};


class Game : public GameState
{

};
int main(int argc, char **argv)
{
  

  Aspen::Log::Log::SetFile("./Aspen.log");

  Engine engine(Aspen::Engine::START_FLAGS::ALL ^(
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS |
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_DEBUGGER |
    Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_FONTCACHE
  ));
  Aspen::Graphics::Graphics *gfx = new Aspen::Graphics::Graphics(980,720);
  gfx->CreateChild<Aspen::Debug::Debug>();
  gfx->CreateChild<Aspen::Graphics::FontCache>();
  engine.AddChild(gfx);


  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(0);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<GameStateManager>()->LoadState<MainMenu>(true);
 // engine.FindChildOfType<GameStateManager>()->LoadState<Game>(false);



  while (engine)
    engine();
  return 0;
}

