/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_CHILD_WINDOW_HPP
#define TGUI_CHILD_WINDOW_HPP


#include <TGUI/Container.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Label.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class ChildWindowRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Child window widget
    ///
    /// Signals:
    ///     - MousePressed (left mouse button went down on top of the child window and the window was in front of other widgets)
    ///         * Optional parameter sf::Vector2f: Position of the mouse relative to the position of the child window
    ///         * Uses Callback member 'mouse'
    ///
    ///     - Closed (Child window was closed)
    ///         * Optional parameter ChildWindow::Ptr: shared pointer to the closed child window
    ///
    ///     - Inherited signals from Container
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ChildWindow : public Container
    {
    public:

        typedef std::shared_ptr<ChildWindow> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const ChildWindow> ConstPtr; ///< Shared constant widget pointer


        /// Title alignments, possible options for the setTitleAlignment function
        enum class TitleAlignment
        {
            Left,   ///< Places the title on the left side of the title bar
            Center, ///< Places the title in the middle of the title bar
            Right   ///< Places the title on the right side of the title bar
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChildWindow();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another child window
        ///
        /// @param childWindow  The other child window
        ///
        /// @return The new child window
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ChildWindow::Ptr copy(ChildWindow::ConstPtr childWindow);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<ChildWindowRenderer> getRenderer() const
        {
            return std::static_pointer_cast<ChildWindowRenderer>(m_renderer);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPosition(const Layout2d& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the child window.
        ///
        /// @param size   Sets the new size of the child window
        ///
        /// This is the size of the child window, without the title bar nor the borders.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the full child window.
        ///
        /// @return Size of the child window
        ///
        /// The size returned by this function is the size of the child window, including the title bar and the borders.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the global font.
        ///
        /// This font will be used by all widgets that are created after calling this function.
        ///
        /// @param filename  Path of the font file to load
        ///
        /// @throw Exception when loading fails
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setGlobalFont(const std::string& filename) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the global font.
        ///
        /// This font will be used by all widgets that are created after calling this function.
        ///
        /// @param font  Font to use
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setGlobalFont(std::shared_ptr<sf::Font> font) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the opacity of the widget.
        ///
        /// @param opacity  The opacity of the widget. 0 means completely transparent, while 1 (default) means fully opaque.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setOpacity(float opacity) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the title that is displayed in the title bar of the child window.
        ///
        /// @param title  New title for the child window
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitle(const sf::String& title);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the title that is displayed in the title bar of the child window.
        ///
        /// @return Title of the child window
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::String& getTitle() const
        {
            return m_titleText.getText();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the title alignment.
        ///
        /// @param alignment  How should the title be aligned in the title bar?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitleAlignment(TitleAlignment alignment);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the title alignment.
        ///
        /// @return How the title is aligned in the title bar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TitleAlignment getTitleAlignment() const
        {
            return m_titleAlignment;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the icon in the top left corner of the child window.
        ///
        /// @param icon  the icon image
        ///
        /// There is no icon by default.
        /// Set an empty texture to remove the icon.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setIcon(const Texture& icon);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the icon in the top left corner of the child window.
        ///
        /// @return the icon image
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const Texture& getIcon();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys the window.
        ///
        /// When no callback is requested when closing the window, this function will be called automatically.
        ///
        /// When you requested a callback then you get the opportunity to cancel the closing of the window.
        /// If you want to keep it open then don't do anything, if you want to close it then just call this function.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void destroy();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the child window to be kept inside its parent.
        ///
        /// @param enabled  When it's set to true, the child window will always be kept automatically inside its parent.
        ///                 It will be fully kept on left, right and top.
        ///                 At the bottom of the parent only the title bar will be kept inside.
        ///                 It's set to false by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keepInParent(bool enabled = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Tells whether the child window is kept inside its parent.
        ///
        /// @return  When it's set to true, the child window will always be kept automatically inside its parent.
        ///          It will be fully kept on left, right and top.
        ///          At the bottom of the parent only the title bar will be kept inside.
        ///          It's set to false by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isKeptInParent() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the close button
        ///
        /// @return closeButton  The new close button
        ///
        /// The close button should have no parent and you should not longer change it after calling this function.
        /// The function is meant to be used like this:
        /// @code
        /// childWindow->setCloseButton(theme->load("CloseButton"));
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCloseButton(Button::Ptr closeButton);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the close button
        ///
        /// @return close button of the child window
        ///
        /// You should not change this close button yourself.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Button::Ptr getCloseButton() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the position of the container and a widget that would be drawn inside
        ///        this container on relative position (0,0).
        ///
        /// @return Offset of the widgets in the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getWidgetsOffset() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Reload the widget
        ///
        /// @param primary    Primary parameter for the loader
        /// @param secondary  Secondary parameter for the loader
        /// @param force      Try to only change the looks of the widget and not alter the widget itself when false
        ///
        /// @throw Exception when the connected theme could not create the widget
        ///
        /// When primary is an empty string the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<ChildWindow>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Texture        m_iconTexture;

        Label          m_titleText;
        sf::Vector2f   m_draggingPosition;
        TitleAlignment m_titleAlignment = TitleAlignment::Center;

        std::shared_ptr<Button> m_closeButton = std::make_shared<Button>();

        bool m_mouseDownOnTitleBar = false;
        bool m_keepInParent = false;

        friend class ChildWindowRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ChildWindowRenderer : public WidgetRenderer, public WidgetBorders
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param childWindow  The child window that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChildWindowRenderer(ChildWindow* childWindow) : m_childWindow{childWindow} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change a property of the renderer
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new serialized value that you like to assign to the property
        ///
        /// @throw Exception when deserialization fails or when the widget does not have this property.
        /// @throw Exception when loading scrollbar fails with the theme connected to the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change a property of the renderer
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property.
        ///                  The ObjectConverter is implicitly constructed from the possible value types.
        ///
        /// @throw Exception for unknown properties or when value was of a wrong type.
        /// @throw Exception when loading scrollbar fails with the theme connected to the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, ObjectConverter&& value) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve the value of a certain property
        ///
        /// @param property  The property that you would like to retrieve
        ///
        /// @return The value inside a ObjectConverter object which you can extract with the correct get function or
        ///         an ObjectConverter object with type ObjectConverter::Type::None when the property did not exist.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ObjectConverter getProperty(std::string property) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get a map with all properties and their values
        ///
        /// @return Property-value pairs of the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::map<std::string, ObjectConverter> getPropertyValuePairs() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the title bar
        ///
        /// @param color  New title bar color
        ///
        /// Note that this color is ignored when you set an image as title bar.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitleBarColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the height of the title bar.
        ///
        /// @param height  New height of the title bar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitleBarHeight(float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the title that is displayed in the title bar of the child window.
        ///
        /// @param color  New title color for the child window
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitleColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the border color.
        ///
        /// @param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the borders.
        ///
        /// @param borders  The size of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(const Borders& borders) override;
        using WidgetBorders::setBorders;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the distance between the title and the side of the title bar.
        ///
        /// @param distanceToSide  distance between the title and the side of the title bar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDistanceToSide(float distanceToSide);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color of the child window.
        ///
        /// @param backgroundColor  New background color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image of the title bar
        ///
        /// @param texture  New title bar texture
        ///
        /// When this image is set, the title bar color property will be ignored.
        /// Pass an empty string to unset the image, in this case the title bar color property will be used again.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitleBarTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer of the close button
        ///
        /// @return The close button renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<ButtonRenderer> getCloseButton() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ChildWindowRenderer(const ChildWindowRenderer&) = default;
        ChildWindowRenderer& operator=(const ChildWindowRenderer&) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        ChildWindow* m_childWindow;

        float        m_titleBarHeight;
        float        m_distanceToSide;

        Texture      m_textureTitleBar;

        sf::Color    m_titleColor;
        sf::Color    m_titleBarColor;

        sf::Color    m_backgroundColor;
        sf::Color    m_borderColor;

        friend class ChildWindow;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CHILD_WINDOW_HPP
