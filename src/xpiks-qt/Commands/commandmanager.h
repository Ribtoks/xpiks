/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014 Taras Kushnir <kushnirTV@gmail.com>
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

#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QList>
#include "../UndoRedo/historyitem.h"
#include "commandbase.h"

namespace Encryption {
    class SecretsManager;
}

namespace UndoRedo {
    class UndoRedoManager;
}

namespace Models {
    class ArtworksRepository;
    class ArtItemsModel;
    class ArtItemInfo;
    class CombinedArtworksModel;
    class IptcProvider;
    class ArtworkUploader;
    class UploadInfoRepository;
    class WarningsManager;
    class UploadInfo;
    class ArtworkMetadata;
    class ZipArchiver;
}

namespace Commands {
    class CommandManager
    {
    public:
        CommandManager():
            m_ArtworksRepository(NULL),
            m_ArtItemsModel(NULL),
            m_CombinedArtworksModel(NULL),
            m_IptcProvider(NULL),
            m_ArtworkUploader(NULL),
            m_UploadInfoRepository(NULL),
            m_WarningsManager(NULL),
            m_SecretsManager(NULL),
            m_UndoRedoManager(NULL),
            m_ZipArchiver(NULL)
        {}

        virtual ~CommandManager() {}

    public:
        void InjectDependency(Models::ArtworksRepository *artworkRepository);
        void InjectDependency(Models::ArtItemsModel *artItemsModel);
        void InjectDependency(Models::CombinedArtworksModel *combinedArtworksModel);
        void InjectDependency(Models::IptcProvider *iptcProvider);
        void InjectDependency(Models::ArtworkUploader *artworkUploader);
        void InjectDependency(Models::UploadInfoRepository *uploadInfoRepository);
        void InjectDependency(Models::WarningsManager *warningsManager);
        void InjectDependency(Encryption::SecretsManager *secretsManager);
        void InjectDependency(UndoRedo::UndoRedoManager *undoRedoManager);
        void InjectDependency(Models::ZipArchiver *zipArchiver);

    public:
        CommandResult *processCommand(CommandBase *command) const;
        void recordHistoryItem(UndoRedo::HistoryItem *historyItem) const;

    public:
        void connectEntitiesSignalsSlots() const;

    public:
        void recodePasswords(const QString &oldMasterPassword,
                                const QString &newMasterPassword,
                                const QList<Models::UploadInfo*> &uploadInfos) const;

        void combineArtworks(const QList<Models::ArtItemInfo*> &artworks) const;
        void setArtworksForIPTCProcessing(const QList<Models::ArtworkMetadata*> &artworks) const;
        void setArtworksForUpload(const QList<Models::ArtworkMetadata*> &artworks) const;
        void setArtworksForZipping(const QList<Models::ArtworkMetadata*> &artworks) const;
        virtual void connectArtworkSignals(Models::ArtworkMetadata *metadata) const;
        void updateArtworks(const QList<int> &indices) const;

    public:
        // methods for getters
        virtual Models::ArtworksRepository *getArtworksRepository() const { return m_ArtworksRepository; }
        virtual Models::ArtItemsModel *getArtItemsModel() const { return m_ArtItemsModel; }
        virtual const Encryption::SecretsManager *getSecretsManager() const { return m_SecretsManager; }
        virtual const Models::UploadInfoRepository *getUploadInfoRepository() const { return m_UploadInfoRepository; }

    private:
        Models::ArtworksRepository *m_ArtworksRepository;
        Models::ArtItemsModel *m_ArtItemsModel;
        Models::CombinedArtworksModel *m_CombinedArtworksModel;
        Models::IptcProvider *m_IptcProvider;
        Models::ArtworkUploader *m_ArtworkUploader;
        Models::UploadInfoRepository *m_UploadInfoRepository;
        Models::WarningsManager *m_WarningsManager;
        Encryption::SecretsManager *m_SecretsManager;
        UndoRedo::UndoRedoManager *m_UndoRedoManager;
        Models::ZipArchiver *m_ZipArchiver;
    };
}

#endif // COMMANDMANAGER_H
