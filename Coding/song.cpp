#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Song {
private:
string songName;
string musicianName;
string filePath;
string duration;

public:
// Constructor to initialize the song details
Song(const string& songName, const string& musicianName,
        const string& filePath, const string& duration)
    : songName(songName), musicianName(musicianName),
        filePath(filePath), duration(duration) {}

// Getter methods
string getSongName() const { return songName; }
string getMusicianName() const { return musicianName; }
string getFilePath() const { return filePath; }
string getDuration() const { return duration; }

// Method to print song details
void printDetails() const {
    cout << "Song Name: " << songName << endl;
    cout << "Musician Name: " << musicianName << endl;
    cout << "File Path: " << filePath << endl;
    cout << "Duration: " << duration << endl;
}
};

// Listener class definition
class Listener {
private:
string name;
vector<Song> collection; // Dynamic list of songs

public:
// Constructor to initialize the listener's name
Listener(const string& name) : name(name) {}

// Method to add a new song to the collection
void addSong(const Song& song) {
    collection.push_back(song);
}

// Method to view the collection of songs
void viewCollection() const {
    cout << "\n" << name << "'s Music Collection:\n";
    for (size_t i = 0; i < collection.size(); ++i) {
        cout << "\nSong " << (i + 1) << ":\n";
        collection[i].printDetails();
    }
}

// Method to access the file path of a song by name
void viewFilePath(const string& songName) const {
    for (const auto& song : collection) {
        if (song.getSongName() == songName) {
            cout << "File Path for '" << songName << "': " << song.getFilePath() << endl;
            return;
        }
    }
    cout << "Song '" << songName << "' not found in the collection." << endl;
}
};

// Function to add a new song
void addSong(vector<Song>& songList) {
string songName, musicianName, filePath, duration;

cout << "Enter song name: ";
getline(cin, songName);

cout << "Enter musician name: ";
getline(cin, musicianName);

cout << "Enter file path: ";
getline(cin, filePath);

cout << "Enter duration (e.g., 3:45): ";
getline(cin, duration);

// Create a new Song object and add it to the vector
Song newSong(songName, musicianName, filePath, duration);
songList.push_back(newSong);
}

// Main function
int main() {
vector<Song> songList;
string listenerName;

cout << "Enter listener's name: ";
getline(std::cin, listenerName);

Listener listener(listenerName);

char choice;
do {
    addSong(songList);

    cout << "Would you like to add another song? (y/n): ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character left in the input buffer
} while (choice == 'y' || choice == 'Y');

// Add all songs to the listener's collection
for (const auto& song : songList) {
    listener.addSong(song);
}

// View the listener's collection
listener.viewCollection();

// Allow the listener to view the file path of a specific song
string songToFind;
cout << "\nEnter the name of the song to view its file path: ";
getline(cin, songToFind);

listener.viewFilePath(songToFind);

return 0;
}
