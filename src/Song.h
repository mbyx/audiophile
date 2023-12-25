#include <SD.h>
#include <Melody.h>

const int maxLineLength = 50;

/* An abstract song that can be loaded from anywhere. */
struct SongLoader
{
    virtual bool hasEnded() = 0;
    virtual Melody nextMelody() = 0;
};

/* A song stored in a string, keeping track of its progress to play the song. */
struct StringSongLoader : SongLoader
{
    String rawSong;
    int startOfLine = 0;

    /* Determines whether the song has finished playing. */
    bool hasEnded()
    {
        return rawSong.substring(startOfLine).length() == 0;
    }

    /* Extract the next melody available from the string.
    This method keeps track of it's current progress through the song. */
    Melody nextMelody()
    {
        int lengthOfLine = 0;

        while (rawSong.charAt(startOfLine + lengthOfLine) != '\n')
        {
            lengthOfLine++;
        }

        Melody outMelody = Melody::fromString(rawSong.substring(startOfLine, startOfLine + lengthOfLine));

        startOfLine += lengthOfLine + 1;

        return outMelody;
    }

    /* Store the string that contains the song. */
    static StringSongLoader* fromString(String unparsedSong)
    {
        StringSongLoader* outSong = new StringSongLoader();
        outSong->rawSong = unparsedSong;

        return outSong;
    }
};

/* A song that is stored in a file, which is streamed line by line to play it. */
struct FileSongLoader: SongLoader
{
    File fileHandle;

    /* Determines whether the song has finished playing. */
    bool hasEnded()
    {
        return fileHandle.available() == 0;
    }

    /* Extract the next melody available from the file.
    This method keeps track of it's current progress through the song. */
    Melody nextMelody()
    {
        int lengthOfLine = 0;
        int startOfLine = fileHandle.position();

        while (fileHandle.peek() != '\n')
        {
            fileHandle.seek(startOfLine + lengthOfLine);
            lengthOfLine++;
        }
        fileHandle.seek(startOfLine);

        char unparsedMelody[maxLineLength];
        fileHandle.read(unparsedMelody, lengthOfLine);

        return Melody::fromString(unparsedMelody);
    }

    /* Load the handle to the file that contains the song. */
    static FileSongLoader* fromFile(String filePath)
    {
        FileSongLoader* outSong = new FileSongLoader();
        outSong->fileHandle = SD.open(filePath);

        return outSong;
    }

    ~FileSongLoader()
    {
        fileHandle.close();
    }
};