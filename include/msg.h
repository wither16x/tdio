#ifndef MSG_H
#define MSG_H

#include <format>
#include <string>

class MessageArea
{
    std::string text;

public:
    template<typename... Args>
    void set(this MessageArea &self, const std::string &new_text, Args &&...args)
    {
        self.text = std::vformat(new_text, std::make_format_args(args...));
    }

    void clear(this MessageArea &self);
    void display(this const MessageArea &self);
};

inline MessageArea msg_area;

#endif // MSG_H