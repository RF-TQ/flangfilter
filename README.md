# flangfilter
To run:

Just compile the three files together. For completeness's sake:

* **Windows** users: 
In Visual Studio, right-click in the Solution Explorer to include the existing code in a blank C++ project. For organization's sake, put the header under the Header Files, and the code under the Source Files. Build / compile from the **Build** menu in the top bar, and run from the "Run without debugging" in the **Debug** menu.
* **Linux** users: `g++ *.cpp -c` (or `clang++`, if that's what you have), then link them together with `g++ *.o -o <insert your executable name here>`; then run with `./<name of executable>`. (You could compile everything separately to prevent whatever other code you have from getting caught in the * wildcard crossfire, but best practice suggests you really should keep separate projects of code in different folders to begin with.)
* **Mac** users: Assuming you've got Xcode or similar running, the same build / run commands for Linux should work without too much fuss on the command line tool.

Please at least remember to run these commands in the same directory as where the files are kept.

You'll want to edit `flang.cpp`, which contains the name of the target `inputFile` to read from, and `outputFile`, which it'll create.

Some things to keep in mind: 
* Specifiying a really high sampling rate will probably result in this filter doing nothing
* Keep the input file to read from in the same folder as the program 
* This filter works directly with .wav files or any audio with the same text format, but as always, it's better to make a backup in case something goes wrong, which is why the code is set to read from a .dat file by default, and why the `sample` folder also contains the .dat files that are just the .wav files with a different file extension.
