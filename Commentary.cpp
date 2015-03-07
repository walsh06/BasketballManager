#include "Commentary.h"

Commentary::Commentary()
{
    readXML();
}

std::string Commentary::getCommentary(int eventType, Player *p, Player *p2)
{
    std::string commentary = "";
    if(eventType == 15 && rand() % 25 < 25)
    {
        int randAnalysis = (rand() % 2) +1;
        int randPos = rand() % analysis[randAnalysis].size();
        if(randAnalysis == 1 && p->getStatList()->getPoints() >= get<0>(analysis[randAnalysis][randPos]))
        {
            commentary = get<1>(analysis[randAnalysis][randPos]);
            commentary.replace(commentary.find("<player>"), 8, p->getName());
            commentary.replace(commentary.find("<points>"), 8, to_string(p->getStatList()->getPoints()));
        }
        else if(randAnalysis == 2 && p->getStatList()->getRebounds() >= get<0>(analysis[randAnalysis][randPos]))
        {
            commentary = get<1>(analysis[randAnalysis][randPos]);
            commentary.replace(commentary.find("<player>"), 8, p->getName());
            commentary.replace(commentary.find("<rebounds>"), 10, to_string(p->getStatList()->getRebounds()));
        }
    }

    if(commentary == "")
    {
        int randPos = rand() % comments[eventType].size();
        commentary = comments[eventType][randPos];

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
        int type = std::stoi(comment.first_attribute().value());
        std::string commentary = comment.last_attribute().value();
        int threshold = std::stoi(comment.attribute("threshold").value());
        tuple<int, std::string> a = make_tuple(threshold, commentary);

        if (analysis.find(type) == analysis.end())
        {
            std::vector<tuple<int, std::string>> analysisCommentary;
            analysisCommentary.push_back(a);
            analysis[type] = analysisCommentary;
        }
        else
        {
            analysis[type].push_back(a);
        }
    }
}
