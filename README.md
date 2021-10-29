# flangfilter
To run:

Just compile the three files together.
You'll want to edit `flang.cpp`, which contains the name of the target `inputFile` to read from, and `outputFile`, which it'll create.

Some things to keep in mind: 
* Specifiying a really high sampling rate will probably result in this filter doing nothing
* Keep the input file to read from in the same folder as the program 
* This filter works directly with .wav files or any audio with the same text format, but as always, it's better to make a backup in case something goes wrong, which is why the code is set to read from a .dat file by default, and why the `sample` folder also contains the .dat files that are just the .wav files with a different file extension.
