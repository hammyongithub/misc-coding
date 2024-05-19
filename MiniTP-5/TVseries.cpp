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
    // To store unique principal names
    unordered_set<string> uniquePrincipals;

    // Find episodes that belong to the specified series
    auto seriesIt = episodes.find(seriesTconst);
    if (seriesIt != episodes.end()) {
        // Iterate through each episode of the series
        for (const auto& episode : seriesIt->second) {
            // Find principals for each episode
            auto episodeIt = principals.find(episode.tconst);
            if (episodeIt != principals.end()) {
                // Insert principal names into the set to ensure uniqueness
                for (const TitlePrincipals& principal : episodeIt->second) {
                    uniquePrincipals.insert(principal.primaryName);
                }
            }
        }
    }

    // Convert the set of unique names to a vector
    vector<string> result(uniquePrincipals.begin(), uniquePrincipals.end());

    // Sort the result alphabetically before returning
    sort(result.begin(), result.end());

    return result;
}

//PERGUNTA 2:


string TVSeriesAPP::getMostSeriesGenre() const {
    unordered_map<string, int> genreFrequency;

    for (const auto& pair : titles) {
        const TitleBasics& title = pair.second;
        for (const string& genre : title.genres) {
            genreFrequency[genre]++;
        }
    }

    
    string mostFrequentGenre;
    int highestFrequency = 0;

    for (const auto& pair : genreFrequency) {
        const std::string& genre = pair.first;
        int frequency = pair.second;

        if (frequency > highestFrequency || (frequency == highestFrequency && genre.length() < mostFrequentGenre.length())) {
            mostFrequentGenre = genre;
            highestFrequency = frequency;
        }
    }

    return mostFrequentGenre;
}


//PERGUNTA 3: 

string TVSeriesAPP::getPrincipalFromCharacter(const string& character) const {
    // Map to store count of characters played by each principal
    unordered_map<string, int> characterCount;
    // Map to store nconst to primaryName mapping
    unordered_map<string, string> principalNames;

    // Iterate through all principals to count character appearances
    for (const auto& entry : principals) {
        for (const auto& principal : entry.second) {
            for (const auto& charName : principal.characters) {
                // Check if the character is part of the principal's character names
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

        // Update the principal with the most appearances based on count and alphabetical order
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
    // Convert the input genres vector to an unordered set for fast lookup
    unordered_set<string> genresSet(vGenres.begin(), vGenres.end());
    
    // Map to store each principal and the set of genres they are associated with
    unordered_map<string, unordered_set<string>> principalToGenres;

    // Iterate through all the series in the titles map
    for (const auto& seriesPair : titles) {
        const TitleBasics& series = seriesPair.second;
        
        // Convert series genres to an unordered set for fast lookup
        unordered_set<string> seriesGenres(series.genres.begin(), series.genres.end());
        
        // Check if the series matches any of the desired genres
        bool matches = false;
        for (const auto& genre : seriesGenres) {
            if (genresSet.find(genre) != genresSet.end()) {
                matches = true;
                break;
            }
        }

        // If the series matches the genres
        if (matches) {
            // Find episodes associated with this series
            auto episodeIt = episodes.find(series.tconst);
            if (episodeIt != episodes.end()) {
                for (const auto& episode : episodeIt->second) {
                    // Find principals associated with this episode
                    auto principalIt = principals.find(episode.tconst);
                    if (principalIt != principals.end()) {
                        for (const auto& principal : principalIt->second) {
                            // For each principal, add the matching genres to their set
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

    // Count the number of principals associated with more than one genre
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













