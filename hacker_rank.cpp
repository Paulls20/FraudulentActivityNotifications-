#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

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
 * @param numPriorDays number of prior days the bank uses to calculate median.
 * @return the notification count.
 */
unsigned activityNotifications(
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
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

