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

#ifndef SCALEQUESTION_H
#define SCALEQUESTION_H

#include "radiobuttonquestion.h"

class QString;
class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

class ScaleQuestion : public RadioButtonQuestion
{
public:
    ScaleQuestion();

    ScaleQuestion(const QString&,
                  const boost::optional<QString>&,
                  const QStringList&,
                  const QString&,
                  const QString&,
                  const boost::optional<bool>&);

    virtual ~ScaleQuestion();

    virtual void setupUi(QGraphicsWidget*) const;
    bool operator==(const ScaleQuestion&) const;
    virtual QString toString() const;

    static const char* name;

private:
    class Private;
    Private* const d_ptr;
};

#endif
