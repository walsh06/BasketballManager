#include "Commentary.h"

Commentary::Commentary()
{
    readXML();
}

std::string Commentary::getCommentary(int eventType, Player *p, Player *p2)
{
    int randPos = rand() % comments[eventType].size();
    std::string commentary = comments[eventType][randPos];

    commentary.replace(commentary.find("<player>"), 8, p->getName());

    int playerTwoPos = commentary.find("<second_player>");

    if(playerTwoPos >= 0 && p2 != NULL)
    {
        commentary.replace(playerTwoPos, 15, p2->getName());
    }

    int adjectivePos = commentary.find("<adjective>");
    if(adjectivePos >= 0)
    {
        std::string adjective = adjectives[rand() % adjectives.size()];
        commentary.replace(adjectivePos, 11, adjective);
    }
    return commentary;
}

void Commentary::readXML()
{
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../BasketballManager/gameData/commentary.xml");

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
    for (pugi::xml_node adjective: doc.child("adjectives"))
    {
        adjectives.push_back(adjective.first_attribute().value());
    }

    for (pugi::xml_node comment: doc.child("analysis"))
    {
        analysis.push_back(comment.first_attribute().value());
    }
}
