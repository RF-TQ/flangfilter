#ifndef FLANG_H
#define FLANG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iomanip>

// Function prototypes
static void populateVectors(vector<string> &time, vector<string> &signal);
static void writeVectors(vector<string> &time, vector<string> &signal);
static void transform(int delay, int sample_rate, double scale, vector<string> &signal);

string trim(const string& str, const string& whitespace);
string reduce(const string& str, const string& fill = " ", const string& whitespace = " \t");
vector<string> &split(const string &str, char delim, vector<string> &element);
vector<string> split(const string &str, char delim);

#endif
