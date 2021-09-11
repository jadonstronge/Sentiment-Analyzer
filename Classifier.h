//
// Created by jadon on 8/28/2021.
//

#ifndef PA01_SENTIMENT_CLASSIFIER_H
#define PA01_SENTIMENT_CLASSIFIER_H

#include "DSString.h"
#include <vector>
using namespace std;

class Classifier {
private:
    DSString sentiment, id, date, query, user, tweet;

    vector<Classifier> tweet_vector;
    vector<DSString> tokens_vector;
    vector<DSString> wrong_sentiment; //the ids of the incorrectly classified tweets

    int correctly_classified = 0;

public:
    Classifier() = default;
    Classifier(const DSString&, const DSString&, const DSString&);
    Classifier(const DSString&, const DSString&);
    ~Classifier() = default;

    void readIn(char*);
    void tokenize_tweet();
    DSString assess_sentiment();
    void get_accuracy(char*);

    void print_to_file(char*);
    void print_tweets();

};


#endif //PA01_SENTIMENT_CLASSIFIER_H
