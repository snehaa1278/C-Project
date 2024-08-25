#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Song {
private:
     songName;
     musicianName;
     filePath;
     duration;

public:
    Song(const &songName, const &musicianName,
         const &filePath, const &duration)
        : songName(songName), musicianName(musicianName),
          filePath(filePath), duration(duration) {}

    getSongName() const { return songName; }
    getMusicianName() const { return musicianName; }
    getFilePath() const { return filePath; }
    getDuration() const { return duration; }

    void setSongName(const &name) { songName = name; }
    void setMusicianName(const &name) { musicianName = name; }
    void setFilePath(const &path) { filePath = path; }
    void setDuration(const &dur) { duration = dur; }

    void printDetails() const {
        cout << "Song Name: " << songName << endl;
        cout << "Musician Name: " << musicianName << endl;
        cout << "File Path: " << filePath << endl;
        cout << "Duration: " << duration << endl;
    }
};

void addSong(vector<Song>& songList) {
  songName, musicianName, filePath, duration;

    cout << "Enter song name: ";
    getline(cin, songName);

    cout << "Enter musician name: ";
    getline(cin, musicianName);

    cout << "Enter file path: ";
    getline(cin, filePath);

    cout << "Enter duration (e.g., 3:45): ";
    getline(cin, duration);

    Song newSong(songName, musicianName, filePath, duration);
    songList.push_back(newSong);
}

int main() {
    vector<Song> songList;
    char choice;

    do {
        addSong(songList);

        cout << "Would you like to add another song? (y/n): ";
        cin >> choice;
        cin.ignore(); 
    } while (choice == 'y' || choice == 'Y');

    cout << "\nList of Songs:\n";
    for (size_t i = 0; i < songList.size(); ++i) {
        cout << "\nSong " << (i + 1) << ":\n";
        songList[i].printDetails();
    }

    return 0;
}
