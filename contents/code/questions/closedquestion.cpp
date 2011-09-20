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

#include "closedquestion.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <boost/optional.hpp>

#include "closedquestion_p.h"

ClosedQuestion::ClosedQuestion()
    : d_ptr(new ClosedQuestionPrivate)
{
}

ClosedQuestion::ClosedQuestion(const QString& val,
                               const boost::optional<QString>& desc,
                               const boost::optional<bool>& required,
                               const boost::optional<int>& min,
                               const boost::optional<int>& max)
    : Question(val, desc, required),
      d_ptr(new ClosedQuestionPrivate)
{
    d_ptr->m_minAnswers = min;
    d_ptr->m_maxAnswers = max;
}

ClosedQuestion::~ClosedQuestion()
{
    delete d_ptr;
}

bool ClosedQuestion::operator==(const ClosedQuestion& other) const
{
    bool base_eq = Question::operator==(other);
    bool eq = d_ptr->m_maxAnswers == other.d_ptr->m_maxAnswers &&
              d_ptr->m_minAnswers == other.d_ptr->m_minAnswers;
    return base_eq && eq;
}

QString ClosedQuestion::toString() const
{
    QString str = Question::toString();
    if(d_ptr->m_minAnswers) {
        str += QString("\n\t\tMin Answers: %1").arg(d_ptr->m_minAnswers.get());
    }
    if(d_ptr->m_maxAnswers) {
        str += QString("\n\t\tMax Answers: %1").arg(d_ptr->m_maxAnswers.get());
    }
    return str;
}
