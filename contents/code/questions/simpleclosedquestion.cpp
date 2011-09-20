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

#include "simpleclosedquestion.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>

#include <boost/optional.hpp>

#include "simpleclosedquestion_p.h"
#include "closedquestion_p.h"

SimpleClosedQuestion::SimpleClosedQuestion()
    : d_ptr(new SimpleClosedQuestionPrivate)
{
}

SimpleClosedQuestion::SimpleClosedQuestion(const QString& val,
        const boost::optional<QString>& desc,
        const QStringList& options,
        const boost::optional<int>& minAnswers,
        const boost::optional<int>& maxAnswers,
        const boost::optional<bool>& required)
    : ClosedQuestion(val, desc, required, minAnswers, maxAnswers),
      d_ptr(new SimpleClosedQuestionPrivate)
{
    d_ptr->m_options = options;
}

SimpleClosedQuestion::~SimpleClosedQuestion()
{
    delete d_ptr;
}

bool SimpleClosedQuestion::operator==(const SimpleClosedQuestion& other) const
{
    bool base_eq = ClosedQuestion::operator==(other);
    return base_eq && d_ptr->m_options == other.d_ptr->m_options;
}

void SimpleClosedQuestion::checkNumberAnswers(const QStringList& answers) const throw(QString)
{
    int nbAnswers = answers.count();
    if(ClosedQuestion::d_ptr->m_minAnswers && nbAnswers < ClosedQuestion::d_ptr->m_minAnswers.get()) {
        throw QString("Min answers: %1").append(ClosedQuestion::d_ptr->m_minAnswers.get());
    }
    if(ClosedQuestion::d_ptr->m_maxAnswers && nbAnswers > ClosedQuestion::d_ptr->m_maxAnswers.get()) {
        throw QString("Max answers: %1").append(ClosedQuestion::d_ptr->m_minAnswers.get());
    }
}

QString SimpleClosedQuestion::toString() const
{
    return QString();
}
