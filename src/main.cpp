#include "RadixTrie.h"

int main(int argc, char const *argv[])
{
    RadixTrie trie;

    trie.append("aleksey");
    trie.print();

    trie.append("sasha");
    trie.print();

    trie.append("aleks");
    trie.print();

    trie.append("alek");
    trie.print();

    trie.append("alesha");
    trie.print();

    trie.append("maksim");
    trie.print();


    return 0;
}