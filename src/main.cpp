#include <Arduino.h>
#include <SD.h>

#include <Speaker.h>

Speaker musicPlayer;

const int speakerPin = 7;
const int cardCSPin = 4;
const int serialBaudRate = 9600;

void setup()
{
    Serial.begin(serialBaudRate);
    
    if(not SD.begin(cardCSPin))
    {
        Serial.println("Failed to initialise SD Card. Perhaps your wires aren't properly connected?");
    }

    musicPlayer.onPin(speakerPin);
}

void loop()
{
    FileSongLoader *inputSong = FileSongLoader::fromFile("SMBTheme.phi");

    musicPlayer.playSong(inputSong);
}