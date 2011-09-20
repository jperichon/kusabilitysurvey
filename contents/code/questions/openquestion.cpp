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

#include "openquestion.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <Plasma/TextEdit>

#include <QtGui/QGraphicsWidget>

#include <boost/optional.hpp>

class OpenQuestion::Private
{
public:
    /** Answer field */
    Plasma::TextEdit* m_answer;
    /** Max length of the answer */
    boost::optional<int> m_maxLength;
};

OpenQuestion::OpenQuestion()
    : d_ptr(new Private)
{
}

OpenQuestion::OpenQuestion(const QString& val,
                           const boost::optional<QString>& desc,
                           boost::optional<int> maxLength,
                           boost::optional<bool> required)
    : Question(val, desc, required),
      d_ptr(new Private)
{
    d_ptr->m_maxLength = maxLength;
}


bool OpenQuestion::operator==(const OpenQuestion& other) const
{
    return Question::operator==(other) && d_ptr->m_maxLength == other.d_ptr->m_maxLength;
}

QString OpenQuestion::toString() const
{
    QString str = Question::toString();
    if(d_ptr->m_maxLength) {
        str += QString("\n\t\tMax length: %1").arg(d_ptr->m_maxLength.get());
    }
    return str;
}

void OpenQuestion::setupUi(QGraphicsWidget* parent) const
{
    d_ptr->m_answer = new Plasma::TextEdit(parent);
}

QStringList OpenQuestion::getAnswers() const throw(QString)
{
    QString answer = d_ptr->m_answer->text();
    if(d_ptr->m_maxLength && d_ptr->m_maxLength.get() > answer.length()) {
        throw QString("Max length is: %1").arg(d_ptr->m_maxLength.get());
    }
    return QStringList() << answer;
}

const char* OpenQuestion::name = "Text";
