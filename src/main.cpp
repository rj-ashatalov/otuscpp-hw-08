#include "RadixTrie.h"

int main(int argc, char const *argv[])
{
    RadixTrie trie;

    while (true)
    {
        std::cout << "Waiting for input:" << std::endl;
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof())
        {
            //TODO @a.shatalov: trie.printPrefixes()
            break;
        }
        trie.append(line);
        trie.print();
    }

    return 0;
}