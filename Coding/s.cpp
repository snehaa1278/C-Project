#include <iostream>
#include <vector>
#include <string>

// Song class definition
class Song {
private:
    std::string songName;
    std::string musicianName;
    std::string filePath;
    std::string duration;

public:
    // Constructor to initialize the song details
    Song(const std::string& songName, const std::string& musicianName,
         const std::string& filePath, const std::string& duration)
        : songName(songName), musicianName(musicianName),
          filePath(filePath), duration(duration) {}

    // Getter methods
    std::string getSongName() const { return songName; }
    std::string getMusicianName() const { return musicianName; }
    std::string getFilePath() const { return filePath; }
    std::string getDuration() const { return duration; }

    // Setter methods
    void setSongName(const std::string& name) { songName = name; }
    void setMusicianName(const std::string& name) { musicianName = name; }
    void setFilePath(const std::string& path) { filePath = path; }
    void setDuration(const std::string& dur) { duration = dur; }

    // Method to print song details
    void printDetails() const {
        std::cout << "Song Name: " << songName << std::endl;
        std::cout << "Musician Name: " << musicianName << std::endl;
        std::cout << "File Path: " << filePath << std::endl;
        std::cout << "Duration: " << duration << std::endl;
    }
};

// Function to add a new song to the vector
void addSong(std::vector<Song>& songList) {
    std::string songName, musicianName, filePath, duration;

    std::cout << "Enter song name: ";
    std::getline(std::cin, songName);

    std::cout << "Enter musician name: ";
    std::getline(std::cin, musicianName);

    std::cout << "Enter file path: ";
    std::getline(std::cin, filePath);

    std::cout << "Enter duration (e.g., 3:45): ";
    std::getline(std::cin, duration);

    // Create a new Song object and add it to the vector
    Song newSong(songName, musicianName, filePath, duration);
    songList.push_back(newSong);
}

// Main function
int main() {
    std::vector<Song> songList;
    char choice;

    do {
        addSong(songList);

        std::cout << "Would you like to add another song? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore the newline character left in the input buffer
    } while (choice == 'y' || choice == 'Y');

    // Print all songs
    std::cout << "\nList of Songs:\n";
    for (size_t i = 0; i < songList.size(); ++i) {
        std::cout << "\nSong " << (i + 1) << ":\n";
        songList[i].printDetails();
    }

    return 0;
}
