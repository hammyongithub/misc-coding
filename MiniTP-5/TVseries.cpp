#include "TVseries.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>
#include <unordered_set>
#include <unordered_map>

TVSeriesAPP::TVSeriesAPP() {

}
   
TVSeriesAPP::~TVSeriesAPP() {
    
}


void TVSeriesAPP::addTitleBasics(const TitleBasics& title) {
    titles[title.tconst] = title;
}

void TVSeriesAPP::addTitleEpisodes(const TitleEpisode& episode) {
    episodes[episode.parentTconst].push_back(episode);
}

void TVSeriesAPP::addTitlePrincipal(const TitlePrincipals& principal) {
    principals[principal.tconst].push_back(principal);
}



//Pergunta 1:

vector<string> TVSeriesAPP::getUniquePrincipals(const string& seriesTconst) const {
    unordered_set<string> uniquePrincipals;  // To store unique principal names

    // Iterate through all episodes that belong to the specified series
    auto seriesIt = episodes.find(seriesTconst);
    if (seriesIt != episodes.end()) {
        for (const auto& episode : seriesIt->second) {
            // Access all principals for each episode
            auto episodeIt = principals.find(episode.tconst);
            if (episodeIt != principals.end()) {
                for (const TitlePrincipals& principal : episodeIt->second) {
                    uniquePrincipals.insert(principal.primaryName);  // Store unique names
                }
            }
        }
    }

    // Convert the set of unique names to a vector
    vector<string> result(uniquePrincipals.begin(), uniquePrincipals.end());

    // Sort the result before returning
    sort(result.begin(), result.end());

    return result;
}

//PERGUNTA 2:


string TVSeriesAPP::getMostSeriesGenre() const {
    unordered_map<string, int> genreCount;

    // Iterate through all TitleBasics objects in the titles map
    for (const auto& pair : titles) {
        const TitleBasics& series = pair.second; // Get the TitleBasics object
        for (const auto& genre : series.genres) {
            genreCount[genre]++;
        }
    }

    string mostPopularGenre;
    int maxCount = 0;

    // Find the genre with the maximum count
    for (const auto& entry : genreCount) {
        if (entry.second > maxCount || 
            (entry.second == maxCount && entry.first.size() < mostPopularGenre.size())) {
            mostPopularGenre = entry.first;
            maxCount = entry.second;
        }
    }

    return mostPopularGenre;
}


//PERGUNTA 3: 

string TVSeriesAPP::getPrincipalFromCharacter(const string& character) const {

    return "";
}



//PERGUNTA 4

vector<string> TVSeriesAPP::principalsWithMultipleCategories(const string& seriesTconst ) const {

  return {};
}
 
//PERGUNTA 5:

int TVSeriesAPP::principalInMultipleGenres(vector<string> vGenres) {


return -1;
}


//PERGUNTA 6: 
vector<string> TVSeriesAPP::principalsInAllEpisodes(const string& seriesTconst) const {

    return {};
}













