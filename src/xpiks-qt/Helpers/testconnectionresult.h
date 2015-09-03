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

#ifndef TESTCONNECTIONRESULT
#define TESTCONNECTIONRESULT

#include <QString>

namespace Helpers {
    class TestConnectionResult {
    public:
        TestConnectionResult ():
            m_Result(false)
        {}

        TestConnectionResult (bool result, const QString &url) :
            m_Url(url),
            m_Result(result)
        {}

        TestConnectionResult (const TestConnectionResult &copy) :
            m_Url(copy.m_Url),
            m_Result(copy.m_Result)
        {}

    public:
        bool getResult() const { return m_Result; }
        QString getUrl() const { return m_Url; }

    private:
        QString m_Url;
        bool m_Result;
    };
}

#endif // TESTCONNECTIONRESULT

