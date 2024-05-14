// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"


int main(){
    Trie word_bank = Trie();
    std::string command;
    std::string parameter;
    
    while(true){//go into an infinite loop, accepting commands via cin
        std::cin>>command;
        if(command == "load"){//if our command is load, call the load function
            word_bank.load();
            std::cout<<"success"<<std::endl;
        }
        if(command == "i"){//if our command is i, call the insert function on the parameter
            std::cin>>parameter;
            word_bank.insert(parameter);
        }
        if(command == "c"){//if our command is c, call the count function on the parameter
            std::cin>>parameter;
            word_bank.count(parameter);
        }
        if(command == "e"){//if our command is e, call the erase function on the parameter
            std::cin>>parameter;
            word_bank.erase(word_bank.root, parameter, 0);
        }
        if(command == "p"){//if our command is p, call the print function
            word_bank.print(word_bank.root, "");
            std::cout<<"\b"<<std::endl;//make to delete the extra space that will be printed at the end, as well as go to a new line
        }
        if(command == "spellcheck"){//if our command is spellcheck, call the spellcheck function on the parameter
            std::cin>>parameter;
            word_bank.spellcheck(parameter);
        }
        if(command == "empty"){//if our command is empty, call the empty function
            word_bank.empty();
        }
        if(command == "clear"){//if our command is clear, call the clear function
            word_bank.clear(word_bank.root);
            std::cout<<"success"<<std::endl; //print success since the function doesn't print it
            word_bank.word_count = 0;
        }
        if(command == "size"){//if our command is size, call the size function
            word_bank.size();
        }
        if(command == "exit"){//if our command is exit, break the loop, ending the program
            break;
        }
    }
}