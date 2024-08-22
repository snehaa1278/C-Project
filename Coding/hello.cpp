#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

int main()
{
    // Load the music file
    Music music;
    if (!music.openFromFile("C:/Users/lalit/OneDrive/Desktop/c++course/Coding/song.wav")) // Replace with your audio file path
    {
        cout << "Error loading music file" << endl;
        return -1;
    }

    // Create a window for the music player
    sf::RenderWindow window(sf::VideoMode(600, 400), "Music Player");

    // Start playing the music
    music.play();

    // Set up a basic text display
    sf::Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf")) // Replace with a valid font file path
    {
        cout << "Error loading font file" << endl;
        return -1;
    }
    sf::Text text("Press P to Play/Pause\nPress S to Stop", font, 20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 350);

    // Create a shape for the animation
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(275, 150);

    // Main loop to keep the window open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Check if the close button was pressed
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle keyboard input
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                {
                    if (music.getStatus() == sf::Music::Playing)
                        music.pause();
                    else
                        music.play();
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    music.stop();
                }
            }
        }

        // Simulate the amplitude based on the music's playing position (for simplicity)
        // In a real-world scenario, you might use FFT or another method to get actual amplitude data
        float amplitude = std::abs(sin(music.getPlayingOffset().asSeconds() * 2)); // Amplitude simulation
        float newRadius = 50 + amplitude * 50; // Scale the circle size based on the amplitude
        circle.setRadius(newRadius);
        circle.setOrigin(newRadius, newRadius); // Adjust origin for scaling
        circle.setPosition(300, 200); // Center the circle

        // Clear the window
        window.clear();

        // Draw the animated circles
        window.draw(circle);

        // Draw the text instructions
        window.draw(text);

        // Display the contents of the window
        window.display();
    }

    return 0;
}

