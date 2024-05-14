#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <iostream>
class character_Node{
    public:
        character_Node();
        character_Node* next_chars[26];
        bool is_final_char;
};

class Trie{
    public:
        character_Node* root;
        int word_count;
        Trie();
        void load();
        void load_insert(std::string word);
        void insert(std::string word);
        void count(std::string prefix);
        bool erase(character_Node* current_char, std::string word, int index);
        void print(character_Node* current_char, std::string curr_word);
        void spellcheck(std::string word);
        void empty();
        void clear(character_Node* current_char);
        void size();

        int count_the_words(character_Node* curr_char);
};
#endif