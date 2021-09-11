//
// Created by jadon on 8/27/2021.
//

#ifndef PA01_SENTIMENT_ANALYZER_H
#define PA01_SENTIMENT_ANALYZER_H

#include "DSString.h"
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
class Analyzer {
private:

    static map<DSString, int> pos_map;
    static map<DSString, int> neg_map;

    //tweet attributes
    DSString sentiment, id, date, query, user, tweet;

public:
    Analyzer();
    Analyzer(const DSString&, const DSString&);
    ~Analyzer();

    void readIn(char *);
    static void fill_pos_map(const DSString&);
    static void fill_neg_map(const DSString&);
    static void print_map();

    static map<DSString, int> get_pos_map() {return pos_map;}
    static map<DSString, int> get_neg_map() {return neg_map;}

};


#endif //PA01_SENTIMENT_ANALYZER_H
