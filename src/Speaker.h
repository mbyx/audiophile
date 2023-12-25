#include <Arduino.h>
#include <Song.h>

/* An active buzzer that can play songs in a custom format. */
struct Speaker
{
    int speakerPin;
    /* This determines how long the speaker pauses between each melody, calculated as `noteDuration * beatSeparation` */
    int beatSeparation = 1.3;

    /* Sets the pin that the speaker will control to play a song. */
    void onPin(int pin)
    {
        speakerPin = pin;
        pinMode(speakerPin, OUTPUT);
    }

    /* Plays a single melody, taking `beatSeparation` into account. */
    void playMelody(Melody melody)
    {
        tone(speakerPin, melody.noteFrequency, melody.noteDuration);
        delay(melody.noteDuration);
        noTone(speakerPin);
        delay(melody.noteDuration * beatSeparation);
    }

    /* Plays a song as a series of melodies to completion. */
    void playSong(SongLoader* song)
    {
        while (not song->hasEnded())
        {
            playMelody(song->nextMelody());
        }
    }
};