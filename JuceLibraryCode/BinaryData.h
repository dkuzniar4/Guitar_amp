/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   switch_ON_png;
    const int            switch_ON_pngSize = 402;

    extern const char*   switch_OFF_png;
    const int            switch_OFF_pngSize = 451;

    extern const char*   cab_OFF_png;
    const int            cab_OFF_pngSize = 494;

    extern const char*   background_png;
    const int            background_pngSize = 29146;

    extern const char*   cab_ON_png;
    const int            cab_ON_pngSize = 472;

    extern const char*   knobRelease_png;
    const int            knobRelease_pngSize = 7654;

    extern const char*   power_OFF_png;
    const int            power_OFF_pngSize = 351;

    extern const char*   power_ON_png;
    const int            power_ON_pngSize = 324;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
