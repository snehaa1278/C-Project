#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Song {

private:
string songName;
string musicianName;
string filePath;
float duration;

public:
Song(const string& songName, const string& musicianName,
        const string& filePath, float duration)
    : songName(songName), musicianName(musicianName),
        filePath(filePath), duration(duration) {}

string getSongName() const { return songName; }
string getMusicianName() const { return musicianName; }
string getFilePath() const { return filePath; }
float getDuration() const { return duration; }

void printDetails() const {
    cout << "Song Name: " << songName << endl;
    cout << "Musician Name: " << musicianName << endl;
    cout << "File Path: " << filePath << endl;
    cout << "Duration: " << duration << "minutes" << endl;
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
    for (const auto& song : collection) {
        if (song.getSongName() == songName) {
            cout << "File Path for '" << songName << "': " << song.getFilePath() << endl;
            return;
        }
    }
    cout << "Song '" << songName << "' not found in the collection." << endl;
}

void deleteSong(const string& songName) {
        auto it = remove_if(collection.begin(), collection.end(),
            [&songName](const Song& song) { return song.getSongName() == songName; });
        collection.erase(it, collection.end());  
    }

    void addToFavorites(const string& songName) {
        for (const auto& song : collection) {
            if (song.getSongName() == songName) {
                favorites.push_back(song);
                return;
            }
        }
        cout << "Song '" << songName << "' not found in the collection." << endl;
    }

        void viewFavorites() const {
        cout << "Favorite Songs:\n";
        for (const auto& song : favorites) {  
            song.printDetails();                   /

            cout << "-------------------------\n";
        }

}
};

void addSong(vector<Song>& songList) {
string songName, musicianName, filePath;
float duration;

cout << "Enter song name: ";
getline(cin, songName);

cout << "Enter musician name: ";
getline(cin, musicianName);

cout << "Enter file path: ";
getline(cin, filePath);

cout << "Enter duration: ";
cin >> duration;
cin.ignore();

Song newSong(songName, musicianName, filePath, duration);
songList.push_back(newSong);
}

int main() {
vector<Song> songList;
string listenerName;

cout << "Enter listener's name: ";
cin.ignore();
getline(cin, listenerName);

Listener listener(listenerName);

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

return 0;
}
