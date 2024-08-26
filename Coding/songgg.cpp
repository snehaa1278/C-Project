#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class Song {
private:
    string songName;
    string musicianName;
    string filePath;
    string imagePath;
    float duration;

public:
    Song(const string& songName, const string& musicianName,
         const string& filePath, const string& imagePath, float duration)
        : songName(songName), musicianName(musicianName),
          filePath(filePath), imagePath(imagePath), duration(duration) {}

    string getSongName() const { return songName; }
    string getMusicianName() const { return musicianName; }
    string getFilePath() const { return filePath; }
    string getImagePath() const { return imagePath; }
    float getDuration() const { return duration; }

    void printDetails() const {
        cout << "Song Name: " << songName << endl;
        cout << "Musician Name: " << musicianName << endl;
        cout << "File Path: " << filePath << endl;
        cout << "Image Path:" << imagePath << endl;
        cout << "Duration: " << duration << " minutes" << endl;
    }

    // Serialize Song to string
    string serialize() const {
        return songName + "|" + musicianName + "|" + filePath + "|" + to_string(duration);
    }

    // Deserialize Song from string
    static Song deserialize(const string& data) {
        size_t pos1 = data.find('|');
        size_t pos2 = data.find('|', pos1 + 1);
        size_t pos3 = data.find('|', pos2 + 1);
        size_t pos4 = data.find('|', pos3 + 1);

        string songName = data.substr(0, pos1);
        string musicianName = data.substr(pos1 + 1, pos2 - pos1 - 1);
        string filePath = data.substr(pos2 + 1, pos3 - pos2 - 1);
        string imagePath = data.substr(pos3 + 1, pos4 - pos3 - 1);
        float duration = stof(data.substr(pos4 + 1));

        return Song(songName, musicianName, filePath, imagePath, duration);
    }
};

class Listener {
private:
    string name;
    vector<Song> collection; 
    vector<Song> favorites;

public:
    Listener(const string& name) : name(name) {}

    void addSong(const Song& song) {
        collection.push_back(song);
    }

    void viewCollection() const {
        cout << "\n" << name << "'s Music Collection:\n";
        for (size_t i = 0; i < collection.size(); ++i) {
            cout << "\nSong " << (i + 1) << ":\n";
            collection[i].printDetails();
        }
    }

    void viewFilePath(const string& songName) const {
        auto it = find_if(collection.begin(), collection.end(),
            [&songName](const Song& song) { return song.getSongName() == songName; });
        if (it != collection.end()) {
            cout << "File Path for '" << songName << "': " << it->getFilePath() << endl;
        } else {
            cout << "Song '" << songName << "' not found in the collection." << endl;
        }
    }

    void deleteSong(const string& songName) {
        auto it = remove_if(collection.begin(), collection.end(),
            [&songName](const Song& song) { return song.getSongName() == songName; });
            if (it != collection.end()) {
        collection.erase(it, collection.end());
         cout << "Song '" << songName << "' has been deleted from the collection." << endl;
        } else {
            cout << "Song '" << songName << "' not found in the collection." << endl;
        }
    }

    void addToFavorites(const string& songName) {
        for (const auto& song : collection) {
            if (song.getSongName() == songName) {
                if (find_if(favorites.begin(), favorites.end(),
                            [&songName](const Song& fav) { return fav.getSongName() == songName; }) == favorites.end()) {
                    favorites.push_back(song);
                } else {
                    cout << "Song '" << songName << "' is already in favorites." << endl;
                }
                return;
            }
        }
        cout << "Song '" << songName << "' not found in the collection." << endl;
    }

    void viewFavorites() const {
        cout << "Favorite Songs:\n";
        if (favorites.empty()) {
            cout << "No favorite songs added yet." << endl;
        } else {
        for (const auto& song : favorites) {
            song.printDetails();
            cout << "-------------------------\n";
        }
    }
    }
    // Save collection and favorites to files
    void saveToFile() const {
        ofstream outFile("collection.txt");
        if (!outFile) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        outFile << "Collection\n";
        for (const auto& song : collection) {
            outFile << song.serialize() << endl;
        }

        outFile << "Favorites\n";
        for (const auto& song : favorites) {
            outFile << song.serialize() << endl;
        }

        outFile.close();
    }

    // Load collection and favorites from files
    void loadFromFile() {
        ifstream inFile("collection.txt");
        if (!inFile) {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        string line;
        string section;
        while (getline(inFile, line)) {
            if (line == "Collection") {
                section = "Collection";
            } else if (line == "Favorites") {
                section = "Favorites";
            } else {
                if (section == "Collection") {
                    collection.push_back(Song::deserialize(line));
                } else if (section == "Favorites") {
                    favorites.push_back(Song::deserialize(line));
                }
            }
        }

        inFile.close();
    }
};

void addSong(vector<Song>& songList) {
    string songName, musicianName, filePath, imagePath;
    float duration;

    cout << "Enter song name: ";
    getline(cin, songName);

    cout << "Enter musician name: ";
    getline(cin, musicianName);

    cout << "Enter file path: ";
    getline(cin, filePath);

    cout << "Enter image file path:";
    getline(cin, imagePath);

    cout << "Enter duration (in minutes): ";
    cin >> duration;
    cin.ignore();

    Song newSong(songName, musicianName, filePath, imagePath, duration);
    songList.push_back(newSong);
}

int main() {
    vector<Song> songList;
    string listenerName;

    cout << "Enter listener's name: ";
    getline(cin, listenerName);

    Listener listener(listenerName);

    // Load previous data
    listener.loadFromFile();

    char choice;
    do {
        addSong(songList);

        cout << "Would you like to add another song? (y/n): ";
        cin >> choice;
        cin.ignore(); 
    } while (choice == 'y' || choice == 'Y');

    for (const auto& song : songList) {
        listener.addSong(song);
    }

    listener.viewCollection();

    string songToFind;
    cout << "\nEnter the name of the song to view its file path: ";
    getline(cin, songToFind);

    listener.viewFilePath(songToFind);

    listener.deleteSong(songToFind);

    listener.addToFavorites(songToFind);

    cout << "Favorite Songs:\n";
    listener.viewFavorites();

    // Save data
    listener.saveToFile();

    return 0;
}
