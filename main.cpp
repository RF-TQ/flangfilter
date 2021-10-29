// file: main.cpp
// 
// description: A feed-forward comb filter for audio files.
//              This is the main function.
//
//              It takes as input a file whose format matches the PCM 
//              file format. (.wav, .dat, whatever, as long as it matches)
//
//              The PCM .dat format expected here has the form
//              <time> <signal>; the value transformed by the filter 
//              is the signal. The program then writes back to an
//              output file in the same format as the file read in.
//
//              The feed-forward comb filter described here is a
//              basic difference function of the form 
//
//                  y[n] = x[n] + ax[n - k]
//
//              where a is some scale factor, and k is a delay factor.
//
// dependencies: flang.cpp
//               flang.h
//
// -----------------------------------------------------------------------------

#include "flang.h"

using std::vector;
using std::string;

/*---- Main function ----*/

int main()
{
	int delay = 0;
	double scale = 0.0;
	int sample_rate = 0;

	vector<string> time;
	vector<string> signal;

	std::cout << "This program transforms a target sound file using a feed-forward.\n"
		<< "Enter a delay: ";
	std::cin >> delay;

	std::cout << "Enter a scale factor for the filter: ";
	std::cin >> scale;

	std::cout << "Enter a sampling rate: ";
	std::cin >> sample_rate;

	populateVectors(time, signal);
	transform(delay, sample_rate, scale, signal);
	writeVectors(time, signal);

	std::cout << "Sound file converted!\n";

	return 0;
}