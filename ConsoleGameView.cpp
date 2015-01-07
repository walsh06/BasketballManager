#include "ConsoleGameView.h"

ConsoleGameView::ConsoleGameView()
{
    readXML();
}

void ConsoleGameView::updateCommentary(int type, std::string nameOne)
{
    //std::vector<std::string> eventComments = comments[type];
    int randPos = rand() % comments[type].size();

    //std::cout << type << " " << nameOne << " " << comments[type][randPos] << std::endl;

    std::cout << createCommentary(comments[type][randPos], nameOne) << std::endl;
}

void ConsoleGameView::updateTime(int time, int shotClock)
{
    std::cout << "TIME: " << time/60 <<":"<< time%60 << " Shotclock: " << shotClock << std::endl;
}

void ConsoleGameView::printValue(std::string valueName, int value)
{
    std::cout << valueName << ": " << value << std::endl;
}

std::string ConsoleGameView::createCommentary(std::string comment, const std::string name) {
    std::string newComment = comment;
    newComment.replace(newComment.find("<player>"), 8, name);

    return newComment;
}

void ConsoleGameView::readXML()
{
    //open the document
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file("../commentary.xml");

        //loop through the tree structure created of the xml
        for (pugi::xml_node event: doc.child("commentary"))
        {

            int type = std::stoi(event.first_attribute().value());
            std::string commentary = event.last_attribute().value();

            if (comments.find(type) == comments.end())
            {
                std::vector<std::string> eventCommentary;
                eventCommentary.push_back(commentary);
                comments[type] = eventCommentary;
            }
            else
            {
                comments[type].push_back(commentary);
            }
        }
}
