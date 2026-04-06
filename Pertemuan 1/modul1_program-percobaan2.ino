int timer = 100; // semakin besar nilainya, semakin lambat

void setup()
{
    // inisialisasi pin 2 sampai 7 sebagai OUTPUT
    for (int ledPin = 2; ledPin <= 7; ledPin++)
    {
        pinMode(ledPin, OUTPUT);
    }
}

void loop()
{
    // dari kiri ke kanan (2 → 7)
    for (int ledPin = 2; ledPin <= 7; ledPin++)
    {
        digitalWrite(ledPin, HIGH);
        delay(timer);
        digitalWrite(ledPin, LOW);
    }

    // dari kanan ke kiri (6 → 3)
    // (hindari duplikasi ujung agar LED 7 & 2 tidak menyala dua kali)
    for (int ledPin = 6; ledPin >= 3; ledPin--)
    {
        digitalWrite(ledPin, HIGH);
        delay(timer);
        digitalWrite(ledPin, LOW);
    }
}
