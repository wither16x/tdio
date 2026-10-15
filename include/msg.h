#ifndef MSG_H
#define MSG_H

#include <format>
#include <string>
#include <vector>

class MessageArea
{
    std::vector<std::string> lines;

public:
    template<typename... Args>
    void set(this MessageArea &self, const std::string &new_text, Args &&...args)
    {
        self.lines.push_back(std::vformat(new_text, std::make_format_args(args...)));
    }

    void clear(this MessageArea &self);
    void display(this const MessageArea &self);
    void displayStats() const;
};

#endif // MSG_H