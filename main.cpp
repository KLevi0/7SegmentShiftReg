#include <Arduino.h>

#define CLR 5
#define CLK 6
#define SER 7
uint8_t nums[10] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110  // 9
};

void shift(bool data)
{
    PORTD &= ~(1 << PORTD6);                                 // digitalWrite(c, LOW);
    data ? PORTD |= (1 << PORTD7) : PORTD &= ~(1 << PORTD7); // digitalWrite(s, data);
    PORTD |= (1 << PORTD6);                                  // digitalWrite(c, HIGH);
}

void clear(int pin)
{
    digitalWrite(pin, LOW);
    digitalWrite(pin, HIGH);
}

void function()
{
    Serial.begin(115200);
    pinMode(CLK, OUTPUT);
    pinMode(SER, OUTPUT);
    pinMode(CLR, OUTPUT);
    digitalWrite(CLR, HIGH);
    clear(CLR);
    uint8_t binary = 0b1000000;
    Serial.printf("%d", binary);
    for (uint8_t j = 0; j < 10; j++)
    {
        uint8_t mask = 0x01;
        for (uint8_t i = 0; i < 9; i++)
        {
            shift(!(nums[j] & mask));
            mask = mask << 1;
        }
        int k = 0;
        int state = 0;
        while (1)
        {
            pinMode(13, INPUT);
            if (digitalRead(13) != state)
            {
                k++;
                state = digitalRead(13);
            }

            if (k == 50)
                break;
        }
    }
}

int main()
{
    Serial.begin(9600);
    function();
    return 0;
}
