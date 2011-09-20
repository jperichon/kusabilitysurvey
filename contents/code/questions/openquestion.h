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

#ifndef OPENQUESTION_H
#define OPENQUESTION_H

#include "question.h"

class QString;
class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

/**
 * Open Question: requires the user to type its answer.
 */
class OpenQuestion : public Question
{
public:
    /**
     * Minimal constructor.
     */
    OpenQuestion();

    /**
     * Full constructor.
     * @param val the question's value
     * @param desc the question's description (optional)
     * @param maxLength the max length of the answer (optional)
     * @param required indicates whether user has to answer to this or not (optional)
     */
    OpenQuestion(const QString& val,
                 const boost::optional<QString>& desc,
                 boost::optional<int> maxLength,
                 boost::optional<bool> required);

    /**
     * Equality operator.
     * @param other the other question to be compared with
     * @return @c true if the two answers are equal, @c false otherwise
     */
    bool operator==(const OpenQuestion& other) const;

    /**
     * Generates the UI of this question.
     * @param parent the parent object
     */
    virtual void setupUi(QGraphicsWidget* parent) const;

    /**
     * Returns all user's answers.
     * @return user's answers
     * @exception if the question has not been answerred correctly
     */
    virtual QStringList getAnswers() const throw(QString);

    /**
     * Returns a string representing this question.
     * @return the string output
     */
    virtual QString toString() const;

    /** Question type's name */
    static const char* name;

private:
    class Private;
    Private* const d_ptr;
};

#endif
