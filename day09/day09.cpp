#include "day09.hpp"
#include <map>

using namespace std;

int part1(std::istream &in)
{
    // parse input
    long long sum = 0;
    int curPos = 0;
    int curId = 0;
    string line;
    in >> line;
    // map from id to mem size, free size
    map<int, pair<int, int>> ids;
    int i = 0;
    for (; i < line.size() - 2; curId++)
    {
        ids[curId] = {static_cast<int>(line[i]) - '0', static_cast<int>(line[i + 1]) - '0'};
        i += 2;
    }
    // add last one with no freespace
    ids[curId] = {static_cast<int>(line[i]) - '0', 0};
    // go through map
    for (auto it = ids.begin(); it != ids.end(); it++)
    {
        // add the memory to sum
        while (it->second.first > 0)
        {
            cout << "sum += " << curPos << "* " << it->first << endl;
            sum += curPos * it->first;
            it->second.first--; // we took one out the memory
            curPos++;
        }
        // for the freespace pull from the BACK of the map (curId)
        // iterator to the last element
        auto last = ids.find(curId);
        for (int j = 0; j < it->second.second; j++)
        {
            // if last is empty go back untils its not
            while (last->second.first == 0 && last != it)
            {
                last--;
            }
            curId = last->first;
            if (last == it)
            {
                break;
            }
            cout << "sum += " << curPos << "* " << last->first << endl;
            sum += curPos * last->first;
            // cout << " there are " << ids.find(6)->second.first << " " << "6's left" << endl;
            last->second.first--; // we took one out the memory
            curPos++;
        }
    }
    cout << sum << endl;
    return sum;
}

struct File
{
    int freespace;
    int size;
    File(int freespace, int size) : freespace(freespace), size(size) {}
};
int part2(std::istream &in)
{
    // parse input
    long long sum = 0;
    string line;
    int curId = 0;
    in >> line;
    int i = 0;
    vector<File> files;
    vector<int> data;
    // map from location in data to freespace size
    vector<pair<int, int>> freespaceSpans; // {start, length}
    for (; i < line.size() - 2; curId++)
    {
        // create a file
        File f(static_cast<int>(line[i + 1]) - '0', static_cast<int>(line[i]) - '0');
        files.push_back(f);
        // add the memory to data
        for (int j = 0; j < static_cast<int>(line[i]) - '0'; j++)
        {
            data.push_back(curId);
        }
        // add the freespace to data
        freespaceSpans.push_back({data.size(), (static_cast<int>(line[i + 1]) - '0')});
        for (int j = 0; j < static_cast<int>(line[i + 1]) - '0'; j++)
        {
            //-1 for freespace
            data.push_back(-1);
        }
        i += 2;
    }
    //add last file w/ no freespace
    File f(0, static_cast<int>(line[i]) - '0');
    files.push_back(f);
    // go from highest to lowest file (parse backwards)
    for (int i = files.size() - 1; i >= 0; i--)
    {
        //find the earliest span that can fit the file 
        //store the index of the span
        int spanIndex = -1;
        for (int k = 0; k < freespaceSpans.size(); k++) {
           // cout << "freespace span: " << freespaceSpans[k].first << " " << freespaceSpans[k].second << endl;
            //cout << i << " file size: " << files[i].size << endl;
            if (freespaceSpans[k].second >= files[i].size) {
                spanIndex = k;
                break;
            }
        }

        if(spanIndex != -1) {
            int spanStart = freespaceSpans[spanIndex].first;
            int length = freespaceSpans[spanIndex].second;

            //change all instances of this file in data to freespace
            for(int j = 0; j < data.size(); j++) {
                if(data[j] == i) {
                    data[j] = -1;
                }
            }
            
            //move file to the span
            for (int j = 0; j < files[i].size; j++) {
                data[spanStart + j] = i;
            }

            //update the span
            if(files[i].size < length) {
                freespaceSpans[spanIndex].first += files[i].size;
                freespaceSpans[spanIndex].second -= files[i].size;
            } else {
                freespaceSpans.erase(freespaceSpans.begin() + spanIndex);
            }

            files.erase(files.begin() + i);
        }
    }
    // go through data and add the sum
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] != -1)
        {
            cout << "sum += " << i << "* " << data[i] << endl;
            sum += i * data[i];
        }
        else{
            cout << "* " << "freespace" << endl;
        }
    }
    cout << sum << endl;    
    return sum;
}