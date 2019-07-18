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
#include "Debug.hpp"
#include "GameState.hpp"
#include <iostream>

// Hello comment!

using Aspen::Engine::Engine;
using Aspen::GameState::GameState;
using Aspen::GameState::GameStateManager;
using Aspen::Graphics::Graphics;
using Aspen::Object::Object;

void ChangeScene(Aspen::Graphics::UI::Button *button, std::string scene, GameStateManager *gsm)
{
  gsm->SetCurrentState(scene);
}

class MainMenu : public GameState
{ 
      float charPosX = 505.0f;
    float charPosY = 1681.0f;

    float enPosX = 2885.0f;
    float enPosY = 1701.0f;

    float bgPosX = 490.0f;
    float bgPosY = 360.0f;

    float offScrX = -1436.0f;
    float offScrY = 566.0f;
    
  Aspen::Graphics::UI::Text *title;
  Aspen::Graphics::Animation *sprite; 
  Aspen::Graphics::Animation *ss4;
  Aspen::Graphics::Animation *ss5;
  Aspen::Graphics::Animation *ss6;
  Aspen::Graphics::Animation *ss7;
  Aspen::Graphics::Animation *ss8;

  public:
  MainMenu(Object *parent = nullptr, std::string name = "Mainmenu") : GameState(parent, name)
  { 
    Aspen::Log::Debug("Started making main menu");

    //  Aspen::Graphics::UniformSpritesheet *ss2 = new Aspen::Graphics::UniformSpritesheet("./resources/Colosseum.png", 1885, 1414, 1, nullptr, "ColosseumSS");
    //  sprite = new Aspen::Graphics::Animation(ss2, 1.0f / 12.0f, this, "Colosseum");
    //  ss2->GetTransform()->SetPosition(529,399);
    //  ss2->GetTransform()->SetScale(0.590 , 0.590);
    //  AddChild(sprite);

    //  Aspen::Graphics::UniformSpritesheet *ss3 = new Aspen::Graphics::UniformSpritesheet("./resources/menu.png", 100,100 , 1, nullptr, "MenuSS");
    //  sprite = new Aspen::Graphics::Animation(ss3, 1.0f / 12.0f, this, "Menu");
    //  ss3->GetTransform()->SetPosition(529,399);
    //  ss3->GetTransform()->SetScale(0.590 , 0.590);
    //  AddChild(sprite);

    ss4 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Rogue.png", 960, 768 , 1, nullptr, "RogueIdle"));
    ss5 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/RogueStab.png", 960, 768 , 6, nullptr, "RogueStab"));
    ss6 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Slop1.png", 1024, 1024 , 5, nullptr, "SlopBounce"));
    ss7 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Slop2.png", 1024, 1024 , 2, nullptr, "SlopHurt"));
    ss8 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/BG.png", 980, 720 , 1, nullptr, "BG"));
    //sprite = new Aspen::Graphics::Animation(ss5, 1.0f / 12.0f, this, "RogueStab");
    
    ss5->GetTransform()->SetScale(0.3 , 0.3);
    ss6->GetTransform()->SetScale(0.3 , 0.3);
    ss7->GetTransform()->SetScale(0.3 , 0.3);
    ss7->GetTransform()->SetScale(1 , 1);

    //Aspen::Graphics::UniformSpritesheet *ss4 = new Aspen::Graphics::UniformSpritesheet("./resources/Rogue.png", 960, 768 , 1, nullptr, "RogueIdle");
    //sprite = new Aspen::Graphics::Animation(ss4, 1.0f / 12.0f, this, "RogueIdle");
    //  ss4->GetTransform()->SetPosition(offScrX,offScrY);
    ss8->GetTransform()->SetPosition(bgPosX,bgPosY);
    ss4->GetTransform()->SetScale(0.3 , 0.3);
    AddChild(ss8);
    AddChild(ss7);
    AddChild(ss6);
    AddChild(ss5);
    AddChild(ss4);
    ss5->GetTransform()->SetPosition(offScrX,offScrY);
    ss6->GetTransform()->SetPosition(enPosX,enPosY);
    ss7->GetTransform()->SetPosition(offScrX,offScrY);


    //  title = new Aspen::Graphics::UI::Text("WEEEEEEEEEEE", this, "Title");
    //  AddChild(title);
    //  title->GetTransform()->SetPosition(201, 83);
    //  title->GetTransform()->SetRotation(0.174f);
    //  title->GetTransform()->SetScale(1.56, 2.6);
    //  title->CreateChild<Aspen::Physics::Rigidbody>();

    


  }
  
  void OnUpdate()
  {
    ss5->GetTransform()->SetPosition(offScrX,offScrY);
    ss4->GetTransform()->SetPosition(charPosX,charPosY);
    ss6->GetTransform()->SetPosition(enPosX,enPosY);
    ss7->GetTransform()->SetPosition(offScrX,offScrY);
    if(Aspen::Input::KeyHeld(SDLK_SPACE))
    {
      ss4->GetTransform()->SetPosition(offScrX,offScrY);
      ss5->GetTransform()->SetPosition(charPosX,charPosY);
      ss6->GetTransform()->SetPosition(offScrX,offScrY);
      ss7->GetTransform()->SetPosition(enPosX,enPosY);

    }

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

