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

#include "settingsmodel.h"
#include <QQmlEngine>
#include "../Helpers/appsettings.h"
#include "../Common/defines.h"
#include "../Commands/commandmanager.h"

#ifdef Q_OS_MAC
#define DEFAULT_EXIFTOOL "/usr/bin/exiftool"
#else
#define DEFAULT_EXIFTOOL "exiftool"
#endif

#define DEFAULT_DICT_PATH ""
#define DEFAULT_MAX_KEYWORDS 50
#define DEFAULT_MAX_DESCRIPTION 200
#define DEFAULT_MIN_MEGAPIXELS 4.0
#define DEFAULT_USE_MASTERPASSWORD false
#define DEFAULT_UPLOAD_TIMEOUT 10
#define DEFAULT_USE_CONFIRMATIONS false
#define DEFAULT_SAVE_BACKUPS true
#define DEFAULT_KEYWORD_SIZE_SCALE 1.0
#define DEFAULT_DISMISS_DURATION 10
#define DEFAULT_MAX_PARALLEL_UPLOADS 2
#define DEFAULT_FIT_SMALL_PREVIEW false
#define DEFAULT_SEARCH_USING_AND true
#define DEFAULT_SCROLL_SPEED_SCALE 1.0
#define DEFAULT_USE_SPELL_CHECK true
#define DEFAULT_HAVE_USER_CONSENT false
#define DEFAULT_COLLECT_USER_STATISTICS true
#define DEFAULT_UPDATE_SERVICE true
#define DEFAULT_APP_WIDTH 900
#define DEFAULT_APP_HEIGHT 725
#define DEFAULT_APP_POSITION -1
#define DEFAULT_AUTO_FIND_VECTORS true
#define DEFAULT_LOCALE "en_US"
#define DEFAULT_SELECTED_THEME_INDEX 0
#define DEFAULT_USE_AUTO_COMPLETE true

namespace Models {
    SettingsModel::SettingsModel(QObject *parent) :
        QObject(parent),
        m_ExifToolPath(DEFAULT_EXIFTOOL),
        m_DictPath(DEFAULT_DICT_PATH),
        m_SelectedLocale(DEFAULT_LOCALE),
        m_MinMegapixelCount(DEFAULT_MIN_MEGAPIXELS),
        m_KeywordSizeScale(DEFAULT_KEYWORD_SIZE_SCALE),
        m_ScrollSpeedScale(DEFAULT_SCROLL_SPEED_SCALE),
        m_MaxDescriptionLength(DEFAULT_MAX_DESCRIPTION),
        m_MaxKeywordsCount(DEFAULT_MAX_KEYWORDS),
        m_UploadTimeout(DEFAULT_UPLOAD_TIMEOUT),
        m_DismissDuration(DEFAULT_DISMISS_DURATION),
        m_MaxParallelUploads(DEFAULT_MAX_PARALLEL_UPLOADS),
        m_SelectedThemeIndex(DEFAULT_SELECTED_THEME_INDEX),
        m_MustUseMasterPassword(DEFAULT_USE_MASTERPASSWORD),
        m_MustUseConfirmations(DEFAULT_USE_CONFIRMATIONS),
        m_SaveBackups(DEFAULT_SAVE_BACKUPS),
        m_FitSmallPreview(DEFAULT_FIT_SMALL_PREVIEW),
        m_SearchUsingAnd(DEFAULT_SEARCH_USING_AND),
        m_UseSpellCheck(DEFAULT_USE_SPELL_CHECK),
        m_UserStatistics(DEFAULT_COLLECT_USER_STATISTICS),
        m_CheckForUpdates(DEFAULT_UPDATE_SERVICE),
        m_DictsPathChanged(false),
        m_AutoFindVectors(DEFAULT_AUTO_FIND_VECTORS),
        m_UseAutoComplete(DEFAULT_USE_AUTO_COMPLETE)
    {
    }

    void SettingsModel::saveExiftool() {
        LOG_DEBUG << "#";
        Helpers::AppSettings appSettings;
        appSettings.setValue(appSettings.getExifToolPathKey(), m_ExifToolPath);
    }

    void SettingsModel::saveLocale() {
        LOG_DEBUG << "#";
        Helpers::AppSettings appSettings;
        appSettings.setValue(appSettings.getSelectedLocaleKey(), m_SelectedLocale);
    }

    void SettingsModel::resetAllValues() {
        LOG_DEBUG << "#";
        resetToDefault();
        saveAllValues();
        emit settingsReset();
    }

    void SettingsModel::saveAllValues() {
        LOG_INFO << "#";

        Helpers::AppSettings appSettings;
        appSettings.setValue(appSettings.getExifToolPathKey(), m_ExifToolPath);
        appSettings.setValue(appSettings.getDictionaryPathKey(), m_DictPath);
        appSettings.setValue(appSettings.getMinMegapixelCountKey(), m_MinMegapixelCount);
        appSettings.setValue(appSettings.getMaxDescriptionLengthKey(), m_MaxDescriptionLength);
        appSettings.setValue(appSettings.getMaxKeywordsCountKey(), m_MaxKeywordsCount);
        appSettings.setValue(appSettings.getOneUploadSecondsTimeoutKey(), m_UploadTimeout);
        appSettings.setValue(appSettings.getMustUseMasterPasswordKey(), m_MustUseMasterPassword);
        appSettings.setValue(appSettings.getUseConfirmationDialogsKey(), m_MustUseConfirmations);
        appSettings.setValue(appSettings.getSaveBackupsKey(), m_SaveBackups);
        appSettings.setValue(appSettings.getKeywordSizeScaleKey(), m_KeywordSizeScale);
        appSettings.setValue(appSettings.getDismissDurationKey(), m_DismissDuration);
        appSettings.setValue(appSettings.getMaxParallelUploadsKey(), m_MaxParallelUploads);
        appSettings.setValue(appSettings.getFitSmallPreviewKey(), m_FitSmallPreview);
        appSettings.setValue(appSettings.getSearchUsingAndKey(), m_SearchUsingAnd);
        appSettings.setValue(appSettings.getScrollSpeedScaleKey(), m_ScrollSpeedScale);
        appSettings.setValue(appSettings.getUseSpellCheckKey(), m_UseSpellCheck);
        appSettings.setValue(appSettings.getUserStatisticsKey(), m_UserStatistics);
        appSettings.setValue(appSettings.getUpdateServiceKey(), m_CheckForUpdates);
        appSettings.setValue(appSettings.getAutoFindVectorsKey(), m_AutoFindVectors);
        appSettings.setValue(appSettings.getSelectedThemeIndexKey(), m_SelectedThemeIndex);
        appSettings.setValue(appSettings.getUseAutoCompleteKey(), m_UseAutoComplete);

        if (!m_MustUseMasterPassword) {
            appSettings.setValue(appSettings.getMasterPasswordHashKey(), "");
        }

        emit keywordSizeScaleChanged(m_KeywordSizeScale);

#if defined(Q_OS_LINUX)
        if (m_DictsPathChanged) {
            // TODO: check if need to restart depending on path
            m_CommandManager->restartSpellChecking();
            m_DictsPathChanged = false;
        }
#endif
    }

    void SettingsModel::clearMasterPasswordSettings() {
        setMustUseMasterPassword(false);
        Helpers::AppSettings appSettings;
        appSettings.setValue(appSettings.getMasterPasswordHashKey(), "");
        appSettings.setValue(appSettings.getMustUseMasterPasswordKey(), false);
    }

    void SettingsModel::resetExifTool() {
        setExifToolPath(DEFAULT_EXIFTOOL);
    }

    void SettingsModel::resetDictPath() {
        setDictionaryPath(DEFAULT_DICT_PATH);
    }

    void SettingsModel::readAllValues() {
        LOG_INFO << "#";

        Helpers::AppSettings appSettings;
        setExifToolPath(appSettings.value(appSettings.getExifToolPathKey(), DEFAULT_EXIFTOOL).toString());
        setDictionaryPath(appSettings.value(appSettings.getDictionaryPathKey(), DEFAULT_DICT_PATH).toString());
        setMinMegapixelCount(appSettings.doubleValue(appSettings.getMinMegapixelCountKey(), DEFAULT_MIN_MEGAPIXELS));
        setMaxDescriptionLength(appSettings.value(appSettings.getMaxDescriptionLengthKey(), DEFAULT_MAX_DESCRIPTION).toInt());
        setMaxKeywordsCount(appSettings.value(appSettings.getMaxKeywordsCountKey(), DEFAULT_MAX_KEYWORDS).toInt());
        setUploadTimeout(appSettings.value(appSettings.getOneUploadSecondsTimeoutKey(), DEFAULT_UPLOAD_TIMEOUT).toInt());
        setMustUseMasterPassword(appSettings.boolValue(appSettings.getMustUseMasterPasswordKey(), DEFAULT_USE_MASTERPASSWORD));
        setMustUseConfirmations(appSettings.boolValue(appSettings.getUseConfirmationDialogsKey(), DEFAULT_USE_CONFIRMATIONS));
        setSaveBackups(appSettings.boolValue(appSettings.getSaveBackupsKey(), DEFAULT_SAVE_BACKUPS));
        setKeywordSizeScale(appSettings.doubleValue(appSettings.getKeywordSizeScaleKey(), DEFAULT_KEYWORD_SIZE_SCALE));
        setDismissDuration(appSettings.value(appSettings.getDismissDurationKey(), DEFAULT_DISMISS_DURATION).toInt());
        setMaxParallelUploads(appSettings.value(appSettings.getMaxParallelUploadsKey(), DEFAULT_MAX_PARALLEL_UPLOADS).toInt());
        setFitSmallPreview(appSettings.boolValue(appSettings.getFitSmallPreviewKey(), DEFAULT_FIT_SMALL_PREVIEW));
        setSearchUsingAnd(appSettings.boolValue(appSettings.getSearchUsingAndKey(), DEFAULT_SEARCH_USING_AND));
        setScrollSpeedScale(appSettings.doubleValue(appSettings.getScrollSpeedScaleKey(), DEFAULT_SCROLL_SPEED_SCALE));
        setUseSpellCheck(appSettings.boolValue(appSettings.getUseSpellCheckKey(), DEFAULT_USE_SPELL_CHECK));
        setUserStatistics(appSettings.boolValue(appSettings.getUserStatisticsKey(), DEFAULT_COLLECT_USER_STATISTICS));
        setUpdateService(appSettings.boolValue(appSettings.getUpdateServiceKey(), DEFAULT_UPDATE_SERVICE));
        setAutoFindVectors(appSettings.boolValue(appSettings.getAutoFindVectorsKey(), DEFAULT_AUTO_FIND_VECTORS));
        setSelectedLocale(appSettings.value(appSettings.getSelectedLocaleKey(), DEFAULT_LOCALE).toString());
        setSelectedThemeIndex(appSettings.value(appSettings.getSelectedThemeIndexKey(), DEFAULT_SELECTED_THEME_INDEX).toInt());
        setUseAutoComplete(appSettings.boolValue(appSettings.getUseAutoCompleteKey(), DEFAULT_USE_AUTO_COMPLETE));
    }

    void SettingsModel::resetToDefault() {
        LOG_INFO << "#";

        setExifToolPath(DEFAULT_EXIFTOOL);
        setDictionaryPath(DEFAULT_DICT_PATH);
        setMinMegapixelCount(DEFAULT_MIN_MEGAPIXELS);
        setMaxDescriptionLength(DEFAULT_MAX_DESCRIPTION);
        setMaxKeywordsCount(DEFAULT_MAX_KEYWORDS);
        setUploadTimeout(DEFAULT_UPLOAD_TIMEOUT);
        setMustUseMasterPassword(DEFAULT_USE_MASTERPASSWORD);
        setMustUseConfirmations(DEFAULT_USE_CONFIRMATIONS);
        setSaveBackups(DEFAULT_SAVE_BACKUPS);
        setKeywordSizeScale(DEFAULT_KEYWORD_SIZE_SCALE);
        setDismissDuration(DEFAULT_DISMISS_DURATION);
        setMaxParallelUploads(DEFAULT_MAX_PARALLEL_UPLOADS);
        setFitSmallPreview(DEFAULT_FIT_SMALL_PREVIEW);
        setSearchUsingAnd(DEFAULT_SEARCH_USING_AND);
        setScrollSpeedScale(DEFAULT_SCROLL_SPEED_SCALE);
        setUseSpellCheck(DEFAULT_USE_SPELL_CHECK);
        setUserStatistics(DEFAULT_COLLECT_USER_STATISTICS);
        setUpdateService(DEFAULT_UPDATE_SERVICE);
        setAutoFindVectors(DEFAULT_AUTO_FIND_VECTORS);
        setSelectedLocale(DEFAULT_LOCALE);
        setSelectedThemeIndex(DEFAULT_SELECTED_THEME_INDEX);
        setUseAutoComplete(DEFAULT_USE_AUTO_COMPLETE);

        Helpers::AppSettings appSettings;
#if defined(QT_DEBUG)
        appSettings.setValue(appSettings.getUserConsentKey(), DEFAULT_HAVE_USER_CONSENT);
        appSettings.setValue(appSettings.getInstalledVersionKey(), 0);
#endif

        // resetting position in settings is pretty useless because
        // we will overwrite them on Xpiks exit. But anyway for the future...
        appSettings.setValue(appSettings.getAppHeightKey(), DEFAULT_APP_HEIGHT);
        appSettings.setValue(appSettings.getAppWidthKey(), DEFAULT_APP_WIDTH);
        appSettings.setValue(appSettings.getAppPosXKey(), DEFAULT_APP_POSITION);
        appSettings.setValue(appSettings.getAppPosYKey(), DEFAULT_APP_POSITION);
    }

    int ensureInBounds(int value, int boundA, int boundB) {
        Q_ASSERT(boundA <= boundB);

        if (value < boundA) {
            value = boundA;
        }

        if (value > boundB) {
            value = boundB;
        }

        return value;
    }

    double ensureInBounds(double value, double boundA, double boundB) {
        Q_ASSERT(boundA <= boundB);

        // double nan
        if (value != value) {
            value = boundA;
        }

        if (value < boundA) {
            value = boundA;
        }

        if (value > boundB) {
            value = boundB;
        }

        return value;
    }
}

