// file: flang.cpp
// author: rtfq
// 
// description: A feed-forward comb filter for audio files.
//
//              This contains the utility functions needed to run 
//              the main function.
//
// dependencies: flang.h
//
// -----------------------------------------------------------------------------

#include "flang.h"

using std::vector;
using std::string;

// Filestream variables
std::ifstream transformIn;
std::ofstream transformOut;

// File targets
string inputFile = "input.dat";
string outputFile = "output.dat";

/*---- Utility functions ----*/

// [static void populateVectors()]
// Takes an input file and populates the vectors.
// This function was written with the SoX .dat files in mind. 
//
// Parameters: two vectors<string>:
//                &time contains the time variable.
//                &signal contains the amplitude per time.
// Returns: Nothing.
// Side effects: Static function. Previous runs affect future output.
//               Reference vectors are modified.

static void populateVectors(vector<string> &time, vector<string> &signal)
{
	// Note: Modify the 
	transformIn.open(inputFile);

	// double x;
	// double y;

	string line;

	// Ignores any leading comments.
	// As a result of the comment ignore function we'll also have to 
	// port the initial fstream to ss before writing to the vectors.

	while (getline(transformIn, line))
	{
		// Drop all commented lines and continue.
		if (line[0] != ';')
		{
			line = reduce(line);

			// Until EOF. Assumed file format:
			// <time> <signal>
			// <time> <signal>
			// And so on.

			// Read all values in pairs and append to back of vector.

			vector<string> tokens = split(line, ' ');

			time.push_back(tokens[0]);
			signal.push_back(tokens[1]);
		}

	}
	transformIn.close();
}

// [static void writeVectors()]
// Takes resulting double-precision vectors from filter and outputs to a file.
//
// Parameters: two vectors<string>:
//                &time contains the time variable.
//                &signal contains the amplitude per time.
// Returns: Nothing.
// Side effects: Writes to the output.pcm file.
//               If non-existent, creates it.

static void writeVectors(vector<string> &time, vector<string> &signal)
{
	// Implement something for these?

	int samplingRate = 44100;
	int numChannels = 1;

	transformOut.open(outputFile);

	transformOut << "; Sample Rate " << samplingRate << '\n'
		<< "; Channels " << numChannels << '\n';

	// Write values from front of vector and then pop them.
	// Repeat until both vectors are empty.
	while (!(time.empty() && signal.empty()))
	{
		transformOut << time.front() << ' '
			<< signal.front() << '\n';
		time.erase(time.begin(), time.begin() + 1);
		signal.erase(signal.begin(), signal.begin() + 1);
	}

	transformOut.close();
}

// [static void transform()]
// This implements the feed-forward, producing a comb filter
// or "flanging" effect. 
//
// The feed-forward transform is defined as 
// 
//    y[n] = x[n] + ax[n - k]
//
// where a is a scale factor, and k is a delay factor.
// For the purposes of this delay, any n - k < 0 will be set to 0,
// which is simply x[0] = 0, or no change.
// Parameters: vector, string &signals
//             integer: delay. constant delay which denotes where to comb from.
//             double: scale. a floating-point amplifier value.
//
// Returns: Nothing.
// Side effects: Modifies / transforms the signals associated with the filter.

static void transform(int delay, int sample_rate, double scale, vector<string> &signal)
{
	// A "check" factor for the delay.
	int realDelay = 0;

	for (int i = 0; i < signal.size(); i += sample_rate)
	{
		realDelay = i - delay;

		// So if n - k < 0, no transform. 
		// Otherwise, n - k should have some actual feed-forward signal.
		if (realDelay < 0)
			realDelay = 0;
		
		// On-the-fly conversion. String to double, and then back again.
		// This is the y[n] = x[n] + ax[n - k] formula as mentioned above.

		signal[i] = std::to_string(stod(signal[i]) + (scale * stod(signal[realDelay])));
	}

	return;
}

// [vector<string> &split]
// Pair overload implementing string splitting.
//
// Parameters: string &str - String to tokenize. 
//             char delim - character demarcation.
//             vector<string> - Target vector.
//
// Returns: vector of type string to caller split() function.
// Side effects: None.

vector<string> &split(const string &str, char delim, vector<string> &element)
{
	std::stringstream strs(str);
	string token;

	while (getline(strs, token, delim))
	{
		element.push_back(token);
	}

	return element;
}

// [vector<string> split]
// Other half of overload pair, calls &split. Wrapper function.
//
// Parameters: string &str - String to tokenize. 
//             char delim - character demarcation.
//
// Returns: vector of type string
// Side effects: None.

vector<string> split(const string &str, char delim)
{
	vector<string> element;
	split(str, delim, element);

	return element;
}

// string trim
// A base function which trims leading whitespace.
//
// Parameters: string &str - String to tokenize. 
//             string &whitespace - Delimiter.
//
// Returns: Trimmed string.
// Side effects: None.

string trim(const string& str, const string& whitespace)
{
	const auto stringBegin = str.find_first_not_of(whitespace);
	if (stringBegin == std::string::npos)
		return "";

	const auto stringEnd = str.find_last_not_of(whitespace);
	const auto stringRange = stringEnd - stringBegin + 1;

	return str.substr(stringBegin, stringRange);
}

// string reduce
// A function which trims leading and infixed whitespace.
// An extension of trim().
//
// Parameters: string &str - String to tokenize. 
//             string &fill - Default: " ", can be overriden with user-defined argument.
//             string &whitespace - Delimiter.
//
// Returns: Trimmed string.
// Side effects: None.

string reduce(const string& str, const string& fill, const string& whitespace)
{
	auto result = trim(str, whitespace);

	auto startSpace = result.find_first_of(whitespace);
	while (startSpace != std::string::npos)
	{
		const auto endSpace = result.find_first_not_of(whitespace, startSpace);
		const auto range = endSpace - startSpace;

		result.replace(startSpace, range, fill);

		const auto newStart = startSpace + fill.length();
		startSpace = result.find_first_of(whitespace, newStart);
	}

	return result;
}
