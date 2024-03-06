#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "TVseries.hpp"

using namespace std;

TVSeries::TVSeries(string seriesTitle, int seasons, vector<int> episodesPerSeason, string seriesGenre, float seriesRating, bool isFinished) :
    title(seriesTitle), numberOfSeasons(seasons), episodesPerSeason(episodesPerSeason), genre(seriesGenre), rating(seriesRating), finished(isFinished) {};

string TVSeries::getTitle() const { return title; }

int TVSeries::getNumberOfSeasons() const { return numberOfSeasons; }

vector<int> TVSeries::getEpisodesPerSeason() const { return episodesPerSeason; }

string TVSeries::getGenre() const { return genre; }

float TVSeries::getRating() const { return rating; }

bool TVSeries::isFinished() const { return finished; }

void TVSeries::displaySeriesInfo() const
{
   }

User::User(string uname, string completeName, string userCountry, vector<string> genres) :
    username(uname), name(completeName), country(userCountry), favoriteGenres(genres) {};

string User::getUsername() const { return username; }

string User::getName() const { return name; }

vector<string> User::getFavoriteGenres() const { return favoriteGenres; }

vector<TVSeries*> User::getWatchedSeries() const { return watchedSeries; }

vector<int> User::getRatings() const { return ratings; }

vector<int> User::getEpisodesWatched() const { return episodesWatched; }

int User::addFavoriteGenre(int genreIdx)
{
    // Check if the index of the genre exists in 'vGenres'
    if (!(genreIdx >= 0 && genreIdx < N_GENRES)) return -1;

    // Check if the genre already exists in the vector
    if (find(favoriteGenres.begin(), favoriteGenres.end(), vGenres[genreIdx]) == favoriteGenres.end()) {
        // Genre doesn't exist, so add it to the vector
        favoriteGenres.push_back(vGenres[genreIdx]);
    }

    // Genre already exists, do nothing
    //cout << "Genre already exists in favorite genres." << endl;
    return 1;
}

int User::addWatchedSeries(TVSeries* series)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Return -1 to indicate an error
    }

    // Check if the series is already in watchedSeries
    auto it = find(watchedSeries.begin(), watchedSeries.end(), series);
    if (it != watchedSeries.end()) {
       // cout << "Series is already in watched series." << endl;
        return 1; // Series already exists, no need to insert
    }

    // Series is not in watchedSeries, so insert it
    watchedSeries.push_back(series);
    episodesWatched.push_back(0); // Initialize episodesWatched for the new series
    ratings.push_back(0);
    //cout << "New watched series inserted." << endl;
    return 0; // Successfully inserted
}

int User::addEpisodesWatched(TVSeries* series, int n)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Exit the function if the series pointer is invalid
    }

    // Find the index of the series in the watchedSeries vector
    auto it = find(watchedSeries.begin(), watchedSeries.end(), series);
    if (it != watchedSeries.end()) {
        // Calculate the index of the series
        int index = distance(watchedSeries.begin(), it);

        // Check if the series has more episodes than the episodes watched
        vector <int> episodesperseason = series->getEpisodesPerSeason(); 
        int totalepisodes = 0;
        for (auto it = episodesperseason.begin(); it!=episodesperseason.end(); it++){
            totalepisodes += *it;
        }
        //cout << "Total episodes: " << totalepisodes;

        // ! Check if total episodes is smaller
        if (n > 0) {
            episodesWatched[index] = min(totalepisodes, n); // Update to the minimum of n or total episodes
        } else {
            // Increment the number of episodes watched by 1 if it's less than the total episodes
            if (episodesWatched[index] < totalepisodes) {
                episodesWatched[index]++;
            }
        }
        return 0;
    } else {
       // cout << "Error: Series not found in watched series." << endl;
        return -2;
    }
}

TVSeriesManagement::TVSeriesManagement(){};

vector<TVSeries*> TVSeriesManagement::getVectorTVSeries() const { return vectorTVSeries; }

int TVSeriesManagement::TVSeriesDelete(string title)
{
    for (auto it = vectorTVSeries.begin(); it != vectorTVSeries.end(); ++it) {
        if ((*it)->getTitle() == title) {
            delete *it; // Free the memory allocated for the TVSerie object
            vectorTVSeries.erase(it); // Remove the pointer from the vector
            return 0; // Series deleted successfully
        }
    }
    return -1; // Series not found
}

UserManagement::UserManagement(){};

vector<User*> UserManagement::getVectorUsers() const { return vectorUsers; }

void UserManagement::addUser(User* newUser)
{
    vectorUsers.push_back(newUser);
}

/**************************/
/*     A implementar      */
/**************************/

void User::displayUserInfo(ostream& os) const {
    // Displaying general user information
    os << "Displaying user info:" << endl;
    os << "-----Username: " << username << endl;
    os << "-----Name: " << name << endl;
    os << "-----Country: " << country << endl;
    
    // Displaying favorite genres of the user
    os << "-----Favorite Genres:" << endl;
    for (const auto& genre : favoriteGenres) {
        os << "------ " << genre << endl;
    }
    
    // Displaying information about watched series by the user
    os << "-----Watched Series:" << endl;
    for (size_t i = 0; i < watchedSeries.size(); ++i) {
        // Looping through each watched series and displaying its title and number of episodes watched
        os << "------ " << watchedSeries[i]->getTitle() << ", Episodes Watched: " << episodesWatched[i] << endl;
    }
}

int User::addRating(TVSeries* series, float rating) {
    // Initialize variables to track whether the series is watched by the user and the index of the series in the watchedSeries vector
    bool seriesWatched = false;
    int index = -1;

    // Iterate through the watchedSeries vector to find the given series
    for (size_t i = 0; i < watchedSeries.size(); ++i) {
        // If the current series matches the given series
        if (watchedSeries[i] == series) {
            // Set seriesWatched to true, indicating the series is watched by the user
            seriesWatched = true;
            // Save the index of the series
            index = i;
            // Exit the loop since the series is found
            break;
        }
    }

    // If the series is not watched by the user, return -2 indicating failure
    if (!seriesWatched) {
        return -2;
    }

    // Update the rating for the series at the corresponding index
    ratings[index] = rating;

    // Return 0 indicating successful addition or update of the rating
    return 0;
}
    // We could just use find(), then get the index using distance(). (Also, auto is so good, but idk if we can use it here.)

    // auto it = find(watchedSeries.begin(), watchedSeries.end(), series);
    // int index = distance(watchedSeries.begin(), it);

float TVSeries::updateRating(const vector<User*>& vectorUser) {
    // Initialize variables to keep track of total users who watched the series and sum of ratings for each season
    int totalWatched = 0;
    vector<float> ratingsSum(numberOfSeasons, 0.0f); // Initialize a vector with size equal to number of seasons, filled with 0.0

    // Iterate through each user in the provided vector
    for (const auto& user : vectorUser) {
        // Get the series watched by the current user and their corresponding ratings
        const auto& userWatchedSeries = user->getWatchedSeries();
        const auto& userRatings = user->getRatings();

        // Check if the current series (this) is watched by the user
        auto it = find(userWatchedSeries.begin(), userWatchedSeries.end(), this);
        if (it != userWatchedSeries.end()) { // If the series is found in user's watched series
            // Determine the index of the series in user's watched series list
            int index = distance(userWatchedSeries.begin(), it);
            // Get the rating given by the user for the series
            float userRating = userRatings[index];
            // Add the user's rating for each season of the series to the corresponding sum
            for (int j = 0; j < numberOfSeasons; ++j) {
                ratingsSum[j] += userRating;
            }
            // Increment the total number of users who watched the series
            totalWatched++;
        }
    }

    // If no users watched the series, return 0 as the rating
    if (totalWatched == 0) {
        return 0.0f;
    }

    // Calculate the average rating for each season
    float averageRating = 0.0f;
    for (int i = 0; i < numberOfSeasons; ++i) {
        ratingsSum[i] /= totalWatched; // Calculate the average rating for each season
        averageRating += ratingsSum[i]; // Sum up the average ratings for each season
    }
    averageRating /= numberOfSeasons; // Calculate the overall average rating for the series

    // Update the rating of the series with the calculated average rating
    rating = averageRating;

    // Return the updated rating of the series
    return rating;
}


int TVSeriesManagement::TVSeriesInsert(TVSeries* series) {
    // Check if the given series pointer is nullptr
    if (series == nullptr) {
        // Return -1 to indicate failure due to nullptr input
        return -1;
    }

    // Iterate through the existing TV series in the vectorTVSeries
    for (auto& existingSeries : vectorTVSeries) {
        // Check if the existing series pointer is not nullptr and its title matches the title of the given series
        if (existingSeries && existingSeries->getTitle() == series->getTitle()) {
            // If a series with the same title exists, update its information with the information of the given series
            *existingSeries = *series;
            // Return 1 to indicate that an existing series was updated with new information
            return 1;
        }
    }

    // If no series with the same title is found, add the given series pointer to the vectorTVSeries
    vectorTVSeries.push_back(series);
    // Return 0 to indicate successful insertion of a new series
    return 0;
}

int UserManagement::updateWatched(string filename, TVSeriesManagement& manager)
{
//answer 5
}