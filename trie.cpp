#include "trie.h"
#include <string>
#include <iostream>
#include <fstream>

character_Node::character_Node(){ //initialize a new character node but setting our array to nullptrs
    for (int i = 0; i < 26; i++){ //when we initialize a new character node, set all the potential next characters it could point to, to nullptrs
        next_chars[i] = nullptr;
    }
    is_final_char = false; //this variable stores whether or not this character node is the end of a word, for now, initialize it to false
}

Trie::Trie(){//initialize Trie by making a new character node and setting it as the root
    root = new character_Node(); //we create a new character node as its root node
    word_count = 0; //stores how many words are in the Trie
}

void Trie::load(){//loads the corpus file and inserts all words into the Trie
    std::ifstream corpusFile("corpus.txt");
    std::string line;
    std::string word = "";
    while (std::getline(corpusFile, line)) {//we read the corpus file line by line, the code below tokenizes the line into words and adds them to the Trie
        int length = line.length();
        word = ""; //stores the individual words
        for(int i = 0; i < length; i++){//we iterate through each line of the file to see if it's a character
            if('A' <= line[i] && line[i] <= 'Z'){ //if it is a character, we add the character to the end of the word
                word += line[i];
            } else { //if it is not a character, we add the completed word to the Trie and reset the word to a blank
                load_insert(word);
                word = "";
            }
        }
        //std::cout<<word<<" ";
        load_insert(word); //this is to insert the last word in the line since lines end in a character so the last word never gets inserted
    }

    // Close the file
    corpusFile.close();
}

void Trie::load_insert(std::string word){//this is basically the exact same as the insert function, except it doesn't print success or failure after it tries inserting a word
    int length = word.length();
    char character;
    bool in_trie = true;
    character_Node* current_char = root;//we start with the root
    for(int i = 0; i < length; i++){ //we iterate through every character in the word, and see if we can insert it
        character = word[i];
        character -= 'A';//here, we turn the character into a number from 0-25, to determine its place in the array of potential next characters of the current node
        if(current_char->next_chars[character] == nullptr){ //if we reach a nullptr, it means the word is not in the Trie
            in_trie = false; //so we set in_trie to false since its not in trie
            current_char->next_chars[character] = new character_Node(); //add i-th character the Trie
            current_char = current_char->next_chars[character]; //move current_char to the newly added character
        } else { //if it's not a nullptr, it means the word, up until that character, is in the Trie
            current_char = current_char->next_chars[character]; //we simply update the current character in the trie to the next character in the word
        }
        if(i == length - 1){ //if we reach the end of the word
            //see if the final character is an end-character
            if(!current_char->is_final_char){
                current_char->is_final_char = true; //set the current character to an end character if it's not
                in_trie = false; //the word is not in the trie if the final character is not an end character yet
            }
        }
    }
    
    if (in_trie){
        
    }else{
        //std::cout<<word<<std::endl;
        word_count++; //if we have added the word, increase the word count by one
    }
}

void Trie::insert(std::string word){//insert performs the exact same thing as load insert except it prints "success" when word is inserted and failure when its not
    int length = word.length();
    char character;
    bool in_trie = true;
    character_Node* current_char = root;//we start with the root
    for(int i = 0; i < length; i++){ //we iterate through every character in the word, and see if we can insert it
        character = word[i];
        character -= 'A';//here, we turn the character into a number from 0-25, to determine its place in the array of potential next characters of the current node
        if(current_char->next_chars[character] == nullptr){ //if we reach a nullptr, it means the word is not in the Trie
            in_trie = false; //so we set in_trie to false since its not in trie
            current_char->next_chars[character] = new character_Node(); //add i-th character the Trie
            current_char = current_char->next_chars[character]; //move current_char to the newly added character
        } else { //if it's not a nullptr, it means the word, up until that character, is in the Trie
            current_char = current_char->next_chars[character]; //we simply update the current character in the trie to the next character in the word
        }
        if(i == length - 1){ //if we reach the end of the word
            //see if the final character is an end-character
            if(!current_char->is_final_char){
                current_char->is_final_char = true; //set the current character to an end character if it's not
                in_trie = false; //the word is not in the trie if the final character is not an end character yet
            }
        }
    }
    if (in_trie){
        std::cout<<"failure"<<std::endl;

    }else{
        std::cout<<"success"<<std::endl;
        //std::cout<<word<<std::endl;
        word_count++;
        //current_char->is_final_char = true;
    }
}

int Trie::count_the_words(character_Node* curr_char){//this counts the total number of node that represent end-of-words that branch from the node curr_char(including curr_char itself)
    int char_count = 0;
    if(curr_char->is_final_char){ //if the current character is an end to a word, we increment the end-of-word count by 1
        char_count++;
    }
    for(int j = 0; j < 26; j++){ //then, we recursively call count_the_words on each of curr_char's child nodes
        if(curr_char->next_chars[j] != nullptr){
            char_count += count_the_words(curr_char->next_chars[j]);//and add the number of end-of-word nodes they each have to the total number of end-word nodes that are below curr_char
        }
    }
    return char_count;//we return this number of end-of-word nodes
}

void Trie::count(std::string prefix){ //counts the number of words that have prefix as its prefix
    int length = prefix.length();
    char character;
    int num = 0;
    character_Node* current_char = root;
    for(int i = 0; i < length; i++){ //we iterate through all characters in the prefix
        character = prefix[i];
        character -= 'A';
        if((root->next_chars)[character] != nullptr){ //we navigate through the trie, ideally until we reach the end of the prefix
            current_char = current_char->next_chars[character];
        } else if((root->next_chars)[character] == nullptr && i != length - 1){//if a character in the prefix doesn't exist in Trie, print not found
            std::cout<<"not found"<<std::endl;
            return;
        }
    }
    num = count_the_words(current_char); //if we do reach the end of the prefix(ie, the prefix exists in the trie)
    // call count_the_words on the character node of the last character of the prefix to count how many end-of-words there are in all of current_char's branches (aka, # of words that begin with prefix)
    std::cout<<"count is "<<num<<std::endl;
}

bool Trie::erase(character_Node* current_char, std::string word, int index){
    char character = word[index] - 'A';
    bool delete_curr;
    if(current_char->next_chars[character] == nullptr && index != word.length()){//if the word doesn't exist in Trie, print failure and tell previous recursions to not delete anything
        std::cout<<"failure"<<std::endl;
        return false;
    }
    //first check if we are at the end of our word
    if(index == word.length()){
        if(!current_char->is_final_char){ //if the final character of the word is not an ending character, the word doesn't exist in Trie
            std::cout<<"failure"<<std::endl;
            return false;
        }
        //if we are at the end of our word, check if that last character has any children
        for(int i = 0; i<26; i++){
            if(current_char->next_chars[i] != nullptr){//if it does have children, return false, telling previous recursions to not delete any characters
                current_char->is_final_char = false; //however, set the last char to not be an end character
                word_count--;
                std::cout<<"success"<<std::endl;
                return false;
            } else if(i == 25){ //if it doesn't have children, delete the current char and tell previous recursions to delete too
                delete current_char;
                word_count--;
                std::cout<<"success"<<std::endl;
                return true;
            }
        }
    } else {//if we are not at the end of our word
        delete_curr = erase(current_char->next_chars[character], word, index + 1); //delete curr stores whether or not current_char->next_chars[character] will be deleted
        if(delete_curr){
            //std::cout<<char(character+'A')<<std::endl;
            current_char->next_chars[character] = nullptr; //if the character after current_char has been deleted, set it to nullptr
            //now check if current_char has any more children
            for(int i = 0; i<26; i++){
                if(current_char->next_chars[i] != nullptr){//if it does have children, return false, telling previous recursions to not delete any characters
                    //current_char->is_final_char = false; //however, set the last char to not be an end character
                    return false;
                } else if(i == 25){ //if current_char doesn't have children, delete the current char and tell previous recursions to delete too
                    delete current_char;
                    return true;
                }
            }
        } else {//if the next character in the word hasn't been deleted, tell previous recursions to not delete anything
            return false;
        }
    }
}
void Trie::print(character_Node* current_char, std::string curr_word){//prints all words in Trie
    //current_char holds the character node we are currently on, curr_word holds the prefix of the word
    if(current_char->is_final_char){ //if the current char is the end of a word, print out the "prefix" of the word as it is now complete
        std::cout<<curr_word<<" ";
    }
    std::string word;
    char character;
    for(int i = 0; i < 26; i++){//then call print again on all of the current character node's children
        if(current_char->next_chars[i] != nullptr){
            character = 'A' + i;
            word = curr_word + character;// while adding the character of the child node it points to, to the end of the prefix
            //this allows us to slowly construct each word in the trie, character by character
            print(current_char->next_chars[i], word);
        }
    }
}

void Trie::spellcheck(std::string word){
    character_Node* current_char = root;
    int length = word.length();
    char character;
    for(int i = 0; i < length; i++){
        character = word[i] - 'A';
        if(current_char->next_chars[character] == nullptr && i != length - 1){ //the i-th character in word doesn't exist
            print(current_char, word.substr(0, i));// then print all words with the first i characters as a prefix
            std::cout<<"\b"<<std::endl;
            return;
        } else if(current_char->next_chars[character] != nullptr && i != length - 1){//if the i-th character exists, then move on to next character
            current_char = current_char->next_chars[character];
        } else if(current_char->next_chars[character] != nullptr && i == length - 1){//if we reach the end of the word
            if(current_char->next_chars[character]->is_final_char){ // if the character node corresponding to last character of the word is an end-of-word node, print correct
                std::cout<<"correct"<<std::endl;
            } else {// if the character node corresponding to last character of the word is not an end-of-word node
                // print all words that have the word we are spellchecking as a prefix
                print(current_char->next_chars[character], word);
                std::cout<<"\b"<<std::endl;
            }
        } else {
            print(current_char, word.substr(0, i)); //if the last character isn't in the Trie, print all words with the first i-1 characters as a prefix
            std::cout<<"\b"<<std::endl;
            //std::cout<<"correct2"<<std::endl;
        }
    }
}

void Trie::empty(){
    bool is_empty = true;
    for(int i = 0; i < 26; i++){//we iterate through the root node
        if(root->next_chars[i] != nullptr){ //if we find any character that has a child node, then the Trie is not empty
            is_empty = false;
        }
    }
    //if all 26 characters of the root node have no children, then the Trie is empty
    if(is_empty){
        std::cout<<"empty 1"<<std::endl;
    } else {
        std::cout<<"empty 0"<<std::endl;
    }
}

void Trie::clear(character_Node* current_char){
    if(current_char == nullptr){//if the current node is a nullptr, simply return
        return;
    }
    for(int i = 0; i < 26; i++){ //we iterate through all 26 characters, and recursively call clear on any child node the current character may have
        if(current_char->next_chars[i] != nullptr){
            clear(current_char->next_chars[i]);
            current_char->next_chars[i] = nullptr;
        }
    }
    if(current_char != root){//once all the child nodes are deleted, delete the current node too(unless it's the root node, deleting it may cause problems so we don't touch it). 
        delete current_char;
    }
}
void Trie::size(){
    std::cout<<"number of words is "<<word_count<<std::endl;//outputs the word count
}
