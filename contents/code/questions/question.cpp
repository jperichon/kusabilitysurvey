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

#include "question.h"

#include <QtCore/QString>

#include <QtGui/QGraphicsWidget>

#include <Plasma/Label>

#include <boost/optional.hpp>

class Question::Private
{
public:
    /** the question's value */
    QString m_value;

    /** the question's description */
    boost::optional<QString> m_description;

    /** indicates whether the question is required or not */
    boost::optional<bool> m_required;
};

Question::Question()
    : d_ptr(new Private)
{
}

Question::Question(const QString& val,
                   const boost::optional<QString>& desc,
                   const boost::optional<bool>& required)
    : d_ptr(new Private)
{
    d_ptr->m_value = val;
    d_ptr->m_description = desc;
    d_ptr->m_required = required;
}

Question::~Question()
{
    delete d_ptr;
}

bool Question::operator==(const Question& q) const
{
    if(this == &q || this->d_ptr == q.d_ptr) return true;
    return  d_ptr->m_value == q.d_ptr->m_value &&
            d_ptr->m_description == q.d_ptr->m_description &&
            d_ptr->m_required == q.d_ptr->m_required;
}

void Question::setupUi(QGraphicsWidget *q) const
{
    Plasma::Label title(q);
    title.setText(d_ptr->m_value);
    if(d_ptr->m_description) {
        Plasma::Label desc(q);
        desc.setText(*d_ptr->m_description);
    }
}

QString Question::toString() const
{
    QString str;
    str += QString("\n\t\tValue: %1").arg(d_ptr->m_value);
    if(d_ptr->m_description) {
        str += QString("\n\t\tDescription: %1").arg(d_ptr->m_description.get());
    }
    str += QString("\n\t\tIs required? %1").arg(d_ptr->m_required && d_ptr->m_required.get() ? "true" : "false");
    return str;
}
