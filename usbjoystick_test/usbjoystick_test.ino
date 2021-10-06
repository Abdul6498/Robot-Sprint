// usbjoystick_test
// This sketch demonstrates simple use of the USBJoystick library
// It intialises the library, establishes callbacks for when inputs change
// and prints out details whenever an input changes and a callback is called.
//
// USB Host Shield uses an interrupt line, but does not establish an interrupt callback
// Note special requirements in documentation if you are using an older version of the USB Host Shield and a newer 
// version of the USB_Host_Shield library.
// Note special requirements to configure the WiShield librray to support the UDP application. 
// mikem@airspayce.com

#include <Usb.h>
#include <USBJoystick.h>

// Our singleton joystick
USBJoystick joy;

// Here we define some callbacks thgat will be called when a stick, button
// or hat switch changes. You can also have a callback called for every polled value, if you prefer.
// Alternatively, you can use the *Value() data accessory to asynchronously get the last read value
// for the sticks, buttons and hats.
char a , b;
// stick will be one of USBJOYSTICK_STICK_*
void stickValueDidChangeCallback(uint8_t stick, uint8_t value)
{
    //Serial.print("stickValueDidChangeCallback: ");
    //Serial.print(stick);
    //Serial.print(": ");
    //Serial.print(value);
    //Serial.println("");
    if(stick == 1 && value == 0 )
    {
    //Serial.println("FORWARD");
    Serial.print('w');
    }
        
    if(stick == 1 && value == 255)
    {
    //Serial.println("BACK"); 
    Serial.print('s');  
    }
    if(stick == 1 && value == 127 )
    {
    //Serial.println("STOP");
    Serial.print('x');
    }
    if(stick == 0 && value == 0)
    {
    //Serial.println("LEFT");
    Serial.print('d');
    }
    
    if(stick == 0 && value == 255)
    {
    //Serial.println("RIGHT");
    Serial.print('a');
    }
    if(stick == 0 && value == 127)
    {
    //Serial.println("STOP");
    Serial.print('b');
    }

}
// button will be one of USBJOYSTICK_BUTTON_*
volatile uint8_t button = 10;
void buttonValueDidChangeCallback(uint8_t button, uint8_t value)
{
    //Serial.print("buttonValueDidChangeCallback: ");
    //Serial.print(button);
    //Serial.print(": ");
    //Serial.print(value);
    //Serial.println("");
    if(button == 10 && value == 1)
    {
    //Serial.println("ANTI clkwise");
    Serial.print('l');
    }
    if(button == 10 && value == 0)
    {
    //Serial.println("Stop Anticlkwise");
    Serial.print('x');
    }
    if(button == 12 && value == 1)
    {
    //Serial.println("clkwise");
    Serial.print('j');
    }
    if(button == 12 && value == 0)
    {
    //Serial.println("Stop clkwise");
    Serial.print('b');
    }
    if(button == 0 && value == 1)
    {
    //Serial.println("KICK");
    Serial.print('k');
    }
    if(button == 0 && value == 0)
    {
    //Serial.println("Stop KICK");
    Serial.print('m');
    }
}
// hat will be one of USBJOYSTICK_HAT_*
// value will be one of USBJOYSTICK_HAT_POS_*
/*void hatValueDidChangeCallback(uint8_t hat, uint8_t value)
{
    Serial.print("hatValueDidChangeCallback: ");
    Serial.print(hat, DEC);
    Serial.print(": ");
    Serial.print(value, DEC);
    Serial.println("");
}*/

void setup()
{
  Serial.begin(115200);

  // Specify callbacks to call when inputs change
  joy.setStickValueDidChangeCallback(stickValueDidChangeCallback);
  joy.setButtonValueDidChangeCallback(buttonValueDidChangeCallback);
//  joy.setHatValueDidChangeCallback(hatValueDidChangeCallback);
  joy.init();
}

void loop()
{
  joy.run();  
}


