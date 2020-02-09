#pragma once

#include <memory>
#include <array>
#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>


class RadixTrie
{
        struct Node
        {
            std::string label = "";
            bool isEnd{false};
            std::array<std::unique_ptr<Node>, 26> children;
        };

        std::unique_ptr<Node> root;

    private:
        static auto findDiff(const std::string& lhs, const std::string& rhs)
        {
            auto length = std::min(lhs.size(), rhs.size());
            int diffIndex = 0;
            for (size_t i = 0; i < length; ++i)
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

        static size_t getCharIndex(char ch)
        {
            static size_t firstChar = static_cast<size_t>('a');
            return static_cast<size_t>(ch) - firstChar;
        }

    public:

        static void append(std::unique_ptr<Node>& node, const std::string& label)
        {
            if (label.empty())
            {
                return;
            }

            if (!node)
            {
                node = std::make_unique<Node>();
                node->label = label;
                node->isEnd = true;
                return;
            }

            if (node->label.empty())
            {
                auto charIndex = getCharIndex(*(label.c_str()));
                append(node->children[charIndex], label);
                return;
            }

            auto[equalPart, childDiff, labelDiff] = findDiff(node->label, label);
            if (node->label != equalPart)
            {
                auto&& radixNode = std::make_unique<Node>();
                radixNode->label = childDiff;
                radixNode->isEnd = node->isEnd;
                radixNode->children = std::move(node->children);
                size_t charIndex = getCharIndex(*(childDiff.c_str()));
                node->children[charIndex] = std::move(radixNode);

                node->label = equalPart;
                node->isEnd = equalPart == label;
            }
            else
            {
                node->isEnd = node->isEnd || node->label == label;
            }

            if (!labelDiff.empty())
            {
                size_t charIndex = getCharIndex(*(labelDiff.c_str()));
                append(node->children[charIndex], labelDiff);
            }
        }

        void append(const std::string& label)
        {
            append(root, label);
        }

        void print()
        {
            printInternal(root, "", "");
        }

        void printWords()
        {
            printNode(root, "");
        }

    private:

        void printNode(std::unique_ptr<Node>& node, std::string word)
        {
            if (!node)
            {
                return;
            }

            if (node->isEnd)
            {
                std::cout << word + node->label << " " << word + node->label.substr(0, 1) << std::endl;
            }

            for (auto& child:node->children)
            {
                if (child)
                {
                    printNode(child, word + node->label);
                }
            }
        }

        void printInternal(std::unique_ptr<Node>& node, std::string prefix, std::string border)
        {
            if (!node)
            {
                return;
            }
            std::cout << prefix;
            std::cout << border;
            std::cout << "\"" << node->label << "\"" << (node->isEnd ? "$" : "") << std::endl;

            auto size = std::count_if(node->children.begin(), node->children.end(), [&](const auto& item)
            {
                return item != nullptr;
            });

            int index = 0;
            for (auto& child:node->children)
            {
                if (child)
                {
                    printInternal(child, prefix + getPrefix(border), getBorder(index, size));
                    ++index;
                }
            }
        }

        std::string getPrefix(const std::string& border)
        {
            if (border == "")
            {
                return "";
            }

            if (border == "└ ")
            {
                return "  ";
            }

            return "│ ";
        }

        std::string getBorder(size_t index, size_t size)
        {
            return (index < size - 1) ? "├ " : "└ ";
        }

};
