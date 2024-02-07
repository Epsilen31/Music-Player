#include <iostream>
#include <string>

using namespace std;

// Node structure for the song
struct SongNode {
  string title;
  string artist;
  SongNode *next;
  SongNode *prev;

  SongNode(string _title, string _artist) {
    this->title = _title;
    this->artist = _artist;
    this->next = NULL;
    this->prev = NULL;
  }
};

class Playlist {
private:
  SongNode *head;
  SongNode *currentSong;

public:
  Playlist() {
    this->head = NULL;
    this->currentSong = NULL;
  }

  // Add a song to the at Tail Position,  playlist
  void insert(string title, string artist) {
    SongNode *newNode = new SongNode(title, artist);
    if (head == nullptr) {
      // First song in the playlist
      head = newNode;
      head->next = head;
      head->prev = head;
      currentSong = head;
    } else {
      // Insert after the last song

      SongNode *temp = head;
      while (temp->next != head) {
        temp = temp->next;
      }
      temp->next = newNode;
      newNode->prev = temp;
      newNode->next = head;
      head->prev = newNode;
    }
    printPlaylist();
  }

  void printPlaylist() {
    if (head == nullptr) {
      cout << "Playlist is empty." << endl;
      return;
    }
    SongNode *temp = head;
    do {
      cout << temp->title << "->";
      temp = temp->next;
    } while (temp != head);
    cout << endl;
  }

  // Remove a song from the head position
  pair<string, string> Delete() {
    if (head == nullptr) {
      cout << "Playlist is empty." << endl;
      return make_pair("", "");
    }
    if (head->next == head) {
      // Only one song in the playlist
      pair<string, string> deletedSong = {head->title, head->artist};
      delete head;
      head = nullptr;
      currentSong = nullptr;
      return deletedSong;
    } else {
      pair<string, string> deletedSong =
          make_pair(currentSong->title, currentSong->artist);

      SongNode *temp = head;
      while (temp->next != head) {
        temp = temp->next;
      }
      SongNode *newHead = head->next;
      temp->next = newHead;
      currentSong = newHead;
      newHead->prev = temp;
      delete head;
      head = newHead;
      return deletedSong;
    }
  }

  // Display the current playlist
  void Show() {
    if (head == nullptr) {
      cout << "Playlist is empty." << endl;
      return;
    }
    SongNode *temp = head;
    do {
      cout << temp->title << " by " << temp->artist << endl;
      temp = temp->next;
    } while (temp != head);
  }

  // Play the next song
  void Next() {
    if (currentSong != nullptr) {
      currentSong = currentSong->next;
      cout << "Now playing: " << currentSong->title << " by "
           << currentSong->artist << endl;
    } else {
      cout << "Playlist is empty." << endl;
    }
  }

  // Play the previous song
  void Prev() {
    if (currentSong != nullptr) {
      currentSong = currentSong->prev;
      cout << "Now playing: " << currentSong->title << " by "
           << currentSong->artist << endl;
    } else {
      cout << "Playlist is empty." << endl;
    }
  }

  // Play the first song
  void First() {
    if (head != nullptr) {
      currentSong = head;
      cout << "Now playing: " << currentSong->title << " by "
           << currentSong->artist << endl;
    } else {
      cout << "Playlist is empty." << endl;
    }
  }

  // Play the last song
  void Last() {
    if (head != nullptr) {
      currentSong = head->prev;
      cout << "Now playing: " << currentSong->title << " by "
           << currentSong->artist << endl;
    } else {
      cout << "Playlist is empty." << endl;
    }
  }

  // Play a specific song by title
  void Specific(string title) {
    if (head == nullptr) {
      cout << "Playlist is empty." << endl;
      return;
    }
    SongNode *temp = head;
    do {
      if (temp->title == title) {
        currentSong = temp;
        cout << "Now playing: " << currentSong->title << " by "
             << currentSong->artist << endl;
        return;
      }
      temp = temp->next;
    } while (temp != head);
    cout << "Song not found." << endl;
  }
};

int main() {
  Playlist playlist;

  int choice;
  while (true) {
    cout << "\n--------Menu for Music Playlist-------------\n";
    cout << "1. Add a new song\n";
    cout << "2. Remove a song\n";
    cout << "3. Show Playlist\n";
    cout << "4. Play Next File\n";
    cout << "5. Play Previous File\n";
    cout << "6. Play First File\n";
    cout << "7. Play Last File\n";
    cout << "8. Play Specific File\n";
    cout << "9. Exit\n\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      string title, artist;
      cout << "Enter song title: ";
      cin.ignore();
      getline(cin, title);
      cout << "Enter artist: ";
      getline(cin, artist);
      playlist.insert(title, artist);
      cout << "Song \"" << title << "\" by " << artist
           << "added to the playlist." << endl;
      break;
    }
    case 2: {
      pair<string, string> deletedSong = playlist.Delete();
      if (deletedSong.first != "") {
        cout << "Song \"" << deletedSong.first << "\" by " << deletedSong.second
             << " removed from the playlist." << endl;
      }
      break;
    }
    case 3:
      cout << "Current Playlist:" << endl;
      playlist.Show();
      break;
    case 4:
      playlist.Next();
      break;
    case 5:
      playlist.Prev();
      break;
    case 6:
      playlist.First();
      break;
    case 7:
      playlist.Last();
      break;
    case 8: {
      string title;
      cout << "Enter the title of the song to play: ";
      cin.ignore();
      getline(cin, title);
      playlist.Specific(title);
      break;
    }
    case 9:
      exit(0);
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  }

  return 0;
}
