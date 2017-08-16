#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

class GpioPin {
private:
    int id;
    std::vector<bool> previous_states(5, LOW);

public:
    GpioPin (int pin);
    ~GpioPin ();
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
    bool isBPinOn(std::string botton);
    bool isPinOn(int pin);

    bool isBPinOff(std::string botton)
    bool isPinOff(int pin);

    // Check if key was pressed once
    bool onRising(std::string botton);
    bool onRising(int pin);

private:
    // botton keys
    std::map<std:string, SDL_Scancode> keyboard_bottons

    // Keys pressed once in actual state
    std::map<Uint8, bool> m_pressKey;

    // Keys pressed in actual state
    const Uint8* m_Keystate;

    // enable gpio inptus
    bool gpio;
    //
    std::map<int, GpioPin*> gpio_inputs;
    std::map<std::string, int> gpio_bottons;
};
#endif
