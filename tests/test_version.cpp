#define BOOST_TEST_MODULE app_test_module

#include "../lib.h"
#include <boost/test/unit_test.hpp>
#include "RadixTrie.h"

BOOST_AUTO_TEST_SUITE(app_test_suite)

BOOST_AUTO_TEST_CASE(test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(test_trie_print)
{
    RadixTrie trie;

    trie.append("aleksey");
    trie.print();

    trie.append("sasha");
    trie.print();

    trie.append("alek");
    trie.print();

    trie.append("aleks");
    trie.print();

    trie.append("alesha");
    trie.print();

    trie.append("maksimilian");
    trie.print();

    trie.append("makson");
    trie.print();

    trie.append("maksim");
    trie.print();

    trie.append("maks");
    trie.print();

    BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
