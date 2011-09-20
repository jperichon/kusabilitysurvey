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

#include "scalequestion.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <Plasma/CheckBox>
#include <Plasma/Label>

#include <boost/optional.hpp>

class ScaleQuestion::Private
{
public:
    QString m_min;
    QString m_max;
};

ScaleQuestion::ScaleQuestion()
    : d_ptr(new Private)
{
}

ScaleQuestion::ScaleQuestion(const QString& val,
                             const boost::optional<QString>& desc,
                             const QStringList& options,
                             const QString& minValue,
                             const QString& maxValue,
                             const boost::optional<bool>& required)
    : RadioButtonQuestion(val, desc, options, required),
      d_ptr(new Private)
{
    d_ptr->m_min = minValue;
    d_ptr->m_max = maxValue;
}

ScaleQuestion::~ScaleQuestion()
{
    delete d_ptr;
}

bool ScaleQuestion::operator==(const ScaleQuestion& other) const
{
    bool base_eq = RadioButtonQuestion::operator==(other);
    bool minmax = d_ptr->m_max == other.d_ptr->m_max && d_ptr->m_min == other.d_ptr->m_min;
    return base_eq && minmax;
}

void ScaleQuestion::setupUi(QGraphicsWidget* parent) const
{
    Plasma::Label min(parent);
    min.setText(d_ptr->m_min);
    RadioButtonQuestion::setupUi(parent);
    Plasma::Label max(parent);
    max.setText(d_ptr->m_max);
}

QString ScaleQuestion::toString() const
{
    QString str = RadioButtonQuestion::toString();
    str += QString("\n\t\tMin value: %1").arg(d_ptr->m_min);
    str += QString("\n\t\tMax value: %1").arg(d_ptr->m_max);
    return str;
}

const char* ScaleQuestion::name = "Scale";
