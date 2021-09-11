//
// Created by jadon on 8/28/2021.
//

#include "Classifier.h"
#include "Analyzer.h"
#include <fstream>
#include <iomanip>

Classifier::Classifier(const DSString &sent, const DSString &id, const DSString &twt) {
    this -> sentiment = " ";
    this -> id = id;
    this -> tweet = twt;
}

Classifier::Classifier(const DSString& sent, const DSString& id) {
    this -> sentiment = sent;
    this -> id = id;
}

void Classifier::readIn(char* arg) {
    ifstream infs(arg);
    if (infs.fail()) {
        cout << "Problem opening file!" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        cout << "File opened successfully!" << endl;
    }

    //wraps tweet and its id in a Classifier object and stores in a vector
    char* buffer = new char[1000];
    infs.getline(buffer, 100, '\n');
    infs.getline(buffer, 100, ','); //read over file headers
    while (!infs.eof()) {
        id = buffer;
        infs.getline(buffer, 100, ','); //date
        infs.getline(buffer, 100, ','); //query
        infs.getline(buffer, 100, ','); //user
        infs.getline(buffer, 1000, '\n'); //tweet
        tweet = buffer;
        tweet_vector.emplace_back(sentiment, id, tweet);
        infs.getline(buffer, 100, ','); //id
    }

    delete[] buffer;
    tokenize_tweet();
//    print_tweets();
}

void Classifier::tokenize_tweet() {
    char* buffer;
    DSString original, token;
    for (Classifier& itr: tweet_vector) {
        original = itr.tweet;
        buffer = strtok(original.c_str(), "*&.?,!\"\\:;'-/()[]{} ");
        while (buffer) {
            token = buffer;
            tokens_vector.push_back(token);
            buffer = strtok(nullptr, "*&.?,!\"\\:;'-/()[]{} ");
        }
        itr.sentiment = assess_sentiment();
        tokens_vector.clear();
    }
}

// receives vector of each tweet's indiv. words at diff. indices.
// function determines if a tweet is positive or negative
DSString Classifier::assess_sentiment() {
    map<DSString, int> pos_map = Analyzer::get_pos_map();
    map<DSString, int> neg_map = Analyzer::get_neg_map();

    // the freq of the word in a pos. and neg. sentiment
    int pos_occurrence;
    int neg_occurrence;

    // the amount of "positive" and "negative" words a test tweet contains
    int pos_word = 0;
    int neg_word = 0;

    //compares each word of test tweet against map of pos. and neg. words
    for (DSString& itr: tokens_vector) {
        auto it = pos_map.find(itr);
        if (it == pos_map.end())
            pos_occurrence = 0;
        else if (itr == it->first)
            pos_occurrence = it->second;

        it = neg_map.find(itr);
        if (it == neg_map.end())
            neg_occurrence = 0;
        else if (itr == it->first)
            neg_occurrence = it->second;


        //else if ensures words of equal occurrence aren't assigned
        if (pos_occurrence > neg_occurrence)
            pos_word++;
        else if (neg_occurrence > pos_occurrence)
            neg_word++;
    }

    DSString pos, neg;
    pos = "4"; neg = "0";
    // >= assigns "neutral" tweets as positive
    if (pos_word >= neg_word)
        return pos;
    else
        return neg;
}

//function determines the accuracy of the sentiment analyzer
void Classifier::get_accuracy(char * arg) {
    ifstream infs(arg);
    if (infs.fail()) {
        cout << "Problem opening file!" << endl;
        exit(EXIT_FAILURE);
    }
    else cout << "File opened successfully!" << endl;

    char* buffer = new char[100];
    infs.getline(buffer, 100, '\n');
    //assumes test files are parallel for this proj.
    for (auto & it : tweet_vector) {
        //1st time, read over file headers
        infs.getline(buffer, 100, ','); //sentiment
        sentiment = buffer;
        infs.getline(buffer, 100, '\n'); //id

        if (sentiment == it.sentiment) {
            correctly_classified++;
        }
        else {
            wrong_sentiment.push_back(it.id);
        }
    }

    double accuracy = ((double)correctly_classified / tweet_vector.size()) * 100;
    cout << "Total accuracy of the sentiment analyzer is "  << fixed << setprecision(3) << accuracy << " percent(%)." << endl;
}

void Classifier::print_to_file(char* arg) {
    ofstream ofs(arg);
    double accuracy = ((double)correctly_classified / tweet_vector.size()) * 100;
    ofs << fixed << setprecision(3) << accuracy << endl;
    for (const auto& itr: wrong_sentiment)
        ofs << itr << endl;
}

void Classifier::print_tweets() {
    for (const Classifier& itr: tweet_vector) {
        cout << "Sentiment: " << itr.sentiment;
        cout << " ID: " << itr.id;
        cout << " Tweet: " << itr.tweet << endl;
    }
}