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
    unordered_map<string, int> characterCount; // Map to store count of characters played by each principal
    unordered_map<string, string> principalNames; // Map to store nconst to primaryName mapping

    // Iterate through all principals to count character appearances
    for (const auto& entry : principals) {
        for (const auto& principal : entry.second) {
            for (const auto& charName : principal.characters) {
                if (charName.find(character) != string::npos) {
                    characterCount[principal.nconst]++;
                    principalNames[principal.nconst] = principal.primaryName;
                }
            }
        }
    }

    // Variables to store the principal with the most appearances of the character
    int maxCount = 0;
    string principalWithMostAppearances;

    // Find the principal with the maximum count, resolving ties by alphabetical order
    for (const auto& entry : characterCount) {
        const string& nconst = entry.first;
        int count = entry.second;
        const string& primaryName = principalNames[nconst];

        if (count > maxCount || (count == maxCount && primaryName < principalWithMostAppearances)) {
            maxCount = count;
            principalWithMostAppearances = primaryName;
        }
    }

    return principalWithMostAppearances;
}


//PERGUNTA 4

vector<string> TVSeriesAPP::principalsWithMultipleCategories(const string& seriesTconst ) const {

    return {};
}

//PERGUNTA 5:

int TVSeriesAPP::principalInMultipleGenres(vector<string> vGenres) {
    unordered_set<string> genresSet(vGenres.begin(), vGenres.end());
    unordered_map<string, unordered_set<string>> principalToGenres;

    // Iterate over all series and their genres
    for (const auto& seriesPair : titles) {
        const TitleBasics& series = seriesPair.second;
        unordered_set<string> seriesGenres(series.genres.begin(), series.genres.end());
        bool matches = false;
        for (const auto& genre : seriesGenres) {
            if (genresSet.find(genre) != genresSet.end()) {
                matches = true;
                break;
            }
        }

        // If the series matches the genres, collect its principals
        if (matches) {
            auto episodeIt = episodes.find(series.tconst);
            if (episodeIt != episodes.end()) {
                for (const auto& episode : episodeIt->second) {
                    auto principalIt = principals.find(episode.tconst);
                    if (principalIt != principals.end()) {
                        for (const auto& principal : principalIt->second) {
                            for (const auto& genre : seriesGenres) {
                                if (genresSet.find(genre) != genresSet.end()) {
                                    principalToGenres[principal.nconst].insert(genre);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Count principals who are in multiple genres
    int count = 0;
    for (const auto& entry : principalToGenres) {
        if (entry.second.size() > 1) {
            count++;
        }
    }

    return count;
}


//PERGUNTA 6: 
vector<string> TVSeriesAPP::principalsInAllEpisodes(const string& seriesTconst) const {

    return {};
}













