#include <iostream>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp>  // Include the nlohmann JSON header

using json = nlohmann::json;
using namespace std;

map<string, vector<string>> userHistory;  // Maps user IDs to video IDs they watched
vector<json> videos;  // List of all videos

void handle_client(int client_sock);
std::string extract_user_id(const std::string& message);
std::string extract_video_id(const std::string& message);
std::string join_recommendations(const std::vector<std::string>& recommendations);
std::vector<std::string> get_recommendations(const std::string& user_id, const std::string& video_id);

int main() {
    const int server_port = 5555;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return 1;
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        close(sock);
        return 1;
    }

    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
        close(sock);
        return 1;
    }

    while (true) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
            continue;
        }

        // Create a new thread to handle the client
        std::thread client_thread(handle_client, client_sock);
        client_thread.detach();  // Detach the thread to allow it to run independently
    }

    close(sock);
    return 0;
}

void handle_client(int client_sock) {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);

    while (true) {
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes <= 0) {
            break;  // Connection closed or error occurred
        }

        std::string message(buffer, read_bytes);
        std::cout << "Received message: " << message << std::endl; // Add this line for debugging
        std::string user_id = extract_user_id(message);
        std::string video_id = extract_video_id(message);

        // Extract video data from the message (assume the video data follows the user and video ID in JSON format)
        size_t json_start = message.find("{");
        if (json_start != std::string::npos) {
            std::string json_data = message.substr(json_start);
            json videoData = json::parse(json_data);

            videos.clear();  // Clear old data
            for (const auto& video : videoData) {
                videos.push_back(video);
            }
        }

        // Update user's history
        userHistory[user_id].push_back(video_id);

        // Get recommendations
        std::vector<std::string> recommendations = get_recommendations(user_id, video_id);
        std::string response = join_recommendations(recommendations);

        send(client_sock, response.c_str(), response.length(), 0);
    }

    close(client_sock);
}

std::string extract_user_id(const std::string& message) {
    size_t start = message.find("USER:") + 5;
    size_t end = message.find(";", start);
    return message.substr(start, end - start);
}

std::string extract_video_id(const std::string& message) {
    size_t start = message.find("VIDEO:") + 6;
    size_t end = message.find(";", start);
    return message.substr(start, end - start);
}

std::string join_recommendations(const std::vector<std::string>& recommendations) {
    std::string result;
    for (const auto& rec : recommendations) {
        if (!result.empty()) result += ";";
        result += rec;
    }
    return result;
}

std::vector<std::string> get_recommendations(const std::string& user_id, const std::string& video_id) {
    std::map<std::string, int> videoScores;  // Maps video ID to its recommendation score

    // Collect scores based on history
    for (const auto& [other_user, watched_videos] : userHistory) {
        if (other_user == user_id) continue;

        for (const auto& vid : watched_videos) {
            if (vid != video_id) {
                videoScores[vid]++;
            }
        }
    }

    // Collect the top recommendations
    std::vector<std::pair<int, std::string>> sorted_videos;
    for (const auto& [vid, score] : videoScores) {
        sorted_videos.emplace_back(score, vid);
    }

    // Sort by score (descending)
    std::sort(sorted_videos.begin(), sorted_videos.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;  // Sort by score
    });

    std::vector<std::string> recommendations;
    for (const auto& [score, vid] : sorted_videos) {
        recommendations.push_back(vid);
    }

    // If there aren't enough recommendations, fill with random videos
    while (recommendations.size() < 6 && recommendations.size() < videos.size()) {
        int randomIndex = rand() % videos.size();
        std::string randomVidId = videos[randomIndex]["_id"].get<std::string>();
        if (std::find(recommendations.begin(), recommendations.end(), randomVidId) == recommendations.end()) {
            recommendations.push_back(randomVidId);
        }
    }

    return recommendations;
}
