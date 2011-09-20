/*
 * Copyright 2011 Jonathan Perichon <jonathan.perichon@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef USABILITYSURVEYCONFIG_H
#define USABILITYSURVEYCONFIG_H

#include <QtCore/QObject>

class QString;

class UsabilitySurveyConfig : public QObject
{
    Q_OBJECT

public:
    UsabilitySurveyConfig();

public Q_SLOTS:
    void surveyCreated(const QString&);

private Q_SLOTS:
    void updateEntries() const;

private:
    class Private;
    Private * const d_ptr;

    void init();
    bool isEnabled(const QString&) const;
};

#endif
