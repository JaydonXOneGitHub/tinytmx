#include "tinyxml2.h"

#include "tinytmxTile.hpp"
#include "tinytmxObject.hpp"

namespace tinytmx {
    Tile::Tile() :
            isAnimated(false),
            hasObjects(false),
            hasObjectGroup(false),
            id(0),
            totalDuration(0),
            probability(0.0f),
            objectGroup(nullptr),
            image(nullptr),
            properties(nullptr) {}

    Tile::Tile(int id) :
            isAnimated(false),
            hasObjects(false),
            hasObjectGroup(false),
            id(id),
            totalDuration(0),
            probability(0.0f),
            objectGroup(nullptr),
            image(nullptr),
            properties(nullptr) {}

    Tile::~Tile() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
        if (objectGroup != nullptr) {
            delete objectGroup;
            objectGroup = nullptr;
        }
    }

    void Tile::Parse(tinyxml2::XMLNode const *tileNode, tinytmx::Map const *_map) {
        tinyxml2::XMLElement const *tileElem = tileNode->ToElement();

        // Parse the attributes.
        id = tileElem->IntAttribute("id");

        // Parse the terrain attribute.
        if (tileElem->Attribute("terrain")) {
            char *terrainString = strdup(tileElem->Attribute("terrain"));
            char *token = strtok(terrainString, ",");
            while (token) {
                terrain.emplace_back(strtol(token, nullptr, 10));
                token = strtok(nullptr, ",");
            }
            free(terrainString);
        }

        // Parse the probability value.
        tileElem->QueryAttribute("probability", &probability);

        // Parse tile type if it has one.
        if (tileElem->FindAttribute("type")) {
            type = std::string(tileElem->Attribute("type"));
        }

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = tileNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet(propertiesNode);
        }

        // Parse the animation if there is one.
        tinyxml2::XMLNode const *animationNode = tileNode->FirstChildElement("animation");
        if (animationNode) {
            isAnimated = true;

            tinyxml2::XMLNode const *frameNode = animationNode->FirstChildElement("frame");
            unsigned int durationSum = 0;
            while (frameNode != nullptr) {

                tinyxml2::XMLElement const *frameElement = frameNode->ToElement();

                int const          tileID   = frameElement->IntAttribute("tileid");
                unsigned int const duration = frameElement->UnsignedAttribute("duration");

                frames.emplace_back(tileID, duration);
                durationSum += duration;

                frameNode = frameNode->NextSiblingElement("frame");
            }

            totalDuration = durationSum;
        }

        tinyxml2::XMLNode const *objectGroupNode = tileNode->FirstChildElement("objectgroup");
        if (objectGroupNode) {
            hasObjectGroup = true;
            objectGroup = new ObjectGroup(this, _map, objectGroupNode);
            if (!objectGroup->GetObjects().empty()) { hasObjects = true; }

        }

        tinyxml2::XMLNode const *imageNode = tileNode->FirstChildElement("image");
        if (imageNode) {
            image = new Image(imageNode);
        }

    }
}
