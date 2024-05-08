#include <gtest/gtest.h>
#include <string>

#include "../src/include/CPLCandidate.hpp"

#include <gtest/gtest.h>
#include "../src/include/CPLCandidate.hpp"

TEST(CPLCandidateUnitTest, DefaultTest) { 
    CPLCandidate* def = nullptr;
    EXPECT_EQ(def, nullptr);
}

TEST(CPLCandidateUnitTest, getNameTest){
    CPLCandidate* joe = new CPLCandidate ("Joe Schmo");
    EXPECT_EQ ("Joe Schmo", joe->get_name());
    CPLCandidate* sam = new CPLCandidate("Sam Politician");
    EXPECT_EQ ("Sam Politician", sam->get_name());
}

TEST(CPLCandidateUnitTest, getWinnerTest){
    CPLCandidate* steven = new CPLCandidate ("Steven Carter");
    EXPECT_EQ(false, steven->get_winner());
    steven->set_winner(true);
    EXPECT_EQ(true, steven->get_winner());
}

TEST(CPLCandidateUnitTest, setWinnerTest){
    CPLCandidate* jenna = new CPLCandidate("Jenna America");
    EXPECT_EQ(false, jenna->get_winner());
    jenna->set_winner(true);
    EXPECT_EQ(true, jenna->get_winner());
    jenna->set_winner(false);
    EXPECT_EQ(false, jenna->get_winner());
    EXPECT_NE(true, jenna->get_winner());
}

TEST(CPLCandidateUnitTest, toStringTest) {
    CPLCandidate* tom = new CPLCandidate("Tom Clancy");
    EXPECT_EQ("Tom Clancy", tom->to_string());
    tom->set_winner(true);
    EXPECT_EQ("> Tom Clancy - WINNER", tom->to_string());
    EXPECT_NE("Tom Clancy", tom->to_string());
}