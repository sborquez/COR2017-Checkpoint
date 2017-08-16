#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

class GpioPin {
public:
  GpioPin (int pin);
  ~GpioPin () {};

  void update_state();

  inline std::vector<bool> get_states() { return states; };
  inline int get_id() { return id; };

private:
    int id;
    std::vector<bool> states;
};



class InputHandler
{
public:
    InputHandler();

    ~InputHandler();

    // Actualize inputs
    void update();

    // Check if key is pressed
    bool isKeyDown(SDL_Scancode key);
    bool isKeyDown(std::string botton);

    // Check if key is not pressed
    bool isKeyUp(SDL_Scancode key);
    bool isKeyUp(std::string botton);

    // Check if key was pressed once
    bool onPress(SDL_Scancode key);
    bool onPress(std::string botton);

    // Gpio
    // setup pin
    bool setupPins();

    // enable a pin:
    // you can use an id, both method and a GpioPin class to
    // gpio_inputs using pin number as key.
    // enable pin as input, don't add to botton_gpio
    bool enablePin(int pin);
    // enable pin as input and add it to botton_gpio
    bool enablePin(int pin, std::string id);

    // inputs
    // Test
    bool isPinOn(int pin);
    inline bool isBPinOn(std::string botton)
    {
      isPinOn(gpio_bottons[botton]);
    }

    bool isPinOff(int pin);
    inline bool isBPinOff(std::string botton)
    {
      isPinOff(gpio_bottons[botton]);
    }

    // Check if key was pressed once
    // TODO
    //bool onRising(int pin);
    //inline bool onRising(std::string botton)
    //{
    //  onRising(gpio_bottons[botton]);
    //}

    inline bool get_gpio() { return gpio; }; 

private:
    // botton keys
    std::map<std::string, Uint8> keyboard_bottons;

    // Keys pressed once in actual state
    std::map<Uint8, bool> m_pressKey;

    // Keys pressed in actual state
    const Uint8* m_Keystate;

    // enable gpio inptus
    bool gpio;
    //
    std::map<std::string, int> gpio_bottons;
    std::map<int, GpioPin*> gpio_inputs;
};
#endif
