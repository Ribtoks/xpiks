/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2015 Taras Kushnir <kushnirTV@gmail.com>
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

#include "artworkuploader.h"
#include <QtConcurrent>
#include <QDebug>
#include "uploadinforepository.h"
#include "../Helpers/curlwrapper.h"
#include "../Helpers/uploadcoordinator.h"

namespace Models {
    ArtworkUploader::ArtworkUploader() :
        ArtworksProcessor(),
        m_IncludeEPS(false),
        m_Percent(0)
    {
        QObject::connect(&m_UploadCoordinator, SIGNAL(uploadStarted()), this, SLOT(onUploadStarted()));
        QObject::connect(&m_UploadCoordinator, SIGNAL(uploadFinished(bool)), this, SLOT(allFinished(bool)));
        QObject::connect(&m_UploadCoordinator, SIGNAL(itemFinished(bool)), this, SLOT(artworkUploaded(bool)));
        QObject::connect(&m_UploadCoordinator, SIGNAL(percentChanged(double)), this, SLOT(uploaderPercentChanged(double)));

        m_TestingCredentialWatcher = new QFutureWatcher<Helpers::TestConnectionResult>(this);
        connect(m_TestingCredentialWatcher, SIGNAL(finished()), SLOT(credentialsTestingFinished()));
    }

    void ArtworkUploader::onUploadStarted()
    {
        beginProcessing();
        m_Percent = 0;
        updateProgress();
    }

    void ArtworkUploader::artworkUploaded(bool status)
    {
        artworkUploadedHandler(status);
    }

    void ArtworkUploader::allFinished(bool status)
    {
        Q_UNUSED(status);
        endProcessing();
        m_Percent = 100;
        updateProgress();
        delete m_ActiveUploads;
    }

    void ArtworkUploader::credentialsTestingFinished()
    {
        Helpers::TestConnectionResult result = m_TestingCredentialWatcher->result();
        emit credentialsChecked(result.getResult(), result.getUrl());
    }

    void ArtworkUploader::uploaderPercentChanged(double percent)
    {
        m_Percent = (int)(percent);
        percentChanged();
    }

    void ArtworkUploader::artworkUploadedHandler(bool success)
    {
        if (!success) {
            setIsError(true);
        }
    }

    void ArtworkUploader::checkCredentials(const QString &host, const QString &username, const QString &password) const
    {
        m_TestingCredentialWatcher->setFuture(QtConcurrent::run(isConnectionValid, host, username, password));
    }

    void ArtworkUploader::doUploadArtworks(const QList<ArtworkMetadata *> &artworkList)
    {
        int artworksCount = artworkList.length();
        if (artworksCount == 0) {
            return;
        }

        const UploadInfoRepository *uploadInfoRepository = m_CommandManager->getUploadInfoRepository();
        const QList<Models::UploadInfo *> &infos = uploadInfoRepository->getUploadInfos();
        const Encryption::SecretsManager *secretsManager = m_CommandManager->getSecretsManager();

        m_UploadCoordinator.uploadArtworks(artworkList, infos, m_IncludeEPS, secretsManager);
    }

    QStringList *ArtworkUploader::getAllFilepathes() const
    {
        QStringList *filesList = new QStringList();
        const QList<ArtworkMetadata*> &artworksList = this->getArtworkList();

        foreach(ArtworkMetadata *metadata, artworksList) {
            QString filepath = metadata->getFilepath();
            filesList->append(filepath);

            if (m_IncludeEPS) {
                QString epsFilepath = filepath.replace(QRegExp("(.*)[.]jpg", Qt::CaseInsensitive), "\\1.eps");
                if (QFileInfo(epsFilepath).exists()) {
                    filesList->append(epsFilepath);
                }
            }
        }

        return filesList;
    }

    void ArtworkUploader::cancelProcessing()
    {
        m_UploadCoordinator.cancelUpload();
    }
}
