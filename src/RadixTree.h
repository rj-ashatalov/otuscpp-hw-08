#pragma once

#include <memory>
#include <array>
#include <string>


class RadixTrie
{
        struct Node
        {
            std::string label;
            bool is_end{};
            std::array<std::unique_ptr<Node>, 26> children;
        };

        std::unique_ptr<Node> root;
    public:

        static void append(std::unique_ptr<Node>& node, const std::string& label)
        {
            // TODO
        }

        void append(const std::string& label)
        {
            append(root, label);
        }
};
