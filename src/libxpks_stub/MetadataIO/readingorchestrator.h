#ifndef READINGORCHESTRATOR_H
#define READINGORCHESTRATOR_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include <QHash>
#include <MetadataIO/artworkssnapshot.h>

namespace Models {
    class ArtworkMetadata;
    class SettingsModel;
}

namespace MetadataIO {
    class MetadataReadingHub;
}

namespace libxpks {
    namespace io {
        class ReadingOrchestrator
        {
        public:
            explicit ReadingOrchestrator(const MetadataIO::ArtworksSnapshot &artworksToRead,
                                         MetadataIO::MetadataReadingHub *readingHub,
                                         Models::SettingsModel *settingsModel);
            virtual ~ReadingOrchestrator();

        public:
            void startReading();

        private:
            const MetadataIO::ArtworksSnapshot &m_ItemsToReadSnapshot;
            MetadataIO::MetadataReadingHub *m_ReadingHub;
            Models::SettingsModel *m_SettingsModel;
        };
    }
}

#endif // READINGORCHESTRATOR_H
