//
// Created by jadon on 8/27/2021.
//

#include "Analyzer.h"
#include <fstream>

Analyzer::Analyzer() = default;
Analyzer::Analyzer(const DSString &sent, const DSString &twt) {
    this -> sentiment = sent;
    this -> tweet = twt;
}
Analyzer::~Analyzer() = default;

void Analyzer::readIn(char * arg) {
    ifstream infs(arg);
    if (infs.fail()) {
        cout << "Problem opening file!" << endl;
    }
    else { cout << "File opened successfully!" << endl;}

    char* buffer = new char[1000];
    infs.getline(buffer, 100, '\n');
    infs.getline(buffer, 100, ','); // read over file headers
    while (!infs.eof()) {
        sentiment = buffer;
        if (sentiment == "4") {
            infs.getline(buffer, 100, ','); //id
            infs.getline(buffer, 100, ','); //date
            infs.getline(buffer, 100, ','); //query
            infs.getline(buffer, 100, ','); //user
            infs.getline(buffer, 1000, '\n'); //tweet
            tweet = buffer;
            fill_pos_map(tweet);
            infs.getline(buffer, 100, ','); //sentiment
        }
        else if (sentiment == "0") {
            infs.getline(buffer, 100, ','); //id
            infs.getline(buffer, 100, ','); //date
            infs.getline(buffer, 100, ','); //query
            infs.getline(buffer, 100, ','); //user
            infs.getline(buffer, 1000, '\n'); //tweet
            tweet = buffer;
            fill_neg_map(tweet);
            infs.getline(buffer, 100, ','); //sentiment
        }
    }

    delete[] buffer;
//    print_map();
}

map<DSString, int> Analyzer::pos_map; //definition to access static variables in function
map<DSString, int> Analyzer::neg_map;

void Analyzer::fill_pos_map(const DSString& arg) {
    // char pointer curr_word instead of DSString object,
    // otherwise will assign null during tokenizing causing a segfault
    char* curr_word;
    DSString original, token;

    original = arg;
    curr_word = strtok(original.c_str(), "*&.?,!\"\\:;'-/()[]{} ");
    while (curr_word) {
        token = curr_word;
        auto itr = pos_map.find(token);
        if (itr == pos_map.end()) {
            pos_map[token] = 1; //curr_word doesn't exist, add to map
        } else {
            pos_map[token]++; //curr_word exists, increase occurrence frequency
        }
        curr_word = strtok(nullptr, "*&.?,!\"\\:;'-/()[]{} ");
    }
}
void Analyzer::fill_neg_map(const DSString& arg) {
    char* curr_word;
    DSString original, token;

    original = arg;
    curr_word = strtok(original.c_str(), "*&.?,!\"\\:;'-/()[]{} ");
    while (curr_word) {
        token = curr_word;
        auto itr = neg_map.find(token);
        if (itr == neg_map.end()) {
            neg_map[token] = 1; //curr_word doesn't exist, add to map
        } else {
            neg_map[token]++; //curr_word exists, increase occurrence frequency
        }
        curr_word = strtok(nullptr, "*&.?,!\"\\:;'-/()[]{} ");
    }
}

void Analyzer::print_map() {
    cout << "---------------" << endl;
    cout << " Positive List " << endl;
    cout << "---------------" << endl;
    cout << pos_map.size() << endl;
    for (const auto& itr: pos_map) {
        cout << itr.first << ", " << itr.second << endl;
    }

    cout << "---------------" << endl;
    cout << " Negative List " << endl;
    cout << "---------------" << endl;
    cout << neg_map.size() << endl;
    for (const auto& itr: neg_map) {
        cout << itr.first << ", " << itr.second << endl;
    }
}