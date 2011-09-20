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

#ifndef SIMPLECLOSEDQUESTION_H
#define SIMPLECLOSEDQUESTION_H

#include "closedquestion.h"

class QString;
class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

class SimpleClosedQuestionPrivate;

class SimpleClosedQuestion : public ClosedQuestion
{
public:
    SimpleClosedQuestion();
    SimpleClosedQuestion(const QString&,
                         const boost::optional<QString>&,
                         const QStringList&,
                         const boost::optional<int>&,
                         const boost::optional<int>&,
                         const boost::optional<bool>&);

    virtual ~SimpleClosedQuestion();
    bool operator==(const SimpleClosedQuestion&) const;

    virtual void setupUi(QGraphicsWidget*) const = 0;
    virtual QStringList getAnswers() const throw(QString) = 0;
    virtual QString toString() const;

protected:
    void checkNumberAnswers(const QStringList& answers) const throw(QString);

    SimpleClosedQuestionPrivate * const d_ptr;
};

#endif
