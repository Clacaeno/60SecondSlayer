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

using Aspen::Engine::Engine;
using Aspen::GameState::GameState;
using Aspen::GameState::GameStateManager;
using Aspen::Graphics::Graphics;
using Aspen::Object::Object;

void ChangeScene(Aspen::Graphics::UI::Button *button, std::string scene, GameStateManager *gsm)
{
  gsm->SetCurrentState(scene);
}


    float charPosX = 543.0f;
    float charPosY = 1684.0f;

    float enPosX = 2948.0f;
    float enPosY = 1618.0f;

    float bgPosX = 490.0f;
    float bgPosY = 360.0f;

class BackGround : public Object
{
    Aspen::Graphics::Animation *BG;

    public:
    BackGround(Object *parent = nullptr, std::string name = "BG") : Object(parent, name)
    {
    BG = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/BG.png", 980, 720 , 1, nullptr, "BG"));
    BG->GetTransform()->SetPosition(bgPosX,bgPosY);
    BG->GetTransform()->SetScale(1,1);
    AddChild(BG);
    }

    void OnUpdate()
    {
    }
};
class Player : public Object
{
    int Hp;
    int MaxHP;
    int Speed;
    int Attack;
    int Defense;
    int Gold;
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
    if(Aspen::Input::KeyHeld(SDLK_SPACE))
    {
      RogueIdle->Deactivate();
      RogueStab->Activate();
    }
    }
};
class Slop : public Object
{
    int Hp;
    int MaxHP;
    int Speed;
    int Attack;
    int Defense;
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
    if(Aspen::Input::KeyHeld(SDLK_SPACE))
    {
      SlopBounce->Deactivate();
      SlopHurt->Activate();
    }

  }
};

class StoreOwner : public Object
{
  Aspen::Graphics::Animation *anim;

    public:
    StoreOwner(Object *parent = nullptr, std::string name = "Store Owner") : Object(parent, name)
    {
    anim = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Rogue.png", 960, 768 , 1, nullptr, "RogueIdle"));
    AddChild(anim);
    }

    void OnUpdate()
    {
    if(Aspen::Input::KeyHeld(SDLK_a))
    {

    }
    if(Aspen::Input::KeyHeld(SDLK_s))
    {
        
    }
    if(Aspen::Input::KeyHeld(SDLK_d))
    {
        
    }
    }
};

class MainMenu : public GameState
{   
    double time;
    
  Aspen::Graphics::UI::Text *title;
  Aspen::Graphics::Animation *sprite; 


  public:
  MainMenu(Object *parent = nullptr, std::string name = "Mainmenu") : GameState(parent, name)
  { 
    CreateChild<BackGround>();
    CreateChild<Player>();
    CreateChild<Slop>();

  }

  void OnUpdate()
  {
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

