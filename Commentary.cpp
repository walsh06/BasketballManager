#include "Commentary.h"

/** Commentary Constructor */
Commentary::Commentary()
{
    //read the xml files to load the commentary
    readXML();
}

/** Returns an appropriate commentary phrase */
std::string Commentary::getCommentary(int eventType, Player *p, Player *p2)
{
    std::string commentary = "";
    //Get analysis commentary phrase
    if(eventType == 15 && rand() % 25 == 0)
    {
        //get a random type of commentary and random phrase for that type
        int randAnalysis = (rand() % 2) +1;
        int randPos = rand() % analysis[randAnalysis].size();

        //if points phrase is chosen and the threshold is passed
        //else if rebounds phrase chosen and threshold passed
        if(randAnalysis == 1 && p->getStatList()->getPoints() >= get<0>(analysis[randAnalysis][randPos]))
        {
            //get the phrase
            commentary = get<1>(analysis[randAnalysis][randPos]);
            //replace <player> with player name
            commentary.replace(commentary.find("<player>"), 8, p->getName());
            //replace <points> with player points total
            commentary.replace(commentary.find("<points>"), 8, to_string(p->getStatList()->getPoints()));
        }
        else if(randAnalysis == 2 && p->getStatList()->getRebounds() >= get<0>(analysis[randAnalysis][randPos]))
        {
            //get the phrase
            commentary = get<1>(analysis[randAnalysis][randPos]);
            //replace <player> with player name
            commentary.replace(commentary.find("<player>"), 8, p->getName());
            //replace <rebounds> with player points total
            commentary.replace(commentary.find("<rebounds>"), 10, to_string(p->getStatList()->getRebounds()));
        }
    }
    //If an analysis phrase was not generated
    if(commentary == "")
    {
        //get a random phrase for the given type
        int randPos = rand() % comments[eventType].size();
        commentary = comments[eventType][randPos];

        //replace <player> with player name
        commentary.replace(commentary.find("<player>"), 8, p->getName());

        //find <second_player> in phrase
        int playerTwoPos = commentary.find("<second_player>");

        //if <second_player> present, replace
        if(playerTwoPos >= 0 && p2 != NULL)
        {
            commentary.replace(playerTwoPos, 15, p2->getName());
        }

        //find <adjective> in phrase
        int adjectivePos = commentary.find("<adjective>");
        //if <adjective present in phrase
        if(adjectivePos >= 0)
        {
            //get a random adjective from the list
            std::string adjective = adjectives[rand() % adjectives.size()];
            //replace <adjective> with random adjective
            commentary.replace(adjectivePos, 11, adjective);
        }
    }
    return commentary;
}

/** Read the commentary from xml files */
void Commentary::readXML()
{
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../BasketballManager/gameData/commentary.xml");

    //loop through the tree structure created of the xml
    for (pugi::xml_node event: doc.child("commentary"))
    {
        //get the event type for the comment and the phrase
        int type = std::stoi(event.first_attribute().value());
        std::string commentary = event.last_attribute().value();

        //add the phrase to the type list
        //create the list if it does not exist
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

    //read the adjectives and add them to a list
    for (pugi::xml_node adjective: doc.child("adjectives"))
    {
        adjectives.push_back(adjective.first_attribute().value());
    }

    //read the analysis phrases
    for (pugi::xml_node comment: doc.child("analysis"))
    {        
        //get the type, phrase and threshold of the comment
        int type = std::stoi(comment.first_attribute().value());
        std::string commentary = comment.last_attribute().value();
        int threshold = std::stoi(comment.attribute("threshold").value());

        //make a tuple of the phrase and threshold
        tuple<int, std::string> a = make_tuple(threshold, commentary);

        //add the phrase to the type list
        //create the list if it does not exist
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
