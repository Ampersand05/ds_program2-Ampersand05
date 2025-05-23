#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include "timer.h"
#include <iostream>
#include <fstream>
using namespace std;

BinarySearchTree<string> dictionary;
BinarySearchTree<string> mispelledWords;

int correctWords = 0;
int incorrectWords = 0;
int uncheckedWords = 0;

void checkWord(string);
string cleanWord(string);

int main(){

    ifstream dictionaryFile("dict.txt");

    if(!dictionaryFile.is_open()){
        cerr << "Error opening the dictionary file!" << "\n";
        return 1;
    }

    string word = "";
    //Loops for each word in the dictionary, inserting it in the "dictionary" tree
    while(true){
        if(!(dictionaryFile>>word)){
            break;
        }
        dictionary.insert(cleanWord(word));
    }
    dictionaryFile.close();
    
    //Dictionary has been loaded into the tree
    //Starting to work with the book
    
    ifstream bookFile("book.txt");

    if(!bookFile.is_open()){
        cerr << "Error opening the book file!" << "\n";
        return 1;
    }

    Timer timer;
    timer.Start();

    //Reads each book word
    while(true){
        if(!(bookFile>>word)){
            break;
        }
        checkWord(cleanWord(word));
    }
    bookFile.close();
    timer.Stop();

    //Output
    mispelledWords.writeLinkedToText();
    cout << "Dictionary size " << dictionary.getSize() << "\n";
    cout << "Done checking and these are the results" << "\n";
    cout << "Finished in time: " << timer.Time() << "\n";
    cout << "There are " << correctWords << " words found in the dictionary" << "\n";
    cout << dictionary.getCorrectCompares() << " compares. Average: " << (dictionary.getCorrectCompares() / correctWords) << "\n";
    cout << "\n";
    cout << "There are " << incorrectWords << " words NOT found in the dictionary" << "\n";
    cout << dictionary.getIncorrectCompares() << " compares. Average: " << (dictionary.getIncorrectCompares() / incorrectWords) << "\n";
    cout << "There are " << uncheckedWords << " words not checked" << "\n";

    return 0;
}

void checkWord(string word){
    //Skips if word begins with a number or apostrophe
    if(isdigit(word[0]) || word[0] == '\''){
        uncheckedWords++;
        return;
    }

    if(!(word.compare(""))){
        return;
    }
    
    //Runs each word through the find method of the dictionary
    if(dictionary.find(word)){
        correctWords++;
    } else {
        mispelledWords.linkedInsert(word);
        incorrectWords++;
    }
}

string cleanWord(string dirtyWord){
    string newString = "";
    char letter;
    //Loops through each character in the word to determine if it should be kept
    for(int i = 0; i < dirtyWord.length(); i++){
        letter = dirtyWord[i];
        //Executes if letter is alphanumeric
        if(isalnum(letter)){
            //Executes if letter is a letter
            if(isalpha(letter)){
                //Executes if letter is uppercase
                if(isupper(letter)){
                    newString += tolower(letter);
                } else {
                    newString += letter;
                }
            } else {
                newString += letter;
            }
        } else if(letter == '\''){
            newString += letter;
        }
    }
    return newString;
}
