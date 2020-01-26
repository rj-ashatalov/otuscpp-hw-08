#pragma once

#include <memory>
#include <array>
#include <string>
#include <math.h>


class RadixTrie
{
        struct Node
        {
            std::string label;
            bool isEnd{};
            std::array<std::unique_ptr<Node>, 26> children;
        };

        std::unique_ptr<Node> root;

    private:
        static auto findDiff(const std::string& lhs, const std::string& rhs)
        {
            auto length = std::min(lhs.size(), rhs.size());
            int diffIndex = 0;
            for (int i = 0; i < length; ++i)
            {
                if (lhs[i] == rhs[i])
                {
                    ++diffIndex;
                }
                else
                {
                    break;
                }
            }
            return std::make_tuple(lhs.substr(0, diffIndex), lhs.substr(diffIndex), rhs.substr(diffIndex));
        }

        static size_t getCharNumber(char ch)
        {
            return 0;////TODO @a.shatalov:
        }

    public:

        static void append(std::unique_ptr<Node>& node, const std::string& label)
        {
            if (label.empty())
            {
                return;
            }

            if (node->label.empty())
            {
                node->label = label;
                return;
            }

            auto[equalPart, childDiff, labelDiff] = findDiff(node->label, label);
            node->label = equalPart;
            node->isEnd = childDiff.empty() && labelDiff.empty();

            if (!childDiff.empty())
            {
                auto&& radixNode = std::make_unique<Node>();
                radixNode->label = childDiff;
                radixNode->isEnd = node->isEnd;

                if(!radixNode->isEnd)
                {
                    radixNode->children = std::move(node->children);
                    radixNode->isEnd = radixNode->children.empty();
                }

                size_t charIndex = getCharNumber(*(childDiff.c_str()));
                node->children[charIndex] = std::move(radixNode);
            }

            if (!labelDiff.empty())
            {
                size_t charIndex = getCharNumber(*(labelDiff.c_str()));
                if (node->children[charIndex] != nullptr)
                {
                    append(node->children[charIndex], childDiff);
                }
                else
                {
                    size_t charIndex = getCharNumber(*(labelDiff.c_str()));
                    node->children[charIndex] = std::make_unique<Node>();
                    node->children[charIndex]->isEnd = true;
                    node->children[charIndex]->label = labelDiff;
                }
            }
        }

        void append(const std::string& label)
        {
            append(root, label);
        }

        void print()
        {
            //todo
        }


};
