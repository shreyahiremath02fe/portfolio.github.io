#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include<algorithm>
#include<queue>

using namespace std;

// Function prototypes
map<string, double> getTopographyData(const vector<string>& cities);
map<string, double> getRainfallData(const vector<string>& cities);
map<string, double> getDrainageCapacity(const vector<string>& cities);
map<string, double> getLandUseData(const vector<string>& cities);
map<string, int> getFloodHistoryData(const vector<string>& cities);
map<string, double> getProximityToWaterBodies(const vector<string>& cities);

template <typename T>
void displayData(const map<string, T>& data, const string& title);

void displayCities(const vector<string>& cities);
void displayHistoricalData(const string& city);
void displayTopography(const string& city);
void displayRainfall(const string& city);
void displayDrainageCapacity(const string& city);
void displayLandUse(const string& city);
void displayFloodHistory(const string& city);
void displayProximityToWaterBodies(const string& city);
void displayAffectedPeople(const string& city);
void estimateEconomicLoss(const string& city);

// Function implementations for data retrieval and display
template <typename T>
void displayData(const map<string, T>& data, const string& title) {
    cout << "\n=== " << title << " ===\n";
    for (const auto& entry : data) {
        cout << entry.first << ": " << entry.second << "\n";
    }
    cout << "=====================================\n";
}

void displayCities(const vector<string>& cities) {
    cout << "\nAvailable Cities:\n";
    for (size_t i = 0; i < cities.size(); ++i) {
        cout << i + 1 << ". " << cities[i] << "\n";
    }
}

void displayTopography(const string& city) {
    cout << "\nTopographical Data for " << city << ":\n";
    cout << "Elevation: " << rand() % 50 + 1 << " meters\n";
}

void displayRainfall(const string& city) {
    cout << "\nRainfall Data for " << city << ":\n";
    cout << "Rainfall: " << rand() % 200 + 50 << " mm\n";
}

void displayDrainageCapacity(const string& city) {
    cout << "\nDrainage Capacity for " << city << ":\n";
    cout << "Drainage Capacity: " << rand() % 100 + 10 << "%\n";
}

void displayLandUse(const string& city) {
    cout << "\nLand Use Data for " << city << ":\n";
    cout << "Impervious Surface: " << rand() % 100 << "%\n";
}

void displayFloodHistory(const string& city) {
    cout << "\nFlood History for " << city << ":\n";
    cout << "Number of Floods in the Last Decade: " << rand() % 5 << " floods\n";
}

void displayProximityToWaterBodies(const string& city) {
    cout << "\nProximity to Water Bodies for " << city << ":\n";
    cout << "Distance to Water Bodies: " << rand() % 10 + 1 << " km\n";
}

void displayAffectedPeople(const string& city) {
    cout << "\nAnalyzing flood data for " << city << "...\n";
    cout << "Estimated affected people: " << rand() % 5000 + 1000 << "\n"; // Random number between 1000 and 6000
}

void estimateEconomicLoss(const string& city) {
    cout << "\nEstimating economic loss for " << city << "...\n";
    cout << "Estimated economic loss: $" << rand() % 100 + 1 << " million\n"; // Random number between 1 and 100 million
}

// Function to calculate the flood probability based on various factors
double calculateFloodProbability(
    const map<string, double>& topography,
    const map<string, double>& rainfall,
    const map<string, double>& drainage,
    const map<string, double>& landUse,
    const map<string, int>& floodHistory,
    const map<string, double>& proximity,
    const string& city,
    double maxTopography = 50.0,
    double maxRainfall = 250.0,
    double maxDrainage = 100.0,
    double maxLandUse = 100.0,
    double maxFloodHistory = 4.0,
    double maxProximity = 10.0
) {
    // Normalize the values
    double normT = topography.at(city) / maxTopography;
    double normR = rainfall.at(city) / maxRainfall;
    double normD = drainage.at(city) / maxDrainage;
    double normL = landUse.at(city) / maxLandUse;
    double normF = floodHistory.at(city) / maxFloodHistory;
    double normP = proximity.at(city) / maxProximity;

    // Weights for each factor
    double w1 = 0.2, w2 = 0.3, w3 = 0.1, w4 = 0.1, w5 = 0.2, w6 = 0.1;

    // Calculate the flood probability
    double floodProbability = w1 * normT + w2 * normR + w3 * normD + w4 * normL + w5 * normF + w6 * normP;

    // Convert to percentage
    return floodProbability * 100.0;
}


// Function to sort cities based on flood probability in descending order and print the city with the highest probability
void sortCitiesByFloodProbability(
    const map<string, double>& topography,
    const map<string, double>& rainfall,
    const map<string, double>& drainage,
    const map<string, double>& landUse,
    const map<string, int>& floodHistory,
    const map<string, double>& proximity,
    const vector<string>& cities
) {
    // Vector to store city and their corresponding flood probability
    vector<pair<string, double>> cityFloodProbabilities;

    for (const auto& city : cities) {
        double floodProb = calculateFloodProbability(topography, rainfall, drainage, landUse, floodHistory, proximity, city);
        cityFloodProbabilities.push_back({city, floodProb});
    }

    // Sort cities by flood probability (descending order)
    sort(cityFloodProbabilities.begin(), cityFloodProbabilities.end(),
         [](const pair<string, double>& a, const pair<string, double>& b) {
             return a.second > b.second;  // Sort by flood probability (descending)
         });

    // Print the city with the highest flood probability
    if (!cityFloodProbabilities.empty()) {
        cout << "City with highest flood probability: "
             << cityFloodProbabilities.front().first
             << " with " << cityFloodProbabilities.front().second
             << "% flood probability.\n";
    }

    // Display the sorted list of cities with their flood probabilities
    cout << "\n=== Cities Sorted by Flood Probability (Descending) ===\n";
    for (const auto& entry : cityFloodProbabilities) {
        cout << entry.first << ": " << entry.second << "%\n";
    }
    cout << "=======================================================\n";
}



// Simulated data retrieval functions
map<string, double> getTopographyData(const vector<string>& cities) {
    map<string, double> data;
    for (const auto& city : cities) {
        data[city] = rand() % 50 + 1; // Random topography values between 1 and 50 meters
    }
    return data;
}

map<string, double> getRainfallData(const vector<string>& cities) {
    map<string, double> data;
    for (const auto& city : cities) {
        data[city] = rand() % 200 + 50; // Random rainfall values between 50 and 250 mm
    }
    return data;
}

map<string, double> getDrainageCapacity(const vector<string>& cities) {
    map<string, double> data;
    for (const auto& city : cities) {
        data[city] = rand() % 100 + 10; // Random drainage capacity values between 10 and 100%
    }
    return data;
}

map<string, double> getLandUseData(const vector<string>& cities) {
    map<string, double> data;
    for (const auto& city : cities) {
        data[city] = rand() % 100; // Random land use values between 0 and 100%
    }
    return data;
}

map<string, int> getFloodHistoryData(const vector<string>& cities) {
    map<string, int> data;
    for (const auto& city : cities) {
        data[city] = rand() % 5; // Random flood history values between 0 and 4 floods
    }
    return data;
}

map<string, double> getProximityToWaterBodies(const vector<string>& cities) {
    map<string, double> data;
    for (const auto& city : cities) {
        data[city] = rand() % 10 + 1; // Random proximity values between 1 and 10 km
    }
    return data;
}

// Function to calculate the preparedness index based on various factors
void calculatePreparednessIndex(const string& city) {
    // Simulated data retrieval for the selected city
    map<string, double> drainageCapacity = getDrainageCapacity({city});
    map<string, int> floodHistory = getFloodHistoryData({city});
    map<string, double> proximityToWaterBodies = getProximityToWaterBodies({city});

    // Get data for the selected city
    double drainage = drainageCapacity.at(city);
    int floodsInLastDecade = floodHistory.at(city);
    double proximity = proximityToWaterBodies.at(city);

    // Normalize the values (assuming max values for each parameter)
    double maxDrainage = 100.0;  // Max drainage capacity as 100%
    double maxFloods = 5.0;  // Max number of floods in the last decade
    double maxProximity = 10.0;  // Max distance to water bodies in km

    double normD = drainage / maxDrainage;
    double normF = (floodsInLastDecade) / maxFloods;
    double normP = proximity / maxProximity;

    // Weights for each factor in the preparedness index
    double w1 = 0.4, w2 = 0.4, w3 = 0.2;  // Drainage, Flood History, Proximity

    // Calculate the preparedness index
    double preparednessIndex = w1 * normD + w2 * (1 - normF) + w3 * (1 - normP);

    // Convert to percentage
    preparednessIndex = preparednessIndex * 100.0;

    // Display the result
    cout << "\nPreparedness Index for " << city << ": " << preparednessIndex << "%\n";
}

// Function to display the community awareness rating for a city
void rateCommunityAwareness(const string& city) {
    unordered_map<string, int> cityAwarenessRatings = {
        {"Kurla", 5},
        {"Chembur", 6},
        {"Andheri", 7},
        {"Lower Parel", 8},
        {"Bandra East", 7},
        {"Sion", 6},
        {"Mumbai City", 8},
        {"Goregaon", 6},
        {"Malad", 6},
        {"Jogeshwari", 5},
        {"Powai", 7},
        {"Vikhroli", 7},
        {"Mulund", 6},
        {"Bhandup", 5},
        {"Borivali", 7},
        {"Kandivali", 6},
        {"Santa Cruz", 6},
        {"Vile Parle", 7},
        {"Charni Road", 5},
        {"Grant Road", 6},
        {"Marine Lines", 7},
        {"Chowpatty", 8},
        {"Colaba", 8},
        {"Fort", 8},
        {"Churchgate", 8},
        {"Nariman Point", 9},
        {"Mazgaon", 6},
        {"Byculla", 5},
        {"Parel", 7},
        {"Worli", 7},
        {"Haji Ali", 6},
        {"Mahalaxmi", 6},
        {"Tardeo", 5},
        {"Elphinstone", 6},
        {"Antop Hill", 4},
        {"Dadar East", 6},
        {"Dadar West", 7},
        {"Wadala", 5},
        {"Matunga", 6},
        {"Sewri", 6},
        {"Kalbadevi", 7},
        {"Girgaon", 7},
        {"Cuffe Parade", 8},
        {"Chinchpokli", 5},
        {"Reay Road", 5},
        {"Mumbai Central", 6},
        {"Agripada", 6},
        {"Malabar Hill", 8},
        {"Walkeshwar", 8}
    };

    if (cityAwarenessRatings.find(city) != cityAwarenessRatings.end()) {
        int rating = cityAwarenessRatings[city];
        string status = (rating >= 7) ? "High" : (rating >= 5) ? "Moderate" : "Low";
        cout << "Community awareness in " << city << " is rated as " << status << " (" << rating << "/10)." << endl;
    } else {
        cout << "City not found in the database." << endl;
    }
}


// Function to simulate the environmental impact of floods
void simulateEnvironmentalImpact(const string& city) {
    unordered_map<string, pair<int, int>> cityEnvironmentalImpacts = {
        {"Dharavi", {13, 10}},{"Kurla", {15, 10}}, {"Chembur", {18, 8}},
        {"Andheri", {20, 12}}, {"Lower Parel", {10, 5}},
        {"Bandra East", {12, 7}}, {"Sion", {17, 9}},
        {"Mumbai City", {25, 15}}, {"Goregaon", {22, 13}},
        {"Malad", {20, 10}}, {"Jogeshwari", {16, 8}},
         {"Powai", {20, 5}}, {"Vikhroli", {19, 11}},
        {"Mulund", {15, 6}}, {"Bhandup", {18, 9}},
        {"Borivali", {14, 6}}, {"Kandivali", {19, 10}},
        {"Santa Cruz", {18, 9}}, {"Vile Parle", {17, 8}},
         {"Charni Road", {15, 7}}, {"Grant Road", {16, 8}},
        {"Marine Lines", {21, 12}}, {"Chowpatty", {22, 13}},
        {"Colaba", {24, 14}}, {"Fort", {23, 13}},
        {"Churchgate", {22, 12}}, {"Nariman Point", {26, 16}},
        {"Mazgaon", {18, 9}}, {"Byculla", {14, 6}},
        {"Parel", {20, 10}}, {"Worli", {19, 9}},
         {"Haji Ali", {18, 8}}, {"Mahalaxmi", {17, 7}},
        {"Tardeo", {15, 6}}, {"Elphinstone", {16, 7}},
         {"Antop Hill", {13, 5}}, {"Dadar East", {17, 8}},
        {"Dadar West", {18, 9}}, {"Wadala", {16, 7}},
        {"Matunga", {17, 8}}, {"Sewri", {19, 10}},
        {"Kalbadevi", {18, 9}}, {"Girgaon", {20, 11}},
         {"Cuffe Parade", {23, 14}}, {"Chinchpokli", {14, 6}},
        {"Reay Road", {15, 7}}, {"Mumbai Central", {17, 8}},
         {"Agripada", {18, 9}}, {"Malabar Hill", {22, 13}},
        {"Walkeshwar", {21, 12}}
    };

    // Check if the city is in the map
    if (cityEnvironmentalImpacts.find(city) != cityEnvironmentalImpacts.end()) {
        // Get the pollution increase and green cover loss for the selected city
        pair<int, int> impact = cityEnvironmentalImpacts[city];
        int waterPollutionIncrease = impact.first;
        int greenCoverLoss = impact.second;

        // Display the simulated environmental impact
        cout << "Flood in " << city << " caused a " << waterPollutionIncrease
             << "% increase in water pollution levels and " << greenCoverLoss
             << "% loss of green cover." << endl;
    } else {
        cout << "City not found in the database." << endl;
    }
}


// Function to display the flood timeline for a selected city
void displayFloodTimeline(const string& city) {
    unordered_map<string, vector<pair<int, string>>> cityFloodTimelines = {
       {"Dharavi", {
            {2010, "Severe flooding caused by overflowing drains and heavy rainfall."},
            {2012, "Waterlogging in low-lying areas disrupted transportation."},
            {2015, "Flash floods after intense rainfall led to property damage."},
            {2018, "Flooding due to clogged drainage system and continuous rains."},
            {2020, "Waterlogging and minor floods due to high monsoon rains."},
            {2023, "Severe flooding caused by torrential rains and overwhelmed drainage system."}
        }},

         {"Kurla", {
            {2010, "Heavy rainfall caused drainage overflow."},
            {2015, "Severe waterlogging disrupted daily life."},
            {2020, "Flooding due to continuous monsoon rains."},
            {2022, "Flash floods caused by intense rainfall."},
            {2023, "Severe flooding due to heavy rainfall."}
        }},
        {"Chembur", {
            {2008, "Heavy rains led to severe waterlogging."},
            {2014, "Flooding affected transportation routes."},
            {2021, "Flash floods caused by unexpected downpours."},
            {2023, "Severe flooding due to continuous rainfall."}
        }},
        {"Andheri", {
            {2011, "Flooding after heavy rains caused traffic disruptions."},
            {2016, "Floodwaters inundated low-lying areas."},
            {2022, "Drainage overflow caused localized flooding."},
            {2023, "Flash floods affected local areas."}
        }},
        {"Lower Parel", {
            {2012, "Flash floods caused by sudden heavy rainfall."},
            {2018, "River overflow affected surrounding areas."},
            {2020, "Flooding due to blocked drainage system."},
            {2023, "Heavy rains caused waterlogging and flooding."}
        }},
        {"Bandra East", {
            {2013, "Flooding caused by excessive rainfall."},
            {2017, "Flooding due to river overflow."},
            {2023, "Flooding caused by heavy monsoon rains."}
        }},
        {"Sion", {
            {2009, "Drainage overflow led to flooding."},
            {2014, "Severe flooding after continuous rainfall."},
            {2020, "Waterlogging caused disruptions in local areas."},
            {2022, "Flooding due to blocked drainage system."}
        }},
        {"Mumbai City", {
            {2005, "Massive flooding after heavy rainfall, affecting thousands."},
            {2016, "Flooding caused by overflowing rivers."},
            {2022, "Severe flooding due to unexpected monsoon rains."},
            {2023, "Flooding caused by continuous heavy rainfall."}
        }},
        {"Goregaon", {
            {2010, "Flooding caused by blocked drainage system."},
            {2015, "Waterlogging after heavy rainfall."},
            {2021, "Flash floods due to intense rainfall."},
            {2023, "Flooding caused by drainage overflow."}
        }},
        {"Malad", {
            {2007, "Flooding due to heavy rains and drainage overflow."},
            {2014, "Flooding caused by overflowing rivers."},
            {2022, "Waterlogging caused by drainage issues."},
            {2023, "Flooding caused by continuous rainfall."}
        }},
        {"Jogeshwari", {
            {2010, "Heavy rainfall caused drainage overflow."},
            {2017, "River flooding affected 15,000 people."},
            {2022, "Waterlogging caused by blocked drainage system."},
            {2023, "Severe flooding due to heavy monsoon rains."}
        }},
        {"Powai", {
            {2011, "Flooding due to heavy rainfall and waterlogging."},
            {2017, "River flooding affected 15,000 people."},
            {2020, "Flooding due to drainage overflow."},
            {2023, "Flash floods caused by sudden heavy rainfall."}
        }},
        {"Vikhroli", {
            {2009, "Flooding caused by continuous rains."},
            {2016, "Flash floods affected low-lying areas."},
            {2021, "Severe flooding due to drainage overflow."},
            {2023, "Flooding caused by waterlogging."}
        }},
        {"Mulund", {
            {2012, "Flooding caused by heavy rainfall and poor drainage."},
            {2016, "River overflow caused flooding in the area."},
            {2020, "Waterlogging caused by excessive rains."},
            {2023, "Flooding due to blocked drainage system."}
        }},
        {"Bhandup", {
            {2014, "Flooding due to continuous heavy rains."},
            {2018, "Flooding caused by drainage overflow."},
            {2023, "Flooding due to river overflow."}
        }},
        {"Borivali", {
            {2010, "Flooding caused by blocked drainage system."},
            {2015, "Heavy rains led to severe waterlogging."},
            {2022, "Flooding caused by excessive rainfall."},
            {2023, "Waterlogging caused by heavy rains."}
        }},
        {"Kandivali", {
            {2011, "Flooding caused by heavy monsoon rains."},
            {2016, "Waterlogging after continuous rainfall."},
            {2023, "Flooding due to drainage issues."}
        }},
        {"Santa Cruz", {
            {2013, "Flooding caused by heavy rainfall."},
            {2018, "Waterlogging after severe rains."},
            {2020, "Flooding due to drainage overflow."},
            {2023, "Flooding caused by continuous rainfall."}
        }},
        {"Vile Parle", {
            {2014, "Flooding caused by sudden heavy rains."},
            {2017, "Waterlogging affected local transportation."},
            {2021, "Flooding due to drainage overflow."},
            {2023, "Flash floods caused by intense rainfall."}
        }},
        {"Charni Road", {
            {2010, "Flooding caused by heavy rains and drainage issues."},
            {2016, "Flash floods affected low-lying areas."},
            {2022, "Waterlogging caused by continuous rainfall."},
            {2023, "Flooding due to drainage overflow."}
        }},
        {"Grant Road", {
            {2012, "Flooding due to excessive rainfall."},
            {2015, "Severe flooding caused by blocked drainage."},
            {2020, "Waterlogging after heavy rains."},
            {2023, "Flooding caused by drainage overflow."}
        }},
        {"Marine Lines", {
            {2008, "Flooding caused by heavy monsoon rains."},
            {2014, "Flooding due to drainage overflow."},
            {2021, "Flash floods caused by sudden heavy rainfall."},
            {2023, "Severe flooding due to heavy rainfall."}
        }},
        {"Chowpatty", {
            {2010, "Flooding caused by heavy rainfall."},
            {2016, "Flooding due to waterlogging."},
            {2020, "Severe flooding after continuous rains."},
            {2023, "Flooding caused by drainage overflow."}
        }},
        {"Colaba", {
            {2011, "Flooding caused by excessive rainfall."},
            {2017, "Waterlogging and drainage overflow."},
            {2022, "Flooding due to heavy rains."},
            {2023, "Flooding caused by intense rainfall."}
        }},
    };

    if (cityFloodTimelines.find(city) != cityFloodTimelines.end()) {
        cout << "Flood Timeline for " << city << ":\n";
        for (const auto& event : cityFloodTimelines[city]) {
            cout << "- " << event.first << ": " << event.second << endl;
        }
    } else {
        cout << "City not found in the database. Please ensure the city name is correct.\n";
    }
}


// Function to display city details
void displayCityDetails(const string &city, const map<string, pair<double, int>> &cityData) {
    auto it = cityData.find(city);
    if (it != cityData.end()) {
        cout << "\nCity: " << city << endl;
        cout << "Geographical Area: " << it->second.first << " sq. km" << endl;
        cout << "Population: " << it->second.second << endl;
    } else {
        cout << "\nCity not found!" << endl;
    }
}


// Function to search for a city using substring matching and display its flood probability
void searchCityByName(
    const map<string, double>& topography,
    const map<string, double>& rainfall,
    const map<string, double>& drainage,
    const map<string, double>& landUse,
    const map<string, int>& floodHistory,
    const map<string, double>& proximity,
    const vector<string>& cities
) {
    // Get the search string from the user
    std::string searchQuery;
    std::cout << "Enter the name of the city to search for: ";
    std::cin.ignore();  // To ignore any leftover newline from previous input
    std::getline(std::cin, searchQuery);

    // Search for cities that match the query
    bool cityFound = false;
    for (const auto& city : cities) {
        if (city.find(searchQuery) != std::string::npos) {  // Check if the city name contains the search query
            cityFound = true;
            double floodProbability = calculateFloodProbability(
                topography, rainfall, drainage, landUse, floodHistory, proximity, city
            );
            std::cout << "City: " << city << "\n";
            std::cout << "Flood Probability: " << floodProbability << "%\n";
        }
    }

    if (!cityFound) {
        std::cout << "No cities found matching your search query.\n";
    }
}

// Function to send flood alerts based on calculated probabilities
void sendFloodAlert(
    const std::vector<std::string>& cities,
    const std::map<std::string, double>& topography,
    const std::map<std::string, double>& rainfall,
    const std::map<std::string, double>& drainage,
    const std::map<std::string, double>& landUse,
    const std::map<std::string, int>& floodHistory,
    const std::map<std::string, double>& proximity
) {
    // Default maximum values for normalization
    double maxTopography = 50.0;
    double maxRainfall = 250.0;
    double maxDrainage = 100.0;
    double maxLandUse = 100.0;
    double maxFloodHistory = 4.0;
    double maxProximity = 10.0;

    // Iterate over each city and send alerts
    for (const auto& city : cities) {
        // Ensure all necessary data exists for the city
        if (topography.count(city) && rainfall.count(city) && drainage.count(city) &&
            landUse.count(city) && floodHistory.count(city) && proximity.count(city)) {

            // Calculate flood probability
            double floodProb = calculateFloodProbability(
                topography, rainfall, drainage, landUse, floodHistory, proximity, city,
                maxTopography, maxRainfall, maxDrainage, maxLandUse, maxFloodHistory, maxProximity
            );

            // Send appropriate alerts based on the probability
            if (floodProb >= 80.0) {
                std::cout << "EVACUATION ALERT: Flood probability in " << city
                          << " is " << floodProb << "%. Evacuate immediately!\n";
            } else if (floodProb >= 70.0) {
                std::cout << "FLOOD WARNING: Flood probability in " << city
                          << " is " << floodProb << "%. Be prepared for evacuation!\n";
            }
        } else {
            // Handle missing data for the city
            std::cerr << "Error: Missing data for city " << city << ". Skipping...\n";
        }
    }
}


const float INF = 1e9;

//structure for affected areas

struct Area {

    int id;
    std::string name;
    std::string district;
    int population;
    float floodRiskLevel;
};

//structure for shelters

struct Shelter {

    std::string name;
    int capacity;
    int currentOccupants;
    std::unordered_map<std::string, float> distanceToArea;

    // Constructor to initialize Shelter

    Shelter(const std::string& name, int capacity, int currentOccupants,
            const std::unordered_map<std::string, float>& distances)
        : name(name), capacity(capacity), currentOccupants(currentOccupants), distanceToArea(distances) {}

};


//structure for the evacuees

struct Evacuee {

    std::string name;
    int age;
    std::string shelter;
    std::string city;

};

//structure for vehicles

struct Vehicle {

    std::string name;
    int capacity; // Maximum number of people
    int currentOccupants; // Current number of people in the vehicle
    std::vector<std::string> assignedRoutes; // List of routes the vehicle is assigned to
    float distanceCovered; // Distance the vehicle has already traveled

};

//structure for food suppliments information storage

struct FoodSupply {

    std::string type;  // Type of food (e.g., "Canned Goods", "Rice", etc.)

    float quantity;    // Quantity of food in kilograms or units

    std::unordered_map<std::string, float> areaSupply; // Area names with corresponding food supply quantities

    std::unordered_map<std::string, float> shelterSupply; // Shelter names with corresponding food supply quantities

};

// Structure for Goods

struct Goods {

    std::string type;
    int quantity;
    std::string target;  // To store whether it's for an Area or Shelter
    std::string targetName;  // Name of the area or shelter

};

//structure to manage rescue teams

struct RescueTeam {

    std::string teamName;
    std::string areaAssigned;
    bool isAvailable;  // If true, the team is available for assignment, else it's occupied

};

//structure for water suppliments management

struct WaterSupply {

    std::string waterType;  // e.g., "Bottled", "Tankers"
    int quantity;  // Amount of water (liters)
    bool isDistributed;  // Flag to indicate if the water is distributed

};


// Function to assess flood risk based on population size

void assessRisk(std::vector<Area>& areas) {

    for (auto& area : areas) {

        if (area.population > 5000) {

            area.floodRiskLevel = 0.8; // High risk

        } else if (area.population > 2000) {

            area.floodRiskLevel = 0.5; // Medium risk

        } else {

            area.floodRiskLevel = 0.2; // Low risk
        }
    }
}

// Function to display flood risk information

void displayRiskInfo(const std::vector<Area>& areas) {

    int cityChoice;

    std::cout << "\nChoose a city to view flood risk information:\n";

    for (size_t i = 0; i < areas.size(); ++i) {

        std::cout << i + 1 << ". " << areas[i].name << "\n";

    }

    std::cout << "Enter city number: ";
    std::cin >> cityChoice;

    if (cityChoice < 1 || cityChoice > areas.size()) {

        std::cout << "Invalid city choice.\n";
        return;

    }

    // Display flood risk for the chosen city


    std::cout << "\nFlood Risk Information for " << areas[cityChoice - 1].name << ":\n";
    std::cout << "Population: " << areas[cityChoice - 1].population << "\n";
    std::cout << "Flood Risk Level: ";

    if (areas[cityChoice - 1].floodRiskLevel > 0.7) {

        std::cout << "High\n";

    } else if (areas[cityChoice - 1].floodRiskLevel > 0.3) {

        std::cout << "Medium\n";

    } else {

        std::cout << "Low\n";

    }

    std::cout << "-------------------------------------------\n";

}

// Function to display shelter information

void displayShelterInfo(const std::vector<Shelter>& shelters, const std::vector<Evacuee>& evacuees) {

    int shelterChoice;

    std::cout << "\nChoose a shelter to view shelter information:\n";

    for (size_t i = 0; i < shelters.size(); ++i) {

        std::cout << i + 1 << ". " << shelters[i].name << "\n";

    }

    std::cout << "Enter shelter number: ";
    std::cin >> shelterChoice;

    if (shelterChoice < 1 || shelterChoice > shelters.size()) {

        std::cout << "Invalid shelter choice.\n";
        return;

    }

    const Shelter& selectedShelter = shelters[shelterChoice - 1];

    // Calculate the number of evacuees in the shelter

    int evacueeCount = 0;

    for (const auto& evacuee : evacuees) {

        if (evacuee.shelter == selectedShelter.name) {
            ++evacueeCount;
        }

    }

    // Display shelter information for the selected shelter

    std::cout << "\nShelter Information for " << selectedShelter.name << ":\n";

    std::cout << "Capacity: " << selectedShelter.capacity << "\n";

    std::cout << "Current Occupants: " << evacueeCount << "\n";

    std::cout << "Available Spaces: " << (selectedShelter.capacity - evacueeCount) << "\n";

    std::cout << "-------------------------------------------\n";
}

// Function to display evacuation routes and distance from area to shelter


void displayEvacuationRoutes(std::vector<Area>& areas, std::vector<Shelter>& shelters) {

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Generate random distances for all shelters and areas

    for (auto& shelter : shelters) {

        for (const auto& area : areas) {

            shelter.distanceToArea[area.name] = (std::rand() % 50) + 1; // Random distance between 1 and 50 km

        }
    }


    // Allow user to choose a specific area and shelter


    int shelterChoice, areaChoice;
    std::cout << "\nChoose an area to view evacuation routes:\n";

    for (size_t i = 0; i < areas.size(); ++i) {

        std::cout << i + 1 << ". " << areas[i].name << "\n";
    }

    std::cout << "Enter area number: ";
    std::cin >> areaChoice;

    if (areaChoice < 1 || areaChoice > areas.size()) {
        std::cout << "Invalid area choice.\n";
        return;
    }

    const Area& selectedArea = areas[areaChoice - 1];

    std::cout << "\nChoose a shelter to view evacuation routes:\n";
    for (size_t i = 0; i < shelters.size(); ++i) {

        std::cout << i + 1 << ". " << shelters[i].name << "\n";

    }

    std::cout << "Enter shelter number: ";
    std::cin >> shelterChoice;

    if (shelterChoice < 1 || shelterChoice > shelters.size()) {

        std::cout << "Invalid shelter choice.\n";
        return;

    }

    const Shelter& selectedShelter = shelters[shelterChoice - 1];

    std::cout << "\nEvacuation Route Details:\n";
    std::cout << "Area: " << selectedArea.name << "\n";
    std::cout << "Shelter: " << selectedShelter.name << "\n";

    if (selectedShelter.distanceToArea.find(selectedArea.name) != selectedShelter.distanceToArea.end()) {

        std::cout << "Distance: " << selectedShelter.distanceToArea.at(selectedArea.name) << " km\n";
    } else {
        std::cout << "Distance information not available for this area and shelter combination.\n";

    }

    std::cout << "-------------------------------------------\n";
}


void registerEvacuees(std::vector<Shelter>& shelters, std::vector<Evacuee>& evacuees) {
    int choice;

    while (true) {

        std::cout << "\n1. View Evacuees Information\n";
        std::cout << "2. Register/Add an Evacuee\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {


            int shelterChoice;
            std::cout << "\nChoose a shelter to view evacuees:\n";

            for (size_t i = 0; i < shelters.size(); ++i) {

                std::cout << i + 1 << ". " << shelters[i].name << "\n";

            }

            std::cout << "Enter shelter number: ";
            std::cin >> shelterChoice;

            if (shelterChoice < 1 || shelterChoice > shelters.size()) {

                std::cout << "Invalid shelter choice.\n";
                continue;

            }

            std::cout << "\nEvacuees in " << shelters[shelterChoice - 1].name << ":\n";

            for (const auto& evacuee : evacuees) {

                if (evacuee.shelter == shelters[shelterChoice - 1].name) {

                    std::cout << "Name: " << evacuee.name << ", Age: " << evacuee.age << ", City: " << evacuee.city << "\n";

                }
            }

            std::cout << "-------------------------------------------\n";

        } else if (choice == 2) {

            std::string name, city;
            int age, shelterChoice;

            std::cout << "\nEnter Evacuee Name: ";
            std::cin >> name;

            std::cout << "Enter Evacuee Age: ";
            std::cin >> age;

            std::cout << "Enter Evacuee City: ";
            std::cin >> city;

            std::cout << "\nChoose a shelter for the evacuee:\n";

            for (size_t i = 0; i < shelters.size(); ++i) {
                std::cout << i + 1 << ". " << shelters[i].name << "\n";
            }

            std::cout << "Enter shelter number: ";
            std::cin >> shelterChoice;

            if (shelterChoice < 1 || shelterChoice > shelters.size()) {

                std::cout << "Invalid shelter choice. Registration failed.\n";
                continue;

            }

            // Update shelter occupant count
            shelters[shelterChoice - 1].currentOccupants++;

            // Register evacuee
            evacuees.push_back({name, age, shelters[shelterChoice - 1].name, city});

            std::cout << "Evacuee registered successfully!\n";
            std::cout << "-------------------------------------------\n";

        } else {

            std::cout << "Invalid choice.\n";

        }

        char continueManaging;
        std::cout << "\nDo you want to manage evacuees again? (Y/N): ";
        std::cin >> continueManaging;

        if (continueManaging == 'N' || continueManaging == 'n') {
            break;
        }
    }
}

//Function to manage transportation

void manageTransportation(std::vector<Vehicle>& vehicles, const std::vector<Area>& areas, const std::vector<Shelter>& shelters) {

    int choice;
    while (true) {

        std::cout << "\nTransportation Management Menu:\n";
        std::cout << "1. View Vehicle Information\n";
        std::cout << "2. Assign Vehicle to Evacuation Route\n";
        std::cout << "3. View Transport Routes\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {

            // View vehicle information

            int vehicleChoice;
            std::cout << "\nChoose a vehicle to view information:\n";

            for (size_t i = 0; i < vehicles.size(); ++i) {
                std::cout << i + 1 << ". " << vehicles[i].name << "\n";
            }

            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleChoice;

            if (vehicleChoice < 1 || vehicleChoice > vehicles.size()) {

                std::cout << "Invalid vehicle choice.\n";
                continue;

            }

            // Display vehicle information

            std::cout << "\nVehicle Information for " << vehicles[vehicleChoice - 1].name << ":\n";

            std::cout << "Capacity: " << vehicles[vehicleChoice - 1].capacity << "\n";

            std::cout << "Current Occupants: " << vehicles[vehicleChoice - 1].currentOccupants << "\n";

            std::cout << "Assigned Routes: ";

            for (const auto& route : vehicles[vehicleChoice - 1].assignedRoutes) {
                std::cout << route << " ";
            }

            std::cout << "\n-------------------------------------------\n";
        }

        else if (choice == 2) {

            // Assign Vehicle to Evacuation Route

            int vehicleChoice, areaChoice, shelterChoice;

            std::cout << "\nChoose a vehicle to assign to a route:\n";
            for (size_t i = 0; i < vehicles.size(); ++i) {

                std::cout << i + 1 << ". " << vehicles[i].name << "\n";

            }

            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleChoice;

            if (vehicleChoice < 1 || vehicleChoice > vehicles.size()) {

                std::cout << "Invalid vehicle choice.\n";
                continue;

            }

            // Allow user to choose area and shelter for the route

            std::cout << "\nChoose a city to choose an evacuation route:\n";
            for (size_t i = 0; i < areas.size(); ++i) {

                std::cout << i + 1 << ". " << areas[i].name << "\n";

            }

            std::cout << "Enter city number: ";
            std::cin >> areaChoice;

            if (areaChoice < 1 || areaChoice > areas.size()) {

                std::cout << "Invalid city choice.\n";
                continue;

            }

            // Display shelter options

            std::cout << "\nChoose a shelter for the evacuation route:\n";
            for (size_t i = 0; i < shelters.size(); ++i) {

                std::cout << i + 1 << ". " << shelters[i].name << "\n";

            }
            std::cout << "Enter shelter number: ";
            std::cin >> shelterChoice;

            if (shelterChoice < 1 || shelterChoice > shelters.size()) {

                std::cout << "Invalid shelter choice.\n";
                continue;

            }

            // Assign the route

            vehicles[vehicleChoice - 1].assignedRoutes.push_back(areas[areaChoice - 1].name + " to " + shelters[shelterChoice - 1].name);

            std::cout << "Vehicle assigned to evacuation route successfully!\n";
            std::cout << "-------------------------------------------\n";
        }

        else if (choice == 3) {

            // View Transport Routes

            int vehicleChoice;

            std::cout << "\nChoose a vehicle to view transport routes:\n";

            for (size_t i = 0; i < vehicles.size(); ++i) {
                std::cout << i + 1 << ". " << vehicles[i].name << "\n";
            }

            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleChoice;

            if (vehicleChoice < 1 || vehicleChoice > vehicles.size()) {

                std::cout << "Invalid vehicle choice.\n";
                continue;

            }

            // Display transport routes for the selected vehicle

            std::cout << "\nTransport Routes for " << vehicles[vehicleChoice - 1].name << ":\n";

            for (const auto& route : vehicles[vehicleChoice - 1].assignedRoutes) {
                std::cout << route << "\n";
            }

            std::cout << "-------------------------------------------\n";
        }

        else {
            std::cout << "Invalid choice.\n";
        }

        // Ask if the user wants to go back to the main menu or continue transportation management

        char continueManaging;

        std::cout << "\nDo you want to manage transportation again? (Y/N): ";
        std::cin >> continueManaging;

        if (continueManaging == 'N' || continueManaging == 'n') {

            break; // Exit transportation management and go back to main menu

        }
    }
}


//Function to manage food suppliments

void manageFoodSupply(std::vector<FoodSupply>& foodSupplies, const std::vector<Area>& areas, const std::vector<Shelter>& shelters) {

    int choice;

    while (true) {

        std::cout << "\nFood Supply Management Menu:\n";
        std::cout << "1. View Food Supplies\n";
        std::cout << "2. Add Food Supply to Area\n";
        std::cout << "3. Add Food Supply to Shelter\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {

            // View current food supplies
            std::cout << "\nCurrent Food Supplies:\n";

            for (const auto& food : foodSupplies) {

                std::cout << "Food Type: " << food.type << "\n";
                std::cout << "Total Quantity: " << food.quantity << " kg\n";
                std::cout << "Supplied to Areas:\n";

                for (const auto& supply : food.areaSupply) {

                    std::cout << "    " << supply.first << ": " << supply.second << " kg\n";

                }

                std::cout << "Supplied to Shelters:\n";

                for (const auto& supply : food.shelterSupply) {

                    std::cout << "    " << supply.first << ": " << supply.second << " kg\n";
                }

                std::cout << "-------------------------------------------\n";
            }
        }

        else if (choice == 2) {

            // Add Food Supply to Area
            std::string foodType;
            float quantity;
            int areaChoice;

            std::cout << "\nEnter Food Type (e.g., Rice, Canned Goods): ";
            std::cin >> foodType;

            std::cout << "Enter Quantity in kilograms: ";
            std::cin >> quantity;

            // Choose Area
            std::cout << "\nChoose an Area to supply food:\n";

            for (size_t i = 0; i < areas.size(); ++i) {

                std::cout << i + 1 << ". " << areas[i].name << "\n";
            }

            std::cout << "Enter area number: ";
            std::cin >> areaChoice;

            if (areaChoice < 1 || areaChoice > areas.size()) {

                std::cout << "Invalid area choice.\n";
                continue;

            }

            // Check if food already exists in foodSupplies
            bool foodExists = false;

            for (auto& food : foodSupplies) {

                if (food.type == foodType) {

                    food.areaSupply[areas[areaChoice - 1].name] += quantity;
                    food.quantity += quantity;
                    foodExists = true;
                    break;

                }
            }

            // If food doesn't exist, create new supply
            if (!foodExists) {

                FoodSupply newFood = {foodType, quantity};
                newFood.areaSupply[areas[areaChoice - 1].name] = quantity;
                foodSupplies.push_back(newFood);

            }

            std::cout << "Food supply added to " << areas[areaChoice - 1].name << ".\n";
            std::cout << "-------------------------------------------\n";
        }

        else if (choice == 3) {

            // Add Food Supply to Shelter

            std::string foodType;
            float quantity;
            int shelterChoice;

            std::cout << "\nEnter Food Type (e.g., Rice, Canned Goods): ";
            std::cin >> foodType;

            std::cout << "Enter Quantity in kilograms: ";
            std::cin >> quantity;

            // Choose Shelter
            std::cout << "\nChoose a Shelter to supply food:\n";

            for (size_t i = 0; i < shelters.size(); ++i) {

                std::cout << i + 1 << ". " << shelters[i].name << "\n";

            }

            std::cout << "Enter shelter number: ";
            std::cin >> shelterChoice;

            if (shelterChoice < 1 || shelterChoice > shelters.size()) {

                std::cout << "Invalid shelter choice.\n";
                continue;
            }

            // Check if food already exists in foodSupplies
            bool foodExists = false;

            for (auto& food : foodSupplies) {

                if (food.type == foodType) {

                    food.shelterSupply[shelters[shelterChoice - 1].name] += quantity;
                    food.quantity += quantity;
                    foodExists = true;
                    break;

                }
            }

            // If food doesn't exist, create new supply

            if (!foodExists) {

                FoodSupply newFood = {foodType, quantity};
                newFood.shelterSupply[shelters[shelterChoice - 1].name] = quantity;
                foodSupplies.push_back(newFood);

            }

            std::cout << "Food supply added to " << shelters[shelterChoice - 1].name << ".\n";
            std::cout << "-------------------------------------------\n";
        }

        else {
            std::cout << "Invalid choice.\n";
        }

        // Ask if the user wants to continue or return to main menu
        char continueManaging;

        std::cout << "\nDo you want to manage food supplies again? (Y/N): ";
        std::cin >> continueManaging;

        if (continueManaging == 'N' || continueManaging == 'n') {
            break; // Exit food supply management and go back to main menu
        }
    }
}


// Function to distribute goods supplements to areas or shelters

void distributeGoodsSupply(std::vector<Area>& areas, std::vector<Shelter>& shelters, std::vector<Goods>& distributedGoods) {

    int choice;
    std::cout << "\nGoods Supplies Management Menu:\n";
    std::cout << "1. Distribute Goods to an Area\n";
    std::cout << "2. Distribute Goods to a Shelter\n";
    std::cout << "3. View All Distributed Goods\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Handle distribution to areas

    if (choice == 1) {

        int areaChoice;
        std::cout << "\nChoose an Area to distribute goods to:\n";
        for (size_t i = 0; i < areas.size(); ++i) {

            std::cout << i + 1 << ". " << areas[i].name << "\n";

        }

        std::cout << "Enter area number: ";
        std::cin >> areaChoice;

        if (areaChoice < 1 || areaChoice > areas.size()) {

            std::cout << "Invalid area choice.\n";
            return;

        }

        // Get details about the goods to distribute

        Goods goods;

        std::cout << "\nEnter Goods Type (e.g., Medical Supplies, Clothing, etc.): ";
        std::cin.ignore();  // To ignore leftover newline from previous input
        std::getline(std::cin, goods.type); // Read goods type
        std::cout << "Enter Quantity to distribute: ";
        std::cin >> goods.quantity;

        // Distribute the goods

        goods.target = "Area";
        goods.targetName = areas[areaChoice - 1].name;
        distributedGoods.push_back(goods);  // Add to distributed goods history

        std::cout << "\nSuccessfully distributed " << goods.quantity << " units of " << goods.type
                  << " to " << goods.targetName << ".\n";
    }

    // Handle distribution to shelters

    else if (choice == 2) {

        int shelterChoice;

        std::cout << "\nChoose a Shelter to distribute goods to:\n";

        for (size_t i = 0; i < shelters.size(); ++i) {

            std::cout << i + 1 << ". " << shelters[i].name << "\n";

        }

        std::cout << "Enter shelter number: ";
        std::cin >> shelterChoice;

        if (shelterChoice < 1 || shelterChoice > shelters.size()) {
            std::cout << "Invalid shelter choice.\n";
            return;
        }

        // Get details about the goods to distribute

        Goods goods;

        std::cout << "\nEnter Goods Type (e.g., Medical Supplies, Clothing, etc.): ";
        std::cin.ignore();  // To ignore leftover newline from previous input
        std::getline(std::cin, goods.type); // Read goods type

        std::cout << "Enter Quantity to distribute: ";
        std::cin >> goods.quantity;

        // Distribute the goods

        goods.target = "Shelter";
        goods.targetName = shelters[shelterChoice - 1].name;
        distributedGoods.push_back(goods);  // Add to distributed goods history

        std::cout << "\nSuccessfully distributed " << goods.quantity << " units of " << goods.type
                  << " to " << goods.targetName << ".\n";
    }

    // View all distributed goods

    else if (choice == 3) {

        std::cout << "\nAll Distributed Goods:\n";

        if (distributedGoods.empty()) {

            std::cout << "No goods have been distributed yet.\n";
        } else {
            for (size_t i = 0; i < distributedGoods.size(); ++i) {

                std::cout << i + 1 << ". "
                          << distributedGoods[i].quantity << " units of "
                          << distributedGoods[i].type << " distributed to "
                          << distributedGoods[i].target << " ("
                          << distributedGoods[i].targetName << ").\n";

            }
        }

    } else {

        std::cout << "Invalid choice.\n";

    }
    std::cout << "-------------------------------------------\n";
}

//Add a new rescue team
void addRescueTeam(std::vector<RescueTeam>& rescueTeams) {

    std::string teamName;
    std::cout << "Enter the name of the new rescue team: ";
    std::cin >> teamName;

    // Add the team to the rescueTeams vector
    rescueTeams.push_back({teamName, "Not Assigned", true});
    std::cout << "Rescue team " << teamName << " added successfully.\n";

}

//Assign the rescue teams
void assignRescueTeam(std::vector<RescueTeam>& rescueTeams) {
    std::string teamName, areaName;
    bool teamFound = false;

    // List available teams
    std::cout << "Available rescue teams:\n";
    for (size_t i = 0; i < rescueTeams.size(); ++i) {
        if (rescueTeams[i].isAvailable) {
            std::cout << i + 1 << ". " << rescueTeams[i].teamName << "\n";
        }
    }

    std::cout << "Enter the team number to assign: ";
    int teamChoice;
    std::cin >> teamChoice;

    if (teamChoice < 1 || teamChoice > rescueTeams.size()) {
        std::cout << "Invalid team choice.\n";
        return;
    }

    std::cout << "Enter the area name to assign the team: ";
    std::cin >> areaName;

    // Assign the team and update their status

    rescueTeams[teamChoice - 1].areaAssigned = areaName;
    rescueTeams[teamChoice - 1].isAvailable = false;
    std::cout << rescueTeams[teamChoice - 1].teamName << " assigned to " << areaName << ".\n";
}

//view all Rescue teams
void viewRescueTeams(const std::vector<RescueTeam>& rescueTeams) {
    std::cout << "\nRescue Teams and Their Assignments:\n";
    for (const auto& team : rescueTeams) {
        std::cout << "Team: " << team.teamName << ", Assigned Area: " << team.areaAssigned
                  << ", Availability: " << (team.isAvailable ? "Available" : "Assigned") << "\n";
    }
}

void manageWaterSupply(std::vector<WaterSupply>& waterSupplies, std::vector<Area>& areas, std::vector<Shelter>& shelters) {
    int choice;
    std::cout << "\nWater Supply Management\n";
    std::cout << "1. Add Water Supply\n";
    std::cout << "2. Distribute Water Supply\n";
    std::cout << "3. View Water Supply History\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {

        case 1: {
            // Add new water supply
            WaterSupply newWater;

            std::cout << "Enter water type (e.g., Bottled, Tankers): ";
            std::cin >> newWater.waterType;
            std::cout << "Enter quantity (liters): ";
            std::cin >> newWater.quantity;

            newWater.isDistributed = false;  // Initially, the supply is not distributed
            waterSupplies.push_back(newWater);
            std::cout << "New water supply added.\n";
            break;

        }
        case 2: {
            // Distribute water supply
            std::cout << "Choose a supply to distribute:\n";
            bool anyAvailable = false;

            for (size_t i = 0; i < waterSupplies.size(); ++i) {
                if (!waterSupplies[i].isDistributed) {
                    anyAvailable = true;
                    std::cout << i + 1 << ". " << waterSupplies[i].waterType << " (" << waterSupplies[i].quantity << " liters)\n";
                }
            }

            if (!anyAvailable) {
                std::cout << "No water supplies available for distribution.\n";
                break;
            }

            int supplyChoice;
            std::cout << "Enter the number of the water supply to distribute: ";
            std::cin >> supplyChoice;

            if (supplyChoice < 1 || supplyChoice > waterSupplies.size() || waterSupplies[supplyChoice - 1].isDistributed) {
                std::cout << "Invalid choice or the supply has already been distributed.\n";
                break;
            }

            // Choose area or shelter for distribution
            std::cout << "Where would you like to distribute water?\n";
            std::cout << "1. Areas\n";
            std::cout << "2. Shelters\n";

            int locationChoice;
            std::cin >> locationChoice;

            if (locationChoice == 1) {

                // Distribute to areas
                std::cout << "Choose an area to distribute to:\n";
                for (size_t i = 0; i < areas.size(); ++i) {
                    std::cout << i + 1 << ". " << areas[i].name << " (District: " << areas[i].district << ", Population: " << areas[i].population << ")\n";

                }

                int areaChoice;
                std::cout << "Enter the number of the area to distribute to: ";
                std::cin >> areaChoice;

                if (areaChoice < 1 || areaChoice > areas.size()) {
                    std::cout << "Invalid area choice.\n";
                    break;
                }

                std::cout << "Distributed " << waterSupplies[supplyChoice - 1].quantity << " liters of water to area " << areas[areaChoice - 1].name << ".\n";
                waterSupplies[supplyChoice - 1].isDistributed = true;  // Mark as distributed

            } else if (locationChoice == 2) {

                // Distribute to shelters
                std::cout << "Choose a shelter to distribute to:\n";
                for (size_t i = 0; i < shelters.size(); ++i) {
                    std::cout << i + 1 << ". " << shelters[i].name << " (Capacity: " << shelters[i].capacity << ", Current Occupants: " << shelters[i].currentOccupants << ")\n";

                }

                int shelterChoice;

                std::cout << "Enter the number of the shelter to distribute to: ";
                std::cin >> shelterChoice;

                if (shelterChoice < 1 || shelterChoice > shelters.size()) {
                    std::cout << "Invalid shelter choice.\n";
                    break;
                }

                std::cout << "Distributed " << waterSupplies[supplyChoice - 1].quantity << " liters of water to shelter " << shelters[shelterChoice - 1].name << ".\n";
                waterSupplies[supplyChoice - 1].isDistributed = true;  // Mark as distributed

            } else {
                std::cout << "Invalid choice.\n";
                break;
            }
            break;
        }
        case 3: {
            // View water supply history
            std::cout << "Water Supply History:\n";
            for (const auto& water : waterSupplies) {

                std::cout << "Water Type: " << water.waterType << ", Quantity: " << water.quantity << " liters, Distributed: " << (water.isDistributed ? "Yes" : "No") << "\n";
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
    }
}


void reallocateEvacuees(std::vector<Shelter>& shelters, std::vector<Evacuee>& evacuees) {

    for (auto& shelter : shelters) {

        if (shelter.currentOccupants > shelter.capacity) {

            // If the shelter is over-occupied, try to move evacuees to other shelters
            int evacueesToMove = shelter.currentOccupants - shelter.capacity;
            std::cout << "Shelter " << shelter.name << " is over-occupied by " << evacueesToMove << " evacuees.\n";

            for (auto& otherShelter : shelters) {

                if (otherShelter.capacity > otherShelter.currentOccupants) {

                    // If another shelter has space, move evacuees there
                    int spaceAvailable = otherShelter.capacity - otherShelter.currentOccupants;
                    int evacueesMoved = std::min(evacueesToMove, spaceAvailable);

                    // Move evacuees
                    otherShelter.currentOccupants += evacueesMoved;
                    shelter.currentOccupants -= evacueesMoved;

                    std::cout << "Moved " << evacueesMoved << " evacuees to " << otherShelter.name << ".\n";
                    evacueesToMove -= evacueesMoved;

                    // If all evacuees have been moved, break out of the loop
                    if (evacueesToMove == 0) {
                        break;
                    }
                }
            }

            // If there are still evacuees that couldn't be moved
            if (evacueesToMove > 0) {
                std::cout << "Could not reallocate all evacuees from " << shelter.name << ". Remaining evacuees: " << evacueesToMove << "\n";
            }
        }
    }

    // Final status update after the reallocation process
    std::cout << "Reallocation completed. Final shelter statuses:\n";
    for (const auto& shelter : shelters) {
        std::cout << "Shelter: " << shelter.name << " - Current Occupants: " << shelter.currentOccupants << "/" << shelter.capacity << "\n";
    }
}


void collectPostEvacuationFeedback(std::vector<Evacuee>& evacuees) {
    // A map to store feedback
    std::unordered_map<std::string, std::unordered_map<std::string, int>> feedback;

    char giveFeedback = 'Y';

    while (giveFeedback == 'Y' || giveFeedback == 'y') {

        // Display evacuees and let the user select one
        std::cout << "\nSelect an evacuee to provide feedback:\n";
        for (size_t i = 0; i < evacuees.size(); ++i) {
            std::cout << i + 1 << ". " << evacuees[i].name << " (" << evacuees[i].city << ")\n";
        }

        int evacueeChoice;
        std::cout << "Enter the number corresponding to the evacuee: ";
        std::cin >> evacueeChoice;

        if (evacueeChoice < 1 || evacueeChoice > evacuees.size()) {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        Evacuee& selectedEvacuee = evacuees[evacueeChoice - 1];

        // Collect feedback for the selected evacuee

        std::cout << "\nCollecting feedback from " << selectedEvacuee.name << " (" << selectedEvacuee.city << ")\n";
        std::cout << "Please rate the following from 1 (poor) to 5 (excellent):\n";

        int shelterRating, transportRating, foodRating, waterRating, overallRating;

        std::cout << "Rate the shelter conditions: ";
        std::cin >> shelterRating;

        std::cout << "Rate the transportation service: ";
        std::cin >> transportRating;

        std::cout << "Rate the food supply: ";
        std::cin >> foodRating;

        std::cout << "Rate the water supply: ";
        std::cin >> waterRating;

        std::cout << "Rate the overall evacuation experience: ";
        std::cin >> overallRating;

        // Store the feedback for this evacuee

        feedback[selectedEvacuee.name] = {
            {"Shelter", shelterRating},
            {"Transport", transportRating},
            {"Food", foodRating},
            {"Water", waterRating},
            {"Overall", overallRating}
        };

        std::cout << "\nThank you for your feedback, " << selectedEvacuee.name << "!\n";

        // Prompt if another feedback is needed

        std::cout << "\nDo you want to provide feedback for another evacuee? (Y/N): ";
        std::cin >> giveFeedback;
    }

    // Display feedback summary
        std::cout << "\nPost-Evacuation Feedback Summary:\n";

    for (const auto& evacueeFeedback : feedback) {

        std::cout << "Evacuee: " << evacueeFeedback.first << "\n";
        for (const auto& aspect : evacueeFeedback.second) {
        std::cout << "  " << aspect.first << ": " << aspect.second << "\n";

        }
        std::cout << "\n";
    }
}

// Function: findEvacueeByName
// Purpose:
// This function searches for evacuees by name using a string matching technique.
// It performs a case-insensitive search to ensure flexibility in matching names containing the query substring.

// Parameters:
// - `evacuees`: A vector of `Evacuee` objects, where each evacuee has attributes such as name, age, shelter, and city.
// - `query`: A string that represents the name (or part of the name) being searched.

// Functionality:
// - The function iterates through all evacuees and checks if the query string is a substring of the evacuee's name.
// - Both the evacuee's name and the query are converted to lowercase for case-insensitive matching.
// - If a match is found, the evacuee's details are printed, including their name, age, shelter, and city.
// - If no evacuee matches the query, a message indicating "No evacuee found" is displayed.

// Steps in the Implementation:
// 1. Initialize a flag `found` to track whether any evacuees match the query.
// 2. Loop through each evacuee in the vector:
//    a. Convert the evacuee's name and query string to lowercase to perform case-insensitive matching.
//    b. Use `std::string::find` to check if the query string is a substring of the evacuee's name.
//    c. If a match is found, print the evacuee's details and set `found` to true.
// 3. After the loop, if no matches were found, output a message indicating no results.

// Output:
// - Prints the details of evacuees whose names contain the query string.
// - If no match is found, prints "No evacuee found with the given name."

// Complexity:
// - Time Complexity: O(N * M), where N is the number of evacuees and M is the average length of names.
// - Space Complexity: O(1), aside from minor temporary string storage for case conversion.


// Function to find evacuee by name using string matching

void findEvacueeByName(const std::vector<Evacuee>& evacuees, const std::string& query) {

    bool found = false;
    std::cout << "\nSearching for evacuee with name containing \"" << query << "\":\n";

    for (const auto& evacuee : evacuees) {

        // Convert both strings to lowercase for case-insensitive matching
        std::string evacueeName = evacuee.name;
        std::string searchQuery = query;
        std::transform(evacueeName.begin(), evacueeName.end(), evacueeName.begin(), ::tolower);
        std::transform(searchQuery.begin(), searchQuery.end(), searchQuery.begin(), ::tolower);

        if (evacueeName.find(searchQuery) != std::string::npos) {

            found = true;
            std::cout << "Name: " << evacuee.name << ", Age: " << evacuee.age
                      << ", Shelter: " << evacuee.shelter << ", City: " << evacuee.city << "\n";

        }
    }

    if (!found) {
        std::cout << "No evacuee found with the given name.\n";
    }
}

// Function to find the Minimum Evacuation Network for all cities

// Prim's Algorithm:
// Prim's algorithm is a greedy algorithm used to find the Minimum Spanning Tree (MST) of a connected, undirected graph.
// It starts from an arbitrary node and grows the MST by selecting the smallest edge connecting a visited node to an unvisited node.

// Why use Prim's Algorithm here:
// In this scenario, we are constructing a Minimum Evacuation Network (MST) for cities.
// The MST ensures that all cities are connected with the minimum total distance, which is critical for efficient evacuation.
// Prim's algorithm is ideal because it ensures the minimal connection cost while guaranteeing connectivity between cities.

// Efficiency of Prim's Algorithm:
// - Time Complexity: O(E log V), where E is the number of edges, and V is the number of vertices (cities).
//   The efficiency is achieved using a priority queue (min-heap) to select the smallest edge quickly.
// - Space Complexity: O(E + V) due to the storage of the graph, priority queue, and visited set.
// This makes it efficient for moderately sized graphs, such as city networks in evacuation planning.

// Algorithm Description:
// 1. Initialize a priority queue to store edges sorted by weight (distance in this case).
// 2. Start from an arbitrary city, marking it as visited and pushing all its edges into the priority queue.
// 3. Repeatedly extract the smallest edge from the queue. If it connects to an unvisited city:
//    a. Mark the city as visited.
//    b. Add the edge to the MST.
//    c. Add all edges from this newly visited city to the queue.
// 4. Continue until all cities are visited or the queue is empty.

// Role in This Code:
// - `visited`: Tracks cities that have been added to the MST to avoid cycles.
// - `pq`: A priority queue used to efficiently fetch the smallest edge at each step.
// - `mstEdges`: Stores the edges of the MST for output purposes.
// - `totalDistance`: Accumulates the total distance of the MST, ensuring the minimal cost of connection.
// The algorithm ensures that the network formed connects all cities with the least total distance,
// which is crucial for minimizing evacuation time and infrastructure cost.

void findMinimumEvacuationNetwork(const std::vector<Area>& areas) {

    // Create a graph (adjacency list) for all cities
    std::unordered_map<std::string, std::unordered_map<std::string, float>> graph;

    // Initialize the graph with random distances between cities
    for (size_t i = 0; i < areas.size(); ++i) {

        for (size_t j = i + 1; j < areas.size(); ++j) {

            float randomDistance = (std::rand() % 50) + 1; // Random distance between 1 and 50 km
            graph[areas[i].name][areas[j].name] = randomDistance;
            graph[areas[j].name][areas[i].name] = randomDistance;

        }
    }

    // Prim's algorithm to find the MST
    std::unordered_map<std::string, bool> visited;

    std::priority_queue<std::pair<float, std::pair<std::string, std::string>>,
                        std::vector<std::pair<float, std::pair<std::string, std::string>>>,
                        std::greater<>> pq;


    std::string startCity = areas[0].name;

    // Add all edges from the starting city to the priority queue
    for (const auto& neighbor : graph[startCity]) {

        pq.push({neighbor.second, {startCity, neighbor.first}});
    }

    visited[startCity] = true;

    std::vector<std::pair<std::string, std::string>> mstEdges; // Store edges in the MST
    float totalDistance = 0;

    while (!pq.empty()) {

        auto [distance, edge] = pq.top();
        pq.pop();
        const auto& [from, to] = edge;
        if (visited[to]) continue;

        visited[to] = true;
        mstEdges.push_back({from, to});
        totalDistance += distance;

        // Add all neighboring edges of the current city
        for (const auto& neighbor : graph[to]) {

            if (!visited[neighbor.first]) {
                pq.push({neighbor.second, {to, neighbor.first}});

            }
        }
    }

    // Output the results
    std::cout << "\nMinimum Evacuation Network for Cities:\n";

    for (const auto& edge : mstEdges) {
        std::cout << edge.first << " <--> " << edge.second << "\n";
    }
        std::cout << "Total Distance: " << totalDistance << " km\n";
}


void handleMedicalEmergency(std::vector<RescueTeam>& rescueTeams,
                             std::vector<Vehicle>& vehicles,
                             const std::vector<Area>& areas) {

    std::string areaName;
    bool areaFound = false;

    // Ask for the area in need of medical emergency support
    std::cout << "Enter the area needing medical emergency support: ";
    std::cin >> areaName;

    // Check if the area exists
    for (const auto& area : areas) {

        if (area.name == areaName) {
            areaFound = true;
            break;

        }
    }

    if (!areaFound) {
        std::cout << "Area not found.\n";
        return;
    }

    // Assign a rescue team to the area (this will directly assign to the selected area)

    for (auto& team : rescueTeams) {

        if (team.isAvailable) {

            team.areaAssigned = areaName;  // Directly assign to the area
            team.isAvailable = false;      // Mark team as unavailable
            std::cout << team.teamName << " assigned to " << areaName << ".\n";
            break; // Exit once the first available team is assigned

        }
    }

    // Find an available vehicle for the medical emergency

    Vehicle* assignedVehicle = nullptr;
    for (auto& vehicle : vehicles) {

        if (vehicle.currentOccupants < vehicle.capacity) {

            assignedVehicle = &vehicle;
            vehicle.currentOccupants++; // Increase vehicle's current occupants
            std::cout << "Vehicle " << vehicle.name << " assigned to " << areaName << ".\n";
            break;

        }
    }

    if (!assignedVehicle) {

        std::cout << "No available vehicle for the medical emergency in " << areaName << ".\n";
        return;

    }

    std::cout << "Medical emergency handled in " << areaName << " with vehicle " << assignedVehicle->name << ".\n";
}



void Evacuation()
{
    std::cout << "\n=== Evacuation Process Started ===\n";
    std::vector<Area> areas = {

        {1, "Dharavi", "Mumbai City", 700000, 0.8},
        {2, "Kurla", "Mumbai Suburban", 540000, 0.9},
        {3, "Chembur", "Mumbai Suburban", 620000, 0.7},
        {4, "Andheri", "Mumbai Suburban", 1100000, 0.6},
        {5, "Lower Parel", "Mumbai City", 150000, 0.85},
        {6, "Bandra East", "Mumbai Suburban", 320000, 0.75},
        {7, "Sion", "Mumbai City", 170000, 0.8},
        {8, "Goregaon", "Mumbai Suburban", 670000, 0.65},
        {9, "Malad", "Mumbai Suburban", 760000, 0.7},
        {10, "Jogeshwari", "Mumbai Suburban", 600000, 0.6},
        {11, "Powai", "Mumbai Suburban", 400000, 0.7},
        {12, "Vikhroli", "Mumbai Suburban", 250000, 0.6},
        {13, "Mulund", "Mumbai Suburban", 450000, 0.65},
        {14, "Bhandup", "Mumbai Suburban", 300000, 0.7},
        {15, "Borivali", "Mumbai Suburban", 1200000, 0.6},
        {16, "Kandivali", "Mumbai Suburban", 1100000, 0.65},
        {17, "Santa Cruz", "Mumbai Suburban", 600000, 0.7},
        {18, "Vile Parle", "Mumbai Suburban", 450000, 0.65},
        {19, "Charni Road", "Mumbai City", 120000, 0.8},
        {20, "Grant Road", "Mumbai City", 250000, 0.75},
        {21, "Marine Lines", "Mumbai City", 200000, 0.85},
        {22, "Chowpatty", "Mumbai City", 180000, 0.9},
        {23, "Colaba", "Mumbai City", 150000, 0.8},
        {24, "Fort", "Mumbai City", 120000, 0.85},
        {25, "Churchgate", "Mumbai City", 90000, 0.8},
        {26, "Nariman Point", "Mumbai City", 70000, 0.85},
        {27, "Mazgaon", "Mumbai City", 250000, 0.75},
        {28, "Byculla", "Mumbai City", 300000, 0.8},
        {29, "Parel", "Mumbai City", 350000, 0.8},
        {30, "Worli", "Mumbai City", 500000, 0.7},
        {31, "Haji Ali", "Mumbai City", 100000, 0.85},
        {32, "Mahalaxmi", "Mumbai City", 220000, 0.8},
        {33, "Tardeo", "Mumbai City", 180000, 0.75},
        {34, "Elphinstone", "Mumbai City", 120000, 0.7},
        {35, "Antop Hill", "Mumbai City", 170000, 0.8},
        {36, "Dadar East", "Mumbai City", 240000, 0.8},
        {37, "Dadar West", "Mumbai City", 220000, 0.75},
        {38, "Wadala", "Mumbai City", 300000, 0.7},
        {39, "Matunga", "Mumbai City", 280000, 0.75},
        {40, "Sewri", "Mumbai City", 200000, 0.8},
        {41, "Kalbadevi", "Mumbai City", 220000, 0.85},
        {42, "Girgaon", "Mumbai City", 210000, 0.8},
        {43, "Cuffe Parade", "Mumbai City", 90000, 0.85},
        {44, "Chinchpokli", "Mumbai City", 150000, 0.75},
        {45, "Reay Road", "Mumbai City", 120000, 0.7},
        {46, "Mumbai Central", "Mumbai City", 350000, 0.8},
        {47, "Agripada", "Mumbai City", 200000, 0.75},
        {48, "Malabar Hill", "Mumbai City", 250000, 0.7},
        {49, "Walkeshwar", "Mumbai City", 120000, 0.85},
        {50, "Breach Candy", "Mumbai City", 150000, 0.8}

        };

    std::vector<Shelter> shelters = {

    {"Shelter 1", 100, 0, {{"Dharavi", 5}, {"Kurla", 10}}},
    {"Shelter 2", 80, 0, {{"Chembur", 8}, {"Andheri", 15}}},
    {"Shelter 3", 120, 0, {{"Lower Parel", 3}, {"Bandra East", 12}}},
    {"Shelter 4", 90, 0, {{"Sion", 6}, {"Goregaon", 14}}},
    {"Shelter 5", 150, 0, {{"Malad", 9}, {"Jogeshwari", 11}}},

};


    std::vector<Evacuee> evacuees = {

    // Evacuees for Shelter 1

    {"Aisha Khan", 10, "Shelter 1", "Dharavi"},
    {"Rahul Mehta", 12, "Shelter 1", "Dharavi"},
    {"Priya Sharma", 9, "Shelter 1", "Dharavi"},
    {"Arjun Patil", 11, "Shelter 1", "Dharavi"},
    {"Sneha Desai", 8, "Shelter 1", "Dharavi"},
    {"Rohan Joshi", 13, "Shelter 1", "Dharavi"},
    {"Kavya Iyer", 7, "Shelter 1", "Dharavi"},
    {"Sameer Gupta", 10, "Shelter 1", "Dharavi"},
    {"Neha Singh", 12, "Shelter 1", "Dharavi"},
    {"Vikram Rao", 11, "Shelter 1", "Dharavi"},

    // Evacuees for Shelter 2

    {"Ananya Verma", 9, "Shelter 2", "Kurla"},
    {"Karan Nair", 10, "Shelter 2", "Kurla"},
    {"Tanvi Bhatia", 8, "Shelter 2", "Kurla"},
    {"Aditya Chavan", 12, "Shelter 2", "Kurla"},
    {"Meera Joshi", 11, "Shelter 2", "Kurla"},
    {"Riya Kapoor", 9, "Shelter 2", "Kurla"},
    {"Ishaan Reddy", 12, "Shelter 2", "Kurla"},
    {"Pooja Malhotra", 10, "Shelter 2", "Kurla"},
    {"Nikhil Agarwal", 11, "Shelter 2", "Kurla"},
    {"Simran Khanna", 10, "Shelter 2", "Kurla"},

    // Evacuees for Shelter 3

    {"Ritesh Yadav", 12, "Shelter 3", "Chembur"},
    {"Aanya Mehta", 9, "Shelter 3", "Chembur"},
    {"Kunal Joshi", 11, "Shelter 3", "Chembur"},
    {"Tara Singh", 8, "Shelter 3", "Chembur"},
    {"Raghav Bansal", 10, "Shelter 3", "Chembur"},
    {"Neelam Rani", 12, "Shelter 3", "Chembur"},
    {"Arnav Kapoor", 11, "Shelter 3", "Chembur"},
    {"Sneha Reddy", 9, "Shelter 3", "Chembur"},
    {"Karan Yadav", 10, "Shelter 3", "Chembur"},
    {"Pooja Sharma", 10, "Shelter 3", "Chembur"},

    // Evacuees for Shelter 4

    {"Ritesh Singh", 12, "Shelter 4", "Andheri"},
    {"Tara Bansal", 8, "Shelter 4", "Andheri"},
    {"Neha Singh", 10, "Shelter 4", "Andheri"},
    {"Aarav Sethi", 10, "Shelter 4", "Andheri"},
    {"Kavya Iyer", 8, "Shelter 4", "Andheri"},
    {"Rohan Desai", 11, "Shelter 4", "Andheri"},
    {"Anika Gupta", 10, "Shelter 4", "Andheri"},
    {"Ishaan Kapoor", 8, "Shelter 4", "Andheri"},
    {"Raghav Agarwal", 12, "Shelter 4", "Andheri"},
    {"Simran Joshi", 10, "Shelter 4", "Andheri"},

    // Evacuees for Shelter 5

    {"Aanya Rani", 9, "Shelter 5", "Lower Parel"},
    {"Kunal Reddy", 11, "Shelter 5", "Lower Parel"},
    {"Ishaan Reddy", 12, "Shelter 5", "Lower Parel"},
    {"Neelam Rani", 12, "Shelter 5", "Lower Parel"},
    {"Arnav Kapoor", 11, "Shelter 5", "Lower Parel"},
    {"Sneha Reddy", 9, "Shelter 5", "Lower Parel"},
    {"Karan Yadav", 10, "Shelter 5", "Lower Parel"},
    {"Pooja Sharma", 10, "Shelter 5", "Lower Parel"},
    {"Ritesh Singh", 12, "Shelter 5", "Lower Parel"},
    {"Tara Bansal", 8, "Shelter 5", "Lower Parel"}

};


    std::vector<Vehicle> vehicles = {

    {"Toyota Land Cruiser", 5, 0, {"Flood Rescue Route 1"}, 0.0},
    {"Jeep Wrangler", 4, 0, {"Flood Rescue Route 2"}, 0.0},
    {"Ford Ranger", 5, 0, {"Flood Rescue Route 3"}, 0.0},
    {"Land Rover Defender", 5, 0, {"Flood Rescue Route 4"}, 0.0},
    {"Range Rover", 5, 0, {"Flood Rescue Route 5"}, 0.0},
    {"Ford EcoSport", 5, 0, {"Flood Rescue Route 6"}, 0.0},
    {"Subaru Outback", 5, 0, {"Flood Rescue Route 7"}, 0.0},
    {"Chevrolet Tahoe", 7, 0, {"Flood Rescue Route 8"}, 0.0},
    {"Nissan Patrol", 5, 0, {"Flood Rescue Route 9"}, 0.0},
    {"Mitsubishi Pajero", 5, 0, {"Flood Rescue Route 10"}, 0.0}

};

    std::vector<FoodSupply> foodSupplies = {
    {
        "Canned Goods",
        500.0,
        {{"Dharavi", 100.0}, {"Kurla", 150.0}, {"Chembur", 250.0}},
        {{"Shelter 1", 200.0}, {"Shelter 2", 300.0}}
    },
    {
        "Rice",
        1000.0,
        {{"Andheri", 200.0}, {"Lower Parel", 300.0}, {"Bandra East", 500.0}},
        {{"Shelter 3", 400.0}, {"Shelter 4", 600.0}}
    },
    {
        "Pulses",
        300.0,
        {{"Sion", 50.0}, {"Goregaon", 100.0}, {"Malad", 150.0}},
        {{"Shelter 5", 100.0}, {"Shelter 6", 200.0}}
    },
    {
        "Vegetable Oil",
        200.0,
        {{"Jogeshwari", 50.0}, {"Powai", 100.0}, {"Vikhroli", 50.0}},
        {{"Shelter 7", 80.0}, {"Shelter 8", 120.0}}
    },
    {
        "Sugar",
        150.0,
        {{"Mulund", 30.0}, {"Bhandup", 70.0}, {"Borivali", 50.0}},
        {{"Shelter 9", 60.0}, {"Shelter 10", 90.0}}
    },
    {
        "Flour",
        400.0,
        {{"Kandivali", 100.0}, {"Santa Cruz", 150.0}, {"Vile Parle", 150.0}},
        {{"Shelter 11", 200.0}, {"Shelter 12", 200.0}}
    },
    {
        "Canned Vegetables",
        250.0,
        {{"Charni Road", 50.0}, {"Grant Road", 100.0}, {"Marine Lines", 100.0}},
        {{"Shelter 13", 100.0}, {"Shelter 14", 150.0}}
    },
    {
        "Instant Noodles",
        300.0,
        {{"Chowpatty", 50.0}, {"Colaba", 100.0}, {"Fort", 150.0}},
        {{"Shelter 15", 120.0}, {"Shelter 16", 180.0}}
    },

    {
        "Snacks",
        200.0,
        {{"Dadar East", 50.0}, {"Dadar West", 50.0}, {"Wadala", 100.0}},
        {{"Shelter 19", 80.0}, {"Shelter 20", 120.0}}

    }

};


std::vector<Goods> goodsHistory = {

    {"Medical Masks", 1000, "Shelter", "Shelter 1"},
    {"Hand Sanitizer", 200, "Shelter", "Shelter 1"},
    {"First Aid Kits", 50, "Shelter", "Shelter 1"},
    {"Thermometers", 30, "Shelter", "Shelter 1"},
    {"Gloves", 500, "Shelter", "Shelter 1"},
    {"Blankets", 150, "Shelter", "Shelter 1"},
    {"Tents", 20, "Shelter", "Shelter 2"},
    {"Sleeping Bags", 100, "Shelter", "Shelter 2"},
    {"Flashlights", 50, "Area", "Dharavi"},
    {"Batteries", 200, "Area", "Dharavi"},
    {"Cooking Utensils", 75, "Shelter", "Shelter 3"},
    {"Water Purification Tablets", 1000, "Area", "Kurla"},
    {"Soap", 200, "Shelter", "Shelter 4"},
    {"Toothpaste", 150, "Shelter", "Shelter 4"},
    {"Shampoo", 100, "Shelter", "Shelter 4"},
    {"Conditioner", 50, "Shelter", "Shelter 4"},
    {"Diapers", 300, "Shelter", "Shelter 5"},
    {"Feminine Hygiene Products", 200, "Shelter", "Shelter 5"},
    {"Portable Generators", 10, "Area", "Bandra"},
    {"Rope", 100, "Area", "Bandra"},
    {"Tarps", 50, "Shelter", "Shelter 6"},
    {"Portable Toilets", 15, "Shelter", "Shelter 7"},
    {"Emergency Blankets", 100, "Shelter", "Shelter 8"},
    {"Life Jackets", 50, "Area", "Goregaon"},
    {"Fire Extinguishers", 20, "Shelter", "Shelter 9"},
    {"Signal Flares", 100, "Area", "Malad"},
    {"Portable Lights", 30, "Area", "Malad"},
    {"Multi-tools", 50, "Area", "Kurla"},
    {"Fishing Gear", 20, "Area", "Dharavi"},
    {"Emergency Contact Cards", 500, "Shelter", "Shelter 10"},
    {"Maps of the Area", 100, "Area", "Bandra"},
    {"Communication Devices", 20, "Shelter", "Shelter 11"},
    {"Portable Water Filters", 100, "Shelter", "Shelter 12"},
    {"Emergency Medical Supplies", 50, "Shelter", "Shelter 13"},
    {"Portable First Aid Kits", 30, "Shelter", "Shelter 14"},
    {"Emergency Hygiene Kits", 100, "Shelter", "Shelter 15"},
    {"Portable Showers", 10, "Shelter", "Shelter 16"},
    {"Water Testing Kits", 30, "Area", "Area 1"},
    {"Portable Stoves", 20, "Shelter", "Shelter 17"},
    {"Cooking Fuel", 100, "Area", "Area 2"},
    {"Emergency Radio", 15, "Shelter", "Shelter 18"},
    {"Survival Kits", 50, "Shelter", "Shelter 19"},
    {"Personal Protective Equipment", 200, "Shelter", "Shelter 20"},
    {"Emergency Lighting", 30, "Shelter", "Shelter 21"},
    {"Rescue Equipment", 10, "Shelter", "Shelter 22"},
    {"Safety Whistles", 100, "Shelter", "Shelter 23"},
    {"Emergency Blankets", 100, "Shelter", "Shelter 24"},
    {"Hand Crank Chargers", 20, " Shelter", "Shelter 25"}

};

std::vector<RescueTeam> rescueTeams = {

    {"Team Alpha", "Dharavi", true},
    {"Team Bravo", "Kurla", false},
    {"Team Charlie", "Goregaon", true},
    {"Team Delta", "Malad", true},
    {"Team Echo", "Bandra", false},
    {"Team Foxtrot", "Chembur", true},
    {"Team Golf", "Andheri", true},
    {"Team Juliet", "Wadala", true},
    {"Team Kilo", "Borivali", false},
    {"Team Lima", "Thane", true},
    {"Team Mike", "Kandivali", true},
    {"Team November", "Dadar", false},
    {"Team Oscar", "Parel", true},
    {"Team Papa", "Versova", true},
    {"Team Phoenix", "Dharavi", true},
    {"Team Thunder", "Kurla", false},
    {"Team Guardian", "Goregaon", true},
    {"Team Resilience", "Malad", true},
    {"Team Unity", "Bandra", false},
    {"Team Hope", "Chembur", true},
    {"Team Valor", "Andheri", true},
    {"Team Shield", "Lower Parel", false},
    {"Team Horizon", "Sion", true},
    {"Team Titan", "Wadala", true},
    {"Team Falcon", "Borivali", false},
    {"Team Spirit", "Thane", true},
    {"Team Ranger", "Kandivali", true},
    {"Team Liberty", "Dadar", false},
    {"Team Valiant", "Parel", true},
    {"Team Rescue", "Versova", true},
    {"Team Endeavor", "Juhu", false},
    {"Team Sentinel", "Malad West", true},
    {"Team Guardian Angels", "Bhandup", true},
    {"Team Phoenix Rising", "Vikhroli", false},
    {"Team Braveheart", "Powai", true},

};

//water suppliments

    std::vector<WaterSupply> waterSupplies = {

    {"Bottled", 5000, false},
    {"Tankers", 15000, true},
    {"Bottled", 3000, true},
    {"Tankers", 20000, false},
    {"Bottled", 10000, true},
    {"Tankers", 12000, false},
    {"Bottled", 8000, true},
    {"Tankers", 18000, true},
    {"Bottled", 6000, false},
    {"Tankers", 25000, false},
    {"Bottled", 4000, true},
    {"Tankers", 22000, true},
    {"Bottled", 7000, false},
    {"Tankers", 16000, true},
    {"Bottled", 9000, true},
    {"Tankers", 14000, false},
    {"Bottled", 11000, true},
    {"Tankers", 13000, false},
    {"Bottled", 5000, false},
    {"Tankers", 17000, true}

};

    // Run flood management system

    assessRisk(areas);

    int choice;
    while (true) {

        std::cout << "\nMain Menu:\n";
        std::cout << "01. View Flood Risk Information\n";
        std::cout << "02. View Shelter Information\n";
        std::cout << "03. View Evacuation Routes\n";
        std::cout << "04. Manage Evacuees\n";
        std::cout << "05. Manage Transportation\n";
        std::cout << "06. Manage Food Supplies\n";
        std::cout << "07. Manage Goods Supplies\n";
        std::cout << "08. Manage Rescue Teams\n";
        std::cout << "09. Manage Water Supplies\n";
        std::cout << "10. Handle Medical Emergency\n";
        std::cout << "11. Search Evacuee\n";
        std::cout << "12. Find Minimum Evacuation Network\n";
        std::cout << "13. Collect Post-Evacuation Feedback\n";
        std::cout << "14. Reallocate evacuees \n";
        std::cout << "15. Back to Main menu\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {

            case 1:
                displayRiskInfo(areas);
                break;

            case 2:
                displayShelterInfo(shelters,evacuees);
                break;

            case 3:
                displayEvacuationRoutes(areas, shelters);
                break;

            case 4:
                registerEvacuees(shelters, evacuees);
                break;

            case 5:
                manageTransportation(vehicles, areas, shelters);
                break;

            case 6:
                manageFoodSupply(foodSupplies, areas, shelters);
                break;

            case 7:
                distributeGoodsSupply(areas, shelters, goodsHistory);
                break;

            case 8: {
                int rescueChoice;

                std::cout << "\nRescue Team Management:\n";
                std::cout << "1. Add Rescue Team\n";
                std::cout << "2. Assign Rescue Team\n";
                std::cout << "3. View Rescue Teams\n";

                std::cout << "Enter your choice: ";
                std::cin >> rescueChoice;

                if (rescueChoice == 1) {
                    addRescueTeam(rescueTeams);

                } else if (rescueChoice == 2) {
                    assignRescueTeam(rescueTeams);

                } else if (rescueChoice == 3) {
                    viewRescueTeams(rescueTeams);

                } else {

                    std::cout << "Invalid choice.\n";
                }

                break;
            }

            case 9:
                manageWaterSupply(waterSupplies, areas, shelters);
                break;

            case 10:
                handleMedicalEmergency(rescueTeams, vehicles, areas);
                break;

            case 11:
            {
                std::string searchQuery;
                std::cout << "Enter the name to search for evacuee: ";
                std::cin >> searchQuery;
                findEvacueeByName(evacuees, searchQuery);
                break;
            }


            case 12:

                findMinimumEvacuationNetwork(areas);
                break;

            case 13:

                collectPostEvacuationFeedback(evacuees);  // Collect feedback
                break;

            case 14:

                reallocateEvacuees(shelters,evacuees);
                break;

            case 15:

                std::cout << "Exiting program.\n";
                return ;

            default:
                std::cout << "Invalid choice.\n";

        }

    }

}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    vector<string> cities = {
        "Dharavi", "Kurla", "Chembur", "Andheri",
        "Lower Parel","Bandra East", "Sion", "Mumbai City",
        "Goregaon", "Malad", "Jogeshwari", "Powai",
        "Vikhroli", "Mulund", "Bhandup", "Borivali",
        "Kandivali", "Santa Cruz", "Vile Parle",
        "Charni Road", "Grant Road", "Marine Lines",
        "Chowpatty", "Colaba", "Fort", "Churchgate",
        "Nariman Point", "Mazgaon", "Byculla", "Parel",
        "Worli", "Haji Ali", "Mahalaxmi", "Tardeo",
        "Elphinstone", "Antop Hill", "Dadar East",
        "Dadar West", "Wadala", "Matunga", "Sewri",
        "Kalbadevi", "Girgaon", "Cuffe Parade",
        "Chinchpokli", "Reay Road", "Mumbai Central",
        "Agripada", "Malabar Hill", "Walkeshwar"
    };


    // Map to store city data: {city_name, {area, population}}
    map<string, pair<double, int>> cityData = {
        {"Dharavi", {2.1, 700000}},
        {"Kurla", {11.7, 800000}},
        {"Chembur", {16.0, 700000}},
        {"Andheri", {20.0, 1500000}},
        {"Lower Parel", {8.5, 500000}},
        {"Bandra East", {12.5, 1200000}},
        {"Sion", {10.2, 600000}},
        {"Mumbai City", {603.4, 20400000}},
        {"Goregaon", {11.0, 900000}},
        {"Malad", {13.0, 1100000}},
        {"Jogeshwari", {14.0, 800000}},
        {"Powai", {6.0, 400000}},
        {"Vikhroli", {8.0, 300000}},
        {"Mulund", {15.0, 700000}},
        {"Bhandup", {12.0, 600000}},
        {"Borivali", {18.0, 1200000}},
        {"Kandivali", {16.5, 1100000}},
        {"Santa Cruz", {9.0, 800000}},
        {"Vile Parle", {10.0, 700000}},
        {"Charni Road", {5.0, 200000}},
        {"Grant Road", {4.5, 300000}},
        {"Marine Lines", {3.0, 150000}},
        {"Chowpatty", {2.5, 100000}},
        {"Colaba", {7.0, 300000}},
        {"Fort", {6.5, 250000}},
        {"Churchgate", {5.5, 200000}},
        {"Nariman Point", {3.5, 150000}},
        {"Mazgaon", {6.0, 400000}},
        {"Byculla", {7.5, 500000}},
        {"Parel", {8.0, 600000}},
        {"Worli", {9.0, 700000}},
        {"Haji Ali", {4.0, 200000}},
        {"Mahalaxmi", {3.5, 150000}},
        {"Tardeo", {4.5, 250000}},
        {"Elphinstone", {5.0, 300000}},
        {"Antop Hill", {6.0, 400000}},
        {"Dadar East", {7.0, 500000}},
        {"Dadar West", {7.5, 600000}},
        {"Wadala", {8.0, 700000}},
        {"Matunga", {8.5, 800000}},
        {"Sewri", {6.0, 400000}},
        {"Kalbadevi", {5.5, 300000}},
        {"Girgaon", {5.0, 250000}},
        {"Cuffe Parade", {4.0, 200000}},
        {"Chinchpokli", {3.5, 150000}},
        {"Reay Road", {4.0, 200000}},
        {"Mumbai Central", {7.0, 500000}},
        {"Agripada", {6.5, 400000}},
        {"Malabar Hill", {9.0, 700000}},
        {"Walkeshwar", {8.0, 600000}}
    };


    // Retrieve data for each factor (simulated data)
    auto topography = getTopographyData(cities);
    auto rainfall = getRainfallData(cities);
    auto drainage = getDrainageCapacity(cities);
    auto landUse = getLandUseData(cities);
    auto floodHistory = getFloodHistoryData(cities);
    auto proximity = getProximityToWaterBodies(cities);




    int mainChoice;
    do {
        cout << "\nMain Menu:\n";
        cout << "1. View Cities\n";
        cout << "2. Show city information\n";
        cout << "3. Search for a city\n";
        cout << "4. Send Evacuation Alert and View the Evacuation Process\n";
        cout << "5. Display cities that require high alert\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                int cityChoice;
                displayCities(cities);
                cout << "\nEnter the number corresponding to your city choice (or 0 to go back): ";
                cin >> cityChoice;

                if (cityChoice == 0) {
                    cout << "Returning to Main Menu.\n";
                } else if (cityChoice < 1 || cityChoice > cities.size()) {
                    cout << "Invalid choice! Please try again.\n";
                } else {
                    string selectedCity = cities[cityChoice - 1];
                    int subChoice;
                    do {
                        cout << "\nYou selected: " << selectedCity;
                        cout << "\nWhat would you like to do?\n";
                        cout << "1. View Historical Data\n";
                        cout << "2. Analyze Flood Data\n";
                        cout << "3. Estimate Economic Loss\n";
                        cout << "4. Calculate Flood Probability\n";
                        cout << "5. Calculate Preparedness Index\n";
                        cout << "6. Rate Community Awareness\n";
                        cout << "7. Simulate Environmental Impact\n";
                        cout << "8. View Flood Timeline\n";
                        cout << "9. Sorted list of cities based on flood probability\n";
                        cout << "10. Back to City Menu\n";
                        cout << "Enter your choice: ";
                        cin >> subChoice;

                        switch (subChoice) {
                            case 1: {
                                int historicalChoice;
                                do {
                                    cout << "\nHistorical Data for " << selectedCity << ":\n";
                                    cout << "1. View Topographical Data\n";
                                    cout << "2. View Rainfall Data\n";
                                    cout << "3. View Drainage Capacity\n";
                                    cout << "4. View Land Use Data\n";
                                    cout << "5. View Flood History\n";
                                    cout << "6. View Proximity to Water Bodies\n";
                                    cout << "7. Back to City Menu\n";
                                    cout << "Enter your choice: ";
                                    cin >> historicalChoice;

                                    switch (historicalChoice) {
                                        case 1: displayTopography(selectedCity); break;
                                        case 2: displayRainfall(selectedCity); break;
                                        case 3: displayDrainageCapacity(selectedCity); break;
                                        case 4: displayLandUse(selectedCity); break;
                                        case 5: displayFloodHistory(selectedCity); break;
                                        case 6: displayProximityToWaterBodies(selectedCity); break;
                                        case 7: cout << "Returning to City Menu.\n"; break;
                                        default: cout << "Invalid choice! Please try again.\n"; break;
                                    }
                                } while (historicalChoice != 7);
                                break;
                            }
                            case 2:
                                displayAffectedPeople(selectedCity);
                                break;
                            case 3:
                                estimateEconomicLoss(selectedCity);
                                break;
                            case 4: {  // Calculate flood probability
                                // Retrieve the simulated data
                                map<string, double> topography = getTopographyData(cities);
                                map<string, double> rainfall = getRainfallData(cities);
                                map<string, double> drainage = getDrainageCapacity(cities);
                                map<string, double> landUse = getLandUseData(cities);
                                map<string, int> floodHistory = getFloodHistoryData(cities);
                                map<string, double> proximity = getProximityToWaterBodies(cities);

                                // Calculate the flood probability
                                double floodProbability = calculateFloodProbability(
                                    topography, rainfall, drainage, landUse, floodHistory, proximity, selectedCity
                                );
                                cout << "Flood Probability for " << selectedCity << ": " << floodProbability << "%" << endl;
                                break;
                            }
                            case 5:  // Calculate preparedness index
                                calculatePreparednessIndex(selectedCity);
                                break;
                            case 6:
                             rateCommunityAwareness(selectedCity);  // Call the function to rate community awareness
                               break;

                        case 7:
                                simulateEnvironmentalImpact(selectedCity);  // Call the function to simulate environmental impact
                                 break;
                        case 8:
                                  displayFloodTimeline(selectedCity);
                                break;

                        case 9:
                              // Sort cities based on flood probability and print the results
                           sortCitiesByFloodProbability(topography, rainfall, drainage, landUse, floodHistory, proximity, cities);
                           break;
                        case 10:
                                cout << "Returning to City Menu.\n";
                                break;
                            default:
                                cout << "Invalid choice! Please try again.\n";
                        }
                    } while (subChoice != 10);
                }
                break;
            }

            case 2:
                     {
                // Ask user to select a city and display its details
                string selectedCity;
                cout << "\nEnter the name of the city you want details for:";
                    cin.ignore();
                getline(cin, selectedCity);

                // Call the displayCityDetails function to show the details
                displayCityDetails(selectedCity, cityData);
                break;
            }
    ;
            case 3:

    searchCityByName(topography, rainfall, drainage, landUse, floodHistory, proximity, cities);
    break;

            case 4:
               Evacuation();

                break;
             case 5:
                sendFloodAlert(cities,topography,rainfall,drainage,landUse,floodHistory,proximity);
                break;

            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (mainChoice != 7);

    return 0;
}
