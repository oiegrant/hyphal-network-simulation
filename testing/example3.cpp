#include <gtest/gtest.h>
// #include <fstream>
#include <string>
#include <vector>

#include "../src/include/ElectionDataParser.hpp"
#include "../src/include/ElectionData.hpp"

// #include "../src/include/OPLCandidate.hpp"
// #include "../src/include/CPLCandidate.hpp"
// #include "../src/include/OPLParty.hpp"
// #include "../src/include/CPLParty.hpp"
// #include "../src/include/CPLElectionData.hpp"
// #include "../src/include/OPLElectionData.hpp"


TEST(ElectionDataParserTest, CPLFilesTest) {
    ElectionData* election = ElectionDataParser::create_election("../testing/test_data/1_person_cpl.csv");
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}

TEST(ElectionDataParserTest, CPLMultipleFilesTest) {
    ElectionData* election = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/cpl_mult1_1.csv", "../testing/test_data/cpl_mult1_2.csv"}));
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}

TEST(ElectionDataParserTest, OPLFilesTest) {
    ElectionData* election = ElectionDataParser::create_election("../testing/test_data/2_party_opl.csv");
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}

TEST(ElectionDataParserTest, OPLMultipleFilesTest) {
    ElectionData* election = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/opl_mult1_1.csv","../testing/test_data/opl_mult1_2.csv","../testing/test_data/opl_mult1_3.csv","../testing/test_data/opl_mult1_4.csv"}));
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}

TEST(ElectionDataParserTest, MPOFilesTest) {
    ElectionData* election1 = ElectionDataParser::create_election("../testing/test_data/mpo_example_1.csv");
    EXPECT_NE(election1, nullptr); // nullptr is returned when there is an invalid election type passed in
    ElectionData* election2 = ElectionDataParser::create_election("../testing/test_data/mpo_example_2.csv");
    EXPECT_NE(election2, nullptr);
}

TEST(ElectionDataParserTest, MPOMultipleFilesTest) {
    ElectionData* election = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/mpo_mult1_1.csv","../testing/test_data/mpo_mult1_2.csv"}));
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}

TEST(ElectionDataParserTest, MVFilesTest) {
    ElectionData* election = ElectionDataParser::create_election("../testing/test_data/mv_example_1.csv");
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}

TEST(ElectionDataParserTest, MVMultipleFilesTest) {
    ElectionData* election = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/mv_mult_1.csv","../testing/test_data/mv_mult_2.csv","../testing/test_data/mv_mult_3.csv"}));
    EXPECT_NE(election, nullptr); // nullptr is returned when there is an invalid election type passed in
}


// class ElectionDataParserTest : public ::testing::Test {
// protected:
//     void SetUp() override {
//         // Create paths to test files
//         oplTestFile = "../testing/test_data/sys_test1_opl.csv";
//         cplTestFile = "../testing/test_data/sys_test3_cpl.csv";
//     }

//     void TearDown() override {}

//     std::string oplTestFile;
//     std::string cplTestFile;
//     std::string election_type;
//     int numSeats;
//     int numBallots;
//     std::string line;
//     int numCandidates;
//     int numParties;
// };

// TEST_F(ElectionDataParserTest, TokenizeLines_base) {
//     std::string line = "Token1,Token2,Token3";
//     std::vector<std::string> tokens = ElectionDataParser::tokenize_lines(line);
//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens[0], "Token1");
//     EXPECT_EQ(tokens[1], "Token2");
//     EXPECT_EQ(tokens[2], "Token3");
// }

// TEST_F(ElectionDataParserTest, TokenizeLines_whitespaces) {
//     std::string line = " Token1 , Token2,Token3 ";
//     std::vector<std::string> tokens = ElectionDataParser::tokenize_lines(line);
//     EXPECT_EQ(tokens.size(), 3);
//     EXPECT_EQ(tokens[0], "Token1");
//     EXPECT_EQ(tokens[1], "Token2");
//     EXPECT_EQ(tokens[2], "Token3");
// }

// TEST_F(ElectionDataParserTest, TokenizeLines_ballots1) {
//     std::string line = ",,1,";
//     std::vector<std::string> tokens = ElectionDataParser::tokenize_lines(line);
//     EXPECT_EQ(tokens.size(), 4);
//     EXPECT_EQ(tokens[0], "");
//     EXPECT_EQ(tokens[1], "");
//     EXPECT_EQ(tokens[2], "1");
//     EXPECT_EQ(tokens[3], "");
// }

// TEST_F(ElectionDataParserTest, TokenizeLines_ballots2) {
//     std::string line = "1,,,";
//     std::vector<std::string> tokens = ElectionDataParser::tokenize_lines(line);
//     EXPECT_EQ(tokens.size(), 4);
//     EXPECT_EQ(tokens[0], "1");
//     EXPECT_EQ(tokens[1], "");
//     EXPECT_EQ(tokens[2], "");
//     EXPECT_EQ(tokens[3], "");
// }

// TEST_F(ElectionDataParserTest, TokenizeLines_ballots3) {
//     std::string line = ",,,1";
//     std::vector<std::string> tokens = ElectionDataParser::tokenize_lines(line);
//     EXPECT_EQ(tokens.size(), 4);
//     EXPECT_EQ(tokens[0], "");
//     EXPECT_EQ(tokens[1], "");
//     EXPECT_EQ(tokens[2], "");
//     EXPECT_EQ(tokens[3], "1");
// }

// TEST_F(ElectionDataParserTest, CreateOPLCandidates) {
//     std::ifstream file(oplTestFile);
    
//     if (!file.is_open()) {
//         // Handle the error by throwing an exception
//         throw std::runtime_error("Failed to open file: " + oplTestFile);
//     }

//     // Read the first line into electionType
//     if (std::getline(file, line)) {
//         election_type = line;
//     }
//     // Read the second line into numSeats
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numSeats;
//     }
//     // Read the third line into numBallots
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numBallots;
//     }
//     // Read fourth line into numCandidates
//     if (std::getline(file, line)) {
//             std::istringstream(line) >> numCandidates;
//     }

//     std::vector<std::tuple<std::string, Candidate*>> candidates = ElectionDataParser::create_OPL_candidates(file, numCandidates);
//     file.close();

//     EXPECT_EQ(numSeats, 2);
//     EXPECT_EQ(numBallots, 9);
//     EXPECT_EQ(numCandidates, 6);
//     EXPECT_EQ(candidates.size(), 6);
//     EXPECT_EQ(std::get<0>(candidates[0]), "Democrat");
//     EXPECT_EQ(std::get<1>(candidates[0])->get_name(), "Pike");
//     EXPECT_EQ(std::get<0>(candidates[1]), "Democrat");
//     EXPECT_EQ(std::get<1>(candidates[1])->get_name(), "Lucy");
//     EXPECT_EQ(std::get<0>(candidates[2]), "Democrat");
//     EXPECT_EQ(std::get<1>(candidates[2])->get_name(), "Beiye");
//     EXPECT_EQ(std::get<0>(candidates[3]), "Republican");
//     EXPECT_EQ(std::get<1>(candidates[3])->get_name(), "Etta");
//     EXPECT_EQ(std::get<0>(candidates[4]), "Republican");
//     EXPECT_EQ(std::get<1>(candidates[4])->get_name(), "Alawa");
//     EXPECT_EQ(std::get<0>(candidates[5]), "Independent1");
//     EXPECT_EQ(std::get<1>(candidates[5])->get_name(), "Sasha");

//     for (const auto& candidate : candidates) {
//         delete std::get<1>(candidate);
//     }
// }

// TEST_F(ElectionDataParserTest, AssignVotesToCandidates) {
//     std::ifstream file(oplTestFile);
    
//     if (!file.is_open()) {
//         // Handle the error by throwing an exception
//         throw std::runtime_error("Failed to open file: " + oplTestFile);
//     }

//     // Read the first line into electionType
//     if (std::getline(file, line)) {
//         election_type = line;
//     }
//     // Read the second line into numSeats
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numSeats;
//     }
//     // Read the third line into numBallots
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numBallots;
//     }
//     // Read fourth line into numCandidates
//     if (std::getline(file, line)) {
//             std::istringstream(line) >> numCandidates;
//     }
//     std::vector<std::tuple<std::string, Candidate*>> candidates = ElectionDataParser::create_OPL_candidates(file, numCandidates);
    
//     std::vector<Candidate*> candidateVec;
//     for (const auto& candidate : candidates) {
//         candidateVec.push_back(std::get<1>(candidate));
//     }

//     ElectionDataParser::assign_votes_to_candidates(file, candidateVec);
//     file.close();

//     EXPECT_EQ(candidateVec[0]->get_num_votes(), 2);
//     EXPECT_EQ(candidateVec[1]->get_num_votes(), 1);
//     EXPECT_EQ(candidateVec[2]->get_num_votes(), 0);
//     EXPECT_EQ(candidateVec[3]->get_num_votes(), 2);
//     EXPECT_EQ(candidateVec[4]->get_num_votes(), 2);
//     EXPECT_EQ(candidateVec[5]->get_num_votes(), 2);

//     for (const auto& candidate : candidates) {
//         delete std::get<1>(candidate);
//     }
// }

// TEST_F(ElectionDataParserTest, CreateOPLParties) {
//     std::ifstream file(oplTestFile);
    
//     if (!file.is_open()) {
//         // Handle the error by throwing an exception
//         throw std::runtime_error("Failed to open file: " + oplTestFile);
//     }

//     // Read the first line into electionType
//     if (std::getline(file, line)) {
//         election_type = line;
//     }
//     // Read the second line into numSeats
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numSeats;
//     }
//     // Read the third line into numBallots
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numBallots;
//     }
//     // Read fourth line into numCandidates
//     if (std::getline(file, line)) {
//             std::istringstream(line) >> numCandidates;
//     }
//     std::vector<std::tuple<std::string, Candidate*>> candidates = ElectionDataParser::create_OPL_candidates(file, numCandidates);

//     std::vector<Party*> parties = ElectionDataParser::create_OPL_parties(candidates);

//     EXPECT_EQ(parties.size(), 3);
//     EXPECT_EQ(parties[0]->get_name(), "Democrat");
//     EXPECT_EQ(parties[0]->get_candidates().size(), 3);
//     EXPECT_EQ(parties[1]->get_name(), "Republican");
//     EXPECT_EQ(parties[1]->get_candidates().size(), 2);
//     EXPECT_EQ(parties[2]->get_name(), "Independent1");
//     EXPECT_EQ(parties[2]->get_candidates().size(), 1);

//     for (const auto& candidate : candidates) {
//         delete std::get<1>(candidate);
//     }

//     for (Party* party : parties) {
//         delete party;
//     }

//     file.close();
// }

// TEST_F(ElectionDataParserTest, CreateCPLParties) {
//     std::ifstream file(cplTestFile);
    
//     if (!file.is_open()) {
//         // Handle the error by throwing an exception
//         throw std::runtime_error("Failed to open file: " + cplTestFile);
//     }

//     // Read the first line into electionType
//     if (std::getline(file, line)) {
//         election_type = line;
//     }
//     // Read the second line into numSeats
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numSeats;
//     }
//     // Read the third line into numBallots
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numBallots;
//     }
//     // Read fourth line into numCandidates
//     if (std::getline(file, line)) {
//             std::istringstream(line) >> numParties;
//     }
//     std::vector<Party*> parties = ElectionDataParser::create_CPL_parties(file, numParties);
//     file.close();

//     EXPECT_EQ(parties.size(), 6);
//     EXPECT_EQ(parties[0]->get_name(), "Democratic");
//     EXPECT_EQ(parties[0]->get_candidates().size(), 3);
//     EXPECT_EQ(parties[1]->get_name(), "Republican");
//     EXPECT_EQ(parties[1]->get_candidates().size(), 3);
//     EXPECT_EQ(parties[2]->get_name(), "New Wave");
//     EXPECT_EQ(parties[2]->get_candidates().size(), 1);
//     EXPECT_EQ(parties[3]->get_name(), "Reform");
//     EXPECT_EQ(parties[3]->get_candidates().size(), 2);
//     EXPECT_EQ(parties[4]->get_name(), "Green");
//     EXPECT_EQ(parties[4]->get_candidates().size(), 1);
//     EXPECT_EQ(parties[5]->get_name(), "Independent");
//     EXPECT_EQ(parties[5]->get_candidates().size(), 1);

//     for (Party* party : parties) {
//         for (Candidate* candidate : party->get_candidates()) {
//             delete candidate;
//         }
//         delete party;
//     }
// }

// // TEST_F(ElectionDataParserTest, AssignVotesToParties) {
// //     std::ifstream file(cplTestFile);
    
// //     if (!file.is_open()) {
// //         // Handle the error by throwing an exception
// //         throw std::runtime_error("Failed to open file: " + cplTestFile);
// //     }

// //     // Read the first line into electionType
// //     if (std::getline(file, line)) {
// //         election_type = line;
// //     }
// //     // Read the second line into numSeats
// //     if (std::getline(file, line)) {
// //         std::istringstream(line) >> numSeats;
// //     }
// //     // Read the third line into numBallots
// //     if (std::getline(file, line)) {
// //         std::istringstream(line) >> numBallots;
// //     }
// //     // Read fourth line into numCandidates
// //     if (std::getline(file, line)) {
// //             std::istringstream(line) >> numParties;
// //     }
// //     std::vector<Party*> parties = ElectionDataParser::create_CPL_parties(file, numParties);

// //     ElectionDataParser::assign_votes_to_parties(file, parties);
// //     file.close();

// //     EXPECT_EQ(parties[0]->get_total_votes(), 3);
// //     EXPECT_EQ(parties[1]->get_total_votes(), 2);
// //     EXPECT_EQ(parties[2]->get_total_votes(), 0);
// //     EXPECT_EQ(parties[3]->get_total_votes(), 2);
// //     EXPECT_EQ(parties[4]->get_total_votes(), 1);
// //     EXPECT_EQ(parties[5]->get_total_votes(), 1);

// //     for (Party* party : parties) {
// //         for (Candidate* candidate : party->get_candidates()) {
// //             delete candidate;
// //         }
// //         delete party;
// //     }
// // }


// //create_election testing is system level testing