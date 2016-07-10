/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2016 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Tests.hpp"
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Panel.hpp>

TEST_CASE("[Button]")
{
    tgui::Button::Ptr button = std::make_shared<tgui::Button>();
    button->getRenderer()->setFont("resources/DroidSansArmenian.ttf");

    SECTION("Signals")
    {
        REQUIRE_NOTHROW(button->connect("Pressed", [](){}));
        REQUIRE_NOTHROW(button->connect("Pressed", [](sf::String){}));
    }

    SECTION("WidgetType")
    {
        REQUIRE(button->getWidgetType() == "Button");
    }

    SECTION("Position and Size")
    {
        button->setPosition(40, 30);
        button->setSize(150, 100);
        button->getRenderer()->setBorders(2);

        REQUIRE(button->getPosition() == sf::Vector2f(40, 30));
        REQUIRE(button->getSize() == sf::Vector2f(150, 100));
        REQUIRE(button->getFullSize() == button->getSize());
        REQUIRE(button->getWidgetOffset() == sf::Vector2f(0, 0));
    }

    SECTION("Text")
    {
        REQUIRE(button->getText() == "");
        button->setText("SomeText");
        REQUIRE(button->getText() == "SomeText");
    }

    SECTION("TextSize")
    {
        button->setTextSize(25);
        REQUIRE(button->getTextSize() == 25);
    }

    SECTION("Events")
    {
        testClickableWidgetSignals(button);

        button->setPosition(40, 30);
        button->setSize(150, 100);

        SECTION("Pressed signal")
        {
            unsigned int pressedCount = 0;

            button->connect("Pressed", genericCallback, std::ref(pressedCount));

            SECTION("mouse click")
            {
                button->leftMouseReleased(115, 80);
                REQUIRE(pressedCount == 0);

                SECTION("mouse press")
                {
                    button->leftMousePressed(115, 80);
                    REQUIRE(pressedCount == 0);
                }

                button->leftMouseReleased(115, 80);
                REQUIRE(pressedCount == 1);
            }

            SECTION("key pressed")
            {
                sf::Event::KeyEvent keyEvent;
                keyEvent.alt = false;
                keyEvent.control = false;
                keyEvent.shift = false;
                keyEvent.system = false;

                keyEvent.code = sf::Keyboard::Space;
                button->keyPressed(keyEvent);
                REQUIRE(pressedCount == 1);

                keyEvent.code = sf::Keyboard::Return;
                button->keyPressed(keyEvent);
                REQUIRE(pressedCount == 2);
            }
        }
    }

    SECTION("Renderer")
    {
        auto renderer = button->getRenderer();

        SECTION("colored")
        {
            SECTION("set serialized property")
            {
                REQUIRE_NOTHROW(renderer->setProperty("TextColor", "rgb(20, 30, 40)"));
                REQUIRE_NOTHROW(renderer->setProperty("TextColorHover", "rgb(30, 40, 50)"));
                REQUIRE_NOTHROW(renderer->setProperty("TextColorDown", "rgb(40, 50, 60)"));
                REQUIRE_NOTHROW(renderer->setProperty("TextColorDisabled", "rgb(90, 100, 110)"));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColor", "rgb(50, 60, 70)"));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColorHover", "rgb(60, 70, 80)"));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColorDown", "rgb(70, 80, 90)"));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColorDisabled", "rgb(100, 110, 120)"));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColor", "rgb(80, 90, 100)"));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColorHover", "rgb(110, 120, 130)"));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColorDown", "rgb(120, 130, 140)"));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColorDisabled", "rgb(130, 140, 150)"));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyle", "Italic"));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyleHover", "Underlined"));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyleDown", "Bold | Underlined"));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyleDisabled", "StrikeThrough"));
                REQUIRE_NOTHROW(renderer->setProperty("Borders", "(1, 2, 3, 4)"));
                REQUIRE_NOTHROW(renderer->setProperty("Opacity", "0.8"));
                REQUIRE_NOTHROW(renderer->setProperty("Font", "resources/DroidSansArmenian.ttf"));
            }

            SECTION("set object property")
            {
                REQUIRE_NOTHROW(renderer->setProperty("TextColor", sf::Color{20, 30, 40}));
                REQUIRE_NOTHROW(renderer->setProperty("TextColorHover", sf::Color{30, 40, 50}));
                REQUIRE_NOTHROW(renderer->setProperty("TextColorDown", sf::Color{40, 50, 60}));
                REQUIRE_NOTHROW(renderer->setProperty("TextColorDisabled", sf::Color{90, 100, 110}));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColor", sf::Color{50, 60, 70}));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColorHover", sf::Color{60, 70, 80}));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColorDown", sf::Color{70, 80, 90}));
                REQUIRE_NOTHROW(renderer->setProperty("BackgroundColorDisabled", sf::Color{100, 110, 120}));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColor", sf::Color{80, 90, 100}));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColorHover", sf::Color{110, 120, 130}));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColorDown", sf::Color{120, 130, 140}));
                REQUIRE_NOTHROW(renderer->setProperty("BorderColorDisabled", sf::Color{130, 140, 150}));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyle", sf::Text::Italic));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyleHover", sf::Text::Underlined));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyleDown", sf::Text::Bold | sf::Text::Underlined));
                REQUIRE_NOTHROW(renderer->setProperty("TextStyleDisabled", sf::Text::StrikeThrough));
                REQUIRE_NOTHROW(renderer->setProperty("Borders", tgui::Borders{1, 2, 3, 4}));
                REQUIRE_NOTHROW(renderer->setProperty("Opacity", 0.8f));
                REQUIRE_NOTHROW(renderer->setProperty("Font", tgui::Font{"resources/DroidSansArmenian.ttf"}));
            }

            SECTION("functions")
            {
                renderer->setTextColor({20, 30, 40});
                renderer->setTextColorHover({30, 40, 50});
                renderer->setTextColorDown({40, 50, 60});
                renderer->setTextColorDisabled({90, 100, 110});
                renderer->setBackgroundColor({50, 60, 70});
                renderer->setBackgroundColorHover({60, 70, 80});
                renderer->setBackgroundColorDown({70, 80, 90});
                renderer->setBackgroundColorDisabled({100, 110, 120});
                renderer->setBorderColor({80, 90, 100});
                renderer->setBorderColorHover({110, 120, 130});
                renderer->setBorderColorDown({120, 130, 140});
                renderer->setBorderColorDisabled({130, 140, 150});
                renderer->setTextStyle(sf::Text::Italic);
                renderer->setTextStyleHover(sf::Text::Underlined);
                renderer->setTextStyleDown(sf::Text::Bold | sf::Text::Underlined);
                renderer->setTextStyleDisabled(sf::Text::StrikeThrough);
                renderer->setBorders({1, 2, 3, 4});
                renderer->setOpacity(0.8f);
                renderer->setFont({"resources/DroidSansArmenian.ttf"});
            }

            REQUIRE(renderer->getProperty("TextColor").getColor() == sf::Color(20, 30, 40));
            REQUIRE(renderer->getProperty("TextColorHover").getColor() == sf::Color(30, 40, 50));
            REQUIRE(renderer->getProperty("TextColorDown").getColor() == sf::Color(40, 50, 60));
            REQUIRE(renderer->getProperty("BackgroundColor").getColor() == sf::Color(50, 60, 70));
            REQUIRE(renderer->getProperty("BackgroundColorHover").getColor() == sf::Color(60, 70, 80));
            REQUIRE(renderer->getProperty("BackgroundColorDown").getColor() == sf::Color(70, 80, 90));
            REQUIRE(renderer->getProperty("BorderColor").getColor() == sf::Color(80, 90, 100));
            REQUIRE(renderer->getProperty("Borders").getOutline() == tgui::Borders(1, 2, 3, 4));
            REQUIRE(renderer->getProperty("Opacity").getNumber() == 0.8f);
            REQUIRE(renderer->getProperty("Font").getFont() != nullptr);

            REQUIRE(renderer->getTextColor() == sf::Color(20, 30, 40));
            REQUIRE(renderer->getTextColorHover() == sf::Color(30, 40, 50));
            REQUIRE(renderer->getTextColorDown() == sf::Color(40, 50, 60));
            REQUIRE(renderer->getBackgroundColor() == sf::Color(50, 60, 70));
            REQUIRE(renderer->getBackgroundColorHover() == sf::Color(60, 70, 80));
            REQUIRE(renderer->getBackgroundColorDown() == sf::Color(70, 80, 90));
            REQUIRE(renderer->getBorderColor() == sf::Color(80, 90, 100));
            REQUIRE(renderer->getBorders() == tgui::Borders(1, 2, 3, 4));
            REQUIRE(renderer->getOpacity() == 0.8f);
            REQUIRE(renderer->getFont().getId() == "resources/DroidSansArmenian.ttf");
        }

        SECTION("textured")
        {
            tgui::Texture textureNormal("resources/Black.png", {0, 64, 45, 50}, {10, 0, 25, 50});
            tgui::Texture textureHover("resources/Black.png", {45, 64, 45, 50}, {10, 0, 25, 50});
            tgui::Texture textureDown("resources/Black.png", {90, 64, 45, 50}, {10, 0, 25, 50});
            tgui::Texture textureDisabled("resources/Black.png", {0, 64, 45, 50}, {10, 0, 25, 50});
            tgui::Texture textureFocused("resources/Black.png", {0, 64, 45, 50}, {10, 0, 25, 50});

            SECTION("set serialized property")
            {
                REQUIRE_NOTHROW(renderer->setProperty("Texture", tgui::Serializer::serialize(textureNormal)));
                REQUIRE_NOTHROW(renderer->setProperty("TextureHover", tgui::Serializer::serialize(textureHover)));
                REQUIRE_NOTHROW(renderer->setProperty("TextureDown", tgui::Serializer::serialize(textureDown)));
                REQUIRE_NOTHROW(renderer->setProperty("TextureDisabled", tgui::Serializer::serialize(textureDisabled)));
                REQUIRE_NOTHROW(renderer->setProperty("TextureFocused", tgui::Serializer::serialize(textureFocused)));
            }

            SECTION("set object property")
            {
                REQUIRE_NOTHROW(renderer->setProperty("Texture", textureNormal));
                REQUIRE_NOTHROW(renderer->setProperty("TextureHover", textureHover));
                REQUIRE_NOTHROW(renderer->setProperty("TextureDown", textureDown));
                REQUIRE_NOTHROW(renderer->setProperty("TextureDisabled", textureDisabled));
                REQUIRE_NOTHROW(renderer->setProperty("TextureFocused", textureFocused));
            }

            SECTION("functions")
            {
                renderer->setTexture(textureNormal);
                renderer->setTextureHover(textureHover);
                renderer->setTextureDown(textureDown);
                renderer->setTextureDisabled(textureDisabled);
                renderer->setTextureFocused(textureFocused);
            }

            REQUIRE(renderer->getProperty("Texture").getTexture().isLoaded());
            REQUIRE(renderer->getProperty("TextureHover").getTexture().isLoaded());
            REQUIRE(renderer->getProperty("TextureDown").getTexture().isLoaded());
            REQUIRE(renderer->getProperty("TextureDisabled").getTexture().isLoaded());
            REQUIRE(renderer->getProperty("TextureFocused").getTexture().isLoaded());

            REQUIRE(renderer->getTexture().getData() == textureNormal.getData());
            REQUIRE(renderer->getTextureHover().getData() == textureHover.getData());
            REQUIRE(renderer->getTextureDown().getData() == textureDown.getData());
            REQUIRE(renderer->getTextureDisabled().getData() == textureDisabled.getData());
            REQUIRE(renderer->getTextureFocused().getData() == textureFocused.getData());
        }

        REQUIRE_THROWS_AS(renderer->setProperty("NonexistentProperty", ""), tgui::Exception);
    }

    SECTION("Saving and loading from file")
    {
        tgui::Theme theme{"resources/Black.txt"};
        button->setRenderer(theme.getRenderer("button"));

        auto parent = std::make_shared<tgui::GuiContainer>();
        parent->add(button);

        button->setText("SomeText");
        button->setTextSize(25);

        REQUIRE_NOTHROW(parent->saveWidgetsToFile("WidgetFileButton1.txt"));
        
        parent->removeAllWidgets();
        REQUIRE_NOTHROW(parent->loadWidgetsFromFile("WidgetFileButton1.txt"));

        REQUIRE_NOTHROW(parent->saveWidgetsToFile("WidgetFileButton2.txt"));
        REQUIRE(compareFiles("WidgetFileButton1.txt", "WidgetFileButton2.txt"));

        SECTION("Copying widget")
        {
            copy(parent, button);

            REQUIRE_NOTHROW(parent->saveWidgetsToFile("WidgetFileButton2.txt"));
            REQUIRE(compareFiles("WidgetFileButton1.txt", "WidgetFileButton2.txt"));
        }
    }
}
