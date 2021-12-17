#include <iostream>
#include <fstream>

using namespace std;

int main() {
  string myText;

// Read from the text file
ifstream MyReadFile("setB.txt");

// Use a while loop together with the getline() function to read the file line by line
while (getline (MyReadFile, myText)) {
  // Output the text from the file
  //cout << myText<<endl;
  //cout << myText.length()<<endl;
  for (char const &c: myText) {
        std::cout << c << ' ';
    }
  cout << endl;
}

// Close the file
MyReadFile.close();
}