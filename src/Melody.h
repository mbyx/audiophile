#include <Arduino.h>

/* Represents a sound frequency and the duration that it is played for.
Multiple melodies chained create a song.
*/
struct Melody
{
    /* The frequency of the note in Hz. */
    int noteFrequency;
    /* The duration the note is played for in milliseconds. */
    int noteDuration;

    /* Create a Melody from a string of the format `FREQUENCY DURATION` */
    static Melody fromString(String s)
    {
        int dividerIndex = s.indexOf(' ');
        
        String unparsedFrequency = s.substring(0, dividerIndex);
        String unparsedDuration = s.substring(dividerIndex + 1);
        
        unparsedFrequency.trim();
        unparsedDuration.trim();

        Melody parsedMelody;
        parsedMelody.noteFrequency = unparsedFrequency.toInt();
        parsedMelody.noteDuration = unparsedDuration.toInt();

        return parsedMelody;
    }
};