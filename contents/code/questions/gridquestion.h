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

#ifndef GRIDQUESTION_H
#define GRIDQUESTION_H

#include "closedquestion.h"

class QString;
class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

class GridQuestionPrivate;

/**
 * Grid question: closed question.
 * Each option is represented by a radiobutton.
 * Allows multiples variables, in order to have the same options
 * repeated over multiple lines.
 */
class GridQuestion : public ClosedQuestion
{
public:
    /**
     * Minimal constructor.
     */
    GridQuestion();

    /**
     * Full constructor.
     * @param val the question's value
     * @param desc the question's description (optional)
     * @param options the question's options
     * @param required indicates whether user has to answer to this or not (optional)
     */
    GridQuestion(const QString& val,
                 const boost::optional<QString>& desc,
                 const QStringList& options,
                 const QStringList& items,
                 const boost::optional<bool>& required);

    /**
     * Destructor.
     */
    virtual ~GridQuestion();

    /**
     * Equality operator
     * @param other the other question to be compared with
     * @return @c true if the two questions are equal, @c false otherwise
     */
    bool operator==(const GridQuestion& other) const;

    /**
     * Returns a string representing this question.
     * @return the string output
     */
    virtual QString toString() const;

    /**
     * Returns all user's answers.
     * @return user's answers
     * @exception if the question has not been answerred correctly
     */
    virtual QStringList getAnswers() const throw(QString);

    /**
     * Generates the UI of this question.
     * @param parent the parent object
     */
    virtual void setupUi(QGraphicsWidget* parent) const;

    /** Question type's name */
    static const char* name;

protected:
    GridQuestionPrivate* const d_ptr;
};

#endif
