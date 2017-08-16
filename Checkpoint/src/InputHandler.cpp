#include "../include/InputHandler.hpp"
#include "../include/Application.hpp"

#include <wiringPi.h>

/***********************/
/*  InputHandler CLASS */
/***********************/

InputHandler::InputHandler()
{
    gpio = false;

    // setup keyboard_bottons
    //test without config file
    // TODO load from config file
    keyboard_bottons["B_UP"] = SDL_SCANCODE_UP;
    keyboard_bottons["B_DOWN"]= SDL_SCANCODE_DOWN;
    keyboard_bottons["B_LEFT"] = SDL_SCANCODE_LEFT;
    keyboard_bottons["B_RIGHT"] = SDL_SCANCODE_RIGHT;
    keyboard_bottons["B_A"] = SDL_SCANCODE_Z;
    keyboard_bottons["B_B"] = SDL_SCANCODE_X;
    keyboard_bottons["B_C"] = SDL_SCANCODE_C;
    keyboard_bottons["B_D"]  = SDL_SCANCODE_S;
    keyboard_bottons["B_LTRIGER"] = SDL_SCANCODE_A;
    keyboard_bottons["B_RTRIGER"] = SDL_SCANCODE_D;
    keyboard_bottons["B_START"] = SDL_SCANCODE_EXECUTE;
    keyboard_bottons["B_SELECT"] = SDL_SCANCODE_BACKSPACE;
    keyboard_bottons["B_RESET"] = SDL_SCANCODE_R;
    keyboard_bottons["B_QUIT"] = SDL_SCANCODE_ESCAPE;

    m_Keystate = SDL_GetKeyboardState(NULL);
}

InputHandler::~InputHandler()
{
    if (gpio) {
      for(auto it=gpio_inputs.begin(); it != gpio_inputs.end(); ++it)
        delete it->second;
      gpio_inputs.clear();
      gpio_bottons.clear();
    }
    m_pressKey.clear();
}

// Actualize inputs
void InputHandler::update()
{
    // update gpio inputs
    if (gpio) {
      for(auto it = gpio_inputs.begin(); it != gpio_inputs.end(); ++it) {
        it->second->update_state();
      }
    }

    // event structure
    SDL_Event event;

    // Clear previous state
    m_pressKey.clear();

    while(SDL_PollEvent(&event)) {
        switch (event.type) {

        // Evento de cierre de la aplicacion
        case SDL_QUIT:
            TheApplication->quit();
            break;

        // Evento de presion de tecla
        case SDL_KEYDOWN:
            // Se guarda si la tecla fue presionada solo una vez o se mantuvo pulsada
            if (not event.key.repeat)
                m_pressKey[event.key.keysym.scancode] = true;
            break;
        default:
            break;
        }
    }
}

// Check if key is pressed
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    return m_Keystate[key];
}
bool InputHandler::isKeyDown(std::string botton)
{
    return m_Keystate[keyboard_bottons[botton]];
}

// Check if key is not pressed
bool InputHandler::isKeyUp(SDL_Scancode key)
{
    return not m_Keystate[key];
}
bool InputHandler::isKeyUp(std::string botton)
{
    return not m_Keystate[keyboard_bottons[botton]];
}

// Check if key was pressed once
bool InputHandler::onPress(SDL_Scancode key)
{
    return m_pressKey[key];
}
bool InputHandler::onPress(std::string botton)
{
    return m_pressKey[keyboard_bottons[botton]];
}

//gpio

bool InputHandler::setupPins()
{
  gpio = true;
  wiringPiSetup();

  // TODO Leer archivo de configuracion
  //
  gpio_bottons["B_QUIT"] = 4;
  gpio_bottons["B_START"] = 5;
  gpio_bottons["B_RESET"] = 6;

  for (auto it=gpio_bottons.begin(); it != gpio_bottons.end(); ++it)
      enablePin(it->second);
}

bool InputHandler::enablePin(int pin)
{
    gpio_inputs[pin] = new GpioPin(pin);
}

bool InputHandler::enablePin(int pin, std::string id)
{
  gpio_bottons[id] = pin;
  enablePin(pin);
}


//TODO define in GpioPin 
bool InputHandler::isPinOn(int pin)
{
  std::vector<bool> tmpStates = gpio_inputs[pin]->get_states();
  short int suma = tmpStates[0] + tmpStates[1] + tmpStates[2] + tmpStates[3] + tmpStates[4] ;
  return suma >= 3;
}

bool InputHandler::isPinOff(int pin)
{
  return !(isPinOn(pin));
}

bool InputHandler::onRising(int pin)
{
  short int edge;
  short int body;
  std::vector<bool> tmpStates = gpio_inputs[pin]->get_states();

  edge = tmpStates[0] + tmpStates[1] + tmpStates[2];
  body = tmpStates[3] + tmpStates[4];

  return (edge == 3 and body == 0);

}


/***************/
/*  GPIO CLASS */
/***************/

GpioPin::GpioPin (int pin)
{
    pinMode(pin, INPUT);
    id = pin;
    states = {0, 0, 0, 0, 0};
}

void GpioPin::update_state()
{
    bool value = digitalRead(id);
    states.insert(states.begin(), value);
    states.pop_back();
}
