#include <Firmata.h>
#include <TCL.h>

const byte SYSEX_SET_COLORS = 1;
const int LEDS = 50;

byte strand[LEDS][3];

void setup()
{
    TCL.begin();
    TCL.setupDeveloperShield();

    clearStrand();

    Firmata.setFirmwareVersion(0, 1);
    Firmata.attach(START_SYSEX, sysexCallback);
    Firmata.begin(57600);
}

void loop()
{
    while(Firmata.available())
    {
        Firmata.processInput();
    }
}

void sysexCallback(byte command, int byteCount, byte *data)
{
    if (command == SYSEX_SET_COLORS)
    {
        int led = 0;
        int color = 0;
        for (int i = 0; i < byteCount; i++)
        {
            strand[led][color] = data[i];
            color = (color + 1) % 3;
            if (color == 0) led++;
        }

        updateStrand();
    }
}

void updateStrand()
{
    TCL.sendEmptyFrame();

    for (int i = 0; i < LEDS; i++)
    {
        TCL.sendColor(strand[i][0], strand[i][1], strand[i][2]);
    }

    TCL.sendEmptyFrame();
}

void clearStrand()
{
    for (int i = 0; i < LEDS; i++)
    {
        strand[i][0] = 0;
        strand[i][1] = 0;
        strand[i][2] = 0;
    }
    updateStrand();
}
