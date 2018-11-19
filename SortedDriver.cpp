// SortedDriver.cpp

// Duyen Pham   11/10/2018
// COSC 2030 Lab06
// Construct sorted sequences and call functions that
// process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	/*
	double gap = 0.0, pre_gap = 0.0, new_gap = 0.0;
	double new_pre_gap = 0.0, pair_gap = 0.0, max_pair_gap = 0.0;
	double pos = 0.0, pre_pos = 0.0, new_pos = 0.0, new_pre_pos = 0.0;
	double most_isolated = 0.0, most_gap = 0.0;


	cout << number.size() << endl;
	
	for (auto i = number.begin(); i != number.end(); i++)
	{
			pos = *i;

			gap = pos - pre_pos;

			pre_pos = pos;

			pair_gap = gap + pre_gap;
			pre_gap = gap;


			// Find the largest gap between a pair of number to find
			// the farthest nearest neighbor
			if (pair_gap > max_pair_gap)
				max_pair_gap = pair_gap;
	}

	cout << max_pair_gap << endl;

	for (auto i = number.begin(); i != number.end(); i++)
	{
		pos = *i;

		new_gap = pos - pre_pos;
		pre_pos = pos;

		most_gap = new_gap - max_pair_gap;

		if (most_gap == new_gap)
		{
			most_gap = new_pre_gap;
			break;
		}
		else
			most_gap = new_gap;

		new_pre_gap = new_gap;
	}



	//Find the most isolated number
	for (auto i = number.begin(); i != number.end(); i++)
	{
		new_pos = *i;

		new_gap = new_pos - new_pre_pos;
		new_pre_pos = new_pos;

		most_gap = max_pair_gap - new_gap;

		if (most_gap == new_pre_gap)
		{
			most_gap = new_pre_gap;
			break;
		}
		else
			most_gap = new_gap;

		new_pre_gap = new_gap;
		most_isolated = new_pre_pos + most_gap;

		if (most_isolated == new_pos)
		{
			most_isolated = new_pre_pos;
			break;
		}
		else
			most_isolated = new_pos;

		new_pre_pos = new_pos;

	}
	*/

	double most_isolated;
	double most_isolated_nearest_neighbor = 0;
	double pre_gap, post_gap = INFINITY;
	double nearest_neighbor;

	for (unsigned int pos = 0; pos < number.size() - 1; pos++)
	{
		pre_gap = post_gap;
		post_gap = number[pos + 1] - number[pos];
		nearest_neighbor = min(pre_gap, post_gap);


		// Check if the new nearest neighbor is further
		// away from the nost isolated neighbor we found so far.
		if (nearest_neighbor > most_isolated_nearest_neighbor)
		{
			most_isolated_nearest_neighbor = nearest_neighbor;
			most_isolated = number[pos];
		}
	}

	return most_isolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	unsigned int words_count = 0;

	list<string>::iterator itA = A.begin();
	list<string>::iterator itB = B.begin();

	
	while ( (itA != A.end()) && (itB != B.end()) )
	{
		if (*itA == *itB) {
			std::advance(itA, 1);
		}
		else if (*itA > *itB)
		{
			std::advance(itB, 1);
		}
		else
		{
			std::advance(itA, 1);
			words_count++;
		}
	}
	// If we get to the end of list B, that mean the rest of the 
	// element in A does not exists in B. Adding the rest of the
	// elements in A to words_count and break out of the loop.
	words_count += std::distance(itA, A.end());
	
	return words_count;
}

int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
