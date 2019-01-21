#include <vector>
#include <array>
#include <iostream>

constexpr int EXP_SIZE = 201; // 0 <= expenditure[i] <= 200
using ExpArray = std::array<unsigned, EXP_SIZE>;


/**
 * This function finds the median of the freqList using Counting Sort.
 * https://www.interviewcake.com/concept/java/counting-sort
 * https://stackoverflow.com/questions/45891475/getting-median-out-of-frequency-table-counting-sort
 * @param freqList frequency table of elements.
 * @param maxValue maximum value to compare.
 * @return the index of median.
 */
constexpr unsigned calc_median(
	const ExpArray& freqList,
	unsigned maxValue) noexcept
{
	unsigned sum = 0;
	for (auto i = 0; i < freqList.size(); ++i) 
	{
		sum += freqList[i];
		if ((2 * sum) == maxValue)
		{
			return (2 * i + 1);
		}
		else if ((2 * sum) > maxValue)
		{
			return (i * 2);
		}
	}
	return 1;
}


/**
 * This function returns the frequency table for expList. e.g:
 * Input:  [4, 8, 4, 2, 9, 9, 6, 2, 9]
 * Counts: [ 0,  0,  2,   0,  2,  0,  1,  0,  1,  3,  0]
 * @param expList list of expenditures.
 * @param numPriorDays number of prior days the bank uses to calculate median.
 * @return frequency table for expList.
 */
ExpArray frequency_list(
	const std::vector<int>& expList,
	unsigned numPriorDays) noexcept
{
	ExpArray expFreqList{ 0 };
	for (auto i = 0; i < numPriorDays; i++) 
	{
		++expFreqList[expList[i]];
	}

	return expFreqList;
}


/**
 * This function returns the notification count over a period of n days, where n = expList.size().
 * @param expList list of expenditures.
 * @param numDays number of transaction days.
 * @param numPriorDays number of prior days the bank uses to calculate median.
 * @return the notification count.
 */
unsigned notification_count(
	const std::vector<int>& expList,
	unsigned numPriorDays) noexcept
{
	auto expFreqList = frequency_list(expList, numPriorDays);
	auto result = 0u;

	for (auto i = numPriorDays; i < expList.size(); ++i) 
	{
		int median = calc_median(expFreqList, numPriorDays);
		if (median <= expList[i]) 
		{
			++result;
		}
		// slide 1 index to right.
		--expFreqList[expList[i - numPriorDays]];
		++expFreqList[expList[i]];
	}

	return result;
}



int main()
{
	std::cout << notification_count({ 2, 3, 4, 2, 3, 6, 8, 4, 5 }, 5);
	std::cin.get();
}