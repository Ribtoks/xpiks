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

#ifndef GLOBALIMAGEPROVIDER_H
#define GLOBALIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QHash>

namespace Helpers
{
    class GlobalImageProvider : public QObject, public QQuickImageProvider
    {
        Q_OBJECT
    public:
        GlobalImageProvider(ImageType type, Flags flags = 0) : QQuickImageProvider(type, flags) {}
        ~GlobalImageProvider() {}

        QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize);
        QPixmap requestPixmap(const QString &id, QSize *size, const QSize& requestedSize);

    public:
        bool tryGetOriginalSize(const QString &filePath, QSize &size) const {
            bool result = false;
            if (m_OriginalSizes.contains(filePath)) {
                size = m_OriginalSizes[filePath];
                result = true;
            }

            return result;
        }

    private:
        QHash<QString, QSize> m_OriginalSizes;
    };
}
#endif // GLOBALIMAGEPROVIDER_H
