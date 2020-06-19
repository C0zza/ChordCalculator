#include <iostream>
#include <string>
#include <vector>
#include "Console.h"

// Intervals between notes
enum Interval
{
    Minor2nd = 1,   // By default enums start from 0 so we manually set to 1, from which the enum shall increment from
    Major2nd,       // 2
    Minor3rd,       // 3
    Major3rd,       // 4
    Perfect4th,     // 5
    Diminished5th,  // 6
    Perfect5th,     // 7
    Minor6th,       // 8
    Major6th,       // 9
    Minor7th,       // 10
    Major7th,       // 11
    Octave          // 12
};

// Each musical note
enum Note
{
    a = 1,
    aSharp, // 2
    b,      // 3
    c,      // 4
    cSharp, // 5
    d,      // 6
    dSharp, // 7
    e,      // 8
    f,      // 9
    fSharp, // 10
    g,      // 11
    gSharp  // 12
};

// Appropriate naming convention for each note
const std::string noteNames[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };

// A combination of notes
struct aChord
{
    // List of notes
    std::vector<Note> notes;

    // Initialise the chord with a list of notes
    aChord(std::vector<Note> n)
    {
        notes = n;
    }

    // Print chord to console window
    void PrintChord()
    {
        // Loop through each note
        for (unsigned int i = 0; i < notes.size(); ++i)
        {
            // Print the name of the note at the index from the noteNames array (-1 because the noteNames array is 0 based)
            std::cout << noteNames[(int)notes[i] - 1] << " ";
        }
    }
};

// The interval sequence of sequence of notes
struct IntervalPattern
{
    // Name of the interval pattern
    std::string name = "";

    // Stores list of intervals
    std::vector<Interval> intervalPattern;

    // Initialise interval pattern with vector of intervals
    IntervalPattern(std::vector<Interval> intervals, std::string patternName)
    {
        intervalPattern = intervals;
        name = patternName;
    }

    // Determine whether an two interval pattern objects are the same
    bool isEqual(const IntervalPattern& other)
    {
        // if they are of equal size
        if (intervalPattern.size() == other.intervalPattern.size())
        {
            // Loop through each index and compare
            for (unsigned int i = 0; i < intervalPattern.size(); ++i)
            {
                if (intervalPattern[i] == other.intervalPattern[i])
                {
                    // indexes are equal so go to next loop
                    continue;
                }
                else
                {
                    // indexes are not equal so return false
                    return false;
                }
            }

            // End of for loop so all indexes were equal, return true
            return true;
        }
        else
        {
            // sizes are different so not equal, return false
            return false;
        }
    }
};

// Forward decleration of function
IntervalPattern GetIntervalPatternFromChord(aChord c);

int main()
{
    // Manages console window
    Console console;
    // Sets text colour to green
    console.setCharacterAttribute(10);

    // List of interval patterns to reference to
    std::vector<IntervalPattern> intervalPatterns;

    // Major interval pattern
    std::vector<Interval> majorIntervalPattern = { Major3rd, Perfect5th };
    IntervalPattern major(majorIntervalPattern, "Major");
    intervalPatterns.push_back(major);

    // Minor interval pattern
    std::vector<Interval> minorIntervalPattern = { Minor3rd, Perfect5th };
    IntervalPattern minor(minorIntervalPattern, "Minor");
    intervalPatterns.push_back(minor);

    // Augmented interval pattern
    std::vector<Interval> augmentedIntervalPattern = { Major3rd, Minor6th };
    IntervalPattern augmented(augmentedIntervalPattern, "Augmented");
    intervalPatterns.push_back(augmented);

    // Diminished interval pattern
    std::vector<Interval> diminishedIntervalPattern = { Minor3rd, Diminished5th };
    IntervalPattern diminished(diminishedIntervalPattern, "Diminished");
    intervalPatterns.push_back(diminished);

    // List of chords to test
    std::vector<aChord> chords;

    // C Major chord
    std::vector<Note> cMajorNotes = { c,e,g };
    aChord cMajor(cMajorNotes);
    chords.push_back(cMajor);

    // C Minor chord
    std::vector<Note> cMinorNotes = { c, dSharp, g };
    aChord cMinor(cMinorNotes);
    chords.push_back(cMinor);

    // F Major chord
    std::vector<Note> fMajorNotes = { f, a, c };
    aChord fMajor(fMajorNotes);
    chords.push_back(fMajor);

    // G Major chord
    std::vector<Note> gMajorNotes = { g, b, d };
    aChord gMajor(gMajorNotes);
    chords.push_back(gMajor);

    // D Minor chord
    std::vector<Note> dMinorNotes = { d, f, a };
    aChord dMinor(dMinorNotes);
    chords.push_back(dMinor);

    // E Minor chord 
    std::vector<Note> eMinorNotes = { e, g, b };
    aChord eMinor(eMinorNotes);
    chords.push_back(eMinor);

    // C Augmented
    std::vector<Note> cAugmentedNotes = { c, e, gSharp };
    aChord cAugmented(cAugmentedNotes);
    chords.push_back(cAugmented);

    // B Diminished
    std::vector<Note> bDiminishedNotes = { b, d, f };
    aChord bDiminished(bDiminishedNotes);
    chords.push_back(bDiminished);

    // Loop through all chords
    for (unsigned int i = 0; i < chords.size(); ++i)
    {
        // Get interval pattern of chords
        IntervalPattern resultIntervalPattern(GetIntervalPatternFromChord(chords[i]));

        // Loop through all potential interval patterns
        for (unsigned int j = 0; j < intervalPatterns.size(); ++j)
        {
            // Check if interval pattern is the same
            if (resultIntervalPattern.isEqual(intervalPatterns[j]))
            {
                // Print the interval pattern the chord matches with
                std::cout << "The chord: ";
                chords[i].PrintChord();
                std::cout << "is a " << intervalPatterns[j].name << " chord." << std::endl;

                // Interval pattern found so stop looking for match for this chord
                break;
            }
        }
    }

    return 0;
}

// Get the interval pattern from a chord
IntervalPattern GetIntervalPatternFromChord(aChord c)
{
    // List to store intervals between each note
    std::vector<Interval> resultIntervals;

    // Loop through all notes in chord
    for (unsigned int i = 0; i < c.notes.size() - 1; ++i)
    {
        if ((int)c.notes[i + 1] < (int)c.notes[0])
        {                                                                                                                                                
            // Since the next note in the chord is less than the root (in the note enum), the interval is calculated from the number of notes - root note position
            resultIntervals.push_back((Interval)(12 - (int)c.notes[0] + (int)c.notes[i + 1]));       // added to the position of the next note (Look at note enum)
        }
        else
        {
            // Add interval between root note and current index + 1 (+ 1 because the interval enum starts from 1 instead of 0)
            resultIntervals.push_back((Interval)((int)c.notes[i + 1] - (int)c.notes[0]));
        }
    }

    // return interval pattern object
    return IntervalPattern(resultIntervals, "");
}
