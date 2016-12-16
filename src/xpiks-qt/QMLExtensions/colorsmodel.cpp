/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2016 Taras Kushnir <kushnirTV@gmail.com>
 *
 * Xpiks is distributed under the GNU General Public License, version 3.0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "colorsmodel.h"
#include <QJsonObject>
#include <QVector>
#include <QString>
#include <QHash>

#include <unordered_map>

#include "../Common/defines.h"


#define DEFAULT_DARK_COLOR "defaultDarkColor"
#define DEFAULT_DARKER_COLOR "defaultDarkerColor"
#define DEFAULT_CONTROL_COLOR "defaultControlColor"
#define INACTIVE_CONTROL_COLOR "inactiveControlColor"
#define WHITE_COLOR "whiteColor"

#define INPUT_BACKGROUND "inputBackgroundColor"
#define INPUT_INACTIVE_BACKGROUND "inputInactiveBackground"
#define INPUT_FOREGROUND "inputForegroundColor"
#define INPUT_INACTIVE_FOREGROUND "inputInactiveForeground"
#define LABEL_ACTIVE_FOREGROUND "labelActiveForeground"
#define LABEL_INACTIVE_FOREGROUND "labelInactiveForeground"

#define ARTWORK_BACKGROUND "artworkBackground"
#define ARTWORK_IMAGE_BACKGROUND "artworkImageBackground"
#define ARTWORK_MODIFIED_COLOR "artworkModifiedColor"
#define ARTWORK_SAVED_COLOR "artworkSavedColor"
#define ARTWORK_ACTIVE_COLOR "artworkActiveColor"

#define LIST_SEPARATOR_COLOR "listSeparatorColor"
#define LIGHT_COLOR "defaultLightColor"
#define LIGHT_GRAY_COLOR "defaultLightGrayColor"

#define BUTTON_HOVER_BACKGROUND "buttonHoverBackground"
#define BUTTON_PRESSED_BACKGROUND "buttonPressedBackground"
#define BUTTON_PRESSED_FOREGROUND "buttonPressedForeground"
#define BUTTON_DISABLED_FOREGROUND "buttonDisabledForeground"

#define LINK_CLICKED_COLOR "linkClickedColor"

#define SELECTED_IMAGE_BACKGROUND "selectedImageBackground"
#define SELECTED_ARTWORK_BACKGROUND "selectedArtworkBackground"
#define CHECKBOX_CHECKED_COLOR "checkboxCheckedColor"

#define ITEMS_SOURCE_BACKGROUND "itemsSourceBackground"
#define ITEMS_SOURCE_SELECTED "itemsSourceSelected"
#define ITEMS_SOURCE_FOREGROUND "itemsSourceForeground"

#define DESTRUCTIVE_COLOR "destructiveColor"
#define GREEN_COLOR "greenColor"

#define STATUS_BAR_COLOR "statusBarColor"
#define LEFT_SLIDER_COLOR "leftSliderColor"
#define POPUP_BACKGROUND_COLOR "popupBackgroundColor"

typedef std::unordered_map<std::string, std::string> ColorsMap;

ColorsMap createBlackTheme() {
    ColorsMap BlackTheme;

    BlackTheme["name"] = "black";

    BlackTheme[DEFAULT_DARK_COLOR] = "#1e1e1e";
    BlackTheme[DEFAULT_DARKER_COLOR] = "#333333";
    BlackTheme[DEFAULT_CONTROL_COLOR] = "#292929";
    BlackTheme[INACTIVE_CONTROL_COLOR] = "#404040";
    BlackTheme[WHITE_COLOR] = "#ffffff";

    BlackTheme[LABEL_ACTIVE_FOREGROUND] = "#c9c9c9";
    BlackTheme[LABEL_INACTIVE_FOREGROUND] = "#939393";
    BlackTheme[INPUT_BACKGROUND] = "#5d5d5d";
    BlackTheme[INPUT_INACTIVE_BACKGROUND] = "#242424";
    BlackTheme[INPUT_FOREGROUND] = BlackTheme[WHITE_COLOR];
    BlackTheme[INPUT_INACTIVE_FOREGROUND] = BlackTheme[LABEL_ACTIVE_FOREGROUND];

    BlackTheme[ARTWORK_BACKGROUND] = "#181818";
    BlackTheme[ARTWORK_IMAGE_BACKGROUND] = "#071215";
    BlackTheme[ARTWORK_MODIFIED_COLOR] = "#f49c12";
    BlackTheme[ARTWORK_SAVED_COLOR] = "#435151";
    BlackTheme[ARTWORK_ACTIVE_COLOR] = "#12b9bc";

    BlackTheme[LIGHT_COLOR] = BlackTheme[INPUT_INACTIVE_FOREGROUND];
    BlackTheme[LIGHT_GRAY_COLOR] = "#D0D0D0";
    BlackTheme[LIST_SEPARATOR_COLOR] = BlackTheme[LABEL_ACTIVE_FOREGROUND];

    BlackTheme[BUTTON_HOVER_BACKGROUND] = BlackTheme[ARTWORK_ACTIVE_COLOR];
    BlackTheme[BUTTON_PRESSED_BACKGROUND] = BlackTheme[DEFAULT_CONTROL_COLOR];
    BlackTheme[BUTTON_PRESSED_FOREGROUND] = BlackTheme[WHITE_COLOR];
    BlackTheme[BUTTON_DISABLED_FOREGROUND] = BlackTheme[INPUT_BACKGROUND];

    BlackTheme[LINK_CLICKED_COLOR] = BlackTheme[WHITE_COLOR];

    BlackTheme[SELECTED_IMAGE_BACKGROUND] = BlackTheme[LABEL_INACTIVE_FOREGROUND];
    BlackTheme[SELECTED_ARTWORK_BACKGROUND] = "#404040";
    BlackTheme[CHECKBOX_CHECKED_COLOR] = "#ffffff";

    BlackTheme[ITEMS_SOURCE_BACKGROUND] = BlackTheme[SELECTED_ARTWORK_BACKGROUND];
    BlackTheme[ITEMS_SOURCE_SELECTED] = BlackTheme[SELECTED_IMAGE_BACKGROUND];
    BlackTheme[ITEMS_SOURCE_FOREGROUND] = BlackTheme[INPUT_INACTIVE_FOREGROUND];

    BlackTheme[DESTRUCTIVE_COLOR] = "#e81313";
    BlackTheme[GREEN_COLOR] = "#2daf02";

    BlackTheme[STATUS_BAR_COLOR] = "#121212";
    BlackTheme[LEFT_SLIDER_COLOR] = BlackTheme[ARTWORK_BACKGROUND];
    BlackTheme[POPUP_BACKGROUND_COLOR] = BlackTheme[DEFAULT_CONTROL_COLOR];

    return BlackTheme;
}

ColorsMap createSlateGrayTheme() {
    ColorsMap SlateGrayTheme;

    SlateGrayTheme["name"] = "slate gray";

    SlateGrayTheme[DEFAULT_DARK_COLOR] = "#22252c";
    SlateGrayTheme[DEFAULT_DARKER_COLOR] = "#373a42";
    SlateGrayTheme[DEFAULT_CONTROL_COLOR] = "#30333b";
    SlateGrayTheme[WHITE_COLOR] = "#ffffff";

    SlateGrayTheme[INPUT_BACKGROUND] = "#7a7e86";
    SlateGrayTheme[INPUT_INACTIVE_BACKGROUND] = SlateGrayTheme[DEFAULT_CONTROL_COLOR];
    SlateGrayTheme[INPUT_FOREGROUND] = "#c7ccd3";
    SlateGrayTheme[INPUT_INACTIVE_FOREGROUND] = SlateGrayTheme[INPUT_BACKGROUND];
    SlateGrayTheme[LABEL_INACTIVE_FOREGROUND] = "#474b54";
    SlateGrayTheme[LABEL_ACTIVE_FOREGROUND] = SlateGrayTheme[INPUT_BACKGROUND];

    SlateGrayTheme[ARTWORK_BACKGROUND] = SlateGrayTheme[DEFAULT_DARK_COLOR];
    SlateGrayTheme[ARTWORK_IMAGE_BACKGROUND] = "#1c2025";
    SlateGrayTheme[ARTWORK_MODIFIED_COLOR] = "#f49c12";
    SlateGrayTheme[ARTWORK_SAVED_COLOR] = SlateGrayTheme[INPUT_BACKGROUND];
    SlateGrayTheme[ARTWORK_ACTIVE_COLOR] = "#2ec1c3";

    SlateGrayTheme[LIGHT_COLOR] = "#E0E0E0";
    SlateGrayTheme[LIGHT_GRAY_COLOR] = "#D0D0D0";
    SlateGrayTheme[LIST_SEPARATOR_COLOR] = SlateGrayTheme[LIGHT_COLOR];

    SlateGrayTheme[BUTTON_HOVER_BACKGROUND] = "#12b9bc";
    SlateGrayTheme[BUTTON_PRESSED_BACKGROUND] = "#41b1b7";
    SlateGrayTheme[BUTTON_DISABLED_FOREGROUND] = "#283c3f";
    SlateGrayTheme[BUTTON_PRESSED_FOREGROUND] = "#283c3f";

    SlateGrayTheme[LINK_CLICKED_COLOR] = SlateGrayTheme[INPUT_FOREGROUND];

    SlateGrayTheme[SELECTED_IMAGE_BACKGROUND] = "#3e434d";
    SlateGrayTheme[SELECTED_ARTWORK_BACKGROUND] = "#474b54";
    SlateGrayTheme[CHECKBOX_CHECKED_COLOR] = "#ffffff";

    SlateGrayTheme[ITEMS_SOURCE_BACKGROUND] = SlateGrayTheme[SELECTED_IMAGE_BACKGROUND];
    SlateGrayTheme[ITEMS_SOURCE_SELECTED] = SlateGrayTheme[ITEMS_SOURCE_BACKGROUND];
    SlateGrayTheme[ITEMS_SOURCE_FOREGROUND] = SlateGrayTheme[INPUT_FOREGROUND];

    SlateGrayTheme[DESTRUCTIVE_COLOR] = "#A81A1A";
    SlateGrayTheme[GREEN_COLOR] = "#2daf02";

    SlateGrayTheme[STATUS_BAR_COLOR] = SlateGrayTheme[ARTWORK_IMAGE_BACKGROUND];
    SlateGrayTheme[LEFT_SLIDER_COLOR] = SlateGrayTheme[ARTWORK_IMAGE_BACKGROUND];
    SlateGrayTheme[POPUP_BACKGROUND_COLOR] = SlateGrayTheme[DEFAULT_CONTROL_COLOR];

    return SlateGrayTheme;
}

namespace QMLExtensions {
    class HashMapColorsProvider: public ColorsProvider {
    public:
        HashMapColorsProvider(const ColorsMap &map):
            m_ColorsMap(map)
        {}

    public:
        virtual bool tryGetColor(const std::string &colorName, QColor &color) const {
            auto it = m_ColorsMap.find(colorName);
            bool contains = it != m_ColorsMap.end();
            if (contains) {
                color = QColor(QString::fromStdString(it->second));
            }

            return contains;
        }

        virtual QString getThemeName() const {
            auto it = m_ColorsMap.find("name");
            if (it != m_ColorsMap.end()) {
                return QString::fromStdString(it->second);
            } else {
                return QLatin1String("unknown");
            }
        }

    private:
        ColorsMap m_ColorsMap;
    };

    ColorsModel::ColorsModel(QObject *parent) : QObject(parent)
    {
        registerTheme(std::shared_ptr<ColorsProvider>(new HashMapColorsProvider(createBlackTheme())));
        registerTheme(std::shared_ptr<ColorsProvider>(new HashMapColorsProvider(createSlateGrayTheme())));
        applyTheme(0);
    }

    const std::shared_ptr<ColorsProvider> &ColorsModel::getFallbackTheme() {
        return m_RegisteredThemes.at(0);
    }

    QColor ColorsModel::getColor(const std::string &colorName, const std::shared_ptr<ColorsProvider> &theme,
                                 const std::shared_ptr<ColorsProvider> &fallbackTheme) {
        QColor result;
        if (!theme->tryGetColor(colorName, result)) {
            if (!fallbackTheme->tryGetColor(colorName, result)) {
                result = QColor("#000000");
            }
        }

        return result;
    }

    void ColorsModel::registerTheme(const std::shared_ptr<ColorsProvider> &provider) {
        QString themeName = provider->getThemeName();
        LOG_DEBUG << themeName;
        m_RegisteredThemes.push_back(provider);
        m_ThemeNames.append(themeName);
    }

    bool ColorsModel::applyTheme(int index) {
        LOG_INFO << index << "out of" << m_RegisteredThemes.size();
        if (index < 0 || index >= (int)m_RegisteredThemes.size()) { return false; }

        auto &theme = m_RegisteredThemes[index];
        auto &fallback = getFallbackTheme();

        setDefaultDarkColor(getColor(DEFAULT_DARK_COLOR, theme, fallback));
        setDefaultDarkerColor(getColor(DEFAULT_DARKER_COLOR, theme, fallback));
        setDefaultControlColor(getColor(DEFAULT_CONTROL_COLOR,theme, fallback));
        setInactiveControlColor(getColor(INACTIVE_CONTROL_COLOR, theme, fallback));
        setWhiteColor(getColor(WHITE_COLOR, theme, fallback));

        setInputBackgroundColor(getColor(INPUT_BACKGROUND, theme, fallback));
        setInputInactiveBackground(getColor(INPUT_INACTIVE_BACKGROUND, theme, fallback));
        setInputForegroundColor(getColor(INPUT_FOREGROUND, theme, fallback));
        setInputInactiveForeground(getColor(INPUT_INACTIVE_FOREGROUND, theme, fallback));
        setLabelActiveForeground(getColor(LABEL_ACTIVE_FOREGROUND, theme, fallback));
        setLabelInactiveForeground(getColor(LABEL_INACTIVE_FOREGROUND, theme, fallback));

        setArtworkBackground(getColor(ARTWORK_BACKGROUND, theme, fallback));
        setArtworkImageBackground(getColor(ARTWORK_IMAGE_BACKGROUND, theme, fallback));
        setArtworkModifiedColor(getColor(ARTWORK_MODIFIED_COLOR, theme, fallback));
        setArtworkSavedColor(getColor(ARTWORK_SAVED_COLOR, theme, fallback));
        setArtworkActiveColor(getColor(ARTWORK_ACTIVE_COLOR, theme, fallback));

        setDefaultLightColor(getColor(LIGHT_COLOR, theme, fallback));
        setDefaultLightGrayColor(getColor(LIGHT_GRAY_COLOR, theme, fallback));
        setListSeparatorColor(getColor(LIST_SEPARATOR_COLOR, theme, fallback));

        setButtonHoverBackground(getColor(BUTTON_HOVER_BACKGROUND, theme, fallback));
        setButtonPressedBackground(getColor(BUTTON_PRESSED_BACKGROUND, theme, fallback));
        setButtonPressedForeground(getColor(BUTTON_PRESSED_FOREGROUND, theme, fallback));
        setButtonDisabledForeground(getColor(BUTTON_DISABLED_FOREGROUND, theme, fallback));

        setLinkClickedColor(getColor(LINK_CLICKED_COLOR, theme, fallback));

        setSelectedImageBackground(getColor(SELECTED_IMAGE_BACKGROUND, theme, fallback));
        setSelectedArtworkBackground(getColor(SELECTED_ARTWORK_BACKGROUND, theme, fallback));
        setCheckboxCheckedColor(getColor(CHECKBOX_CHECKED_COLOR, theme, fallback));

        setItemsSourceBackground(getColor(ITEMS_SOURCE_BACKGROUND, theme, fallback));
        setItemsSourceSelected(getColor(ITEMS_SOURCE_SELECTED, theme, fallback));
        setItemsSourceForeground(getColor(ITEMS_SOURCE_FOREGROUND, theme, fallback));

        setDestructiveColor(getColor(DESTRUCTIVE_COLOR, theme, fallback));
        setGreenColor(getColor(GREEN_COLOR, theme, fallback));

        setStatusBarColor(getColor(STATUS_BAR_COLOR, theme, fallback));
        setLeftSliderColor(getColor(LEFT_SLIDER_COLOR, theme, fallback));
        setPopupBackgroundColor(getColor(POPUP_BACKGROUND_COLOR, theme, fallback));

        emit themeChanged();

        return true;
    }
}
