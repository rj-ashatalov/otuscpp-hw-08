#include "RadixTrie.h"

int main(int, char const *[])
{
    RadixTrie trie;

    while (true)
    {
        std::cout << "Waiting for input:" << std::endl;
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof())
        {
            trie.printWords();
            break;
        }
        trie.append(line);
        trie.print();
    }

    return 0;
}
